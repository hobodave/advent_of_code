#include <bits/stdc++.h>

using namespace std;

constexpr int MAX = 130;

enum Direction { UP, RIGHT, DOWN, LEFT };

struct Point {
  int x, y;

  bool valid() { return x >= 0 && x < MAX && y >= 0 && y < MAX; }

  bool operator==(const Point &p) const { return x == p.x && y == p.y; }

  friend ostream &operator<<(ostream &out, const Point &p) {
    return out << "{" << p.x << ", " << p.y << "}";
  }
};

struct PointHash {
  size_t operator()(const Point &p) const {
    return hash<int>()(p.x) ^ hash<int>()(p.y);
  }
};

struct Grid {
  vector<vector<char>> grid{MAX, vector<char>(MAX, '.')};

  char &operator[](Point p) { return grid[p.y][p.x]; }
};

struct Guard {
  Direction facing{UP};
  Point pos;
  Grid map;
  unordered_set<Point, PointHash> visited;

  void init(Point p) {
    pos = p;
    visited.insert(p);
  }

  void move() {
    Point nextPos = next();

    if (nextPos.valid() && peek(nextPos) == '#') {
      facing = static_cast<Direction>((facing + 1) % 4);
    } else {
      pos = nextPos;

      if (gone())
        return;

      visited.insert(pos);
    }
  }

  Point next() {
    switch (facing) {
    case UP:
      return {pos.x, pos.y - 1};
    case RIGHT:
      return {pos.x + 1, pos.y};
    case DOWN:
      return {pos.x, pos.y + 1};
    case LEFT:
      return {pos.x - 1, pos.y};
    }
  }

  char peek(const Point &p) { return map[p]; }

  bool gone() { return !pos.valid(); }

  friend ostream &operator<<(std::ostream &out, const Guard &guard) {
    out << "Guard at " << guard.pos << " facing ";
    out << (guard.facing == UP      ? "UP"
            : guard.facing == RIGHT ? "RIGHT"
            : guard.facing == DOWN  ? "DOWN"
                                    : "LEFT");
    return out << "\tVisited " << guard.visited.size() << " points\n";
  }
};

void printGrid(Grid &grid) {
  for (int y = 0; y < MAX; y++) {
    for (int x = 0; x < MAX; x++) {
      cout << grid[{x, y}];
    }
    cout << "\n";
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);

  string line;
  Guard guard;

  for (int y = 0; y < MAX; y++) {
    getline(cin, line);

    for (int x = 0; x < MAX; x++) {
      guard.map[{x, y}] = line[x];

      if ('^' == line[x]) {
        guard.init({x, y});
      }
    }
  }

  printGrid(guard.map);
  cout << guard;

  while (!guard.gone()) {
    guard.move();
  }

  cout << guard << "\n";
  cout << guard.visited.size() << "\n";

  return 0;
}
