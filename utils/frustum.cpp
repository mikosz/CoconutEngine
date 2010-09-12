/*
 * frustum.cpp
 *
 *  Created on: Dec 9, 2008
 *      Author: mikosz
 */

#include <frustum.hpp>

using namespace CoconutEngine;

Frustum::Frustum(const Plane& near, const Plane& far, const Plane& top, const Plane& bottom, const Plane& left,
        const Plane& right) :
    planes_(6) {
    planes_[NEAR] = near;
    planes_[FAR] = far;
    planes_[TOP] = top;
    planes_[BOTTOM] = bottom;
    planes_[LEFT] = left;
    planes_[RIGHT] = right;
}

Frustum::Containment Frustum::contains(const Vec3D& point) const {
    for (int i = 0; i < 6; ++i) {
        Plane::Face face = planes_[i].faces(point);
        if (face == Plane::BACK) {
            return OUT;
        } else if (face == Plane::IN) {
            return INTERSECT;
        }
    }
    return IN;
}

Frustum::Containment Frustum::contains(const Rectangle<Vec3D> box) const {
    Vec3D vertices[] = { box.bottomLeft, Vec3D(box.topRight.x(), box.bottomLeft.y(), box.bottomLeft.z()), Vec3D(
            box.topRight.x(), box.bottomLeft.y(), box.topRight.z()), Vec3D(box.bottomLeft.x(), box.bottomLeft.y(),
            box.topRight.z()), Vec3D(box.bottomLeft.x(), box.topRight.y(), box.bottomLeft.z()), Vec3D(box.topRight.x(),
            box.topRight.y(), box.bottomLeft.z()), box.topRight, Vec3D(box.bottomLeft.x(), box.topRight.y(),
            box.topRight.z()) };

    Containment result = IN;

    for (unsigned int plane = 0; plane < 6; ++plane) {
        unsigned int in = 0, out = 0;
        for (unsigned int vertex = 0; vertex < 8; ++vertex) {
            if (planes_[plane].faces(vertices[vertex]) == Plane::BACK) {
                ++out;
            } else {
                ++in;
            }
        }
        if (!in) {
            return OUT;
        }
        if (out) {
            result = INTERSECT;
        }
    }

    return result;
}
