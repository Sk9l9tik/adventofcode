//part 1 and part 2
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <regex>
#include <unordered_map>
#include <map>
#include <sstream>
#include <unordered_set>
#include <omp.h>

// Определение оператора == для std::pair<uint64_t, uint64_t>
namespace std {
    template <>
    struct hash<pair<uint64_t, uint64_t>> {
        size_t operator()(const pair<uint64_t, uint64_t>& p) const {
            return hash<uint64_t>()(p.first) ^ (hash<uint64_t>()(p.second) << 1);
        }
    };

    template <>
    struct equal_to<pair<uint64_t, uint64_t>> {
        bool operator()(const pair<uint64_t, uint64_t>& lhs, const pair<uint64_t, uint64_t>& rhs) const {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
    };
}

uint64_t toint(const std::string& s) {
    uint64_t numb = 0;
    for (uint64_t i = 0, e = s.size(); i < e; i++) {
        numb *= 10;
        numb += (uint64_t)s[i] - 48;
    }
    return numb;
}

//#pragma omp parallel for
std::vector<uint64_t> split_part1(std::vector<uint64_t>& stones) {
    for (int i = 0, e = stones.size(); i < e; i++) {
        std::string s_div_2 = std::to_string(stones[i]);
        if (s_div_2.size() % 2 == 0) {
            std::string s_2 = s_div_2.substr((int)(s_div_2.size() / 2));
            stones[i] = toint(s_div_2.substr(0, (int)(s_div_2.size() / 2)));
            stones.insert(stones.begin() + i + 1, toint(s_2));
            i++;
            e++;
        }
        else if (stones[i] == 0) {
            stones[i] = 1;
        }
        else {
            stones[i] *= 2024;
        }
    }
    return stones;
}

std::unordered_map<std::pair<uint64_t, uint64_t>, uint64_t> cache;

uint64_t split_part2(uint64_t x, uint64_t n) {
    std::pair<uint64_t, uint64_t> key = std::make_pair(x, n);
    if (cache.find(key) != cache.end()) {
        return cache[key];
    }
    if (n == 0) {
        return 1;
    }

    uint64_t res = 0;
    if (x == 0) {
        res = split_part2(1, n - 1);
    }
    else if (std::to_string(x).size() % 2 == 0) {
        uint64_t left = toint(std::to_string(x).substr(0, std::to_string(x).size() / 2));
        uint64_t right = toint(std::to_string(x).substr(std::to_string(x).size() / 2));
        res = split_part2(left, n - 1) + split_part2(right, n - 1);
    }
    else {
        res = split_part2(2024 * x, n - 1);
    }

    cache[key] = res;
    return res;
}

void input_day_11() {
    std::fstream f("input_day_11.txt");
    std::string s;
    std::vector<uint64_t> stones;

    while (f >> s) {
        stones.push_back(toint(s));
    }

#ifdef PART_1
    std::vector<uint64_t> total_stones(stones) ;
    for (int i = 0; i < 25; i++) {
        split_part1(total_stones);
    }
    std::cout << total_stones.size() << '\n';
#endif

#ifdef PART_2
    uint64_t total_stones2 = 0;
    for (const auto& stone : stones) {
        total_stones2 += split_part2(stone, 1000);
    }
    std::cout << total_stones2 << '\n';
#endif
}

