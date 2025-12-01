//part 1 and 2

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <regex>
#include <unordered_map>
#include <sstream>
#include <unordered_set>

#define PART_2

std::vector<uint64_t> split(const std::string& s, char del = ' ') {
    std::vector<uint64_t> v;
    std::string token;
    std::istringstream ss(s);
    while (std::getline(ss, token, del)) {
        v.push_back(std::stoi(token));
    }
    return v;
}



uint64_t toint(const std::string& s) {
    uint64_t numb = 0;
    for (uint64_t i = 0, e = s.size(); i < e; i++) {
        numb *= 10;
        numb += (uint64_t)s[i] - 48;
    }
    return numb;
}

uint64_t canmul(uint64_t t, std::vector<uint64_t>& n, uint64_t cur, uint64_t index) {
    if (index >= n.size())
        return cur == t;

    if (canmul(t, n, cur + n[index], index + 1))
        return 1;
    if (canmul(t, n, cur * n[index], index + 1))
        return 1;
#ifdef PART_2
    if (canmul(t, n, toint(std::to_string(cur) + std::to_string(n[index])), index + 1)) {
        return true;
    }
#endif
    return 0;
}

uint64_t input_day_7() {

    std::fstream f("input_day_7.txt");

    std::string s;

    uint64_t ans = 0;

    while (std::getline(f, s)) {
        size_t colonPos = s.find(':');
        uint64_t target = toint(s.substr(0, colonPos));

        std::vector<uint64_t> numbers = split(s.substr(colonPos + 2));

        if (canmul(target, numbers, numbers[0], 1)) {
            ans += target;
        }

    }
    std::cout << ans;
    return 0;
}
