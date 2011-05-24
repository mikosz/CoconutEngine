/*
 * image.hpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <vector>

#include <boost/scoped_array.hpp>
#include <boost/cstdint.hpp>

#include "GL/gl.h"

#include "colour.hpp"

namespace coconutengine
{

class Image
{
public:

    typedef std::vector<boost::uint8_t> Pixels;

    enum Format {
        RGB = GL_RGB,
        RGBA = GL_RGBA,
        GREYSCALE = (GL_RGB < GL_RGBA ? GL_RGBA : GL_RGB) + 1
    };

    virtual ~Image() {
    }

    const Pixels& pixels() const {
        return pixels_;
    }

    size_t width() const {
        return width_;
    }

    size_t height() const {
        return height_;
    }

    Format format() const {
        return format_;
    }

    void addAlpha(boost::uint8_t value);

    void transparentColour(const Colour& colour);

protected:

    Pixels pixels_;

    size_t width_;

    size_t height_;

    Format format_;

    Image() {
    }

};

} // namespace coconutengine

#endif /* IMAGE_HPP_ */
