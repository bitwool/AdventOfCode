#pragma once
#include <string>
#include <vector>
#include <filesystem>

std::vector<std::string> split_lines(const std::string& input, char delimiter);
std::string read_file(const std::filesystem::path& p);
long power(const int a, const int b);