/*
 * bitmap.cpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#include <bitmap.hpp>

#include <fstream>
#include <stdexcept>
#include <log.hpp>

using namespace CoconutEngine;

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
        throw std::runtime_error("While loading " + filename + ": " + e.what());
    }
    file.close();
}

Bitmap::Bitmap(std::istream& inputStream) {
    load(inputStream);
}

void Bitmap::load(std::istream& inputStream) {
    SET_LOG_CONTEXT("Bitmap::Load");

    uint16_t header = read<uint16_t> (inputStream);
    if (header != BMP_HEADER) {
        throw std::runtime_error("Not a valid bitmap");
    }

    inputStream.ignore(8);
    uint32_t offset = read<uint32_t> (inputStream);
    if (read<uint32_t> (inputStream) != WINDOWS_V3_BITMAP) {
        throw std::runtime_error("Not a windows V3 bitmap");
    }

    width_ = read<uint32_t> (inputStream);
    height_ = read<uint32_t> (inputStream);
    inputStream.ignore(2);
    uint16_t bpp = read<uint16_t> (inputStream);

    if (bpp % 8) {
        throw std::runtime_error("Bits per pixel must by a multiple of 8");
    }
    if (read<uint16_t> (inputStream)) {
        throw std::runtime_error("Compressed bitmaps not supported");
    }

    inputStream.seekg(offset, std::ios_base::beg);

    pixels_.reset(new unsigned char[width_ * height_]);

    size_t bytesPerRow = width_ * (bpp / 8);
    size_t padding = 8 - (bytesPerRow % 8);
    if (padding == 8)
        padding = 0;

    for (size_t row = 0; row < height_; ++row) {
        inputStream.read(reinterpret_cast<char*> (pixels_.get() + (row * bytesPerRow)), bytesPerRow);
        inputStream.ignore(padding);
    }

    LOG_DEBUG   << "Loaded a " << width_ << "x" << height_ << " bitmap" << LOG_END;
}
