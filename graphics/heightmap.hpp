/*
 * heightmap.hpp
 *
 *  Created on: 2010-09-06
 *      Author: mikosz
 */

#ifndef HEIGHTMAP_HPP_
#define HEIGHTMAP_HPP_

#include "matrix.hpp"
#include "vector.hpp"

namespace coconutengine {

class Bitmap;

struct HeightMapNode {

    Vec3D vertex;

    Vec3D normal;

};

class HeightMap {
public:

    typedef Matrix<HeightMapNode> Container;

    HeightMap(const Settings<std::string>& settings, const std::string& prefix);

    Container& data() {
        return heightMap_;
    }

private:

    void setupHeightMap(const Settings<std::string>& settings, const std::string& prefix);

    void setupNormals(size_t scale);

    /**
     * heightMap_[0][0] is the top left corner of the map
     * heightMap_[height - 1][0] is at the (0, 0) point
     */
    Container heightMap_;

    size_t height_;

    size_t width_;

};

} // namespace coconutengine

#endif /* HEIGHTMAP_HPP_ */
