/*
 * positioneduielement.cpp
 *
 *  Created on: Nov 5, 2008
 *      Author: mikosz
 */

#include <positioneduielement.hpp>

#include <settings.hpp>

using namespace coconutengine;

PositionedUiElement::PositionedUiElement(const Settings<std::string>& settings, const std::string& prefix) :
    area_(
            std::make_pair(getSetting<float>(settings, prefix + ".bottom_left.x"),
                    getSetting<float>(settings, prefix + ".bottom_left.y")),
            std::make_pair(getSetting<float>(settings, prefix + ".top_right.x"),
                    getSetting<float>(settings, prefix + ".top_right.y"))
    )
{}
