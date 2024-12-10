#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;

  static Point up;
  static Point down;
  static Point left;
  static Point right;

  bool valid(int size) const {
    return x >= 0 && x < size && y >= 0 && y < size;
  }

  Point operator*(int k) const { return {x * k, y * k}; }

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

Point Point::up = {0, -1};
Point Point::down = {0, 1};
Point Point::left = {-1, 0};
Point Point::right = {1, 0};

struct Grid {
  vector<vector<int>> grid;

  int &operator[](Point p) { return grid[p.y][p.x]; }

  const int &operator[](Point p) const { return grid[p.y][p.x]; }

  int size() const { return grid.size(); }

  void push_back(const vector<int> &row) { grid.push_back(row); }
};

void printGrid(const Grid &grid) {
  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid.size(); x++) {
      cout << grid[{x, y}];
    }
    cout << endl;
  }
}

int bfs(const Grid &grid, const Point &p) {
  int completePaths = 0;
  queue<Point> q;
  q.push(p);

  while (!q.empty()) {
    Point curr = q.front();
    q.pop();

    if (grid[curr] == 9) {
      completePaths++;
      continue;
    }

    int nextValue = grid[curr] + 1;

    Point up = curr + Point::up;
    Point down = curr + Point::down;
    Point left = curr + Point::left;
    Point right = curr + Point::right;

    if (up.valid(grid.size()) && grid[up] == nextValue)
      q.push(up);

    if (down.valid(grid.size()) && grid[down] == nextValue)
      q.push(down);

    if (left.valid(grid.size()) && grid[left] == nextValue)
      q.push(left);

    if (right.valid(grid.size()) && grid[right] == nextValue)
      q.push(right);
  }

  return completePaths;
}

int main(int argc, char **argv) {
  cin.tie(0);
  ios::sync_with_stdio(0);

  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <input file>" << endl;
    return 1;
  }

  string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);

  Grid grid;
  string line;

  while (getline(cin, line)) {
    vector<int> row;
    for (int i = 0; i < line.size(); i++) {
      row.push_back(line[i] - '0');
    }
    grid.push_back(row);
  }

  printGrid(grid);

  int score = 0;

  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid.size(); x++) {
      if (grid[{x, y}] == 0) {
        score += bfs(grid, {x, y});
      }
    }
  }

  cout << score << endl;

  return 0;
}
