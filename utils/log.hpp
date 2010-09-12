/*
 * log.hpp
 *
 *  Created on: Aug 26, 2008
 *      Author: mikosz
 */

#ifndef LOG_HPP_
#define LOG_HPP_

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/noncopyable.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace CoconutEngine
{

struct LogLevel
{
    static enum LogLevel_
    {
        TRACE = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,

        NONE = 5
    } level_;
};

class FileOutputStream
{
public:

    FileOutputStream();

    ~FileOutputStream();

    template <class T>
    FileOutputStream& operator<< (const T& value)
    {
        boost::mutex::scoped_lock(mutex_);
        file_ << value;
        file_.flush();
        return *this;
    }

private:

    std::ofstream file_;

    boost::mutex mutex_;

};

class StdoutStream
{
public:

    template <class T>
    StdoutStream& operator<< (const T& value)
    {
        mutex_.lock();
        std::cout << value;
        std::cout.flush();
        mutex_.unlock();
        return *this;
    }

private:

    boost::mutex mutex_;

};

#ifdef LOG_OUTPUT_STREAM
typedef LOG_OUTPUT_STREAM logOutputStream;
#else
typedef StdoutStream LogOutputStream;
#endif

class Log : boost::noncopyable
{
public:

    LogLevel::LogLevel_ getLogLevel()
    {
        return LogLevel::level_;
    }

    void setLogLevel(LogLevel::LogLevel_ level)
    {
        LogLevel::level_ = level;
    }

    LogOutputStream& getOutputStream()
    {
        return outputStream_;
    }

    static Log& instance();

private:

    static Log* instance_;

    Log()
    {}

    LogOutputStream outputStream_;

};

} // namespace CoconutEngine

#define SET_LOG_LEVEL(level__)                                  \
    CoconutEngine::Log::instance()                              \
        .setLogLevel(level__)

const char LOG_CONTEXT__[] = "NO_CONTEXT";

#define SET_LOG_CONTEXT(context__)                              \
    const char LOG_CONTEXT__[] = context__

#define LOG(level__, levelString__)                             \
    {                                                           \
        if(CoconutEngine::Log::instance()                       \
            .getLogLevel() <= level__)                          \
        {                                                       \
            std::stringstream LOG_STREAM;                       \
            LOG_STREAM << levelString__ << LOG_CONTEXT__        \
                << ": "

#define LOG_END                                                 \
            '\n';                                               \
            CoconutEngine::Log::instance()                      \
                .getOutputStream() <<                           \
                LOG_STREAM.str();                               \
        }                                                       \
    }

#define LOG_TRACE LOG(LogLevel::TRACE, "[TRACE] ")
#define LOG_DEBUG LOG(LogLevel::DEBUG, "[DEBUG] ")
#define LOG_INFO LOG(LogLevel::INFO, "[INFO] ")
#define LOG_WARN LOG(LogLevel::WARN, "[WARN] ")
#define LOG_ERROR LOG(LogLevel::ERROR, "[ERROR] ")

#endif /* LOG_HPP_ */
