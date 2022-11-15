#include <bits/stdc++.h>
using namespace std;

struct position {
    int y;
    int x;
};

struct field {
    bool has_light = false;
    bool visited = false;
};

struct component {
    bool is_start = false;
    bool is_target = false;
    int min_row = 2000;
    int max_row = -1;
};

vector<vector<field>> grid;

component dfs(position pos, component comp) {
    int n = grid.size();
    grid[pos.y][pos.x].visited = true;
    if (pos.y > comp.max_row)
        comp.max_row = pos.y;
    if (pos.y < comp.min_row)
        comp.min_row = pos.y;

    if (pos.y == 0 && pos.x == n - 1)
        comp.is_start = true;
    if (pos.y == n - 1 && pos.x == 0)
        comp.is_target = true;

    // up
    if (pos.y < n - 1 && !grid[pos.y + 1][pos.x].visited &&
        grid[pos.y + 1][pos.x].has_light)
        comp = dfs(position{pos.y + 1, pos.x}, comp);
    // right
    if (pos.x < n - 1 && !grid[pos.y][pos.x + 1].visited &&
        grid[pos.y][pos.x + 1].has_light)
        comp = dfs(position{pos.y, pos.x + 1}, comp);
    // down
    if (pos.y > 0 && !grid[pos.y - 1][pos.x].visited &&
        grid[pos.y - 1][pos.x].has_light)
        comp = dfs(position{pos.y - 1, pos.x}, comp);
    // left
    if (pos.x > 0 && !grid[pos.y][pos.x - 1].visited &&
        grid[pos.y][pos.x - 1].has_light)
        comp = dfs(position{pos.y, pos.x - 1}, comp);

    return comp;
}

int solve() {
    int n = grid.size();
    unordered_map<int, vector<component>> rows_components;
    for (int i = 0; i < n; i++) {
        rows_components[i] = vector<component>();
    }
    component starting_component;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!grid[i][j].visited && grid[i][j].has_light) {
                component comp = dfs(position{i, j}, component{});
                rows_components[comp.min_row].push_back(comp);
                if (comp.is_start)
                    starting_component = comp;
            }
        }
    }
    int count = 0;
    component current_comp = starting_component;
    while (true) {
        if (current_comp.is_target)
            break;
        component next_comp;
        for (int i = current_comp.min_row; i < current_comp.max_row + 2; i++) {
            for (component c : rows_components[i]) {
                if (c.max_row > next_comp.max_row)
                    next_comp = c;
                if (c.is_target)
                    return count + 1;
            }
        }
        current_comp = next_comp;
        count++;
    }
    return count;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        grid.push_back(vector<field>());
        for (int j = 0; j < n; j++) {
            grid[i].push_back(field{});
        }
    }
    int x, y;
    unordered_set<int> rows_active;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        rows_active.insert(x);
        grid[n - x][y - 1].has_light = true;
    }
    if (rows_active.size() != n) {
        cout << "-1" << endl;
    } else {
        cout << solve() << endl;
    }
}