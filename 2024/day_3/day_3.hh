//part 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>

#define PART_1

int main1() {
	std::ifstream f("input_day_3.txt");
	if (!f.is_open()) {
		return 1;
	}

	std::string line;
	int ans = 0;

	while (f >> line) {
		//std::cout << line << '\n';

		int start = 0, cstart = 0, bend = 0;

		while ((start = line.find("mul(", start + 1)) != std::string::npos) {
			int lhs = 0, rhs = 0;
			//std::cout << start << "-";

			cstart = line.find(",", start);
			if (cstart != std::string::npos)
				//std::cout <<  cstart << '-';
				bend = line.find(")", cstart);
			if (bend != std::string::npos)
				//std::cout << bend << ' ';

				if (bend - cstart > 4) {
					continue;
				}

			int t;
			for (int i = start + 4; i < cstart; i++) {
				//std::cout << "(" << line[i] << ")";
				t = (int)line[i] - 48;
				if (t < 10 && t >= 0) {
					lhs *= 10;
					lhs += t;
				}
				else
					continue;
			}
			//std::cout << '\n';
			for (int i = cstart + 1; i < bend; i++) {
				//std::cout << "(" << line[i] << ")";
				t = (int)line[i] - 48;
				if (t < 10 && t >= 0) {
					rhs *= 10;
					rhs += t;
				}
				else
					continue;
			}
			//std::cout << '\n';
			//std::cout << lhs << '-' << rhs << '\n';
			ans += lhs * rhs;
		}



		//std::cout << line.find("mul(", 2) << " =\n";
	}

	std::cout << ans << std::endl;

	f.close();
	return 0;
}

int input_day_3() {
	std::ifstream f("input_day_3.txt");
	if (!f.is_open()) {
		return 1;
	}

	std::string line;
	int ans = 0;

	while (std::getline(f, line)) {
		std::regex rmul{ "mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don't\\(\\)" };
		std::regex rdo{ "do(n't)?\\(\\)" };
		std::sregex_iterator beg{ line.cbegin(), line.cend(), rmul };
		//std::sregex_iterator dobeg{ line.cbegin(), line.cend(), rdo };

		std::sregex_iterator end{};

		int len = 0;

		std::vector<std::pair<int, std::string>> v;

		for (auto i = beg; i != end; i++) {
			v.push_back(std::make_pair(i->position(), i->str()));
			len++;
		}
		//std::cout << len << '-';
		//for (auto i = dobeg; i != end; i++) {
		//	v.push_back(std::make_pair(i->position(), i->str()));
		//	len++;
		//}
		//std::cout << len << '\n';
		//std::sort(v.begin(), v.end(), [](std::pair<int, std::string> a, std::pair<int, std::string>  b)
		//	{return a.first < b.first; });


		int isdo = 1;

		for (int i = 0; i < len; i++) {
			std::cout << v[i].first << ' ' << v[i].second << '\n';
			if (v[i].second == "don't()") {
				isdo = 0;
				continue;
			}
			else if (v[i].second == "do()") {
				isdo = 1;
				continue;
			}
			else {
				if (isdo) {
					std::cout << "+\n";
					bool right = 0;
					int lhs = 0, rhs = 0;
					for (int j = 0, e = v[i].second.size(); j < e; j++) {
						int t = (int)(v[i].second)[j] - 48;
						//std::cout << t << '\n';
						if ((v[i].second)[j] == ',')
							right = 1;
						if (t < 10 && t >= 0) {
							if (right) {
								rhs *= 10;
								rhs += t;
							}
							else {
								lhs *= 10;
								lhs += t;
							}
						}
					}
					ans += lhs * rhs;
				}
				else {
					std::cout << "-\n";
					continue;
				}
			}
		}

		//std::cout << len << '\n';
	}
	std::cout << ans;
}
//175040835
//70553436
//63013756