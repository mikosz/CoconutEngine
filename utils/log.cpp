/*
 * log.cpp
 *
 *  Created on: Aug 28, 2008
 *      Author: mikosz
 */

#include <log.hpp>

using namespace coconutengine;

namespace
{
    const char LOG_FILENAME[] = "coconutengine.log";
}

LogLevel::LogLevel_ LogLevel::level_ = NONE;
Log* Log::instance_ = 0;

Log& Log::instance()
{
    if(!instance_)
    {
        instance_ = new Log();
    }
    return *instance_;
}

FileOutputStream::FileOutputStream() :
    file_(LOG_FILENAME, std::ios::ate)
{}

FileOutputStream::~FileOutputStream()
{
    file_.close();
}
