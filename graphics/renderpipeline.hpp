#ifndef RENDERPIPELINE_HPP_
#define RENDERPIPELINE_HPP_

#include <map>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace coconutengine {

class SceneElement;
class Camera;

class RenderPipeline : boost::noncopyable {
public:

    typedef size_t ElementID;

    static RenderPipeline& instance();

    ElementID addSceneElement(boost::shared_ptr<SceneElement> element);

    void render(const Camera& camera) const;

private:

    RenderPipeline();

    std::map<ElementID, boost::shared_ptr<SceneElement> > elements_;

};

} // namespace coconutengine

#endif /* RENDERPIPELINE_HPP_ */
