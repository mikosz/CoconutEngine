/*
 * window.cpp
 *
 *  Created on: Sep 6, 2008
 *      Author: mikosz
 */

#include <window.hpp>

#include <settings.hpp>
#include <eventhandler.hpp>

using namespace coconutengine;

// TODO: change videomode parms?
Window::Window(const Settings<std::string>& settings, const std::string& prefix)
    : width_(getSetting<unsigned int>(settings, prefix + ".width")),
      height_(getSetting<unsigned int>(settings, prefix + ".height")),
      bpp_(getSetting<unsigned int>(settings, prefix + ".bpp")),
      fullscreen_(getSetting<bool>(settings, prefix + ".fullscreen")),
      caption_(getSetting<std::string>(settings, prefix + ".caption")),
      windowSurface_(SDL_SetVideoMode(width_, height_, bpp_, SDL_OPENGL |
        (fullscreen_ ? SDL_FULLSCREEN : 0)))
{
    init();
}

Window::~Window()
{
    SDL_FreeSurface(windowSurface_);
}

void Window::init()
{
    SDL_WM_SetCaption(caption_.c_str(), 0);
}

void Window::flip()
{
    SDL_Flip(windowSurface_);
}

float Window::aspectRatio() const
{
    return height_ ? static_cast<float>(width_) / height_ : 0.0f;
}
