#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "utils.hpp"

namespace day07 {
    long part1(const std::vector<std::string> &lines) {
        long result{0};

        const size_t width = lines[0].size();

        std::vector<char> last_line(lines[0].begin(), lines[0].end());
        for (size_t i = 1; i < lines.size(); ++i) {
            std::vector<char> curr_line(width);

            for (size_t j = 0; j < width; ++j) {
                char c = lines[i][j];
                if (c == '^') {
                    if (last_line[j] == '.') {
                        curr_line[j] = '^';
                    } else if (last_line[j] == '|' || last_line[j] == 'S') {
                        result++;
                        curr_line[j - 1] = '|';
                        curr_line[j] = '^';
                        if (j + 1 < width) {
                            curr_line[j + 1] = '|';
                        }
                    }
                } else if (c == '.') {
                    if (last_line[j] == '.' && curr_line[j] == '.') {
                        curr_line[j] = '.';
                    } else if (last_line[j] == '|' || last_line[j] == 'S') {
                        curr_line[j] = '|';
                    }
                }
            }
            last_line = curr_line;
        }


        return result;
    }


    long count_timelines(size_t r, size_t c, const std::vector<std::string> &grid,
                         std::vector<std::vector<long> > &memo) {
        if (r >= grid.size() || c >= grid[0].size()) {
            return 1;
        }

        if (memo[r][c] != -1) {
            return memo[r][c];
        }

        for (size_t curr_r = r; curr_r < grid.size(); ++curr_r) {
            char cell = grid[curr_r][c];

            if (cell == '^') {
                long left_paths = count_timelines(curr_r + 1, c - 1, grid, memo);
                long right_paths = count_timelines(curr_r + 1, c + 1, grid, memo);

                memo[r][c] = left_paths + right_paths;
                return memo[r][c];
            }
        }

        memo[r][c] = 1;
        return 1;
    }

    long part2(const std::vector<std::string> &lines) {
        const size_t rows = lines.size();
        const size_t width = lines[0].size();
        std::vector memo(rows, std::vector<long>(width, -1));
        const size_t s_index = lines[0].find('S');
        return count_timelines(0, s_index, lines, memo);
    }

    void run(const std::string &input) {
        std::vector<std::string> lines = split_lines(input, '\n');

        const auto p1 = part1(lines);
        std::cout << "part1: " << p1 << "\n";
        const auto p2 = part2(lines);
        std::cout << "part2: " << p2 << "\n";
    }
} // namespace day07
