/*
 * uielementfactory.cpp
 *
 *  Created on: Nov 26, 2008
 *      Author: mikosz
 */

#include <uielementfactory.hpp>

using namespace CoconutEngine;

UiElementFactory* UiElementFactory::instance_ = 0;

UiElementFactory& UiElementFactory::instance()
{
    if(!instance_)
    {
        instance_ = new UiElementFactory();
    }
    return *instance_;
}

UiElementFactory::UiElementFactory()
{}

UiElement& produce(const std::string& name, const Settings<std::string>& settings, const std::string& prefix)
{
    throw "";
}
