//
// Created by Fabian Simon on 28.11.23.
//

#ifndef GREPY_LOGGER_H
#define GREPY_LOGGER_H

#include <iostream>

#include "common.h"

enum LogType {
    NEUTRAL,
    SUCCESS,
    WARNING,
    ERROR,
};

class Logger {
private:
    static void log(const std::string& message, LogType type);

public:
    inline static void log_neutral(const std::string& message) {
        log(message, LogType::NEUTRAL);
    };
    inline static void log_success(const std::string& message) {
        log(message, LogType::SUCCESS);
    };
    inline static void log_warning(const std::string& message) {
        log(message, LogType::WARNING);
    };
    inline static void log_error(const std::string& message) {
        log(message, LogType::ERROR);
    };
    inline static void log_debug(const std::string& message) {
        if (DEBUG_ENABLED) log(message, LogType::WARNING);
    };
};


#endif //GREPY_LOGGER_H
