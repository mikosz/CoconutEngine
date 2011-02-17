#include "texture.hpp"

#include <stdexcept>

#include <GL/glu.h>

using namespace coconutengine;

Texture::Texture(const Image& image, Dimensionality dimensionality, Filter magnificationFilter, Filter minificationFilter) :
        dimensionality_(dimensionality) {
    glGenTextures(1, &id_);
    glBindTexture(dimensionality, id_);
    glTexParameteri(dimensionality, GL_TEXTURE_MAG_FILTER, magnificationFilter);
    glTexParameteri(dimensionality, GL_TEXTURE_MIN_FILTER, minificationFilter);
    if (magnificationFilter == MIPMAP_NEAREST || magnificationFilter == MIPMAP_LINEAR ||
            minificationFilter == MIPMAP_NEAREST || minificationFilter == MIPMAP_LINEAR) {
        glTexParameteri(dimensionality, GL_GENERATE_MIPMAP, GL_TRUE);
    }
    switch (dimensionality) {
    case TEXTURE_1D:
        glTexImage1D(dimensionality, 0, GL_RGB, image.width(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.pixels());
        break;
    case TEXTURE_2D:
        glTexImage2D(dimensionality, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                image.pixels());
        break;
    default:
        throw std::runtime_error("Invalid texture dimensionality");
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &id_);
}

void Texture::bind() const {
    glBindTexture(dimensionality_, id_);
}
