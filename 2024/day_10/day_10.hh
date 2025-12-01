//part 1 and part 2
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
#include <set>

std::vector<std::pair<int, int>> findTrailheads(const std::vector<std::vector<int>>& map) {
	std::vector<std::pair<int, int>> trailheads;
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			if (map[i][j] == 0) {
				trailheads.push_back({ i, j });
			}
		}
	}
	return trailheads;
}

int findTrailScore(const std::vector<std::vector<int>>& map, int x, int y, std::vector<std::vector<bool>>& visited) {

	if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size() || visited[x][y]) {
		return 0;
	}

	visited[x][y] = true;
	if (map[x][y] == 9) {
		return 1;
	}
	int score = 0;
	std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
	for (const auto& dir : directions) {
		int newX = x + dir.first;
		int newY = y + dir.second;
		if (newX >= 0 && newX < map.size() && newY >= 0 && newY < map[0].size() && map[newX][newY] == map[x][y] + 1) {
			score += findTrailScore(map, newX, newY, visited);
		}
	}
	visited[x][y] = false;
	return score;
}

int findTrailScore2(const std::vector<std::vector<int>>& map, int x, int y) {
	
	if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size()) {
		return 0;
	}

	if (map[x][y] == 9) {
		return 1;
	}

	int score = 0;
	std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
	for (const auto& dir : directions) {
		int newX = x + dir.first;
		int newY = y + dir.second;
		if (newX >= 0 && newX < map.size() && newY >= 0 && newY < map[0].size() && map[newX][newY] == map[x][y] + 1) {
			score += findTrailScore2(map, newX, newY);
		}
	}

	return score;
}

void input_day_10() {
	std::fstream f("input_day_10.txt");
	if (!f.is_open()) {
		std::cout << "not open file";
		return;
	}


	std::vector<std::vector<int>> grid;

	std::string s;
	while (f >> s) {
		std::vector<int> m;
		for (char& c : s) {
			m.push_back(c - '0');
		}
		grid.push_back(m);
	}

	std::vector<std::pair<int, int>> trailheads = findTrailheads(grid);

	int totalScore = 0;
#ifdef PART_1
	totalScore = 0;
	for (const auto& trailhead : trailheads) {
		std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
		int score = findTrailScore(grid, trailhead.first, trailhead.second, visited);
		totalScore += score;
	}
	std::cout << totalScore;
#endif

#ifdef PART_2
	totalScore = 0;
	for (const auto& trailhead : trailheads) {
		int score = findTrailScore2(grid, trailhead.first, trailhead.second);
		totalScore += score;
	}
	std::cout << totalScore;
#endif
}