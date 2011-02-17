/*
 * gamescreen.cpp
 *
 *  Created on: Sep 24, 2008
 *      Author: mikosz
 */

#include <gamescreen.hpp>
#include <graphics.hpp>
#include <core.hpp>

using namespace coconutengine;

GameScreen::GameScreen(const Settings<std::string>& settings, const std::string& prefix) :
    game_(settings, prefix + ".game"), gameView_(game_, settings, prefix + ".game_view") {
}

void GameScreen::update(Milliseconds delta) {
    game_.update(delta);
}

void GameScreen::render() const {
    gameView_.render();
}
