#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;

  Point above() const { return {x, y - 1}; }
  Point below() const { return {x, y + 1}; }
  Point left() const { return {x - 1, y}; }
  Point right() const { return {x + 1, y}; }

  vector<Point> neighbors() const {
    return {above(), below(), left(), right()};
  }

  bool valid(int size) const {
    return x >= 0 && x < size && y >= 0 && y < size;
  }

  Point operator+(const Point &p) const { return {x + p.x, y + p.y}; }

  Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }

  bool operator<(const Point &p) const {
    return y < p.y || (y == p.y && x < p.x);
  }

  bool operator==(const Point &p) const { return x == p.x && y == p.y; }

  friend ostream &operator<<(ostream &out, const Point &p) {
    return out << "{" << p.x << ", " << p.y << "}";
  }
};

struct Grid {
  vector<vector<char>> grid;

  char &operator[](Point p) { return grid[p.y][p.x]; }

  const char &operator[](Point p) const { return grid[p.y][p.x]; }

  int size() const { return grid.size(); }

  void push_back(const vector<char> &row) { grid.push_back(row); }
};

void printGrid(const Grid &grid) {
  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid.size(); x++) {
      cout << grid[{x, y}];
    }
    cout << endl;
  }
}

uint64_t totalFenceCosts(const Grid &grid) {
  uint64_t total = 0;
  set<Point> visited;

  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid.size(); x++) {
      Point p = {x, y};

      if (visited.count(p)) // skip visited points
        continue;

      char c = grid[p];
      int regionCost = 0;
      int regionSize = 0;
      stack<Point> s;
      s.push(p);
      while (!s.empty()) {
        Point curr = s.top();
        s.pop();
        if (visited.count(curr)) {
          continue;
        }
        visited.insert(curr);
        regionSize++;
        for (auto neighbor : curr.neighbors()) {
          if (!neighbor.valid(grid.size())) {
            regionCost++;
          } else if (grid[neighbor] != c) {
            regionCost++;
          } else if (grid[neighbor] == c) {
            s.push(neighbor);
          }
        }
      }

      total += regionCost * regionSize;
    }
  }

  return total;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <input_file>" << endl;
    return 1;
  }

  cin.tie(0);
  ios::sync_with_stdio(0);

  string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);

  Grid grid;
  string line;

  while (getline(cin, line)) {
    vector<char> row;
    for (int i = 0; i < line.size(); i++) {
      row.push_back(line[i]);
    }
    grid.push_back(row);
  }

  printGrid(grid);
  cout << endl;

  cout << totalFenceCosts(grid) << endl;

  return 0;
}
