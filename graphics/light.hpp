/*
 * light.hpp
 *
 *  Created on: Oct 13, 2008
 *      Author: mikosz
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <GL/gl.h>

#include <colour.hpp>
#include <vector.hpp>
#include <valarray>
#include <string>
#include <boost/noncopyable.hpp>

namespace coconutengine {

template<class > class Settings;

class Light {
public:

    Light(const Settings<std::string>& settings, const std::string& prefix);

    void on();

    void off();

private:

    bool positional_;

    Colour ambientColour_;

    Colour diffuseColour_;

    Colour specularColour_;

    Vec3D position_;

    char id_;

    bool on_;

    GLenum lightId();

};

} // namespace coconutengine

#endif /* LIGHT_HPP_ */
