/*
 * game.cpp
 *
 *  Created on: Sep 10, 2008
 *      Author: mikosz
 */

#include <game.hpp>

#include <player.hpp>
#include <settings.hpp>

#include <cameramoveaction.hpp>

using namespace coconutengine;

Game::Game(const Settings<std::string>& settings, const std::string& prefix) :
    map_(settings, prefix + ".map"), sun_(settings, prefix + ".sun") {
    sun_.on();
}

void Game::update(Milliseconds delta) {
    for (std::vector<boost::shared_ptr<Player> >::iterator i = players_.begin(); i != players_.end(); ++i) {
        (*i)->update(delta);
    }
}
