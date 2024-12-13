//part 1 and 2

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#define PART_2

void part_1(std::vector<int>& l, std::vector<int>& r) {
    std::sort(l.begin(), l.end());
    std::sort(r.begin(), r.end());

    uint64_t sum = 0;
    for (uint64_t i = 0, e = r.size(); i < e; i++) {
        sum += (l[i] > r[i] ? l[i] - r[i] : r[i] - l[i]);
    }

    std::cout << sum << "\n";
}

void part_2(std::vector<int>& l, std::vector<int>& r) {
    uint64_t ans = 0;
    for (uint64_t i = 0, e = l.size(); i < e; i++) {
        ans += l[i] * std::count(r.begin(), r.end(), l[i]);
    }

    std::cout << ans << "\n";
}


void input_day_1() {
    std::vector<int> l, r;

    int s, ss;

    std::ifstream f("input_day_1.txt");

    if (f.is_open()) {
        while (f >> s >> ss) {
            l.push_back(s);
            r.push_back(ss);
        }
    }

#ifdef PART_1
    part_1(l, r);
#endif
    

#ifdef PART_2
    part_2(l, r);
#endif
    

    f.close();
}
