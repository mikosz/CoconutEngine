/*
 * terrain.hpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#ifndef TERRAIN_HPP_
#define TERRAIN_HPP_

#include <string>

#include <GL/gl.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "terrainpatch.hpp"
#include "vector.hpp"
#include "texture.hpp"
#include "heightmap.hpp"

namespace coconutengine {

template <class > class Settings;

class Terrain {
public:

    Terrain(const Settings<std::string>& settings, const std::string& prefix);

    const std::vector<GLuint>& indexArray(size_t lod) const {
        return lod < indexArrays_.size() ? indexArrays_[lod] : indexArrays_.back();
    }

    const std::vector<Vec2D>& textureCoordArray() const {
        return textureCoordArray_;
    }

    const Texture& texture() const {
        return texture_;
    }

    size_t lod(float distance) const {
        return distance / lodStep_;
    }

    const HeightMap& heightMap() const {
        return heightMap_;
    }

private:

    HeightMap heightMap_;

    Texture texture_;

    std::vector<std::vector<GLuint> > indexArrays_;

    std::vector<Vec2D> textureCoordArray_;

    std::vector<boost::shared_ptr<TerrainPatch> > patches_;

    float lodStep_;

};

} // namespace coconutengine

#endif /* TERRAIN_HPP_ */
