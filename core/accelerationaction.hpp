/*
 * moveaction.hpp
 *
 *  Created on: 2010-01-26
 *      Author: mikosz
 */

#ifndef ACCELERATIONACTION_HPP_
#define ACCELERATIONACTION_HPP_

#include <action.hpp>

namespace coconutengine {

template<class > class Settings;

class AccelerationAction: public Action {
public:

    AccelerationAction(const Settings<std::string>& settings, const std::string& settingsPrefix);

    void update(TimeDuration delta);

    bool complete();

    float& velocity() {
        return velocity_;
    }

    const float& velocity() const {
        return velocity_;
    }

private:

    float velocity_;

    float acceleration_;

    float targetVelocity_;

};

}

#endif /* ACCELERATIONACTION_HPP_ */
