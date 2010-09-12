/*
 * timemanager.hpp
 *
 *  Created on: Sep 6, 2008
 *      Author: mikosz
 */

#ifndef TIMEMANAGER_HPP_
#define TIMEMANAGER_HPP_

#include <boost/thread.hpp>
#include <queue>

namespace CoconutEngine
{

template <class> class Settings;

typedef uint16_t Milliseconds;

class TimeManager
{
public:

    TimeManager(const Settings<std::string>& settings, const std::string& prefix);

    void reset();

    void frameEnd();

    Milliseconds lastFrameLength() const { return lastFrameLength_; }

    unsigned int fps() const;

private:

    bool manageFrameLength_;

    Milliseconds minFrameLength_;

    Milliseconds maxFrameLength_;

    boost::xtime thisFrameStart_;

    Milliseconds lastFrameLength_;

    std::deque<boost::xtime> last100FrameStarts_;

};

} // namespace CoconutEngine

#endif /* TIMEMANAGER_HPP_ */
