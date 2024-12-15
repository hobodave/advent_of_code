#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);

  string line;
  int safe = 0;

  while (getline(cin, line)) {
    istringstream iss(line);
    int mode = 0; // 0 - ascending, 1 - descending
    int previous = -1;
    int current = -1;
    bool valid = false;

    iss >> previous;
    iss >> current;

    int descending = previous - current;
    int ascending = current - previous;

    if (descending >= 1 && descending <= 3) {
      mode = 1;
    } else if (ascending >= 1 && ascending <= 3) {
      mode = 0;
    } else {
      // unsafe
      continue;
    }

    valid = true;
    previous = current;

    while (iss >> current) {
      if (mode == 0) {
        if (current - previous >= 1 && current - previous <= 3) {
          previous = current;
        } else {
          valid = false;
          break;
        }
      } else {
        if (previous - current >= 1 && previous - current <= 3) {
          previous = current;
        } else {
          valid = false;
          break;
        }
      }
    }

    if (valid) {
      safe++;
    }
  }

  cout << safe << endl;

  return 0;
}
