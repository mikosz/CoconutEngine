/*
 * utility.hpp
 *
 *  Created on: Nov 24, 2008
 *      Author: mikosz
 */

#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <algorithm>

namespace coconutengine
{

const float PI = 3.14159265f;

template <class L, class R>
L min(L lhs, R rhs) {
    return lhs < rhs ? lhs : rhs;
}

template <class L, class R>
L max(L lhs, R rhs) {
    return lhs < rhs ? rhs : lhs;
}

template <class V, class B, class T>
V clamp(V value, B bottom, T top)
{
    return min(max(value,bottom), top);
}

inline float toDegrees(float radians)
{
    return 180.0f * radians / PI;
}

} // namespace CoconuteEngine

#endif /* UTILITY_HPP_ */
