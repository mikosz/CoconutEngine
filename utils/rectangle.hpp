/*
 * rectangle.hpp
 *
 *  Created on: Nov 5, 2008
 *      Author: mikosz
 */

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <boost/call_traits.hpp>

namespace coconutengine {

/**
 * Represents a rectangle in some space, depending on the PointType.
 * For PointType being a type representing a point in a 2D space, this will be a usual rectangle.
 * In 1D space, this will be a segment. In 3D space - a box.
 */
template <class PointType>
class Rectangle {
public:

    typedef typename boost::call_traits<PointType>::param_type PointParamType;

    PointType bottomLeft, topRight;

    Rectangle() {
    }

    Rectangle(PointType bottomLeft, PointType topRight) :
        bottomLeft(bottomLeft), topRight(topRight) {
    }

    bool contains(PointParamType point) const {
        return point >= bottomLeft && point <= topRight;
    }

    bool contains(const Rectangle<PointType>& rhs) const {
        return contains(rhs.bottomLeft) && contains(rhs.topRight);
    }

    bool intersects(const Rectangle<PointType>& rhs) const {
        return contains(rhs.bottomLeft) || contains(rhs.topRight);
    }

};

}

#endif /* RECTANGLE_HPP_ */
