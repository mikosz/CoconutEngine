/*
 * gamescreen.hpp
 *
 *  Created on: Sep 24, 2008
 *      Author: mikosz
 */

#ifndef GAMESCREEN_HPP_
#define GAMESCREEN_HPP_

#include <screen.hpp>
#include <timemanager.hpp>
#include <gameview.hpp>
#include <camera.hpp>
#include <game.hpp>

namespace coconutengine {

template<class > class Settings;

class GameScreen : public Screen {
public:

    GameScreen(const Settings<std::string>& settings, const std::string& prefix);

    void update(TimeDuration delta);

    void render() const;

private:

    Game game_;

    GameView gameView_;

};

}

#endif /* GAMESCREEN_HPP_ */
