/*
 * map.cpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#include <map.hpp>

#include <settings.hpp>
#include <camera.hpp>

using namespace coconutengine;

Map::Map(const Settings<std::string>& settings, const std::string& prefix) :
    terrain_(settings, prefix) {
}
