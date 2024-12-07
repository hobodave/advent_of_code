#include <bits/stdc++.h>

using namespace std;

int MAX = 10;

enum Direction { UP, RIGHT, DOWN, LEFT };

struct Point {
  int x, y;

  bool valid() { return x >= 0 && x < MAX && y >= 0 && y < MAX; }

  bool operator==(const Point &p) const { return x == p.x && y == p.y; }

  friend ostream &operator<<(ostream &out, const Point &p) {
    return out << "{" << p.x << ", " << p.y << "}";
  }
};

struct Visit {
  Point pos;
  Direction facing;

  bool operator==(const Visit &v) const {
    return pos == v.pos && facing == v.facing;
  }
};

namespace std {
template <> struct hash<Point> {
  size_t operator()(const Point &p) const {
    return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
  }
};

template <> struct hash<Visit> {
  size_t operator()(const Visit &v) const {
    return hash<Point>()(v.pos) ^ (hash<int>()(v.facing) << 1);
  }
};
} // namespace std

struct Grid {
  vector<vector<char>> grid;

  Grid(int size) : grid(size, vector<char>(size, '.')) {}

  char &operator[](Point p) { return grid[p.y][p.x]; }
};

struct Guard {
  Direction facing{UP};
  Point pos;
  Grid map{MAX};
  unordered_set<Point> visitedPoints;
  unordered_set<Visit> visits;
  bool looping{false};

  void init(Point p) {
    pos = p;
    facing = UP;
    visitedPoints.insert(p);
    visits.insert({p, facing});
  }

  void move() {
    Point nextPos = next();

    if (nextPos.valid() && peek(nextPos) == '#') {
      facing = static_cast<Direction>((facing + 1) % 4);
    } else {
      pos = nextPos;

      if (gone())
        return;

      if (visits.contains({pos, facing})) {
        looping = true;
        return;
      }

      visitedPoints.insert(pos);
      visits.insert({pos, facing});
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

  void reset() {
    pos = {0, 0};
    facing = UP;
    visitedPoints.clear();
    visits.clear();
    looping = false;
  }

  friend ostream &operator<<(std::ostream &out, const Guard &guard) {
    out << "Guard at " << guard.pos << " facing ";
    out << (guard.facing == UP      ? "UP"
            : guard.facing == RIGHT ? "RIGHT"
            : guard.facing == DOWN  ? "DOWN"
                                    : "LEFT");
    return out << "\tVisited " << guard.visitedPoints.size() << " points\n";
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

int main(int argc, char **argv) {
  cin.tie(0);
  ios::sync_with_stdio(0);

  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
  }

  char *filename = argv[1];

  freopen(filename, "r", stdin);

  string line;
  Guard guard;
  Point start;
  Grid grid(MAX);
  int y = 0;

  while (getline(cin, line)) {

    if (y == 0) {
      MAX = line.size();
      grid = Grid(MAX);
      guard.map = Grid(MAX);
    }

    for (int x = 0; x < MAX; x++) {
      guard.map[{x, y}] = line[x];
      grid[{x, y}] = line[x];

      if ('^' == line[x]) {
        start = {x, y};
        guard.init(start);
      }
    }

    y++;
  }

  while (!guard.gone()) {
    guard.move();
  }

  auto visited = guard.visitedPoints;
  int loopablePoints = 0;
  for (Point p : visited) {
    guard.reset();
    guard.map = grid;
    guard.map[p] = '#';
    guard.init(start);

    while (!(guard.gone() || guard.looping)) {
      guard.move();
    }

    if (guard.looping) {
      loopablePoints++;
    }
  }

  cout << loopablePoints << "\n";

  return 0;
}
