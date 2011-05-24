#include "lightmap.hpp"

#include "bitmap.hpp"

using namespace coconutengine;
using namespace coconutengine::graphics::terrain;

namespace {

void loadLightmap(LightMap& lightMap, const Bitmap& bitmap) {
    lightMap.resize(bitmap.height(), bitmap.width());

    for (size_t row = 0; row < bitmap.height(); ++row) {
        for (size_t column = 0; column < bitmap.width(); ++column) {
            lightMap(row, column) = bitmap.pixels()[(bitmap.height() - row - 1) * bitmap.width() + column] / 255.0f;
        }
    }
}


} // anonymous namespace

LightMap::LightMap(const Bitmap& bitmap, float scale) :
    scale_(scale) {
    loadLightmap(*this, bitmap);
}
