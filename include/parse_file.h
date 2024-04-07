#pragma once

#ifndef INTEGRATE_SERIAL_PARSE_FILE_H
#define INTEGRATE_SERIAL_PARSE_FILE_H

#include <string>
#include <unordered_map>

std::unordered_map<std::string, double>
process_config(const std::string &filename);

#endif // INTEGRATE_SERIAL_PARSE_FILE_H
