/*
 * frustum.hpp
 *
 *  Created on: Dec 9, 2008
 *      Author: mikosz
 */

#ifndef FRUSTUM_HPP_
#define FRUSTUM_HPP_

#include <plane.hpp>
#include <vector.hpp>
#include <rectangle.hpp>
#include <vector>

namespace coconutengine {

class Frustum {
public:

    enum {
        NEAR, FAR, TOP, BOTTOM, LEFT, RIGHT
    };

    enum Containment {
        OUT, IN, INTERSECT
    };

    Frustum(const Plane& near, const Plane& far, const Plane& top, const Plane& bottom, const Plane& left,
            const Plane& right);

    Containment contains(const Vec3D& point) const;

    Containment contains(const Rectangle<Vec3D> box) const;

    std::vector<Plane>& planes() {
        return planes_;
    }

    const std::vector<Plane>& planes() const {
        return planes_;
    }

private:

    std::vector<Plane> planes_;

};

} // namespace coconutengine

#endif /* FRUSTUM_HPP_ */
