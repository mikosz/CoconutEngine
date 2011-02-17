/*
 * button.hpp
 *
 *  Created on: Nov 5, 2008
 *      Author: mikosz
 */

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <positioneduielement.hpp>

#include <SDL/SDL.h>

#include <log.hpp>

namespace coconutengine
{

template <class> class Settings;

class Button : public PositionedUiElement
{
public:

    virtual ~Button();

    virtual bool clicked(const SDL_Event& event) { return true; }

protected:

	Button(const Settings<std::string>& settings, const std::string& prefix);

private:

    size_t clickedCallbackId_;

};

}

#endif /* BUTTON_HPP_ */
