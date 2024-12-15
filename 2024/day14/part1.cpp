#include <bits/stdc++.h>
using namespace std;

struct Robot {
  int x, y;
  int dx, dy;

  static int xMax;
  static int yMax;

  void move() {
    x = (x + dx + xMax) % xMax;
    y = (y + dy + yMax) % yMax;
  }

  void printPos() { cout << "x: " << x << ", y: " << y << endl; }
};

int Robot::xMax = 101;
int Robot::yMax = 103;

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <input file>" << endl;
    return 1;
  }

  cin.tie(0);
  ios::sync_with_stdio(0);

  string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);

  vector<Robot> robots;
  int px, py, dx, dy;
  string line;
  regex lineRegex(R"(p=(\d+),(\d+) v=(-?\d+),(-?\d+))");
  smatch match;

  while (getline(cin, line)) {
    if (regex_match(line, match, lineRegex)) {
      px = stoi(match[1]);
      py = stoi(match[2]);
      dx = stoi(match[3]);
      dy = stoi(match[4]);
      robots.push_back({px, py, dx, dy});
    }
  }

  int tl = 0, tr = 0, bl = 0, br = 0;

  for (auto &robot : robots) {
    for (int i = 0; i < 100; i++) {
      robot.move();
      // robot.printPos();
    }

    if (robot.x < 50) {
      if (robot.y < 51) {
        tl++;
      } else if (robot.y > 51) {
        bl++;
      }
    } else if (robot.x > 50) {
      if (robot.y < 51) {
        tr++;
      } else if (robot.y > 51) {
        br++;
      }
    }
  }

  cout << tl * tr * bl * br << endl;

  return 0;
}
