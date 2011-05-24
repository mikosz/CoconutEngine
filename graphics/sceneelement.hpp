/*
 * sceneelement.hpp
 *
 *  Created on: 2010-08-23
 *      Author: mikosz
 */

#ifndef SCENEELEMENT_HPP_
#define SCENEELEMENT_HPP_

#include <string>
#include <limits>

#include <boost/enable_shared_from_this.hpp>

#include "rectangle.hpp"
#include "vector.hpp"
#include "renderpipeline.hpp"

namespace coconutengine {

template <class > class Settings;

class Camera;

class SceneElement : public boost::enable_shared_from_this<SceneElement> {
public:

    virtual ~SceneElement() {
    }

    const Rectangle<Vec3D> boundingBox() const {
        return boundingBox_;
    }

    void render(const Camera& camera) const;

protected:

    RenderPipeline::ElementID id_;

    Rectangle<Vec3D> boundingBox_;

    SceneElement(bool drawBoundingBox) :
        id_(0), boundingBox_(Vec3D(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max()), Vec3D(-std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max())),
                drawBoundingBox_(drawBoundingBox) {
    }

    virtual void doRender(const Camera& camera) const = 0;

    void renderBoundingBox(const Camera& camera) const;

private:

    bool drawBoundingBox_;

};

} // namespace coconutengine

#endif /* SCENEELEMENT_HPP_ */
