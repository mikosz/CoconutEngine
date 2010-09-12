/*
 * heightmap.hpp
 *
 *  Created on: 2010-09-06
 *      Author: mikosz
 */

#ifndef HEIGHTMAP_HPP_
#define HEIGHTMAP_HPP_

#include "vector.hpp"

namespace CoconutEngine {

class Bitmap;

struct HeightMapNode {

    Vec3D vertex;

    Vec3D normal;

};

class HeightMap {
public:

    typedef Matrix<HeightMapNode> Container;

    HeightMap(const Settings<std::string>& settings, const std::string& prefix);

    const Container& heightMap() const {
        return heightMap_;
    }

private:

    void setupHeightMap(const Settings<std::string>& settings, const std::string& prefix);

    float scale_;

    Container heightMap_;

};

} // namespace CoconutEngine

#endif /* HEIGHTMAP_HPP_ */
