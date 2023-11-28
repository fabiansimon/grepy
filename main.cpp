#include <iostream>
#include <string>

#include "logger.h"

int count_digits(const std::string& input) {
    int count = 0;
    for (const char& c : input) {
        if (isdigit(c)) count++;
    }

    return count;
}

int count_alphanum(const std::string& input) {
    int count = 0;
    for (const char& c : input) {
        if (isalnum(c)) count++;
    }

    return count;
}

bool match_pattern(const std::string& input_line, const std::string& pattern) {
    if (pattern.length() == 1) {
        return input_line.find(pattern) != std::string::npos;
    }

    if (pattern.length() == 0) {
        throw std::runtime_error("Must include a pattern");
    }

    // Character classes
    if (pattern.at(0) == '\\' && isalpha(pattern.at(1))) {
        char c = pattern[1];
        switch (c) {
            case 'd': {
                return count_digits(input_line) > 0;
            }
            case 'w': {
                return count_alphanum(input_line) > 0;
            }
            default: {
                return false;
            }
        }
    }

    throw std::runtime_error("Unhandled pattern " + pattern);
}

int main(int argc, char* argv[]) {
    // You can use print statements as follows for debugging, they'll be visible when running tests.
    // Logger::log_debug("Logs from your program will appear here");

    if (argc < 2) {
        Logger::log_error("Expected at least two arguments");
        return 1;
    }

    std::string pattern_arg;

    for (int i = 1; i < argc; ++i) {
        Logger::log_success(argv[i]);
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        Logger::log_error("Expected first argument to be '-E'");
        return 1;
    }

    std::string input_line;
    std::getline(std::cin, input_line);

    try {
        if (match_pattern(input_line, pattern)) {
            Logger::log_debug("Success");
            return 0;
        } else {
            Logger::log_debug("Failure");
            return 1;
        }

    } catch (const std::runtime_error& e) {
        Logger::log_error(e.what());
        return 1;
    }
}

