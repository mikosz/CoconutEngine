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
#include "normalsmap.hpp"
#include "lightmap.hpp"

namespace coconutengine {

template <class > class Settings;

namespace graphics {
namespace terrain {


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

    bool drawNormals() const {
        return drawNormals_;
    }

    bool drawBoundingBox() const {
        return drawBoundingBox_;
    }

private:

    Texture texture_;

    std::vector<std::vector<GLuint> > indexArrays_;

    std::vector<Vec2D> textureCoordArray_;

    std::vector<boost::shared_ptr<TerrainPatch> > patches_;

    float scale_;

    float lodStep_;

    HeightMap heightMap_;

    NormalsMap normalsMap_;

    LightMap lightMap_;

    bool drawNormals_;

    bool drawBoundingBox_;

};

} // namespace terrain
} // namespace graphics
} // namespace coconutengine

#endif /* TERRAIN_HPP_ */
