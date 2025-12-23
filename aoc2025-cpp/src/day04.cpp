#include <format>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

#include "utils.hpp"

namespace day04 {
    constexpr std::array<std::array<int, 2>, 8> directions = {
        {

            {0, 1},
            {1, 1},
            {1, 0},
            {1, -1},
            {0, -1},
            {-1, -1},
            {-1, 0},
            {-1, 1},
        }
    };

    long part1(const std::vector<std::string> &lines) {
        long result = 0;
        size_t m = lines.size();
        size_t n = lines[0].size();

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                char c = lines[i][j];
                if (c != '@') {
                    continue;
                }
                int count = 0;
                for (size_t k = 0; k < 8; ++k) {
                    int newx = static_cast<int>(i) + directions[k][0];
                    int newy = static_cast<int>(j) + directions[k][1];
                    if (newx >= 0 && newx < static_cast<int>(m) && newy >= 0 && newy < static_cast<int>(n)
                        && lines[static_cast<size_t>(newx)][static_cast<size_t>(newy)] == '@') {
                        count++;
                    }
                }
                if (count < 4) {
                    result++;
                }
            }
        }

        return result;
    }


    long part2(const std::vector<std::string> &lines) {
        size_t m = lines.size();
        size_t n = lines[0].size();
        std::vector<std::string> mutableLines = lines;
        long result = 0;
        while (true) {
            std::vector<std::array<size_t, 2> > removed_list;
            for (size_t i = 0; i < m; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    char c = mutableLines[i][j];
                    if (c != '@') {
                        continue;
                    }
                    int count = 0;
                    for (size_t k = 0; k < 8; ++k) {
                        int newx = static_cast<int>(i) + directions[k][0];
                        int newy = static_cast<int>(j) + directions[k][1];
                        if (newx >= 0 && newx < static_cast<int>(m) && newy >= 0 && newy < static_cast<int>(n)
                            && mutableLines[static_cast<size_t>(newx)][static_cast<size_t>(newy)] == '@') {
                            count++;
                        }
                    }
                    if (count < 4) {
                        removed_list.push_back({i, j});
                    }
                }
            }
            for (size_t i = 0; i < removed_list.size(); ++i) {
                mutableLines[removed_list[i][0]][removed_list[i][1]] = '.';
            }
            result += removed_list.size();
            if (removed_list.empty()) {
                break;
            }
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
} // namespace day04
