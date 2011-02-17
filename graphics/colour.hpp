/*
 * colour.hpp
 *
 *  Created on: Oct 13, 2008
 *      Author: mikosz
 */

#ifndef COLOUR_HPP_
#define COLOUR_HPP_

#include <string>

namespace coconutengine
{

template <class> class Settings;

class Colour
{
public:

    static const Colour WHITE;

    static const Colour BLACK;

    Colour(float red, float green, float blue, float alpha);

    Colour(float rgba[]);

    Colour(const Settings<std::string>& settings, const std::string& settingsPrefix);

    const float* toRGBA() const;

    void set(float red, float green, float blue, float alpha);

    void set(float rgba[]);

    float& red() { return rgba_[0]; }

    const float& red() const { return rgba_[0]; }

    float& green() { return rgba_[1]; }

    const float& green() const { return rgba_[1]; }

    float& blue() { return rgba_[2]; }

    const float& blue() const { return rgba_[2]; }

    float& alpha() { return rgba_[3]; }

    const float& alpha() const { return rgba_[3]; }

private:

    float rgba_[4];

};

}

#endif /* COLOUR_HPP_ */
