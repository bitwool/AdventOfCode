#include <algorithm>

#include "day03.hpp"

#include <format>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "utils.hpp"

namespace day05 {
    std::pair<long long, long long> parse_range(const std::string &rangeStr) {
        std::stringstream ss(rangeStr);
        long long start{0};
        long long end{0};
        char dash;
        ss >> start >> dash >> end;
        return {start, end};
    }

    std::vector<std::pair<long long, long long> > merge_ranges(std::vector<std::pair<long long, long long> > intervals) {
        std::vector<std::pair<long long, long long> > result;
        std::pair<long long, long long> curr = intervals[0];
        for (size_t i = 1; i < intervals.size(); ++i) {
            auto p = intervals[i];
            if (p.first <= curr.second) {
                curr.second = std::max(curr.second, p.second);
            } else {
                result.push_back(curr);
                curr = intervals[i];
            }
        }
        result.push_back(curr);
        return result;
    }

    bool isFresh(std::vector<std::pair<long long, long long> > merged_intervals, long long target) {
        auto it = std::upper_bound(merged_intervals.begin(), merged_intervals.end(), target,
                                   [](long long val, const std::pair<long long, long long> &interval) {
                                       return val < interval.first;
                                   });
        if (it == merged_intervals.begin()) {
            return false;
        }
        --it;
        return target <= it->second;
    }


    std::vector<std::pair<long long, long long> > preprocess(const std::vector<std::string> &ranges) {
        std::vector<std::pair<long long, long long> > intervals;
        for (const auto &range: ranges) {
            intervals.push_back(parse_range(range));
        }
        std::sort(intervals.begin(), intervals.end());
        return merge_ranges(intervals);
    }


    long part1(const std::vector<std::string> &ranges, const std::vector<std::string> &ids) {
        auto merged_intervals = preprocess(ranges);

        long result{0};
        for (const auto &id: ids) {
            if (isFresh(merged_intervals, std::stoll(id))) {
                result++;
            }
        }
        return result;
    }


    long long part2(const std::vector<std::string> &ranges) {
        auto merged_intervals = preprocess(ranges);

        long result{0};
        for (auto merged_interval: merged_intervals) {
            result += (merged_interval.second - merged_interval.first + 1);
        }
        return result;
    }

    void run(const std::string &input) {
        std::vector<std::string> lines = split_lines(input, '\n');
        std::vector<std::string> ranges;
        std::vector<std::string> ids;
        bool rangeEnd{false};
        for (auto &line: lines) {
            if (line.empty()) {
                rangeEnd = true;
            } else if (rangeEnd) {
                ids.push_back(line);
            } else {
                ranges.push_back(line);
            }
        }
        const auto p1 = part1(ranges, ids);
        const auto p2 = part2(ranges);
        std::cout << "part1: " << p1 << "\n";
        std::cout << "part2: " << p2 << "\n";
    }
} // namespace day05
