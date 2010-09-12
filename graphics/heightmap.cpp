/*
 * heightmap.cpp
 *
 *  Created on: 2010-09-12
 *      Author: mikosz
 */

#include "heightmap.hpp"

#include <boost/filesystem.hpp>

#include "bitmap.hpp"

using namespace CoconutEngine;

HeightMap::HeightMap(const Settings<std::string>& settings, const std::string& prefix) {
    setupHeightMap(settings, prefix);
}

void HeightMap::setupHeightMap(const Settings<std::string>& settings, const std::string& prefix) {
    Bitmap bitmap(getSetting<boost::filesystem::path> (settings, prefix + ".heightmap"));
    heightMap_.resize(bitmap.height(), bitmap.width());

    Container::Iterator it, end = heightMap_.end();
    for (it = heightMap_.begin(); it != end; ++it) {

    }
}
