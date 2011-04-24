#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "image.hpp"
#include "colour.hpp"

#include <GL/gl.h>

namespace coconutengine {

class Texture {
public:

    enum Dimensionality {
        TEXTURE_1D = GL_TEXTURE_1D,
        TEXTURE_2D = GL_TEXTURE_2D
    };

    enum Filter {
        NEAREST = GL_NEAREST,
        LINEAR = GL_LINEAR,
        MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
        MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR
    };

    Texture(Dimensionality dimensionality = TEXTURE_2D, Filter magnificationFilter = LINEAR,
            Filter minificationFilter = LINEAR);

    Texture(const Image& image, Dimensionality dimensionality = TEXTURE_2D,
            Filter magnificationFilter = LINEAR, Filter minificationFilter = LINEAR);

    ~Texture();

    void enable() const;

    void disable() const;

    void bind() const;

    void load(const Image& image) const;

private:

    GLuint id_;

    Dimensionality dimensionality_;

};

}  // namespace coconutengine

#endif /* TEXTURE_HPP_ */
