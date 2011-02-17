/*
 * action.hpp
 *
 *  Created on: Nov 4, 2008
 *      Author: mikosz
 */

#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <timemanager.hpp>

namespace coconutengine
{

class Actor;

class Action
{
public:

	virtual ~Action() {}

	virtual void update(Milliseconds delta) = 0;

	virtual bool complete() = 0;

};

} // namespace coconutengine

#endif /* ACTION_HPP_ */
