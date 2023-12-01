#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

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

    // text based
    return input_line.find(pattern) != std::string::npos;

    throw std::runtime_error("Unhandled pattern " + pattern);
}

bool is_file(const std::string& input_line) {
    try {
        std::filesystem::path file_path(input_line);
        return !file_path.empty() && file_path.has_filename();
    } catch (const std::exception& e) {
        return false;
    }
}

std::vector<std::string> read_lines(const std::string& file_name) {
    std::vector<std::string> total_lines;

    std::ifstream input_file(file_name);

    if (!input_file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    std::string line;
    while (std::getline(input_file, line)) {
        total_lines.push_back(line);
    }

    input_file.close();

    return total_lines;
}

void report_results(const std::vector<std::string>& results) {
    for (const std::string& result : results) {
        Logger::log_neutral(result);
    }
    Logger::log_debug("Success");
}

void report_results(const std::string& result) {
    Logger::log_neutral(result);
}

int main(int argc, char* argv[]) {
    // Logger::log_debug("Logs from your program will appear here");

    if (argc < 2) {
        Logger::log_error("Expected at least two arguments");
        return 1;
    }

    std::string pattern_arg;

    for (int i = 1; i < argc; ++i) {
        // Logger::log_success(argv[i]);
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
        // if input is a file
        if (is_file(input_line)) {
            std::vector<std::string> total_lines = read_lines(input_line);
            std::vector<std::string> matching_lines;

            for (int i = 0; i < total_lines.size(); i++) {
                std::string line = total_lines[i];
                if (match_pattern(line, pattern)) {
                    matching_lines.push_back(std::to_string(i+1) + ": " + line);
                }
            }

            report_results(matching_lines);
            return 0;
        }

        // if input is a string
        if (match_pattern(input_line, pattern)) {
            report_results(input_line);
            return 0;
        }

        // failure
        Logger::log_debug("Failure");
        return 1;

    } catch (const std::runtime_error& e) {
        Logger::log_error(e.what());
        return 1;
    }
}

