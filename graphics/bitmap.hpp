/*
 * bitmap.hpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include <istream>

#include <boost/filesystem.hpp>

#include "image.hpp"

namespace coconutengine {

class Bitmap: public Image {
public:

    explicit Bitmap(const boost::filesystem::path& filename);

    explicit Bitmap(std::istream& inputStream);

private:

    void load(std::istream& inputStream);

};

} // namespace coconutengine

#endif /* BITMAP_HPP_ */
