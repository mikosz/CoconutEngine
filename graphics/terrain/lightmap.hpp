#ifndef COCONUTENGINE_GRAPHICS_TERRAIN_LIGHTMAP_HPP_
#define COCONUTENGINE_GRAPHICS_TERRAIN_LIGHTMAP_HPP_

#include "matrix.hpp"
#include "vector.hpp"

namespace coconutengine {

class Bitmap;

namespace graphics {
namespace terrain {

class LightMap : public Matrix<float> {
public:

    /**
     * Loads a lightmap from a bitmap object.
     * heightMap[0][0] is the top left pixel, heightMap[height - 1][width - 1] is the bottom right corner.
     */
    LightMap(const Bitmap& bitmap, float scale);

    float brightness(const Vec2D& position) const {
        return (*this)(height() - 1 - (position.y() / scale_), position.x() / scale_);
    }

private:

    float scale_;

};

} // namespace terrain
} // namespace graphics
} // namespace coconutengine

#endif /* COCONUTENGINE_GRAPHICS_TERRAIN_LIGHTMAP_HPP_ */
