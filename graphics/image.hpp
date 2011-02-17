/*
 * image.hpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <boost/scoped_array.hpp>

namespace coconutengine
{

class Image
{
public:

    virtual ~Image() {}

    const unsigned char* pixels() const { return pixels_.get(); }

    size_t width() const { return width_; }

    size_t height() const { return height_; }

protected:

    Image() {}

    boost::scoped_array<unsigned char> pixels_;

    size_t width_;

    size_t height_;

};

} // namespace coconutengine

#endif /* IMAGE_HPP_ */
