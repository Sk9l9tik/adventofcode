//part 1 and 2

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define PART_2

bool isSafe(std::vector<int>& l) {
	bool inc = true;
	bool dec = true;

	for (size_t i = 1; i < l.size(); ++i) {
		if (l[i] < l[i - 1]) {
			inc = false;
		}
		if (l[i] > l[i - 1]) {
			dec = false;
		}
		if (abs(l[i] - l[i - 1]) < 1 || abs(l[i] - l[i - 1]) > 3) {
			return false;
		}
	}

	return inc || dec;
}

bool isSafe2(std::vector<int>& l) {
	bool inc = true;
	bool dec = true;

	for (size_t i = 1; i < l.size(); ++i) {
		if (l[i] < l[i - 1]) {
			inc = false;
		}
		if (l[i] > l[i - 1]) {
			dec = false;
		}

		if (abs(l[i] - l[i - 1]) < 1 || abs(l[i] - l[i - 1]) > 3) {
			for (int i = 0, e = l.size(); i < e; i++) {
				std::vector<int> v(l.begin(), l.end());
				v.erase(v.begin() + i);

				if (isSafe(v)) {
					return 1;
				}
			}
			return false;
		}
	}


	if (inc || dec) {
		//for (int i = 0; i < l.size(); i++)
		//	std::cout << l[i] << ' ';
		//std::cout << "_____\n";
		return true;
	}
	else {
		for (int i = 0, e = l.size(); i < e; i++) {
			std::vector<int> v(l.begin(), l.end());
			v.erase(v.begin() + i);

			if (isSafe(v)) {
				return 1;
			}

		}
		return 0;
	}
}

int input_day_2() {
	std::ifstream f("input_day_2.txt");
	if (!f.is_open()) {
		return 1;
	}

	std::string line;
	int count = 0;

	while (std::getline(f, line)) {
		std::istringstream ss(line);
		std::vector<int> l;
		int num;

		while (ss >> num) {
			l.push_back(num);
		}

#ifdef PART_1
		if (isSafe(l)) {
			count++;
		}
#endif


#ifdef PART_2
		if (isSafe2(l)) {
			count++;
		}
#endif
	}

	std::cout << count << std::endl;

	f.close();
	return 0;
}

