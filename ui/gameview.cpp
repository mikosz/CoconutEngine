#include <gameview.hpp>
#include <game.hpp>
#include <core.hpp>
#include <eventhandler.hpp>
#include <log.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <utility.hpp>
#include <actiondispatcher.hpp>
#include <vector.hpp>
#include <cameramoveaction.hpp>
#include <graphics.hpp>
#include "renderpipeline.hpp"

#include "bitmap.hpp"

using namespace coconutengine;

namespace {

Vec3D getDirection(const SDL_Event& event) {
    Vec3D direction(0, 0, 0);
    switch (event.key.keysym.sym) {
    case SDLK_w:
        direction.y() = 1.0f;
        break;
    case SDLK_s:
        direction.y() = -1.0f;
        break;
    case SDLK_a:
        direction.x() = -1.0f;
        break;
    case SDLK_d:
        direction.x() = 1.0f;
        break;
    case SDLK_EQUALS:
        direction.z() = -1.0f;
        break;
    case SDLK_MINUS:
        direction.z() = 1.0f;
        break;
    default:
        assert(false);
    }
    return direction;
}

} // anonymous namespace

GameView::GameView(Game& game, const Settings<std::string>& settings, const std::string& prefix) :
    PositionedUiElement(settings, prefix), game_(game), camera_(game.map().terrain(), settings, prefix + ".camera"), wireframe_(getSetting<
            bool> (settings, prefix + ".wireframe")), settings_(settings), prefix_(prefix), cameraZoomSensitivity_(
            getSetting<float> (settings, prefix + ".cameraZoomSensitivity")), cameraStartFreeMoveEventId_(0),
            cameraStopFreeMoveEventId_(0), cameraFreeMoveEventId_(0), cameraStartMoveForwardEventId_(0),
            cameraStopMoveForwardEventId_(0), cameraStartMoveBackEventId_(0), cameraStopMoveBackEventId_(0),
            cameraStartMoveLeftEventId_(0), cameraStopMoveLeftEventId_(0), cameraStartMoveRightEventId_(0),
            cameraStopMoveRightEventId_(0), font_(settings, prefix + ".font") {

    cameraStartFreeMoveEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new MouseEventType(MouseEventType::MIDDLE_BUTTON_DOWN, area_)), boost::bind(&GameView::cameraStartFreeMove,
            this, _1));

    cameraZoomInEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(new MouseEventType(
            MouseEventType::WHEEL_UP, area_)), boost::bind(&GameView::cameraZoomIn, this, _1));
    cameraZoomOutEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(new MouseEventType(
            MouseEventType::WHEEL_DOWN, area_)), boost::bind(&GameView::cameraZoomOut, this, _1));

    EventCallback cameraStartMoveCallback = boost::bind(&GameView::cameraStartMove, this, _1);
    cameraStartMoveForwardEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new KeyboardEventType(KeyboardEventType::KEY_DOWN, SDLK_w)), cameraStartMoveCallback);
    cameraStopMoveForwardEventId_
            = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(new KeyboardEventType(
                    KeyboardEventType::KEY_UP, SDLK_w)), boost::bind(&GameView::cameraStopMove, this, _1));
    cameraStartMoveBackEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new KeyboardEventType(KeyboardEventType::KEY_DOWN, SDLK_s)), cameraStartMoveCallback);
    cameraStopMoveBackEventId_
            = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(new KeyboardEventType(
                    KeyboardEventType::KEY_UP, SDLK_s)), boost::bind(&GameView::cameraStopMove, this, _1));
    cameraStartMoveLeftEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new KeyboardEventType(KeyboardEventType::KEY_DOWN, SDLK_a)), cameraStartMoveCallback);
    cameraStopMoveLeftEventId_
            = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(new KeyboardEventType(
                    KeyboardEventType::KEY_UP, SDLK_a)), boost::bind(&GameView::cameraStopMove, this, _1));
    cameraStartMoveRightEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new KeyboardEventType(KeyboardEventType::KEY_DOWN, SDLK_d)), cameraStartMoveCallback);
    cameraStopMoveRightEventId_
            = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(new KeyboardEventType(
                    KeyboardEventType::KEY_UP, SDLK_d)), boost::bind(&GameView::cameraStopMove, this, _1));
    cameraStartZoomInEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new KeyboardEventType(KeyboardEventType::KEY_DOWN, SDLK_EQUALS)), cameraStartMoveCallback);
    cameraStopZoomInEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new KeyboardEventType(KeyboardEventType::KEY_UP, SDLK_EQUALS)), boost::bind(
            &GameView::cameraStopMove, this, _1));
    cameraStartZoomOutEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new KeyboardEventType(KeyboardEventType::KEY_DOWN, SDLK_MINUS)), cameraStartMoveCallback);
    cameraStopZoomOutEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new KeyboardEventType(KeyboardEventType::KEY_UP, SDLK_MINUS)), boost::bind(
            &GameView::cameraStopMove, this, _1));
}

