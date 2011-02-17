/*
 * colour.cpp
 *
 *  Created on: Oct 13, 2008
 *      Author: mikosz
 */

#include <colour.hpp>

#include <settings.hpp>
#include <cstring>

using namespace coconutengine;

const Colour Colour::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const Colour Colour::BLACK(0.0f, 0.0f, 0.0f, 1.0f);

Colour::Colour(float red, float green, float blue, float alpha)
{
    set(red, green, blue, alpha);
}

Colour::Colour(float rgba[])
{
    set(rgba);
}

Colour::Colour(const Settings<std::string>& settings, const std::string& settingsPrefix)
{
    set(getSetting<float>(settings, settingsPrefix + ".red"),
        getSetting<float>(settings, settingsPrefix + ".green"),
        getSetting<float>(settings, settingsPrefix + ".blue"),
        getSetting<float>(settings, settingsPrefix + ".alpha")
        );
}

void Colour::set(float red, float green, float blue, float alpha)
{
    rgba_[0] = red;
    rgba_[1] = green;
    rgba_[2] = blue;
    rgba_[3] = alpha;
}

void Colour::set(float rgba[])
{
    memcpy(rgba_, rgba, 4);
}

const float* Colour::toRGBA() const
{
    return rgba_;
}
