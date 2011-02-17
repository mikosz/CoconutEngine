/*
 * plane.hpp
 *
 *  Created on: Dec 9, 2008
 *      Author: mikosz
 */

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include <vector.hpp>

namespace coconutengine
{

class Plane
{
public:

    float a, b, c, d;

    Plane() {
    }

    Plane(float a, float b, float c, float d);

    enum Face
    {
        FRONT,
        BACK,
        IN
    };

    Face faces(const Vec3D& point) const;

};

} // namespace coconutengine

#endif /* PLANE_HPP_ */
