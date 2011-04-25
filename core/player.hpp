/*
 * player.hpp
 *
 *  Created on: Sep 10, 2008
 *      Author: mikosz
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <timemanager.hpp>
#include <actor.hpp>

namespace coconutengine
{

class Player : boost::noncopyable
{
protected:

    explicit Player(const std::string& name);

public:

    virtual ~Player();

    virtual void action() = 0;

    void update(TimeDuration delta);

    const std::string& getName() const { return name_; }

    void setName(const std::string& name) { name_ = name; }

private:

    std::string name_;

    std::vector<boost::shared_ptr<Actor> > units_;

};

}

#endif /* PLAYER_HPP_ */
