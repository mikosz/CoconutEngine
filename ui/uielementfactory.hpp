/*
 * uielementfactory.hpp
 *
 *  Created on: Nov 26, 2008
 *      Author: mikosz
 */

#ifndef UIELEMENTFACTORY_HPP_
#define UIELEMENTFACTORY_HPP_

#include <boost/noncopyable.hpp>
#include <string>

namespace CoconutEngine
{

template <class> class Settings;

class UiElement;

class UiElementFactory : boost::noncopyable
{
public:

    static UiElementFactory& instance();

    UiElement& produce(const std::string& name, const Settings<std::string>& settings, const std::string& prefix);

private:

    static UiElementFactory* instance_;

    UiElementFactory();

};

}

#endif /* UIELEMENTFACTORY_HPP_ */
