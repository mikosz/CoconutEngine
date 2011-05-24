/*
 * terrainpatch.hpp
 *
 *  Created on: 2010-08-23
 *      Author: mikosz
 */

#ifndef TERRAINPATCH_HPP_
#define TERRAINPATCH_HPP_

#include <vector>

#include <boost/shared_ptr.hpp>

#include "sceneelement.hpp"
#include "vector.hpp"

namespace coconutengine {

class Camera;

namespace graphics {
namespace terrain {

class Terrain;

class TerrainPatch : public SceneElement {
public:

    struct Vertex {

        Vec3D position;

        Vec3D normal;

        Vec3D brightness;

    };

    static boost::shared_ptr<TerrainPatch> create(const graphics::terrain::Terrain& terrain);

    void doRender(const Camera& camera) const;

    void addVertex(const Vertex& vertex);

private:

    const graphics::terrain::Terrain& terrain_;

    std::vector<Vertex> vertices_;

    TerrainPatch(const graphics::terrain::Terrain& terrain);

    size_t lod(const Camera& camera) const;

};

} // namespace terrain
} // namespace graphics
} // namespace coconutengine

#endif /* TERRAINPATCH_HPP_ */
