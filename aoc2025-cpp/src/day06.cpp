#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "utils.hpp"

namespace day06 {
    long long calculate_result_part1(const std::vector<std::string> &lines, size_t start, size_t end, char sign) {
        long long result = sign == '*' ? 1 : 0;
        for (size_t i = 0; i < lines.size() - 1; ++i) {
            long long t = 0;
            for (size_t j = start; j <= end && j < lines[i].size(); ++j) {
                if (lines[i][j] == ' ') {
                    continue;
                }
                t = t * 10 + lines[i][j] - '0';
            }
            if (sign == '*') {
                result *= t;
            } else {
                result += t;
            }
        }
        return result;
    }

    long long calculate_result_part2(const std::vector<std::string> &lines, size_t start, size_t end, char sign) {
        long long result = sign == '*' ? 1 : 0;
        for (size_t i = start; i <= end; ++i) {
            long long t = 0;
            for (size_t j = 0; j < lines.size() - 1; ++j) {
                if (lines[j].size() < i + 1) {
                    continue;
                }
                if (lines[j][i] == ' ') {
                    continue;
                }
                t = t * 10 + lines[j][i] - '0';
            }
            if (sign == '*') {
                result *= t;
            } else {
                result += t;
            }
        }
        return result;
    }

    long long common(const std::vector<std::string> &lines, int part) {
        const size_t line_cnt = lines.size();
        size_t max_width{0};
        for (const auto &line: lines) {
            max_width = std::max(max_width, line.size());
        }
        const size_t sign_line_width = lines[line_cnt - 1].size();

        long long result{0};
        size_t start = 0;
        char sign = lines[line_cnt - 1][0];
        for (size_t i = 1; i < sign_line_width; ++i) {
            if (lines[line_cnt - 1][i] != ' ') {
                long long t;
                if (part == 1) {
                    t = calculate_result_part1(lines, start, i - 2, sign);
                } else {
                    t = calculate_result_part2(lines, start, i - 2, sign);
                }
                result += t;
                sign = lines[line_cnt - 1][i];
                start = i;
            }
        }

        long long t;
        if (part == 1) {
            t = calculate_result_part1(lines, start, max_width - 1, sign);
        } else {
            t = calculate_result_part2(lines, start, max_width - 1, sign);
        }

        result += t;
        return result;
    }

    long long part1(const std::vector<std::string> &lines) {
        return common(lines, 1);
    }


    long long part2(const std::vector<std::string> &lines) {
        return common(lines, 2);
    }

    void run(const std::string &input) {
        std::vector<std::string> lines = split_lines(input, '\n');

        const auto p1 = part1(lines);
        std::cout << "part1: " << p1 << "\n";
        const auto p2 = part2(lines);
        std::cout << "part2: " << p2 << "\n";
    }
} // namespace day06
