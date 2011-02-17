/*
 * player.cpp
 *
 *  Created on: Sep 10, 2008
 *      Author: mikosz
 */

#include <player.hpp>

using namespace coconutengine;

Player::Player(const std::string& name) :
    name_(name)
{}

Player::~Player()
{

}

void Player::update(Milliseconds delta)
{
    for(std::vector<boost::shared_ptr<Actor> >::iterator i = units_.begin();
        i != units_.end(); ++ i)
    {
        (*i)->update(delta);
    }
}
