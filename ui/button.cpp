/*
 * button.cpp
 *
 *  Created on: Nov 26, 2008
 *      Author: mikosz
 */

#include <button.hpp>

#include <settings.hpp>
#include <eventhandler.hpp>
#include <boost/bind.hpp>

using namespace CoconutEngine;

Button::Button(const Settings<std::string>& settings, const std::string& prefix) :
    PositionedUiElement(settings, prefix)
{
    clickedCallbackId_ = EventHandler::instance().registerCallback(
            boost::shared_ptr<EventType>(new MouseEventType(MouseEventType::LEFT_BUTTON_DOWN, area_)),
            boost::bind(&Button::clicked, this, _1));
}

Button::~Button()
{
    EventHandler::instance().unregisterCallback(clickedCallbackId_);
}
