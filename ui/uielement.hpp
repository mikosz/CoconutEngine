/*
 * uielement.hpp
 *
 *  Created on: Nov 5, 2008
 *      Author: mikosz
 */

#ifndef UIELEMENT_HPP_
#define UIELEMENT_HPP_

#include <eventhandler.hpp>
#include <timemanager.hpp>

namespace coconutengine
{

class UiElement
{
public:

	virtual ~UiElement()
	{}

	virtual void render() const
	{}

	virtual void update(Milliseconds delta)
	{}

protected:

	UiElement()
	{}

};

}

#endif /* UIELEMENT_HPP_ */
