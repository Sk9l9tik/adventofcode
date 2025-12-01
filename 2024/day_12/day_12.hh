//part 1
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
#include <functional>
#include <omp.h>


int calc_all_regions_1(const std::vector<std::vector<char>>& map) {
    int rows = map.size();
    int cols = map[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    int totalCost = 0;

    std::function<void(int, int, char, int&, int&)> dfs = [&](int x, int y, char type, int& square, int& area) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || visited[x][y] || map[x][y] != type) {
            return;
        }
        visited[x][y] = true;
        square++;
        std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            if (newX < 0 || newX >= rows || newY < 0 || newY >= cols || map[newX][newY] != type) {
                area++;
            }
            else {
                dfs(newX, newY, type, square, area);
            }
        }
        };

#pragma parallel for reduction (+ : totalCost)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!visited[i][j]) {
                int square = 0;
                int area = 0;
                dfs(i, j, map[i][j], square, area);
                totalCost += square * area;
            }
        }
    }

    return totalCost;
}

int calc_all_regions_2(const std::vector<std::vector<char>>& map) {
    int rows = map.size();
    int cols = map[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    int totalCost = 0;

    std::function<void(int, int, char, int&, int&)> dfs = [&](int x, int y, char type, int& square, int& area) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || visited[x][y] || map[x][y] != type) {
            return;
        }
        visited[x][y] = true;
        square++;
        std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            if (newX < 0 || newX >= rows || newY < 0 || newY >= cols || map[newX][newY] != type) {
                area++;
            }
            else {
                dfs(newX, newY, type, square, area);
            }
            
        }
        };

#pragma parallel for reduction (+ : totalCost)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!visited[i][j]) {
                int square = 0;
                int area = 0;
                dfs(i, j, map[i][j], square, area);
                totalCost += square * area / 2;
            }
        }
    }

    return totalCost;
}

void input_day_12() {
	std::fstream f("input_day_12.txt");
	if (!f.is_open()) {
		std::cout << "not open file";
		return;
	}

	std::vector<std::vector<char>> grid;

	std::string s;
	while (f >> s) {
		std::vector<char> m;
		for (char& c : s) {
			m.push_back(c);
		}
		grid.push_back(m);
	}
	std::cout << calc_all_regions_2(grid);
}