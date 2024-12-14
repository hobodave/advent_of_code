#include <bits/stdc++.h>

using namespace std;

int cramersRuleCost(int ax, int ay, int bx, int by, int px, int py) {
  int det = ax * by - ay * bx;
  int detA = px * by - py * bx;
  int detB = ax * py - ay * px;

  if (det == 0) // Either 0 or infinite solutions
    return 0;

  int a, b;

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

  int ax, ay, bx, by, px, py, totalCost = 0;
  string line;
  regex buttonARegex(R"(Button A: X\+(\d+), Y\+(\d+))");
  regex buttonBRegex(R"(Button B: X\+(\d+), Y\+(\d+))");
  regex prizeRegex(R"(Prize: X=(\d+), Y=(\d+))");

  while (getline(cin, line)) {
    smatch match;
    if (regex_match(line, match, buttonARegex)) {
      ax = stoi(match[1]);
      ay = stoi(match[2]);
    }
    getline(cin, line);
    if (regex_match(line, match, buttonBRegex)) {
      bx = stoi(match[1]);
      by = stoi(match[2]);
    }
    getline(cin, line);
    if (regex_match(line, match, prizeRegex)) {
      px = stoi(match[1]);
      py = stoi(match[2]);
    }

    // cout << "Button A: (" << ax << ", " << ay << ")" << endl;
    // cout << "Button B: (" << bx << ", " << by << ")" << endl;
    // cout << "Prize: (" << px << ", " << py << ")" << endl;
    // cout << cramersRuleCost(ax, ay, bx, by, px, py) << endl;
    // cout << endl;

    totalCost += cramersRuleCost(ax, ay, bx, by, px, py);

    getline(cin, line); // Skip empty line
  }

  cout << totalCost << endl;

  return 0;
}
