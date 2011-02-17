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

class Terrain;
class Camera;

class TerrainPatch : public SceneElement {
public:

    struct Vertex {

        Vec3D position;

        Vec3D normal;

    };

    static boost::shared_ptr<TerrainPatch> create(const Terrain& terrain);

    void doRender(const Camera& camera) const;

    void addVertex(const Vertex& vertex);

private:

    const Terrain& terrain_;

    std::vector<Vertex> vertices_;

    TerrainPatch(const Terrain& terrain);

    size_t lod(const Camera& camera) const;

};

} // namespace coconutengine

#endif /* TERRAINPATCH_HPP_ */
