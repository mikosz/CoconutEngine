/*
 * actor.hpp
 *
 *  Created on: Sep 10, 2008
 *      Author: mikosz
 */

#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <deque>
#include <boost/shared_ptr.hpp>

#include <vector.hpp>
#include <timemanager.hpp>
#include <sprite.hpp>
#include <action.hpp>

namespace coconutengine {

class Actor {
public:

    typedef std::deque<boost::shared_ptr<Action> > ActionQueue;

    virtual ~Actor();

    virtual void update(TimeDuration delta) = 0;

    Vec3D& position() {
        return position_;
    }

    Vec3D& rotation() {
        return rotation_;
    }

    ActionQueue& actionQueue() {
        return actionQueue_;
    }

private:

    boost::shared_ptr<Sprite> sprite_;

    Vec3D position_;

    Vec3D rotation_;

    ActionQueue actionQueue_;

};

}

#endif /* ACTOR_HPP_ */
