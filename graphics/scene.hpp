/*
 * scene.hpp
 *
 *  Created on: 2010-09-06
 *      Author: mikosz
 */

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <boost/shared_ptr.hpp>

#include "sceneelement.hpp"
#include "octree.hpp"

namespace CoconutEngine {

class Scene {

    typedef Octree<boost::shared_ptr<SceneElement> > Octree;

public:

    typedef Octree::Iterator Iterator;

    Iterator insert(boost::shared_ptr<SceneElement> element);

private:

    Octree elements_;

};

} // namespace CoconutEngine

#endif /* SCENE_HPP_ */
