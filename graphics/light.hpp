/*
 * light.hpp
 *
 *  Created on: Oct 13, 2008
 *      Author: mikosz
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <colour.hpp>
#include <vector.hpp>
#include <vector>
#include <string>
#include <boost/noncopyable.hpp>

namespace CoconutEngine {

namespace Light_ {

class LightRegistry : boost::noncopyable {
public:

    char allocate();

    void free(char id);

    static LightRegistry& instance();

private:

    static LightRegistry* instance_;

    LightRegistry();

    std::vector<bool> usage_;

};

} // namespace Light_

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

    unsigned int lightId();

};

} // namespace CoconutEngine

#endif /* LIGHT_HPP_ */
