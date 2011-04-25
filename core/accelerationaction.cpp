/*
 * moveaction.cpp
 *
 *  Created on: 2010-01-26
 *      Author: mikosz
 */

#include <accelerationaction.hpp>
#include <settings.hpp>
#include <limits>

using namespace coconutengine;

AccelerationAction::AccelerationAction(const Settings<std::string>& settings, const std::string& settingsPrefix) :
    velocity_(getSetting<float> (settings, settingsPrefix + ".velocity", 0.0f)), acceleration_(getSetting<float> (
            settings, settingsPrefix + ".acceleration")), targetVelocity_(getSetting<float> (settings, settingsPrefix
            + ".targetVelocity")) {
}

bool AccelerationAction::complete() {
    return false;
}

void AccelerationAction::update(TimeDuration delta) {
    velocity_ += acceleration_ * delta.total_milliseconds();
    if ((acceleration_ > 0 && velocity_ > targetVelocity_) || (acceleration_ < 0 && velocity_ < targetVelocity_)) {
        velocity_ = targetVelocity_;
    }
}
