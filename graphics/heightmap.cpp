/*
 * heightmap.cpp
 *
 *  Created on: 2010-09-12
 *      Author: mikosz
 */

#include "heightmap.hpp"

#include <boost/filesystem.hpp>

#include "utility.hpp"
#include "bitmap.hpp"
#include "log.hpp"

using namespace coconutengine;

namespace {

void modifyNormal(Vec3D& normal, const Vec3D& middle, const Vec3D* v1, const Vec3D* v2) {
    if (v1 && v2) {
        Vec3D diff1 = *v1 - middle, diff2 = *v2 - middle;
        normal += diff1.crossProduct(diff2).normalise();
    }
}

} // anonymous namespace

HeightMap::HeightMap(const Settings<std::string>& settings, const std::string& prefix) :
        scale_(getSetting<float> (settings, prefix + ".scale")),
        heightScale_(getSetting<float> (settings, prefix + ".height_scale")) {
    setupHeightMap(settings, prefix);
}

void HeightMap::setupHeightMap(const Settings<std::string>& settings, const std::string& prefix) {
    SET_LOG_CONTEXT("HeightMap::setupHeightMap");

    LOG_INFO    << "Setting up the height map" << LOG_END;

    Bitmap bitmap(getSetting<std::string> (settings, prefix + ".heightmap"));
    height_ = bitmap.height();
    width_ = bitmap.width();

    heightMap_.resize(height_, width_);

    for (size_t row = 0; row < height_; ++row) {
        for (size_t column = 0; column < width_; ++column) {
            const size_t x = column;
            const size_t y = height_ - row - 1;
            const size_t z = bitmap.pixels()[y * width_ + x];
            heightMap_(row, column).vertex = Vec3D(scale_ * x, scale_ * y, heightScale_ * z / 255.0f);
            LOG_TRACE   << "vertex: " << heightMap_(row, column).vertex << LOG_END;
        }
    }

    setupNormals(scale_);

    LOG_INFO    << "Complete" << LOG_END;
}

void HeightMap::setupNormals(const size_t scale) {
    Container::Iterator end = heightMap_.end();
    for (Container::Iterator it = heightMap_.begin(); it != end; ++it) {
        Vec3D normal(0, 0, 0);
        const Vec3D& current = it->vertex;


        const Vec3D *left = 0, *topLeft = 0, *top = 0, *topRight = 0, *right = 0, *bottomRight = 0, *bottom = 0,
                *bottomLeft = 0;
        if (it.column() > 0) {
            left = &((it + std::make_pair(0, -1))->vertex);
            if (it.row() > 0) {
                topLeft = &((it + std::make_pair(-1, -1))->vertex);
            }
            if (it.row() < heightMap_.height() - 1) {
                bottomLeft = &((it + std::make_pair(1, -1))->vertex);
            }
        }
        if (it.row() > 0) {
            top = &((it + std::make_pair(-1, 0))->vertex);
        }
        if (it.column() < heightMap_.width() - 1) {
            right = &((it + std::make_pair(0, 1))->vertex);
            if (it.row() > 0) {
                topRight = &((it + std::make_pair(-1, 1))->vertex);
            }
            if (it.row() < heightMap_.height() - 1) {
                bottomRight = &((it + std::make_pair(1, 1))->vertex);
            }
        }
        if (it.row() < heightMap_.height() - 1) {
            bottom = &((it + std::make_pair(1, 0))->vertex);
        }

        modifyNormal(normal, current, left, bottomLeft);
        modifyNormal(normal, current, bottomLeft, bottom);
        modifyNormal(normal, current, bottom, bottomRight);
        modifyNormal(normal, current, bottomRight, right);
        modifyNormal(normal, current, right, topRight);
        modifyNormal(normal, current, topRight, top);
        modifyNormal(normal, current, top, topLeft);
        modifyNormal(normal, current, topLeft, left);

        it->normal = normal.normalise();
    }
}

float HeightMap::elevation(const Vec2D& position) const {
    size_t row = height_ - 1 - (position.y() / scale_),
            column = position.x() / scale_;

    row = clamp(row, 0, height_ - 1);
    column = clamp(column, 0, width_ - 1);

    return heightMap_(row, column).vertex.z();
}
