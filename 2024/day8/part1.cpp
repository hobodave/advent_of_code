#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;

  bool valid(int width, int height) const {
    return x >= 0 && x < width && y >= 0 && y < height;
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

bool comp(const Point &a, const Point &b) {
  return a.y < b.y || (a.y == b.y && a.x < b.x);
}

int main(int argc, char **argv) {
  cin.tie(0);
  ios::sync_with_stdio(0);

  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <input_file>\n";
  }

  string filename = argv[1];
  ifstream file(filename);
  freopen(filename.c_str(), "r", stdin);

  unordered_map<char, set<Point>> antennas;

  int width = 0, height = 0, y = 0;
  string line;
  while (getline(cin, line)) {
    istringstream iss(line);

    int x = 0;
    for (char c; iss >> c; x++) {
      if ('.' == c)
        continue;

      antennas[c].insert({x, y});
    }

    width = max(width, x);
    height = max(height, ++y);
  }

  set<Point> antinodes;

  for (auto iter = antennas.begin(); iter != antennas.end(); iter++) {
    auto points = iter->second;

    for (auto it = points.begin(); it != points.end(); it++) {
      for (auto jt = next(it); jt != points.end(); jt++) {
        Point diff = *it - *jt;
        Point left = *it + diff;
        Point right = *jt - diff;

        if (left.valid(width, height))
          antinodes.insert(left);

        if (right.valid(width, height))
          antinodes.insert(right);
      }
    }
  }

  cout << antinodes.size() << endl;

  return 0;
}
