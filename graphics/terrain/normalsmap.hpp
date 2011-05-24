#ifndef COCONUTENGINE_GRAPHICS_TERRAIN_NORMALSMAP_HPP_
#define COCONUTENGINE_GRAPHICS_TERRAIN_NORMALSMAP_HPP_

#include "heightmap.hpp"
#include "matrix.hpp"
#include "vector.hpp"

namespace coconutengine {
namespace graphics {
namespace terrain {

class NormalsMap : public Matrix<Vec3D> {
public:

    NormalsMap(const HeightMap& heightMap);

};


} // namespace terrain
} // namespace graphics
} // namespace coconutengine

#endif /* COCONUTENGINE_GRAPHICS_TERRAIN_NORMALSMAP_HPP_ */
