/*
 * actiondispatcher.cpp
 *
 *  Created on: 2010-01-26
 *      Author: mikosz
 */

#include <actiondispatcher.hpp>
#include <action.hpp>

namespace coconutengine {

ActionDispatcher* ActionDispatcher::instance_ = 0;

ActionDispatcher::ActionDispatcher() {
}

ActionDispatcher& ActionDispatcher::instance() {
    if (!instance_) {
        instance_ = new ActionDispatcher();
    }
    return *instance_;
}

ActionId ActionDispatcher::registerAction(boost::shared_ptr<Action> action) {
    ActionId actionId = reinterpret_cast<ActionId> (&*action);
    actions_.insert(std::make_pair(actionId, action));
    return actionId;
}

void ActionDispatcher::unregisterAction(ActionId actionId) {
    actions_.erase(actionId);
}

void ActionDispatcher::dispatch(Milliseconds delta) {
    std::map<ActionId, boost::shared_ptr<Action> >::iterator it = actions_.begin(), end = actions_.end(), eraser;
    while (it != end) {
        if (it->second->complete()) {
            eraser = it++;
            actions_.erase(eraser);
        } else {
            (it++)->second->update(delta);
        }
    }
}

}
