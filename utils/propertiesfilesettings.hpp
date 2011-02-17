/*
 * propertiesfilesettings.h
 *
 *  Created on: Oct 6, 2008
 *      Author: mikosz
 */

#ifndef PROPERTIESFILESETTINGS_HPP_
#define PROPERTIESFILESETTINGS_HPP_

#include <string>
#include <boost/filesystem.hpp>
#include <loki/AssocVector.h>
#include <settings.hpp>

namespace coconutengine
{

class PropertiesFileSettings : public Settings<std::string>
{
public:

    PropertiesFileSettings(const boost::filesystem::path& propertiesFilePath);

    boost::any get(const std::string& arg) const;

    boost::any get(const std::string& arg, boost::any defaultValue) const;

private:

    typedef Loki::AssocVector<std::string, boost::any> PropertyMap;
    PropertyMap properties_;

};

}

#endif /* PROPERTIESFILESETTINGS_HPP_ */
