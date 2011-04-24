/*
 * bitmap.cpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#include <bitmap.hpp>

#include <fstream>
#include <stdexcept>

#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>

#include "log.hpp"

using namespace coconutengine;

namespace {

const uint16_t BMP_HEADER = 0x4D42;

const uint32_t WINDOWS_V3_BITMAP = 40;

template<class T>
T read(std::istream& inputStream) {
    if (!inputStream.good()) {
        throw std::runtime_error("Bad stream state");
    }

    T result;
    inputStream.read(reinterpret_cast<char*> (&result), sizeof(result));
    return result;
}

} // anonymous namespace

Bitmap::Bitmap(const boost::filesystem::path& filename) {
    SET_LOG_CONTEXT("Bitmap::Bitmap");
    LOG_DEBUG   << "Loading bitmap from file " << filename << LOG_END;

    std::ifstream file(filename.string().c_str());
    try {
        load(file);
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("While loading " + filename.string() + ": " + e.what());
    }
    file.close();
}

Bitmap::Bitmap(std::istream& inputStream) {
    load(inputStream);
}

void Bitmap::load(std::istream& inputStream) {
    SET_LOG_CONTEXT("Bitmap::Load");

    boost::uint16_t header = read<boost::uint16_t> (inputStream);
    if (header != BMP_HEADER) {
        throw std::runtime_error("Not a valid bitmap");
    }

    inputStream.ignore(8);
    boost::uint32_t offset = read<boost::uint32_t> (inputStream);
    if (read<boost::uint32_t> (inputStream) != WINDOWS_V3_BITMAP) {
        throw std::runtime_error("Not a windows V3 bitmap");
    }

    width_ = read<boost::uint32_t> (inputStream);
    height_ = read<boost::uint32_t> (inputStream);
    inputStream.ignore(2);
    boost::uint16_t bitsPerPixel = read<boost::uint16_t> (inputStream);

    switch (bitsPerPixel) {
    case 8:
        format_ = Image::GREYSCALE;
        break;
    case 24:
        format_ = Image::RGB;
        break;
    default:
        throw std::runtime_error("Unsupported bpp value: " + boost::lexical_cast<std::string>(bitsPerPixel));
    }

    if (read<uint16_t> (inputStream)) {
        throw std::runtime_error("Compressed bitmaps not supported");
    }

    inputStream.seekg(offset, std::ios_base::beg);

    boost::uint8_t bytesPerPixel = bitsPerPixel / 8;

    pixels_.resize(width_ * height_ * bytesPerPixel);

    size_t bytesInRow = width_ * bytesPerPixel;
    size_t padding = (4 - (bytesInRow % 4)) % 4;

    for (size_t row = 0; row < height_; ++row) {
        inputStream.read(reinterpret_cast<char*> (&pixels_[row * bytesInRow]), bytesInRow);
        inputStream.ignore(padding);
    }

    LOG_DEBUG   << "Loaded a " << width_ << "x" << height_ << " bitmap" << LOG_END;
}
