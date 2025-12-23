#include "day01.hpp"

#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

namespace day01 {
int part1(const std::vector<std::string>& lines) {
    int result{0};
    int cur = {50};
    for (const auto& line : lines) {
        char first_char = line.front();
        std::string_view number_view(line.data() + 1, line.size() - 1);
        int number = std::stoi(std::string(number_view));
        switch (first_char) {
            case 'L': {
                int t = (cur - number) % 100;
                if (t < 0) {
                    cur = 100 + t;
                } else {
                    cur = t;
                }
                break;
            }
            case 'R':
                cur = (cur + number) % 100;
                break;
        }
        if (cur == 0) {
            result++;
        }
    }

    return result;
}

int part2(const std::vector<std::string>& lines) {
    int result{0};
    int cur{50};

    auto get_floor = [](int val) { return val >= 0 ? val / 100 : (val - 99) / 100; };

    for (const auto& line : lines) {
        char first_char = line.front();
        std::string_view number_view(line.data() + 1, line.size() - 1);
        int number = std::stoi(std::string(number_view));
        switch (first_char) {
            case 'L': {
                int next_cur = cur - number;
                result += get_floor(cur - 1) - get_floor(next_cur - 1);
                cur = next_cur;
                break;
            }
            case 'R': {
                int next_cur = cur + number;
                result += get_floor(next_cur) - get_floor(cur);
                cur = next_cur;
                break;
            }
        }
    }
    return static_cast<int>(result);
}

void run(const std::string& input) {
    std::vector<std::string> lines = split_lines(input, '\n');
    int p1 = part1(lines);
    const auto p2 = part2(lines);
    std::cout << "part1: " << p1 << "\n";
    std::cout << "part2: " << p2 << "\n";
}
}  // namespace day01
