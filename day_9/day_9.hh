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

std::vector<std::pair<int, int>> parse(const std::string& s) {
	std::vector<std::pair<int, int>> map;
	bool isf = 1;
	int fid = 0;
	for (char c : s) {
		int count = c - '0';
		if (isf) {
			map.push_back({ fid, count });
			fid++;
		}
		else {
			for (int i = 0; i < count; ++i) {
				map.push_back({ -1, 1 }); // -1 для свободного пространства
			}
		}
		isf = !isf;
	}
	return map;
}

std::vector<std::pair<int, int>> complect_part1(std::vector<std::pair<int, int>>& map) {
	int last = map.size() - 1;
	for (int i = 0, e = map.size(); i < e; i++) {
		if (map[i].first == -1 && i < last) {
			if (map[last].second <= 0) {
				map[last].first = -1;
				map[last].second = 1;
				last--;
			}
			while (map[last].first == -1)
				last--;
			map[i].first = map[last].first;
			map[last].second--;
		}
	}
	return map;
}

std::vector<std::pair<int, int>> complect_part2(std::vector<std::pair<int, int>>& map) {
	int last = map.size() - 1;
	int fist_pos = 0, count_free = 0;

	for (int i = last; i >=0 ; i--) {
		/*if (map[i].first == -1 && i < last) {
			int j = i;
			fist_pos = i;
			while (map[j].first == -1) {
				count_free++;
				j++;
			}
			while(last > i){

				while (map[last].first == -1)
					last--;

				if (map[last].second <= count_free) {
					std::cout << "---" << map[last].second << "---" << count_free << "\n";
					while (map[last].second--) {
						map[fist_pos].first = map[last].first;
						fist_pos++;
					}
					map[last].second = 1;
					map[last].first = -1;
					count_free = 0;
					break;
				}
				else {
					last--;
				}
			}
			count_free = 0;
		}*/

		if (map[i].first == -1)
			continue;
		int j = 0;
		while (j < i) {
			//std::cout << map[i].first << ' ' << map[i].second << "\n";
			if (map[j].first != -1) {
				j++;
			}
			else {
				fist_pos = j;
				while (map[j].first == -1) {
					count_free++;
					j++;
				}
				if (map[i].second <= count_free && map[i].second != -1) {
					int counter = 0;
					while (map[i].second--) {
						counter++;
						map[fist_pos].first = map[i].first;
						map[fist_pos].second = -1;
						fist_pos++;
					}
					map[i].second = counter;
					map[i].first = -1;
					count_free = 0;
					break;
				}
			}
			count_free = 0;
		}

	}
	for (int i = 0; i <= last; i++) {
		if (map[i].second == -1)
			map[i].second = 1;
	}

	return map;
}


uint64_t summer(std::vector<std::pair<int, int>>& map) {
	uint64_t sum = 0, id = 0;
	for (int i = 0; i < map.size(); i++) {
		while (map[i].second) {
			if (map[i].first == -1) {
				id+= map[i].second;
				break;
			}
			sum += map[i].first * id;
			map[i].second--;
			id++;
		}
	}
	return sum;
}

void input_day_9() {
	std::fstream f("input_day_9.txt");
	if (!f.is_open())
		return;

	std::string s;
#ifdef PART_1
	if (std::getline(f, s)) {
		std::vector<std::pair<int, int>> map = parse(s);
		complect_part1(map);
		//for (int i = 0; i < map.size(); i++) {
		//	std::cout << map[i].first << ' ' << map[i].second << "\n";
		//}
		std::cout << summer(map);
	}
#endif

#ifdef PART_2
	if (std::getline(f, s)) {
		std::vector<std::pair<int, int>> map = parse(s);
		complect_part2(map);
		//for (int i = 0; i < map.size(); i++) {
		//	std::cout << map[i].first << ' ' << map[i].second << "\n";
		//}
		std::cout << summer(map);
	}
#endif

}