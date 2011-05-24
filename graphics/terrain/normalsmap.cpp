#include "normalsmap.hpp"

#include "log.hpp"

using namespace coconutengine::graphics::terrain;

namespace {

using coconutengine::Vec3D;

void updateNormal(Vec3D& normal, const Vec3D& middle, const Vec3D* v1, const Vec3D* v2) {
    if (v1 && v2) {
        Vec3D diff1 = *v1 - middle, diff2 = *v2 - middle;
        normal += diff1.crossProduct(diff2).normalise();
    }
}

void setupNormalsMap(NormalsMap& normalsMap, const HeightMap& heightMap) {
    normalsMap.resize(heightMap.height(), heightMap.width());

    HeightMap::ConstIterator end = heightMap.end();
    for (HeightMap::ConstIterator it = heightMap.begin(); it != end; ++it) {
        const Vec3D *left = 0, *topLeft = 0, *top = 0, *topRight = 0, *right = 0, *bottomRight = 0, *bottom =
                0, *bottomLeft = 0;
        if (it.column() > 0) {
            left = &*(it + std::make_pair(0, -1));
            if (it.row() > 0) {
                topLeft = &*(it + std::make_pair(-1, -1));
            }
            if (it.row() < heightMap.height() - 1) {
                bottomLeft = &*(it + std::make_pair(1, -1));
            }
        }
        if (it.row() > 0) {
            top = &*(it + std::make_pair(-1, 0));
        }
        if (it.column() < heightMap.width() - 1) {
            right = &*(it + std::make_pair(0, 1));
            if (it.row() > 0) {
                topRight = &*(it + std::make_pair(-1, 1));
            }
            if (it.row() < heightMap.height() - 1) {
                bottomRight = &*(it + std::make_pair(1, 1));
            }
        }
        if (it.row() < heightMap.height() - 1) {
            bottom = &*(it + std::make_pair(1, 0));
        }

        Vec3D normal(0, 0, 0);
        const Vec3D& current = *it;

        updateNormal(normal, current, left, bottomLeft);
        updateNormal(normal, current, bottomLeft, bottom);
        updateNormal(normal, current, bottom, bottomRight);
        updateNormal(normal, current, bottomRight, right);
        updateNormal(normal, current, right, topRight);
        updateNormal(normal, current, topRight, top);
        updateNormal(normal, current, top, topLeft);
        updateNormal(normal, current, topLeft, left);

        normalsMap(it.row(), it.column()) = normal.normalise();
    }
}

} // anonymous namespace

NormalsMap::NormalsMap(const HeightMap& heightMap) {
    setupNormalsMap(*this, heightMap);
}
