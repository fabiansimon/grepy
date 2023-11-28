//
// Created by Fabian Simon on 28.11.23.
//

#include "logger.h"

// ANSI colors
#define COLOR_RED     "\x1b[31m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

void Logger::log(const std::string &message, LogType type) {
    switch (type) {
        case LogType::NEUTRAL: {
            std::cout << COLOR_RESET << message << std::endl;
            break;
        }
        case LogType::SUCCESS: {
            std::cout << COLOR_GREEN << message << COLOR_RESET << std::endl;
            break;
        }
        case LogType::WARNING: {
            std::cout << COLOR_YELLOW << message << COLOR_RESET << std::endl;
            break;
        }
        case LogType::ERROR: {
            std::cout << COLOR_RED << message << COLOR_RESET << std::endl;
            break;
        }
    }
}
