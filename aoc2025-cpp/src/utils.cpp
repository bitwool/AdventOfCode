#include "utils.hpp"
#include <sstream>
#include <fstream>

std::vector<std::string> split_lines(const std::string &input, char delimiter) {
    std::vector<std::string> lines;
    std::stringstream ss(input);
    std::string line;
    while (std::getline(ss, line, delimiter)) {
        lines.push_back(line);
    }
    return lines;
}

std::string read_file(const std::filesystem::path &p) {
    std::ifstream in(p);
    if (!in) {
        return ""; // Return empty string if file cannot be opened
    }
    // Read the entire file content into a string
    return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}

long power(const int a, const int b) {
    long result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}
