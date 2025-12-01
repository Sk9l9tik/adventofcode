//part 1 and 2

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>

#define PART_2

bool isxmas_1(const std::vector<std::string>& v, int x, int y, const int& dx, const int& dy, const std::string& xmas) {
	for (char c : xmas) {
		if (x < 0 || x >= v.size() || y < 0 || y >= v[0].size() || v[y][x] != c)
			return false;
		x += dx;
		y += dy;
	}
	return true;
}

bool isxmas_2(const std::vector<std::string>& v, int x, int y) {
	if (v[y][x] != 'M' || v[y + 1][x + 1] != 'A' || v[y + 2][x + 2] != 'S')
		return false;
	if (v[y][x + 2] != 'M' || v[y + 1][x + 1] != 'A' || v[y + 2][x] != 'S')
		return false;
	return true;
}

int input_day_4() {
	std::ifstream f("input_day_4.txt");
	if (!f.is_open()) {
		return 1;
	}

	std::string line;

	std::vector <std::string> grid;

	while (f >> line) {
		grid.push_back(line);
	}

	int ans = 0;

	std::vector<std::pair<int, int>> dir{
		{0, 1},{1,0}, { 1, 1 }, { 1, -1 },
		{0, -1}, {-1, 0}, { -1, -1 }, {-1, 1}
	};

	std::string xmas{ "XMAS" };

	int rows = grid.size();
	int cols = grid[0].size();

#ifdef PART_1
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			for (auto d : dir) {
				if (isxmas_1(grid, i, j, d.first, d.second, xmas))
					ans++;
			}
		}
	}
#endif

#ifdef PART_2
	for (int i = 0; i <= rows - 3; i++) {
		for (int j = 0; j <= cols - 3; j++) {
			if (isxmas_2(grid, i, j))
				ans++;
		}
	}
#endif


	std::cout << ans;
}

//M.M
//.A.
//S.S - 399

//S.S
//.A.
//M.M - 508

//S.M
//.A.
//S.M - 498

//M.S
//.A.
//M.S - 503