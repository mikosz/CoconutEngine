#include "image.hpp"

#include <stdexcept>
#include <limits>
#include <cassert>

#include "log.hpp"

using namespace coconutengine;

namespace {

void toRGBA(std::vector<boost::uint8_t>& pixels) {
    assert(pixels.size() % 3 == 0);

    std::vector<boost::uint8_t> widened;
    widened.reserve(4 * (pixels.size() / 3));

    for (size_t i = 0; i < pixels.size();) {
        widened.push_back(pixels[i++]);
        widened.push_back(pixels[i++]);
        widened.push_back(pixels[i++]);
        widened.push_back(std::numeric_limits<boost::uint8_t>::max());
    }

    pixels.swap(widened);
}

} // anonymous namespace

void Image::addAlpha(boost::uint8_t value) {
    if (format_ == GREYSCALE) {
        throw std::runtime_error("Cannot add an alpha channel to a greyscale image");
    }

    if (format_ == RGB) {
        format_ = RGBA;
        toRGBA(pixels_);
    }

    for (size_t i = 3; i < pixels_.size(); i += 4) {
        pixels_[i] = value;
    }
}

void Image::transparentColour(const Colour& colour) {
    boost::uint8_t r = std::numeric_limits<boost::uint8_t>::max() * colour.red(),
            g = std::numeric_limits<boost::uint8_t>::max() * colour.green(),
            b = std::numeric_limits<boost::uint8_t>::max() * colour.blue();

    addAlpha(std::numeric_limits<boost::uint8_t>::max());

    assert(format_ == RGBA);
    assert(pixels_.size() % 4 == 0);

    for (size_t i = 0; i < pixels_.size(); i += 4) {
        if (pixels_[i] == r && pixels_[i + 1] == g && pixels_[i + 2] == b) {
            pixels_[i + 3] = 0;
        }
    }
}
