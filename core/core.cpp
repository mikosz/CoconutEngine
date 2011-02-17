/*
 * core.cpp
 *
 *  Created on: Sep 4, 2008
 *      Author: mikosz
 */

#include <core.hpp>
#include <stdexcept>
#include <SDL/SDL.h>
#include <log.hpp>
#include <gamescreen.hpp>
#include <propertiesfilesettings.hpp>
#include <graphics.hpp>
#include <actiondispatcher.hpp>

using namespace coconutengine;

Core* Core::instance_ = 0;

Core& Core::instance() {
    if (!instance_) {
        instance_ = new Core();
    }
    return *instance_;
}

Core::Core() :
    applicationSettings_(new PropertiesFileSettings("coconutengine.properties")), window_(*applicationSettings_,
            "window"), timeManager_(*applicationSettings_, "time_manager"), screen_(new GameScreen(
            *applicationSettings_, "game_screen")) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        throw std::runtime_error("Failed to initialize SDL");
    }
}

Core::~Core() {
    SDL_Quit();
}

void Core::loop() {
    SET_LOG_CONTEXT("Core_::loop");

    Graphics::instance().initEngine();

    timeManager_.reset();
    while (1) {
        LOG_TRACE   << "Frame start" << LOG_END;

        if (EventHandler::instance().handleEvents()) {
            break;
        }

        ActionDispatcher::instance().dispatch(timeManager_.lastFrameLength());

        screen_->update(timeManager_.lastFrameLength());

        Graphics::instance().beginScene();
        screen_->render();
        Graphics::instance().endScene();

        SDL_GL_SwapBuffers();

        timeManager_.frameEnd();
        LOG_TRACE   << "Frame end after " << timeManager_.lastFrameLength() << "ms (fps: " << timeManager_.fps() << ")"
                            << LOG_END;
    }
}
