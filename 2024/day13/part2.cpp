#include <bits/stdc++.h>

using namespace std;

uint64_t cramersRuleCost(int64_t ax, int64_t ay, int64_t bx, int64_t by,
                         int64_t px, int64_t py) {
  int64_t det = ax * by - ay * bx;
  int64_t detA = px * by - py * bx;
  int64_t detB = ax * py - ay * px;

  if (det == 0) // Either 0 or infinite solutions
    return 0;

  int64_t a, b;

  if (detA % det != 0 || detB % det != 0) // No integer solutions
    return 0;

  a = detA / det;
  b = detB / det;

  return 3 * a + b;
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

  int64_t ax, ay, bx, by, px, py, totalCost = 0;
  string line;
  regex buttonARegex(R"(Button A: X\+(\d+), Y\+(\d+))");
  regex buttonBRegex(R"(Button B: X\+(\d+), Y\+(\d+))");
  regex prizeRegex(R"(Prize: X=(\d+), Y=(\d+))");

  while (getline(cin, line)) {
    smatch match;
    if (regex_match(line, match, buttonARegex)) {
      ax = stoll(match[1]);
      ay = stoll(match[2]);
    }
    getline(cin, line);
    if (regex_match(line, match, buttonBRegex)) {
      bx = stoll(match[1]);
      by = stoll(match[2]);
    }
    getline(cin, line);
    if (regex_match(line, match, prizeRegex)) {
      px = stoll(match[1]) + 10000000000000;
      py = stoll(match[2]) + 10000000000000;
    }

    cout << "Button A: (" << ax << ", " << ay << ")" << endl;
    cout << "Button B: (" << bx << ", " << by << ")" << endl;
    cout << "Prize: (" << px << ", " << py << ")" << endl;
    cout << cramersRuleCost(ax, ay, bx, by, px, py) << endl;
    cout << endl;

    totalCost += cramersRuleCost(ax, ay, bx, by, px, py);

    getline(cin, line); // Skip empty line
  }

  cout << totalCost << endl;

  return 0;
}
