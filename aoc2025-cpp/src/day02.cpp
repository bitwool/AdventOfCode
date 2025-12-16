#include "day02.hpp"

#include <format>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

#include "utils.hpp"

namespace day02 {
    std::pair<long, long> parseRange(const std::string &rangeStr) {
        std::stringstream ss(rangeStr);
        long start{0};
        long end{0};
        char dash;
        ss >> start >> dash >> end;
        return {start, end};
    }

    int countDigits(long num) {
        int result = 0;
        while (num > 0) {
            num = num / 10;
            result++;
        }
        return result;
    }

    long isTwiceDuplicate(long number) {
        const int digit = countDigits(number);
        if (digit % 2 != 0) {
            return false;
        }

        long t = power(10, digit / 2);
        long left = number / t;
        long right = number % t;
        return left == right;
    }

    long part1(const std::vector<std::string> &lines) {
        long result{0};
        for (const auto &line: lines) {
            auto [start, end] = parseRange(line);
            for (long i = start; i <= end; i++) {
                if (isTwiceDuplicate(i)) {
                    result += i;
                }
            }
        }
        return result;
    }

    long isMultiDuplicate(long number) {
        int digit = countDigits(number);

        for (int i = 1; i <= digit / 2; ++i) {
            if (digit % i == 0) {
                long splitPow = power(10, digit - i);
                long high = number / splitPow;
                long low = number % splitPow;
                long shiftPow = power(10, i);
                long shiftedNum = low * shiftPow + high;
                if (shiftedNum == number) {
                    return true;
                }
            }
        }

        return false;
    }

    long part2(const std::vector<std::string> &lines) {
        long result{0};
        for (const auto &line: lines) {
            auto [start, end] = parseRange(line);
            for (long i = start; i <= end; i++) {
                if (isMultiDuplicate(i)) {
                    result += i;
                }
            }
        }
        return result;
    }

    void run(const std::string &input) {
        std::vector<std::string> lines = split_lines(input, ',');
        long p1 = part1(lines);
        long p2 = part2(lines);
        std::cout << "part1: " << p1 << "\n";
        std::cout << "part2: " << p2 << "\n";
    }
} // namespace day02
