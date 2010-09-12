/*
 * light.cpp
 *
 *  Created on: Oct 13, 2008
 *      Author: mikosz
 */

#include <light.hpp>

#include <GL/gl.h>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <settings.hpp>

using namespace CoconutEngine;

Light_::LightRegistry* Light_::LightRegistry::instance_ = 0;

Light_::LightRegistry& Light_::LightRegistry::instance() {
    if (!instance_) {
        instance_ = new Light_::LightRegistry();
    }
    return *instance_;
}

Light_::LightRegistry::LightRegistry() :
    usage_(8, false) {
}

char Light_::LightRegistry::allocate() {
    for (size_t i = 0; i < usage_.size(); ++i) {
        if (!usage_[i]) {
            usage_[i] = true;
            return i;
        }
    }
    // TODO: throw exception here
    throw "";
}

void Light_::LightRegistry::free(char id) {
    assert(usage_[id]);
    usage_[id] = false;
}

Light::Light(const Settings<std::string>& settings_, const std::string& prefix) :
    positional_(getSetting<bool> (settings_, prefix + ".positional")), ambientColour_(settings_, prefix + ".ambient"),
            diffuseColour_(settings_, prefix + ".diffuse"), specularColour_(settings_, prefix + ".specular"),
            position_(settings_, prefix + ".position"), on_(false) {
}

void Light::on() {
    if (!on_) {
        id_ = Light_::LightRegistry::instance().allocate();
        unsigned int light = lightId();

        glEnable(light);
        GLfloat lightDir[] = { position_.x(), position_.y(), position_.z(), positional_ };
        glLightfv(light, GL_POSITION, lightDir);

        glLightfv(light, GL_AMBIENT, ambientColour_.toRGBA());
        glLightfv(light, GL_DIFFUSE, diffuseColour_.toRGBA());
        glLightfv(light, GL_SPECULAR, specularColour_.toRGBA());
    }
}

void Light::off() {
    if (on_) {
        Light_::LightRegistry::instance().free(id_);
        glDisable(lightId());
    }
}

unsigned int Light::lightId() {
    switch (id_) {
    case 0:
        return GL_LIGHT0;
    case 1:
        return GL_LIGHT1;
    case 2:
        return GL_LIGHT2;
    case 3:
        return GL_LIGHT3;
    case 4:
        return GL_LIGHT4;
    case 5:
        return GL_LIGHT5;
    case 6:
        return GL_LIGHT6;
    case 7:
        return GL_LIGHT7;
    default:
        throw std::logic_error("Bad light id");
    }
}
