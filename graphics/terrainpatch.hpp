/*
 * terrainpatch.hpp
 *
 *  Created on: 2010-08-23
 *      Author: mikosz
 */

#ifndef TERRAINPATCH_HPP_
#define TERRAINPATCH_HPP_

#include <vector>

#include "graphics/sceneelement.hpp"
#include "vector.hpp"

namespace CoconutEngine {

class TerrainPatch : public SceneElement {
public:

    TerrainPatch(Terrain& terrain) :
        terrain_(terrain) {
    }

    void render() const;

private:

    struct TerrainVertex {

        Vec3D position;

        Vec3D normal;

    };

    Terrain& terrain_;

    std::vector<TerrainVertex> vertices_;

};

} // namespace CoconutEngine

#endif /* TERRAINPATCH_HPP_ */
