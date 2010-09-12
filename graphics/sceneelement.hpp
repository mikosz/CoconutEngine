/*
 * sceneelement.hpp
 *
 *  Created on: 2010-08-23
 *      Author: mikosz
 */

#ifndef SCENEELEMENT_HPP_
#define SCENEELEMENT_HPP_

#include "graphics/camera.hpp"
#include "utils/rectangle.hpp"
#include "utils/vector.hpp"

namespace CoconutEngine {

class SceneElement {
public:

    virtual ~SceneElement() {
    }

    const Rectangle<Vec3D> boundingBox() const {
        return boundingBox_;
    }

    virtual void render() const = 0;

protected:

    SceneElement();

    Rectangle<Vec3D> boundingBox_;

};

} // namespace CoconutEngine

#endif /* SCENEELEMENT_HPP_ */
