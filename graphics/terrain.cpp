/*
 * heightmap.cpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#include "terrain.hpp"
#include "terrainpatch.hpp"
#include "bitmap.hpp"
#include "log.hpp"

#include <stdexcept>

using namespace coconutengine;

namespace {

inline size_t index(const size_t row, const size_t column, const size_t patchSize) {
    return row * patchSize + column;
}

void setupIndexArrays(size_t minLod, std::vector<std::vector<GLuint> >& indexArrays, const size_t patchSize) {
    indexArrays.resize(minLod + 1);
    for (size_t lod = 0; lod <= minLod; ++lod) {
        size_t step = 1 << lod;
        std::vector<GLuint>& indexArray = indexArrays[lod];
//        indexArray.reserve((patchSize - 1) * (4 * (patchSize - 1) + 2));
        for (size_t row = 0; row + step < patchSize; row += step) {
            for (size_t column = 0; column + step < patchSize; column += step) {
                indexArray.push_back(index(row, column, patchSize));
                indexArray.push_back(index(row + step, column, patchSize));
                indexArray.push_back(index(row, column + step, patchSize));
                indexArray.push_back(index(row + step, column + step, patchSize));
            }
            if (row + (2 * step) < patchSize) {
                indexArray.push_back(indexArray.back());
                indexArray.push_back(index(row + step, 0, patchSize));
            }
        }
    }
}

}  // anonymous namespace

Terrain::Terrain(const Settings<std::string>& settings, const std::string& prefix) :
    heightMap_(settings, prefix),
    texture_(Bitmap("grass.bmp"), Texture::TEXTURE_2D, Texture::LINEAR, Texture::MIPMAP_LINEAR),
    lodStep_(getSetting<float> (settings, prefix + ".lod_step")) {
    const size_t patchSize = getSetting<unsigned int> (settings, prefix + ".patch_size"),
            heightMapHeight = heightMap_.data().height(),
            heightMapWidth = heightMap_.data().width();

    if ((heightMapHeight - 1) % (patchSize - 1) || (heightMapWidth - 1) % (patchSize - 1)) {
        throw std::runtime_error("Height map dimentions are not divisible by patchSize");
    }

    for (size_t row = 0; row < heightMapHeight - 1; row += patchSize - 1) {
        for (size_t col = 0; col < heightMapWidth - 1; col += patchSize - 1) {
            boost::shared_ptr<TerrainPatch> current(TerrainPatch::create(*this));
            patches_.push_back(current);
            std::pair<HeightMap::Container::Iterator, HeightMap::Container::Iterator> rangeIt =
                    heightMap_.data().range(row, col, row + patchSize, col + patchSize);
            for (; rangeIt.first != rangeIt.second; ++rangeIt.first) {
                TerrainPatch::Vertex vertex;
                vertex.normal = rangeIt.first->normal;
                vertex.position = rangeIt.first->vertex;
                current->addVertex(vertex);
            }
        }
    }

    textureCoordArray_.reserve(patchSize * patchSize);
    for (size_t row = 0; row < patchSize; ++row) {
        for (size_t column = 0; column < patchSize; ++column) {
            textureCoordArray_.push_back(Vec2D(static_cast<float> (column) / (patchSize - 1),
                    static_cast<float> (row) / (patchSize - 1)));
        }
    }

    setupIndexArrays(getSetting<unsigned int> (settings, prefix + ".max_lod"), indexArrays_, patchSize);
}
