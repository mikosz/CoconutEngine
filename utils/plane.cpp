/*
 * plane.cpp
 *
 *  Created on: Dec 9, 2008
 *      Author: mikosz
 */

#include <plane.hpp>

using namespace coconutengine;

Plane::Plane(float a, float b, float c, float d) :
    a(a),
    b(b),
    c(c),
    d(d)
{}

Plane::Face Plane::faces(const Vec3D& point) const
{
    float result = a * point.x() + b * point.y() + c * point.z() + d;
    if(result < 0) return BACK;
    if(result > 0) return FRONT;
    return IN;
}
