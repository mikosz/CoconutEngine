/*
 * actiondispatcher.hpp
 *
 *  Created on: 2010-01-26
 *      Author: mikosz
 */

#ifndef ACTIONDISPATCHER_HPP_
#define ACTIONDISPATCHER_HPP_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <timemanager.hpp>

namespace CoconutEngine {

class Action;

typedef size_t ActionId;

class ActionDispatcher: boost::noncopyable {
public:

    static ActionDispatcher& instance();

    ActionId registerAction(boost::shared_ptr<Action> action);

    void unregisterAction(ActionId actionId);

    void dispatch(Milliseconds delta);

private:

    static ActionDispatcher* instance_;

    std::map<size_t, boost::shared_ptr<Action> > actions_;

    ActionDispatcher();

};

}

#endif /* ACTIONDISPATCHER_HPP_ */
