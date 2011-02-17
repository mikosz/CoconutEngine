/*
 * window.hpp
 *
 *  Created on: Sep 3, 2008
 *      Author: mikosz
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <log.hpp>
#include <SDL/SDL.h>

namespace coconutengine
{

template <class> class Settings;

class Window
{
public:

    Window(const Settings<std::string>& settings, const std::string& prefix);

    ~Window();

    void flip();

    float aspectRatio() const;

    unsigned int width() const { return width_; }

    unsigned int height() const { return height_; }

private:

    unsigned int width_;

    unsigned int height_;

    unsigned int bpp_;

    bool fullscreen_;

    std::string caption_;

    SDL_Surface* windowSurface_;

    void init();

};

} // namespace coconutengine

#endif /* WINDOW_HPP_ */
