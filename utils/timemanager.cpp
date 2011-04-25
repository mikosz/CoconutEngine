#include <timemanager.hpp>

#include <algorithm>

#include <boost/thread.hpp>

#include <settings.hpp>
#include <utility.hpp>

using namespace coconutengine;

namespace {

TimeDuration fpsToFrameLength(unsigned int fps) {
    if (fps == 0) {
        return boost::posix_time::seconds(0);
    }
    return boost::posix_time::seconds(1) / fps;
}

} // anonymous namespace

TimeManager::TimeManager(const Settings<std::string>& settings, const std::string& prefix) :
    manageFrameLength_(getSetting<bool> (settings, prefix + ".manage_frame_length")),
    minFrameLength_(boost::date_time::not_a_date_time),
    maxFrameLength_(boost::date_time::not_a_date_time) {
    if (manageFrameLength_) {
        minFrameLength_ = fpsToFrameLength(getSetting<unsigned int> (settings, prefix + ".max_fps", 0));
        maxFrameLength_ = fpsToFrameLength(getSetting<unsigned int> (settings, prefix + ".min_fps", 0));
    }
}

void TimeManager::reset() {
    thisFrameStart_ = boost::posix_time::microsec_clock::local_time();

    last100FrameStarts_.push_back(thisFrameStart_);
}

void TimeManager::frameEnd() {
    boost::posix_time::ptime lastFrameStart = thisFrameStart_;

    if (manageFrameLength_ && !minFrameLength_.is_not_a_date_time()) {
        boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        TimeDuration diff = now - thisFrameStart_;
        if (diff < minFrameLength_) {
            boost::this_thread::sleep(minFrameLength_ - diff);
        }
    }

    thisFrameStart_ = boost::get_xtime(boost::get_system_time());
    if (manageFrameLength_ && !maxFrameLength_.is_not_a_date_time()) {
        lastFrameLength_ = std::min(thisFrameStart_ - lastFrameStart, maxFrameLength_);
    } else {
        lastFrameLength_ = thisFrameStart_ - lastFrameStart;
    }

    if (last100FrameStarts_.size() >= 100) {
        last100FrameStarts_.pop_front();
    }

    last100FrameStarts_.push_back(thisFrameStart_);
}

unsigned int TimeManager::fps() const {
    if (last100FrameStarts_.size()) {
        float avgFrameLength =
                static_cast<float>((last100FrameStarts_.back() - last100FrameStarts_.front()).total_milliseconds())
                / last100FrameStarts_.size();
        if (avgFrameLength) {
            return 1000 / avgFrameLength;
        }
    }
    return 0;
}
