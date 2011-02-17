/*
 * light.cpp
 *
 *  Created on: Oct 13, 2008
 *      Author: mikosz
 */

#include <light.hpp>

#include <algorithm>
#include <cassert>
#include <stdexcept>

#include <iostream>

#include "settings.hpp"

using namespace coconutengine;

namespace {

class LightRegistry : boost::noncopyable {
public:

    static LightRegistry& instance();

    char allocate();

    void free(char id);

private:

    static LightRegistry* instance_;

    LightRegistry();

    std::valarray<bool> usage_;

};

LightRegistry* LightRegistry::instance_ = 0;

LightRegistry& LightRegistry::instance() {
    if (!instance_) {
        instance_ = new LightRegistry();
    }
    return *instance_;
}

LightRegistry::LightRegistry() :
    usage_(false, 8) {
}

char LightRegistry::allocate() {
    glEnable(GL_LIGHTING);
    for (size_t i = 0; i < usage_.size(); ++i) {
        if (!usage_[i]) {
            usage_[i] = true;
            return i;
        }
    }
    throw std::runtime_error("Too many lights lit");
}

void LightRegistry::free(char id) {
    assert(usage_[id]);
    usage_[id] = false;
    if (!usage_.max()) {
        glDisable(GL_LIGHTING);
    }
}

}  // anonymous namespace

Light::Light(const Settings<std::string>& settings_, const std::string& prefix) :
    positional_(getSetting<bool> (settings_, prefix + ".positional")), ambientColour_(settings_, prefix + ".ambient"),
            diffuseColour_(settings_, prefix + ".diffuse"), specularColour_(settings_, prefix + ".specular"),
            position_(settings_, prefix + ".position"), on_(false) {
}

void Light::on() {
    if (!on_) {
        on_ = true;
        id_ = LightRegistry::instance().allocate();
        GLenum light = lightId();

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
        LightRegistry::instance().free(id_);
        glDisable(lightId());
        on_ = false;
    }
}

GLenum Light::lightId() {
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
