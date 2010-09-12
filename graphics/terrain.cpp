/*
 * heightmap.cpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#include <terrain.hpp>

#include <settings.hpp>
#include <GL/gl.h>
#include <camera.hpp>
#include <log.hpp>
#include <frustum.hpp>
#include <limits>
#include <utility.hpp>

using namespace CoconutEngine;

namespace {

inline float heightMapToWorld(size_t heightMapCoord, float renderingStep) {
    if (renderingStep == 1.0f) {
        return heightMapCoord;
    } else {
        return heightMapCoord * renderingStep;
    }
}

}

std::auto_ptr<Terrain> Terrain::create(const Settings<std::string>& settings, const std::string& prefix) {
    Bitmap* heightMapImage = new Bitmap(getSetting<std::string> (settings, prefix + ".heightmap"));
    std::auto_ptr<Terrain> result(new Terrain(heightMapImage, settings, prefix));
    delete heightMapImage;
    return result;
}

Terrain::Terrain(const Bitmap* heightMapImage, const Settings<std::string>& settings, const std::string& prefix) :
    quadTree_(getSetting<unsigned int> (settings, prefix + ".quad_tree_depth")), heightMap_(heightMapImage->width(),
            heightMapImage->height()), waterLevel_(getSetting<float> (settings, prefix + ".water_level")),
            renderingStep_(getSetting<float> (settings, prefix + ".rendering_step")) {
    setupHeightMap(heightMapImage, getSetting<float> (settings, prefix + ".height_scaling_factor"));
    setupQuadTree(0, Rectangle<Vector3D<size_t> > (Vector3D<size_t> (0, 0, 0), Vector3D<size_t> (
            heightMapImage->width() - 1, heightMapImage->height() - 1, 0)), 0);
}

void Terrain::setupHeightMap(const Bitmap* heightMapImage, float heightScalingFactor) {
    SET_LOG_CONTEXT("Terrain::setupHeightMap");
    LOG_INFO << "Setting up the heightmap info" << LOG_END;

    for (size_t row = 0; row < heightMap_.size1(); ++row) {
        for (size_t column = 0; column < heightMap_.size2(); ++column) {
            heightMap_(row, column).height = (static_cast<float> (heightMapImage->pixels()[row
                    * heightMapImage->width() + column]) / 255.0f) * heightScalingFactor;
        }
    }
    for (size_t row = 0; row < heightMap_.size1(); ++row) {
        for (size_t column = 0; column < heightMap_.size2(); ++column) {
            Vec3D normal(0, 0, 0);

            Vec3D current = Vec3D(heightMapToWorld(column, renderingStep_), heightMapToWorld(row, renderingStep_),
                    heightMap_(row, column).height);

            Vec3D v1, v2;
            if (row > 0) {
                Vec3D bottom = Vec3D(heightMapToWorld(column, renderingStep_),
                        heightMapToWorld(row - 1, renderingStep_), heightMap_(row - 1, column).height);

                if (column > 0) {
                    Vec3D left = Vec3D(heightMapToWorld(column - 1, renderingStep_), heightMapToWorld(row,
                            renderingStep_), heightMap_(row, column - 1).height);

                    v1 = left - current;
                    v2 = bottom - current;
                    normal += v1.crossProduct(v2).normalised();
                }
                if (column < heightMap_.size2() - 1) {
                    Vec3D right = Vec3D(heightMapToWorld(column + 1, renderingStep_), heightMapToWorld(row,
                            renderingStep_), heightMap_(row, column + 1).height);
                    Vec3D bottomRight = Vec3D(heightMapToWorld(column + 1, renderingStep_), heightMapToWorld(row - 1,
                            renderingStep_), heightMap_(row - 1, column + 1).height);

                    v1 = bottom - current;
                    v2 = bottomRight - current;
                    normal += v1.crossProduct(v2).normalised();

                    v1 = bottomRight - current;
                    v2 = right - current;
                    normal += v1.crossProduct(v2).normalised();
                }
            }
            if (row < heightMap_.size1() - 1) {
                Vec3D top = Vec3D(heightMapToWorld(column, renderingStep_), heightMapToWorld(row + 1, renderingStep_),
                        heightMap_(row + 1, column).height);

                if (column > 0) {
                    Vec3D left = Vec3D(heightMapToWorld(column - 1, renderingStep_), heightMapToWorld(row,
                            renderingStep_), heightMap_(row, column - 1).height);
                    Vec3D topLeft = Vec3D(heightMapToWorld(column - 1, renderingStep_), heightMapToWorld(row + 1,
                            renderingStep_), heightMap_(row + 1, column - 1).height);

                    v1 = topLeft - current;
                    v2 = left - current;
                    normal += v1.crossProduct(v2).normalised();

                    v1 = top - current;
                    v2 = topLeft - current;
                    normal += v1.crossProduct(v2).normalised();
                }
                if (column < heightMap_.size2() - 1) {
                    Vec3D right = Vec3D(heightMapToWorld(column + 1, renderingStep_), heightMapToWorld(row,
                            renderingStep_), heightMap_(row, column + 1).height);

                    v1 = right - current;
                    v2 = top - current;
                    normal += v1.crossProduct(v2).normalised();
                }
            }

            normal.normalise();
            heightMap_(row, column).normal = normal;
        }
    }
}

Terrain::QuadTreeEntry Terrain::setupQuadTree(unsigned short level, Rectangle<Vector3D<size_t> > area, size_t node) {
    SET_LOG_CONTEXT("Terrain::setupQuadTree");
    LOG_DEBUG   << "Running for area: " << area.bottomLeft.x() << ", " << area.bottomLeft.y() << " x "
                        << area.topRight.x() << ", " << area.topRight.y() << "; level: " << level << "; node: " << node
                        << LOG_END;

    QuadTreeEntry result;
    result.area = area;
    result.boundingBox = Rectangle<Vec3D> (Vec3D(renderingStep_ * area.bottomLeft.x(), renderingStep_
            * area.bottomLeft.y(), std::numeric_limits<float>::max()), Vec3D(renderingStep_ * area.topRight.x(),
            renderingStep_ * area.topRight.y(), std::numeric_limits<float>::min()));

    if (level == quadTree_.depth()) {
        for (size_t row = area.bottomLeft.y(); row <= area.topRight.y(); ++row) {
            for (size_t column = area.bottomLeft.x(); column <= area.topRight.x(); ++column) {
                result.boundingBox.bottomLeft.z() = min(heightMap_(row, column).height,
                        result.boundingBox.bottomLeft.z());
                result.boundingBox.topRight.z() = max(heightMap_(row, column).height, result.boundingBox.topRight.z());
            }
        }
    } else {
        Vector3D<size_t> divisionPoint((area.topRight - area.bottomLeft) / 2 + area.bottomLeft);

        LOG_DEBUG   << "Dividing at: " << divisionPoint.x() << ", " << divisionPoint.y() << LOG_END;

        QuadTreeEntry childResult;
        size_t childNode = quadTree_.getLeftChild(node);

        // top left
        childResult = setupQuadTree(level + 1, Rectangle<Vector3D<size_t> > (Vector3D<size_t> (area.bottomLeft.x(),
                divisionPoint.y(), 0.0f), Vector3D<size_t> (divisionPoint.x(), area.topRight.y(), 0.0f)), childNode++);
        result.boundingBox.bottomLeft.z() = min(childResult.boundingBox.bottomLeft.z(),
                result.boundingBox.bottomLeft.z());
        result.boundingBox.topRight.z() = max(childResult.boundingBox.topRight.z(), result.boundingBox.topRight.z());

        // top right
        childResult = setupQuadTree(level + 1, Rectangle<Vector3D<size_t> > (Vector3D<size_t> (divisionPoint.x(),
                divisionPoint.y(), 0.0f), Vector3D<size_t> (area.topRight.x(), area.topRight.y(), 0.0f)), childNode++);
        result.boundingBox.bottomLeft.z() = min(childResult.boundingBox.bottomLeft.z(),
                result.boundingBox.bottomLeft.z());
        result.boundingBox.topRight.z() = max(childResult.boundingBox.topRight.z(), result.boundingBox.topRight.z());

        // bottom left
        childResult
                = setupQuadTree(level + 1, Rectangle<Vector3D<size_t> > (Vector3D<size_t> (area.bottomLeft.x(),
                        area.bottomLeft.y(), 0.0f), Vector3D<size_t> (divisionPoint.x(), divisionPoint.y(), 0.0f)),
                        childNode++);
        result.boundingBox.bottomLeft.z() = min(childResult.boundingBox.bottomLeft.z(),
                result.boundingBox.bottomLeft.z());
        result.boundingBox.topRight.z() = max(childResult.boundingBox.topRight.z(), result.boundingBox.topRight.z());

        // bottom right
        childResult = setupQuadTree(level + 1, Rectangle<Vector3D<size_t> > (Vector3D<size_t> (divisionPoint.x(),
                area.bottomLeft.y(), 0.0f), Vector3D<size_t> (area.topRight.x(), divisionPoint.y(), 0.0f)), childNode);
        result.boundingBox.bottomLeft.z() = min(childResult.boundingBox.bottomLeft.z(),
                result.boundingBox.bottomLeft.z());
        result.boundingBox.topRight.z() = max(childResult.boundingBox.topRight.z(), result.boundingBox.topRight.z());
    }

    LOG_DEBUG   << "Box containing node " << node << ": " << result.boundingBox.bottomLeft.x() << ", "
                        << result.boundingBox.bottomLeft.y() << ", " << result.boundingBox.bottomLeft.z() << "; "
                        << result.boundingBox.topRight.x() << ", " << result.boundingBox.topRight.y() << ", "
                        << result.boundingBox.topRight.z() << "; " << LOG_END;

    quadTree_.tree()[node] = result;
    return result;
}

void Terrain::render(const Camera& camera, size_t node) const {
    Frustum::Containment containment = camera.frustum().contains(quadTree_.tree()[node].boundingBox);

    if (containment != Frustum::OUT) {
        size_t leftChild = quadTree_.getLeftChild(node);
        if (containment == Frustum::INTERSECT && leftChild < quadTree_.tree().size()) {
            for (int i = 0; i < 4; ++i) {
                render(camera, leftChild + i);
            }
        } else {
            const Rectangle<Vector3D<size_t> >& area = quadTree_.tree()[node].area;
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);

            size_t size = 9 * (size_t)((area.topRight.y() - area.bottomLeft.y()) * (area.topRight.x() - area.bottomLeft.x()));
            float* vertices = new float[size];
            float* normals = new float[size];
            float* colors = new float[size];
            int xxx = 0;
            glVertexPointer(3, GL_FLOAT, 0, vertices);
            glNormalPointer(GL_FLOAT, 0, normals);
            glColorPointer(3, GL_FLOAT, 0, colors);

            std::vector<GLuint> indices;
            size_t width = area.topRight.y() - area.bottomLeft.y();

            for (size_t row = area.bottomLeft.y(); row < area.topRight.y(); ++row) {
                for (size_t column = area.bottomLeft.x(); column <= area.topRight.x(); ++column) {
                    HeightMapVertex vertex = heightMap_(row, column);

                    normals[xxx] = vertex.normal.x();
                    colors[xxx] = 1.0f;
                    vertices[xxx++] = heightMapToWorld(column, renderingStep_);

                    normals[xxx] = vertex.normal.y();
                    colors[xxx] = 1.0f;
                    vertices[xxx++] = heightMapToWorld(row, renderingStep_);

                    normals[xxx] = vertex.normal.z();
                    colors[xxx] = 1.0f;
                    vertices[xxx++] = vertex.height;

                    size_t r = row - area.bottomLeft.y();
                    size_t c = column - area.bottomLeft.x();
                    indices.push_back(r * width + c);
                    indices.push_back((r + 1) * width + c);
                    indices.push_back(r * width + c + 1);
                    indices.push_back((r + 1) * width + c);
                    indices.push_back((r + 1) * width + c + 1);
                    indices.push_back(r * width + c + 1);
                }
            }

            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices.front());

            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);

            delete[] vertices;
            delete[] normals;
            delete[] colors;
        }
    }
    //        glBegin(GL_QUADS);
    //        for (size_t row = 0; row < height_ - 1; ++row) {
    //            for (size_t column = 0; column < width_; ++column) {
    //                glColor4f(0.0f, 0.0f, 0.5f, 1.0f);
    //                glNormal3f(0.0f, 0.0f, 1.0f);
    //                glVertex3f(column, row, waterLevel_);
    //                glVertex3f(column + 1, row, waterLevel_);
    //                glVertex3f(column + 1, row + 1, waterLevel_);
    //                glVertex3f(column, row + 1, waterLevel_);
    //            }
    //        }
    //        glEnd();
}

void Terrain::render(const Camera& camera) const {
    render(camera, 0);
}