GameView::~GameView() {
    EventHandler::instance().unregisterCallback(cameraStartFreeMoveEventId_);
    EventHandler::instance().unregisterCallback(cameraStopFreeMoveEventId_);
    EventHandler::instance().unregisterCallback(cameraFreeMoveEventId_);
    EventHandler::instance().unregisterCallback(cameraStartMoveForwardEventId_);
    EventHandler::instance().unregisterCallback(cameraStartMoveBackEventId_);
    EventHandler::instance().unregisterCallback(cameraStartMoveLeftEventId_);
    EventHandler::instance().unregisterCallback(cameraStartMoveRightEventId_);
}

void GameView::render() const {
    if (wireframe_) {
        Graphics::instance().drawWireframe();
    }
    camera_.setupPerspective(Core::instance().window().aspectRatio());
    game_.sun().on();
    RenderPipeline::instance().render(camera_);
    game_.sun().off();

    camera_.setupOrthographic(Core::instance().window().width(), Core::instance().window().height());

    font_.print("Current fps: " + boost::lexical_cast<std::string>(Core::instance().timeManager().fps()),
            Rectangle<Vec2D> (
                    Vec2D(0.0f, 0.0f),
                    Vec2D(Core::instance().window().width(), Core::instance().window().height())),
            Colour::WHITE);
}

bool GameView::cameraStartFreeMove(const SDL_Event& event) {
    SET_LOG_CONTEXT("GameView::cameraStartFreeMove");
    LOG_DEBUG   << "Camera free move starts" << LOG_END;

    SDL_ShowCursor(false);
    grabMode_ = SDL_WM_GrabInput(SDL_GRAB_QUERY);
    SDL_GetMouseState(&mousePosition_.x(), &mousePosition_.y());
    SDL_WM_GrabInput(SDL_GRAB_ON);

    EventHandler::instance().addCallbackLayer();

    cameraStopFreeMoveEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(
            new MouseEventType(MouseEventType::MIDDLE_BUTTON_UP, area_)), boost::bind(&GameView::cameraStopFreeMove,
            this, _1));
    cameraFreeMoveEventId_ = EventHandler::instance().registerCallback(boost::shared_ptr<EventType>(new MouseEventType(
            MouseEventType::MOTION, area_)), boost::bind(&GameView::cameraFreeMove, this, _1));

    return true;
}

bool GameView::cameraStopFreeMove(const SDL_Event& event) {
    SET_LOG_CONTEXT("GameView::cameraStopFreeMove");
    LOG_DEBUG   << "Camera free move stops" << LOG_END;

    EventHandler::instance().deleteCallbackLayer();

    SDL_WM_GrabInput(grabMode_);
    SDL_WarpMouse(mousePosition_.x(), mousePosition_.y());
    SDL_ShowCursor(true);

    return true;
}

bool GameView::cameraFreeMove(const SDL_Event& event) {
    SET_LOG_CONTEXT("GameView::cameraFreeMove");
    LOG_DEBUG   << "Camera moves" << LOG_END;

    camera_.rotation().x() = clamp(camera_.rotation().x() - ((static_cast<float> (event.motion.yrel)
            / Core::instance().window().width()) * PI), 0, PI / 2);
    camera_.rotation().z() -= (static_cast<float> (event.motion.xrel) / Core::instance().window().width()) * PI;

    return true;
}

bool GameView::cameraStartMove(const SDL_Event& event) {
    SET_LOG_CONTEXT("GameView::cameraStartMove");
    LOG_DEBUG   << "Camera move starts" << LOG_END;

    Vec3D direction = getDirection(event);

    if (!cameraMoveAction_) {
        cameraMoveAction_.reset(new CameraMoveAction(camera_, direction, settings_, prefix_ + ".camera_move_action"));
    } else {
        cameraMoveAction_->direction() += direction;
    }

    cameraMoveActionId_ = ActionDispatcher::instance().registerAction(cameraMoveAction_);

    return true;
}

bool GameView::cameraStopMove(const SDL_Event& event) {
    SET_LOG_CONTEXT("GameView::cameraStopMove");
    LOG_DEBUG   << "Camera move stops" << LOG_END;

    if (!cameraMoveAction_) {
        return true;
    }

    Vec3D direction = getDirection(event);
    cameraMoveAction_->direction() -= direction;

    if (cameraMoveAction_->direction() == Vec3D(0, 0, 0)) {
        ActionDispatcher::instance().unregisterAction(cameraMoveActionId_);
        cameraMoveAction_.reset();
    }

    return true;
}

bool GameView::cameraZoomIn(const SDL_Event& event) {
    SET_LOG_CONTEXT("GameView::cameraZoomIn");
    LOG_DEBUG   << "Camera zooms in" << LOG_END;

    camera_.position() -= Vec3D(0, 0, cameraZoomSensitivity_);

    return true;
}

bool GameView::cameraZoomOut(const SDL_Event& event) {
    SET_LOG_CONTEXT("GameView::cameraZoomOut");
    LOG_DEBUG   << "Camera zooms out" << LOG_END;

    camera_.position() += Vec3D(0, 0, cameraZoomSensitivity_);

    return true;
}
