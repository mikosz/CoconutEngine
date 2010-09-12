/*
 * game.hpp
 *
 *  Created on: Sep 10, 2008
 *      Author: mikosz
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <timemanager.hpp>
#include <map.hpp>
#include <light.hpp>

namespace CoconutEngine
{

template <class> class Settings;
class Player;

class Game
{
public:

    Game(const Settings<std::string>& settings, const std::string& prefix);

    void update(Milliseconds delta);

    Map& map() { return map_; }

    const Map& map() const { return map_; }

    void render(const Camera& camera) const;

private:

    std::vector<boost::shared_ptr<Player> > players_;

    Map map_;

    Light sun_;

};

}

#endif /* GAME_HPP_ */
