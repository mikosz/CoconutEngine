#ifndef COCONUTENGINE_GRAPHICS_TERRAIN_HEIGHTMAP_HPP_
#define COCONUTENGINE_GRAPHICS_TERRAIN_HEIGHTMAP_HPP_

#include "matrix.hpp"
#include "vector.hpp"

namespace coconutengine {

class Bitmap;

namespace graphics {
namespace terrain {

class HeightMap : public Matrix<Vec3D> {
public:

    /**
     * Loads heightmap from a bitmap object, scaling the height values by the given factor.
     * heightMap[0][0] is the top left pixel, heightMap[height - 1][width - 1] is the bottom right corner.
     */
    HeightMap(const Bitmap& bitmap, float scale, float heightScale);

    float elevation(const Vec2D& position) const {
        return (*this)(height() - 1 - (position.y() / scale_), position.x() / scale_).z();
    }

private:

    float scale_;

    float heightScale_;

};

} // namespace terrain
} // namespace graphics
} // namespace coconutengine

#endif /* COCONUTENGINE_GRAPHICS_TERRAIN_HEIGHTMAP_HPP_ */
