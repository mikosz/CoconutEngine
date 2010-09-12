/*
 * map.hpp
 *
 *  Created on: Nov 5, 2008
 *      Author: mikosz
 */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include <terrain.hpp>
#include <boost/scoped_ptr.hpp>

namespace CoconutEngine
{

template <class> class Settings;
class Camera;

class Map
{
public:

    Map(const Settings<std::string>& settings, const std::string& prefix);

private:

};

}

#endif /* MAP_HPP_ */
