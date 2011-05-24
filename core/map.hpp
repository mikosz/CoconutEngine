/*
 * map.hpp
 *
 *  Created on: Nov 5, 2008
 *      Author: mikosz
 */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include <terrain/terrain.hpp>
#include <boost/scoped_ptr.hpp>

namespace coconutengine
{

template <class> class Settings;
class Camera;

class Map
{
public:

    Map(const Settings<std::string>& settings, const std::string& prefix);

    const graphics::terrain::Terrain& terrain() const {
        return terrain_;
    }

private:

    graphics::terrain::Terrain terrain_;

};

}

#endif /* MAP_HPP_ */
