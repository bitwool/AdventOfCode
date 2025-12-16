#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "day01.hpp"
#include "day02.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        std::cerr << "usage: aoc2025 <day> [input_path]\n";
        return 1;
    }
    int day = std::stoi(argv[1]);

    std::filesystem::path inputPath;
    char buf[16];
    std::snprintf(buf, sizeof(buf), "day%02d.txt", day);
    inputPath = std::filesystem::path("inputs") / buf;
    std::string input = read_file(inputPath);
    if (input.empty()) {
        std::cerr << "failed to read input: " << inputPath << "\n";
        return 1;
    }

    if (day == 1) {
        day01::run(input);
    } else if (day == 2) {
        day02::run(input);
    } else {
        return 1;
    }
    return 0;
}
