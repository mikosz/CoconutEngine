/*
 * core.hpp
 *
 *  Created on: Sep 4, 2008
 *      Author: mikosz
 */

#ifndef CORE_HPP_
#define CORE_HPP_

#include <boost/scoped_ptr.hpp>
#include <window.hpp>
#include <settings.hpp>
#include <eventhandler.hpp>
#include <timemanager.hpp>
#include <screen.hpp>
#include <boost/noncopyable.hpp>

namespace coconutengine
{

class Core : boost::noncopyable
{
public:

    ~Core();

    Settings<std::string>& getApplicationSettings() { return *applicationSettings_; }

    void loop();

    Window& window() { return window_; }

    static Core& instance();

private:

    static Core* instance_;

    Core();

    boost::scoped_ptr<Settings<std::string> > applicationSettings_;

    Window window_;

    TimeManager timeManager_;

    boost::scoped_ptr<Screen> screen_;

};

} // namespace coconutengine

#endif /* CORE_HPP_ */
