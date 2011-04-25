/*
 * timemanager.hpp
 *
 *  Created on: Sep 6, 2008
 *      Author: mikosz
 */

#ifndef TIMEMANAGER_HPP_
#define TIMEMANAGER_HPP_

#include <queue>

#include <boost/date_time.hpp>

namespace coconutengine
{

template <class> class Settings;

typedef boost::posix_time::time_duration TimeDuration;

class TimeManager
{
public:

    TimeManager(const Settings<std::string>& settings, const std::string& prefix);

    void reset();

    void frameEnd();

    unsigned int fps() const;

    const TimeDuration& lastFrameLength() const {
        return lastFrameLength_;
    }

private:

    bool manageFrameLength_;

    TimeDuration minFrameLength_;

    TimeDuration maxFrameLength_;

    boost::posix_time::ptime thisFrameStart_;

    TimeDuration lastFrameLength_;

    std::deque<boost::posix_time::ptime> last100FrameStarts_;

};

} // namespace coconutengine

#endif /* TIMEMANAGER_HPP_ */
