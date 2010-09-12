/*
 * eventhandler.cpp
 *
 *  Created on: Sep 6, 2008
 *      Author: mikosz
 */

#include <eventhandler.hpp>

#include <algorithm>
#include <log.hpp>
#include <cassert>

using namespace CoconutEngine;

EventHandler* EventHandler::instance_ = 0;

const EventCallback EventHandler::EMPTY_EVENT_CALLBACK = boost::bind(&EventHandler::doNothing, _1);

EventHandler::EventHandler() {
    addCallbackLayer();
}

EventHandler& EventHandler::instance() {
    if (!instance_) {
        instance_ = new EventHandler();
    }
    return *instance_;
}

bool EventHandler::doNothing(const SDL_Event&) {
    return true;
}

bool EventHandler::handleEvents() {
    assert(callbackStack_.size());
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }

        bool handled = false;
        EventCallbackStack::reverse_iterator stackIt = callbackStack_.rbegin(), stackEnd = callbackStack_.rend();
        while (stackIt != stackEnd) {
            EventCallbackLayer::iterator layerIt = stackIt->begin(), layerEnd = stackIt->end();
            while (layerIt != layerEnd) {
                if (layerIt->second == event && layerIt->second.callback(event)) {
                    handled = true;
                    break;
                }
                ++layerIt;
            }
            if (handled) {
                break;
            }
            ++stackIt;
        }
    }

    return false;
}

EventId EventHandler::registerCallback(boost::shared_ptr<EventType> eventType, const EventCallback& callback) {
    assert(callbackStack_.size());

    EventCallbackEntry entry;
    entry.callback = callback;
    entry.type = eventType;
    callbackStack_.back().insert(std::make_pair(eventType->eventId(), entry));

    return eventType->eventId();
}

void EventHandler::unregisterCallback(EventId id) {
    assert(callbackStack_.size());
    EventCallbackStack::reverse_iterator rend = callbackStack_.rend();
    for (EventCallbackStack::reverse_iterator stackIt = callbackStack_.rbegin(); stackIt != rend; ++stackIt) {
        if (stackIt->erase(id)) {
            return;
        }
    }
}

void EventHandler::addCallbackLayer() {
    callbackStack_.push_back(EventCallbackLayer());
}

void EventHandler::deleteCallbackLayer() {
    assert(callbackStack_.size() > 1);
    callbackStack_.pop_back();
}

KeyboardEventType::KeyboardEventType(KeyState keyState, SDLKey key) :
    keyState_(keyState), key_(key) {
}

bool KeyboardEventType::operator==(const SDL_Event& event) const {
    return ((keyState_ == KEY_DOWN && event.type == SDL_KEYDOWN) || (keyState_ == KEY_UP && event.type == SDL_KEYUP))
            && event.key.keysym.sym == key_;
}

MouseEventType::MouseEventType(MouseState mouseState, const Rectangle<std::pair<float, float> >& area) :
    mouseState_(mouseState), area_(area) {
}

bool MouseEventType::operator==(const SDL_Event& event) const {
    return (((mouseState_ == LEFT_BUTTON_DOWN && event.type == SDL_MOUSEBUTTONDOWN && event.button.button
            == SDL_BUTTON_LEFT) || (mouseState_ == LEFT_BUTTON_UP && event.type == SDL_MOUSEBUTTONUP
            && event.button.button == SDL_BUTTON_LEFT) || (mouseState_ == RIGHT_BUTTON_DOWN && event.type
            == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) || (mouseState_ == RIGHT_BUTTON_UP
            && event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_RIGHT) || (mouseState_
            == MIDDLE_BUTTON_DOWN && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_MIDDLE)
            || (mouseState_ == MIDDLE_BUTTON_UP && event.type == SDL_MOUSEBUTTONUP && event.button.button
                    == SDL_BUTTON_MIDDLE) || (mouseState_ == WHEEL_UP && event.type == SDL_MOUSEBUTTONUP
            && event.button.button == SDL_BUTTON_WHEELUP) || (mouseState_ == WHEEL_DOWN && event.type
            == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_WHEELDOWN)) && area_.contains(std::make_pair(
            event.button.x, event.button.y))) || (mouseState_ == MOTION && event.type == SDL_MOUSEMOTION
            && area_.contains(std::make_pair(event.motion.x, event.motion.y)));
}
