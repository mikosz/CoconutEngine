/*
 * screen.hpp
 *
 *  Created on: Sep 24, 2008
 *      Author: mikosz
 */

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <timemanager.hpp>

namespace coconutengine
{

class Screen
{
public:

    virtual ~Screen()
    {}

    virtual void update(TimeDuration delta) = 0;

    virtual void render() const = 0;

protected:

    Screen() {}

};

}

#endif /* SCREEN_HPP_ */
