/*
 * propertiesfilesettings.cpp
 *
 *  Created on: Oct 6, 2008
 *      Author: mikosz
 */

#include <propertiesfilesettings.hpp>

#include <vector>
#include <algorithm>
#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <log.hpp>

using namespace CoconutEngine;

namespace fs = boost::filesystem;

namespace
{
const boost::regex emptyLineRegex("^(\\s*)|(\\s*#.*)$");
const boost::regex settingsLineRegex("^(\\S+)\\s+([^=]+)=(.*)$");

boost::any string2Any(const std::string& type, const std::string& value)
{
    if(type == "string") return value;
    if(type == "uint") return boost::lexical_cast<unsigned int>(value);
    if(type == "float") return boost::lexical_cast<float>(value);
    if(type == "bool")
    {
        if(value == "true") return static_cast<bool>(true);
        if(value == "false") return static_cast<bool>(false);
        return boost::lexical_cast<bool>(value);
    }

    throw std::runtime_error("Unknown property type");
}

} // anonymous namespace

PropertiesFileSettings::PropertiesFileSettings(const fs::path& propertiesFilePath)
{
    SET_LOG_CONTEXT("PropertiesFileSettings::PropertiesFileSettings");

    fs::ifstream propertiesFile(propertiesFilePath, std::ios::in);

    LOG_INFO << "Reading properties file " << propertiesFilePath << LOG_END;

    std::string line;
    boost::smatch matches;
    while(propertiesFile.good())
    {
        std::getline(propertiesFile, line);
        if(!boost::regex_match(line, emptyLineRegex))
        {
            try
            {
                if(!boost::regex_match(line, matches, settingsLineRegex))
                    throw std::runtime_error("Failed to parse line");
                std::string value;
                if(matches.size() == 4) value = matches[3];
                properties_.insert(std::make_pair(matches[2], string2Any(matches[1], value)));
                LOG_DEBUG << "Inserted property " << matches[2]
                    << "\n\ttype: " << matches[1] << "\n\tvalue: " << value << LOG_END;
            }
            catch(const std::exception& e)
            {
                LOG_WARN << "Caught: \"" << e.what() << "\" when parsing line \""
                    << line << "\"" << LOG_END;
            }
        }
    }

    LOG_INFO << "Read " << properties_.size() << " properties." << LOG_END;
}

boost::any PropertiesFileSettings::get(const std::string& arg) const
{
    PropertyMap::const_iterator it = properties_.find(arg);
    if(it != properties_.end())
        return it->second;
    throw std::runtime_error("Property " + arg + " not found");
}

boost::any PropertiesFileSettings::get(const std::string& arg, boost::any defaultValue) const
{
    PropertyMap::const_iterator it = properties_.find(arg);
    if(it != properties_.end())
        return it->second;
    return defaultValue;
}
