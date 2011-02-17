/*
 * eventhandler.hpp
 *
 *  Created on: Sep 6, 2008
 *      Author: mikosz
 */

#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include <SDL/SDL.h>
#include <list>
#include <map>
#include <limits>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <rectangle.hpp>

namespace coconutengine {

typedef size_t EventId;

class EventType {
public:

    virtual ~EventType() {
    }

    virtual bool operator==(const SDL_Event& event) const = 0;

protected:

    EventType() {
    }

    virtual EventId eventId() const {
        return reinterpret_cast<EventId> (this);
    }

    friend class EventHandler;

};

class WildcardEventType : public EventType {
public:

    bool operator==(const SDL_Event& event) const {
        return true;
    }

protected:

    EventId eventId() const {
        return std::numeric_limits<EventId>::max();
    }

    friend class EventHandler;

};

class KeyboardEventType : public EventType {
public:

    enum KeyState {
        KEY_DOWN, KEY_UP
    };

    KeyboardEventType(KeyState keyState, SDLKey key);

    bool operator==(const SDL_Event& event) const;

private:

    KeyState keyState_;

    SDLKey key_;

};

class MouseEventType : public EventType {
public:

    enum MouseState {
        LEFT_BUTTON_DOWN,
        LEFT_BUTTON_UP,
        RIGHT_BUTTON_DOWN,
        RIGHT_BUTTON_UP,
        MIDDLE_BUTTON_DOWN,
        MIDDLE_BUTTON_UP,
        WHEEL_UP,
        WHEEL_DOWN,
        MOTION
    };

    MouseEventType(MouseState mouseState, const Rectangle<std::pair<float, float> >& area);

    bool operator==(const SDL_Event& event) const;

private:

    MouseState mouseState_;

    Rectangle<std::pair<float, float> > area_;

};

typedef boost::function<bool(const SDL_Event&)> EventCallback;

class EventHandler : boost::noncopyable {
public:

    static const EventCallback EMPTY_EVENT_CALLBACK;

    bool handleEvents();

    EventId registerCallback(boost::shared_ptr<EventType> eventType, const EventCallback& callback);

    void unregisterCallback(EventId id);

    void addCallbackLayer();

    void deleteCallbackLayer();

    static EventHandler& instance();

private:

    EventHandler();

    static EventHandler* instance_;

    static bool doNothing(const SDL_Event&);

    class EventCallbackEntry {
    public:

        boost::shared_ptr<EventType> type;

        EventCallback callback;

        bool operator==(const SDL_Event& eventType) const {
            return *type == eventType;
        }
    };

    typedef std::map<EventId, EventCallbackEntry> EventCallbackLayer;

    typedef std::list<EventCallbackLayer> EventCallbackStack;

    EventCallbackStack callbackStack_;

};

} // namespace coconutengine

#endif /* EVENTHANDLER_HPP_ */
