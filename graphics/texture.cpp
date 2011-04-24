#include "texture.hpp"

#include <stdexcept>

#include <GL/glu.h>

using namespace coconutengine;

namespace {

void allocate(GLuint& id, Texture::Dimensionality dimensionality, Texture::Filter magnificationFilter,
        Texture::Filter minificationFilter) {
    glGenTextures(1, &id);
    glBindTexture(dimensionality, id);
    glTexParameteri(dimensionality, GL_TEXTURE_MAG_FILTER, magnificationFilter);
    glTexParameteri(dimensionality, GL_TEXTURE_MIN_FILTER, minificationFilter);
    if (magnificationFilter == Texture::MIPMAP_NEAREST || magnificationFilter == Texture::MIPMAP_LINEAR
            || minificationFilter == Texture::MIPMAP_NEAREST || minificationFilter == Texture::MIPMAP_LINEAR) {
        glTexParameteri(dimensionality, GL_GENERATE_MIPMAP, GL_TRUE);
    }
}

} // anonymous namespace

Texture::Texture(Dimensionality dimensionality, Filter magnificationFilter, Filter minificationFilter) :
    dimensionality_(dimensionality) {
    allocate(id_, dimensionality, magnificationFilter, minificationFilter);
}

Texture::Texture(const Image& image, Dimensionality dimensionality, Filter magnificationFilter, Filter minificationFilter) :
        dimensionality_(dimensionality) {
    allocate(id_, dimensionality, magnificationFilter, minificationFilter);
    load(image);
}

Texture::~Texture() {
    glDeleteTextures(1, &id_);
}

void Texture::bind() const {
    glBindTexture(dimensionality_, id_);
}

void Texture::enable() const {
    glEnable(dimensionality_);
}

void Texture::disable() const {
    glDisable(dimensionality_);
}

void Texture::load(const Image& image) const {
    bind();

    switch (dimensionality_) {
    case TEXTURE_1D:
        glTexImage1D(dimensionality_, 0, image.format(), image.width(), 0, image.format(), GL_UNSIGNED_BYTE,
                image.pixels());
        break;
    case TEXTURE_2D:
        glTexImage2D(dimensionality_, 0, image.format(), image.width(), image.height(), 0, image.format(),
                GL_UNSIGNED_BYTE, image.pixels());
        break;
    default:
        throw std::runtime_error("Invalid texture dimensionality");
    }
}
