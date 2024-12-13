#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <functional>

// Specialization of std::hash for std::pair<int, int>
namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };

    // Specialization of std::hash for std::pair<std::pair<int, int>, std::pair<int, int>>
    template <>
    struct hash<std::pair<std::pair<int, int>, std::pair<int, int>>> {
        size_t operator()(const std::pair<std::pair<int, int>, std::pair<int, int>>& p) const {
            return std::hash<std::pair<int, int>>()(p.first) ^ (std::hash<std::pair<int, int>>()(p.second) << 1);
        }
    };
}

// Function to parse the map
std::tuple<std::vector<std::string>, std::pair<std::pair<int, int>, std::pair<int, int>>, std::set<std::pair<int, int>>> parse_map(const std::vector<std::string>& input_map) {
    std::vector<std::string> map_data;
    std::pair<std::pair<int, int>, std::pair<int, int>> guard_pos;
    std::set<std::pair<int, int>> obstacles;

    for (int y = 0; y < input_map.size(); ++y) {
        const std::string& row = input_map[y];
        for (int x = 0; x < row.size(); ++x) {
            if (row[x] == '^') {
                guard_pos = std::make_pair(std::make_pair(x, y), std::make_pair(0, -1)); // Initial direction is up
            }
            else if (row[x] == '#') {
                obstacles.insert(std::make_pair(x, y));
            }
        }
    }

    return std::make_tuple(input_map, guard_pos, obstacles);
}

// Function to move the guard
std::pair<int, int> move_guard(const std::pair<int, int>& position, const std::pair<int, int>& direction) {
    int x = position.first;
    int y = position.second;
    return std::make_pair(x + direction.first, y + direction.second);
}

// Function to turn the guard right
std::pair<int, int> turn_right(const std::pair<int, int>& direction) {
    std::vector<std::pair<int, int>> directions = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
    int index = std::find(directions.begin(), directions.end(), direction) - directions.begin();
    return directions[(index + 1) % 4];
}

// Function to simulate the guard's movement
std::pair<std::set<std::pair<int, int>>, bool> simulate_guard(const std::vector<std::string>& map_data, std::pair<std::pair<int, int>, std::pair<int, int>> guard_pos, const std::set<std::pair<int, int>>& obstacles) {
    int x = guard_pos.first.first;
    int y = guard_pos.first.second;
    std::pair<int, int> direction = guard_pos.second;
    std::set<std::pair<int, int>> visited;
    visited.insert(std::make_pair(x, y));

    std::unordered_map<std::pair<int, int>, std::pair<int, int>> direction_map;
    direction_map[std::make_pair(x, y)] = direction;

    std::unordered_set<std::pair<std::pair<int, int>, std::pair<int, int>>> state_set;
    state_set.insert(std::make_pair(std::make_pair(x, y), direction));

    bool in_loop = false;
    while (true) {
        std::pair<int, int> next_pos = move_guard(std::make_pair(x, y), direction);
        if (next_pos.first < 0 || next_pos.first >= map_data[0].size() || next_pos.second < 0 || next_pos.second >= map_data.size()) {
            break;
        }
        if (obstacles.find(next_pos) != obstacles.end()) {
            direction = turn_right(direction);
        }
        else {
            x = next_pos.first;
            y = next_pos.second;
            if (state_set.find(std::make_pair(std::make_pair(x, y), direction)) != state_set.end()) {
                in_loop = true;
                break;
            }
            visited.insert(std::make_pair(x, y));
            direction_map[std::make_pair(x, y)] = direction;
            state_set.insert(std::make_pair(std::make_pair(x, y), direction));
        }
    }

    return std::make_pair(visited, in_loop);
}

// Function to find loop positions
std::set<std::pair<int, int>> find_loop(const std::vector<std::string>& map_data, std::pair<std::pair<int, int>, std::pair<int, int>> guard_pos, const std::set<std::pair<int, int>>& obstacles) {
    std::set<std::pair<int, int>> loop_positions;
    int guard_x = guard_pos.first.first;
    int guard_y = guard_pos.first.second;

    for (int y = 0; y < map_data.size(); ++y) {
        for (int x = 0; x < map_data[0].size(); ++x) {
            if (obstacles.find(std::make_pair(x, y)) == obstacles.end() && !(x == guard_x && y == guard_y)) {
                std::set<std::pair<int, int>> new_obstacles = obstacles;
                new_obstacles.insert(std::make_pair(x, y));
                auto result = simulate_guard(map_data, guard_pos, new_obstacles);
                std::set<std::pair<int, int>> visited = result.first;
                bool in_loop = result.second;
                if (in_loop) {
                    loop_positions.insert(std::make_pair(x, y));
                }
            }
        }
    }

    return loop_positions;
}

int input_day_6() {
    std::ifstream input_file("input_day_6.txt");
    if (!input_file.is_open()) {
        return 1;
    }

    std::vector<std::string> input_map;
    std::string line;
    while (std::getline(input_file, line)) {
        input_map.push_back(line);
    }
    input_file.close();

    auto result = parse_map(input_map);
    std::vector<std::string> map_data = std::get<0>(result);
    std::pair<std::pair<int, int>, std::pair<int, int>> guard_pos = std::get<1>(result);
    std::set<std::pair<int, int>> obstacles = std::get<2>(result);

#ifdef PART_1
    std::set<std::pair<int, int>> visited_positions = simulate_guard(map_data, guard_pos, obstacles).first;
    std::cout << visited_positions.size() << "\n";
#endif

#ifdef PART_2
    std::set<std::pair<int, int>> loop_positions = find_loop(map_data, guard_pos, obstacles);
    std::cout << loop_positions.size() << "\n";
#endif
    return 0;
}
