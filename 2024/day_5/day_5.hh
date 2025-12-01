//part 1 and 2

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <regex>
#include <unordered_map>
#include <unordered_set>

#define PART_2

std::vector<int> split(std::string& s, char del = ',') {
    std::vector<int> v;

    for (int i = 0, e = s.size(); i < e - 2; i += 3) {
        v.push_back(std::stoi(s.substr(i, i + 2)));
        //std::cout << std::stoi(s.substr(i, i + 2)) << " - ";
    }

    return v;
}

int find_median(std::vector<int>& v) {
    if (v.size() % 2 == 0) {
        return v[v.size() / 2];
    }
    return v[v.size() / 2];
}


std::vector<int> make_correct(std::vector<int>& unsorted, std::unordered_map<int, std::vector<int>>& rules) {
    std::vector<int> q;

    for (int i = 0, e = unsorted.size(); i < e; i++) {
        std::vector<int> temp{ rules[unsorted[i]] };
        for (auto& el : temp) {
            return q;
        }
    }
}


void sort(std::vector<int>& unsorted, const std::unordered_map<int, std::vector<int>>& rules) {
    std::sort(unsorted.begin(), unsorted.end(), [&](int a, int b) {
        if (rules.find(a) != rules.end() && std::find(rules.at(a).begin(), rules.at(a).end(), b) != rules.at(a).end()) {
            return true;
        }
        if (rules.find(b) != rules.end() && std::find(rules.at(b).begin(), rules.at(b).end(), a) != rules.at(b).end()) {
            return false;
        }
        return a < b;
        });
}


int input_day_5() {

    std::fstream f("input_day_5.txt");

    std::unordered_map<int, std::string> m;
    std::unordered_map<int, std::vector<int>> mm;

    std::string s;

    if (f.is_open()) {
        while (std::getline(f, s)) {
            if (s == "")
                break;
            //std::cout << s << " ";
            m[std::stoi(s.substr(0, 2))] = m[std::stoi(s.substr(0, 2))] + s.substr(3, 5) + ",";

            //std::cout << m[std::stoi(s.substr(0, 2))] << " \n";
        }


        for (auto& u : m) {
            mm[u.first] = split(u.second);
        }

        int count = 0;
        while (std::getline(f, s)) {
            std::string unsorted_s = s + ",";
            std::vector<int>unsorted{ split(unsorted_s) };
            std::vector<int> q;

            bool correct = 1;
            for (int i = 0, e = unsorted.size(); i < e; i++) {
                q.push_back(unsorted[i]);
                std::vector<int> temp{ mm[unsorted[i]] };
                for (auto el : temp) {
                    if (std::find(q.begin(), q.end(), el) != q.end()) {
                        correct = 0;
                        break;
                    }
                }
                if (!correct) {
#ifdef PART_2
                    std::vector<int> vv{ unsorted };
                    sort(vv, mm);
                    count += find_median(vv);
#endif
                    break;
                }
            }
            if (correct) {
#ifdef PART_1
                count += find_median(unsorted);
#endif
                //std::cout << unsorted_s << " /" << find_median(unsorted) << "\n";
            }
        }
        std::cout << count;
    }


    //std::vector<int> v {split(m[97])};

    f.close();

    return 0;
}
