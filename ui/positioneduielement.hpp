/*
 * positioneduielement.hpp
 *
 *  Created on: Nov 5, 2008
 *      Author: mikosz
 */

#ifndef POSITIONEDUIELEMENT_HPP_
#define POSITIONEDUIELEMENT_HPP_

#include <uielement.hpp>
#include <rectangle.hpp>

namespace coconutengine
{

template <class> class Settings;

class PositionedUiElement : public UiElement
{
public:

protected:

	PositionedUiElement(const Settings<std::string>& settings, const std::string& prefix);

	Rectangle<std::pair<float, float> > area_;

};

}

#endif /* POSITIONEDUIELEMENT_HPP_ */
