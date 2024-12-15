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

void printGrid(vector<vector<char>> &grid) {
  for (auto &row : grid) {
    for (auto &cell : row) {
      cout << cell;
    }
    cout << endl;
  }
}

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

  int minArea = INT_MAX, minAreaTime = 0;

  for (int i = 1; i < 100000; i++) {
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;

    for (auto &robot : robots) {
      robot.move();
      minX = min(minX, robot.x);
      maxX = max(maxX, robot.x);
      minY = min(minY, robot.y);
      maxY = max(maxY, robot.y);
    }

    int width = maxX - minX + 1;
    int height = maxY - minY + 1;
    int area = width * height;

    if (area < minArea) {
      minArea = area;
      minAreaTime = i;
    }

    if (8258 == i) {
      vector<vector<char>> grid(Robot::yMax, vector<char>(Robot::xMax, '.'));
      for (auto &robot : robots) {
        grid[robot.y][robot.x] = '#';
      }
      printGrid(grid);
    }
  }

  cout << "Smallest area: " << minArea << " at time " << minAreaTime << endl;

  // // reopen cin to read from stdin
  // freopen("/dev/tty", "r", stdin);
  //
  // vector<vector<char>> grid(Robot::yMax, vector<char>(Robot::xMax, '.'));
  //
  // for (auto &robot : robots) {
  //   grid[robot.y][robot.x] = '#';
  // }
  //
  // printGrid(grid);
  //
  // int secondsElapsed = 0;
  // cout << "Seconds elapsed: " << secondsElapsed << endl;
  //
  // while (true) {
  //   getchar();
  //
  //   cout << endl << endl << endl << endl;
  //
  //   for (auto &row : grid) {
  //     fill(row.begin(), row.end(), '.');
  //   }
  //
  //   for (auto &robot : robots) {
  //     robot.move();
  //     grid[robot.y][robot.x] = '#';
  //   }
  //
  //   printGrid(grid);
  //
  //   cout << "Seconds elapsed: " << ++secondsElapsed << endl;
  // }

  return 0;
}
