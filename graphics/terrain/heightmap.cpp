/*
 * heightmap.cpp
 *
 *  Created on: 2010-09-12
 *      Author: mikosz
 */

#include "heightmap.hpp"

#include <boost/filesystem.hpp>

#include "utility.hpp"
#include "bitmap.hpp"
#include "log.hpp"

using namespace coconutengine;
using namespace coconutengine::graphics::terrain;

namespace {

void loadHeightmap(HeightMap& heightMap, const Bitmap& bitmap, float scale, float heightScale) {
    SET_LOG_CONTEXT("loadHeightMap");

    LOG_INFO << "Setting up the height map" << LOG_END;

    heightMap.resize(bitmap.height(), bitmap.width());

    for (size_t row = 0; row < bitmap.height(); ++row) {
        for (size_t column = 0; column < bitmap.width(); ++column) {
            const size_t x = column;
            const size_t y = bitmap.height() - row - 1;
            const size_t z = bitmap.pixels()[y * bitmap.width() + x];
            heightMap(row, column) = Vec3D(x * scale, y * scale, heightScale * z / 255.0f);
        }
    }

    LOG_INFO << "Complete" << LOG_END;
}


} // anonymous namespace

HeightMap::HeightMap(const Bitmap& bitmap, float scale, float heightScale) :
    scale_(scale), heightScale_(heightScale) {
    loadHeightmap(*this, bitmap, scale, heightScale);
}
