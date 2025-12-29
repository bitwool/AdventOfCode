#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <tuple>

#include "utils.hpp"

namespace day08 {
    struct Point {
        int x, y, z;
    };

    struct UnionFind {
        std::vector<size_t> parent, sz;
        size_t components;

        explicit UnionFind(size_t n) : parent(n), sz(n, 1), components(n) {
            std::iota(parent.begin(), parent.end(), 0);
        }

        size_t find(size_t x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        }

        bool unite(size_t a, size_t b) {
            a = find(a);
            b = find(b);
            if (a == b) return false;
            if (sz[a] < sz[b]) std::swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
            components--;
            return true;
        }
    };

    long long distance(const Point &a, const Point &b) {
        long long dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
        return dx * dx + dy * dy + dz * dz;
    }

    auto get_sorted_edges(const std::vector<std::string> &lines) {
        std::vector<Point> points;
        for (const auto &line: lines) {
            auto parts = split_lines(line, ',');
            if (parts.size() >= 3) {
                points.push_back({std::stoi(parts[0]), std::stoi(parts[1]), std::stoi(parts[2])});
            }
        }

        std::vector<std::tuple<long long, size_t, size_t>> edges;
        size_t n = points.size();
        edges.reserve(n * (n - 1) / 2);

        for (size_t i = 0; i < n; i++) {
            for (size_t j = i + 1; j < n; j++) {
                edges.emplace_back(distance(points[i], points[j]), i, j);
            }
        }

        std::sort(edges.begin(), edges.end());
        return std::make_pair(std::move(points), std::move(edges));
    }

    long long part1(const std::vector<std::string> &lines) {
        auto [points, edges] = get_sorted_edges(lines);
        size_t n = points.size();
        if (n == 0) return 0;

        UnionFind uf(n);
        size_t limit = std::min(n <= 20 ? size_t{10} : size_t{1000}, edges.size());

        for (size_t i = 0; i < limit; i++) {
            auto [dist, a, b] = edges[i];
            uf.unite(a, b);
        }

        std::vector<size_t> sizes;
        for (size_t i = 0; i < n; i++) {
            if (uf.parent[i] == i) {
                sizes.push_back(uf.sz[i]);
            }
        }

        std::sort(sizes.rbegin(), sizes.rend());
        long long a = sizes.size() > 0 ? static_cast<long long>(sizes[0]) : 1;
        long long b = sizes.size() > 1 ? static_cast<long long>(sizes[1]) : 1;
        long long c = sizes.size() > 2 ? static_cast<long long>(sizes[2]) : 1;
        return a * b * c;
    }

    long long part2(const std::vector<std::string> &lines) {
        auto [points, edges] = get_sorted_edges(lines);
        size_t n = points.size();
        if (n <= 1) return 0;

        UnionFind uf(n);
        for (auto [dist, a, b]: edges) {
            if (uf.unite(a, b) && uf.components == 1) {
                return (long long) points[a].x * points[b].x;
            }
        }
        return 0;
    }

    void run(const std::string &input) {
        auto lines = split_lines(input, '\n');
        std::cout << "part1: " << part1(lines) << "\n";
        std::cout << "part2: " << part2(lines) << "\n";
    }
}
