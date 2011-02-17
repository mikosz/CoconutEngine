/*
 * timemanager.cpp
 *
 *  Created on: Sep 6, 2008
 *      Author: mikosz
 */

#include <timemanager.hpp>

#include <settings.hpp>
#include <utility.hpp>

using namespace coconutengine;

namespace {

Milliseconds operator-(boost::xtime lhs, boost::xtime rhs) {
    if (lhs.sec != rhs.sec) {
        return ((lhs.nsec ? (1000000000 - lhs.nsec) : 0) + rhs.nsec) / 1000000;
    } else {
        return (lhs.nsec - rhs.nsec) / 1000000;
    }
}

Milliseconds fpsToFrameLength(unsigned int fps) {
    if (fps == 0) {
        return 0;
    }
    return 1000 / fps;
}

} // anonymous namespace

TimeManager::TimeManager(const Settings<std::string>& settings, const std::string& prefix) :
    manageFrameLength_(getSetting<bool> (settings, prefix + ".manage_frame_length")), minFrameLength_(
            manageFrameLength_ ? fpsToFrameLength(getSetting<unsigned int> (settings, prefix + ".max_fps", 0)) : 0),
            maxFrameLength_(manageFrameLength_ ? fpsToFrameLength(getSetting<unsigned int> (settings, prefix
                    + ".min_fps", 0)) : 0) {
}

void TimeManager::reset() {
    thisFrameStart_ = boost::get_xtime(boost::get_system_time());

    last100FrameStarts_.push_back(thisFrameStart_);
}

void TimeManager::frameEnd() {
    boost::xtime lastFrameStart = thisFrameStart_;

    if (manageFrameLength_ && minFrameLength_) {
        boost::xtime now = boost::get_xtime(boost::get_system_time());
        Milliseconds diff = now - thisFrameStart_;
        if (diff < minFrameLength_) {
            boost::xtime sleepTill = thisFrameStart_;
            sleepTill.nsec += (minFrameLength_ * 1000000) - diff;
            boost::thread::sleep(sleepTill);
        }
    }

    thisFrameStart_ = boost::get_xtime(boost::get_system_time());
    if (manageFrameLength_ && maxFrameLength_) {
        lastFrameLength_ = min(thisFrameStart_ - lastFrameStart, maxFrameLength_);
    } else {
        lastFrameLength_ = thisFrameStart_ - lastFrameStart;
    }

    if (last100FrameStarts_.size() >= 100) {
        last100FrameStarts_.pop_front();
    }
    last100FrameStarts_.push_back(thisFrameStart_);
}

unsigned int TimeManager::fps() const {
    return 1000 / ((last100FrameStarts_.back() - last100FrameStarts_.front()) / last100FrameStarts_.size());
}
