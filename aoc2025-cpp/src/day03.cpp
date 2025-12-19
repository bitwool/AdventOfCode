#include "day03.hpp"

#include <format>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

#include "utils.hpp"

namespace day03 {
    std::pair<size_t, int> single_line_range(const std::string &line, size_t start, size_t end) {
        size_t max_idx = start;
        int max = line[start] - '0';
        for (size_t i = start; i <= end; ++i) {
            if (line[static_cast<size_t>(i)] - '0' > max) {
                max = line[i] - '0';
                max_idx = i;
            }
        }
        return {max_idx, max};
    }


    long single_line_max(const std::string &line, const size_t digits) {
        const size_t len = line.length();
        long result{0};
        size_t digits_filled = 0;
        size_t last_idx = 0;
        bool first = true;
        for (size_t i = 0; i < digits; ++i) {
            const size_t start = first ? 0 : last_idx + 1;
            const size_t end = len - (digits - digits_filled);

            auto [max_idx, max] = single_line_range(line, start, end);
            first = false;
            last_idx = max_idx;
            result = result * 10 + max;
            digits_filled++;
        }
        return result;
    }

    long part1(const std::vector<std::string> &lines) {
        long result{0};
        for (const auto &line: lines) {
            result += single_line_max(line, 2);
        }
        return result;
    }


    long part2(const std::vector<std::string> &lines) {
       long result{0};
        for (const auto &line: lines) {
            result += single_line_max(line, 12);
        }
        return result;
    }

    void run(const std::string &input) {
        std::vector<std::string> lines = split_lines(input, '\n');
        const auto p1 = part1(lines);
        const auto p2 = part2(lines);
        std::cout << "part1: " << p1 << "\n";
        std::cout << "part2: " << p2 << "\n";
    }
} // namespace day03
