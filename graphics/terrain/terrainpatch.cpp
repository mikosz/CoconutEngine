/*
 * terrainpatch.cpp
 *
 *  Created on: 2010-09-26
 *      Author: mikosz
 */

#include "terrainpatch.hpp"

#include <cassert>
#include <algorithm>

#include <boost/bind.hpp>

#include <GL/gl.h>

#include "camera.hpp"
#include "colour.hpp"
#include "terrain/terrain.hpp"
#include "renderpipeline.hpp"
#include "log.hpp"

using namespace coconutengine::graphics::terrain;

namespace {

void renderNormal(const TerrainPatch::Vertex& vertex) {
    glVertex3fv(vertex.position.toXYZ());
    coconutengine::Vec3D end = vertex.position + (vertex.normal * 100);
    glVertex3fv(end.toXYZ());
}

void renderNormals(const std::vector<TerrainPatch::Vertex>& vertices) {
    glBegin(GL_LINES);
    glColor3fv(coconutengine::Colour::RED.toRGBA());
    std::for_each(vertices.begin(), vertices.end(), boost::bind(renderNormal, _1));
    glEnd();
}

} // anonymous namespace

boost::shared_ptr<TerrainPatch> TerrainPatch::create(const Terrain& terrain) {
    boost::shared_ptr<TerrainPatch> result(new TerrainPatch(terrain));
    result->id_ = RenderPipeline::instance().addSceneElement(result);
    return result;
}

TerrainPatch::TerrainPatch(const Terrain& terrain) :
        coconutengine::SceneElement(terrain.drawBoundingBox()),
        terrain_(terrain) {
}

void TerrainPatch::addVertex(const Vertex& vertex) {
    boundingBox_.bottomLeft.x() = std::min(boundingBox_.bottomLeft.x(), vertex.position.x());
    boundingBox_.bottomLeft.y() = std::min(boundingBox_.bottomLeft.y(), vertex.position.y());
    boundingBox_.bottomLeft.z() = std::min(boundingBox_.bottomLeft.z(), vertex.position.z());
    boundingBox_.topRight.x() = std::max(boundingBox_.topRight.x(), vertex.position.x());
    boundingBox_.topRight.y() = std::max(boundingBox_.topRight.y(), vertex.position.y());
    boundingBox_.topRight.z() = std::max(boundingBox_.topRight.z(), vertex.position.z());

    vertices_.push_back(vertex);
}

void TerrainPatch::doRender(const Camera& camera) const {
    assert(vertices_.size());

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 1000.0f);
    glFogf(GL_FOG_END, camera.farPlane());
    glFogf(GL_FOG_DENSITY, 1.0f);
    glFogfv(GL_FOG_COLOR, Colour::WHITE.toRGBA());

    glDisable(GL_LIGHTING);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    terrain_.texture().enable();
    terrain_.texture().bind();
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices_.front().position);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &vertices_.front().normal);
    glTexCoordPointer(2, GL_FLOAT, 0, &terrain_.textureCoordArray().front());
    glColorPointer(3, GL_FLOAT, sizeof(Vertex), &vertices_.front().brightness);

    size_t level = lod(camera);
    glDrawElements(GL_TRIANGLE_STRIP, terrain_.indexArray(level).size(), GL_UNSIGNED_INT,
            &terrain_.indexArray(level).front());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glDisable(GL_FOG);

    terrain_.texture().disable();

    if (terrain_.drawNormals()) {
        renderNormals(vertices_);
    }
}

size_t TerrainPatch::lod(const Camera& camera) const {
    return terrain_.lod((camera.position() - vertices_[vertices_.size() / 2].position).length());
}
