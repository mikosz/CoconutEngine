/*
 * renderpipeline.cpp
 *
 *  Created on: 2010-09-26
 *      Author: mikosz
 */

#include "renderpipeline.hpp"
#include "sceneelement.hpp"
#include "camera.hpp"

using namespace coconutengine;

namespace {

RenderPipeline::ElementID nextID() {
    static RenderPipeline::ElementID id = 0;
    return ++id;
}

} // anonymous namespace

RenderPipeline::RenderPipeline() {
}

RenderPipeline& RenderPipeline::instance() {
    static RenderPipeline renderPipeline;
    return renderPipeline;
}

RenderPipeline::ElementID RenderPipeline::addSceneElement(boost::shared_ptr<SceneElement> element) {
    ElementID id = nextID();
    elements_.insert(std::make_pair(id, element));
    return id;
}

void RenderPipeline::render(const Camera& camera) const {
    std::map<ElementID, boost::shared_ptr<SceneElement> >::const_iterator it, end = elements_.end();
    for (it = elements_.begin(); it != end; ++it) {
        it->second->render(camera);
    }
}
