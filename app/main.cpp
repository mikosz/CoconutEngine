/*
 * main.cpp
 *
 *  Created on: Aug 26, 2008
 *      Author: mikosz
 */

#include <core.hpp>
#include <exception>

#define LOG_OUTPUT_STREAM StdoutStream
#include <log.hpp>

using namespace CoconutEngine;

int main() {
    SET_LOG_LEVEL(LogLevel::DEBUG);
    SET_LOG_CONTEXT("main");

    try {
        Core::instance().loop();
    } catch (const std::exception& e) {
        LOG_ERROR   << "Caught exception: " << e.what() << LOG_END;
    }

    return 0;
}
