#include "parse_file.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::unordered_map<std::string, double>
process_config(const std::string &filename) {
    std::unordered_map<std::string, double> configuration_parameters = {
        {"init_steps_x", 100}, {"init_steps_y", 100}, {"abs_err", 0.000005},
        {"rel_err", 0.0002},   {"max_iter", 20},
    };
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        exit(Unable_To_Open_Configuration_File);
    }
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream is_line(line);
        std::string key;
        double value{};
        if (std::getline(is_line, key, '=')) {
            if (is_line >> value) {
                configuration_parameters[key] = value;
            } else {
                is_line.clear();
            }
        }
    }
    return configuration_parameters;
}
