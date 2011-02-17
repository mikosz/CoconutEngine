/*
 * gameview.hpp
 *
 *  Created on: Dec 2, 2008
 *      Author: mikosz
 */

#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

#include <positioneduielement.hpp>
#include <string>
#include <camera.hpp>
#include <SDL/SDL.h>
#include <actiondispatcher.hpp>
#include <boost/shared_ptr.hpp>
#include <accelerationaction.hpp>
#include <cameramoveaction.hpp>

namespace coconutengine {

template<class > class Settings;
class Game;

class GameView : public PositionedUiElement {
public:

    GameView(Game& game, const Settings<std::string>& settings, const std::string& prefix);

    ~GameView();

    void render() const;

private:

    Game& game_;

    Camera camera_;

    bool wireframe_;

    const Settings<std::string>& settings_;

    std::string prefix_;

    float cameraZoomSensitivity_;

    EventId cameraStartFreeMoveEventId_;

    EventId cameraStopFreeMoveEventId_;

    EventId cameraFreeMoveEventId_;

    EventId cameraStartMoveForwardEventId_;

    EventId cameraStopMoveForwardEventId_;

    EventId cameraStartMoveBackEventId_;

    EventId cameraStopMoveBackEventId_;

    EventId cameraStartMoveLeftEventId_;

    EventId cameraStopMoveLeftEventId_;

    EventId cameraStartMoveRightEventId_;

    EventId cameraStopMoveRightEventId_;

    EventId cameraZoomInEventId_;

    EventId cameraZoomOutEventId_;

    EventId cameraStartZoomInEventId_;

    EventId cameraStopZoomInEventId_;

    EventId cameraStartZoomOutEventId_;

    EventId cameraStopZoomOutEventId_;

    ActionId cameraMoveActionId_;

    boost::shared_ptr<CameraMoveAction> cameraMoveAction_;

    bool cameraStartFreeMove(const SDL_Event& event);

    bool cameraStopFreeMove(const SDL_Event& event);

    bool cameraFreeMove(const SDL_Event& event);

    bool cameraStartMove(const SDL_Event& event);

    bool cameraStopMove(const SDL_Event& event);

    bool cameraZoomIn(const SDL_Event& event);

    bool cameraZoomOut(const SDL_Event& event);

    bool cameraStartZoomIn(const SDL_Event& event);

    bool cameraStopZoomIn(const SDL_Event& event);

    bool cameraStartZoomOut(const SDL_Event& event);

    bool cameraStopZoomOut(const SDL_Event& event);

    Vector2D<int> mousePosition_;

    SDL_GrabMode grabMode_;

};

} // namespace coconutengine

#endif /* GAMEVIEW_HPP_ */
