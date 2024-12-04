#include <bits/stdc++.h>

using namespace std;

bool isValid(vector<int> set) {
  int mode = 0; // 0 - ascending, 1 - descending
  int previous = -1;
  int current = -1;
  bool valid = false;

  previous = set[0];
  current = set[1];

  int descending = previous - current;
  int ascending = current - previous;

  if (descending >= 1 && descending <= 3) {
    mode = 1;
  } else if (ascending >= 1 && ascending <= 3) {
    mode = 0;
  } else {
    return false;
  }

  valid = true;
  previous = current;

  for (int i = 2; i < set.size(); i++) {
    current = set[i];
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

  return valid;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);

  int validCount = 0;

  string line;

  while (getline(cin, line)) {
    // cout << line << "\n";

    vector<int> numbers;
    int number;
    istringstream iss(line);

    while (iss >> number) {
      numbers.push_back(number);
    }

    if (isValid(numbers)) {
      validCount++;
      continue;
    }

    vector<vector<int>> subsets(numbers.size());

    for (int i = 0; i < numbers.size(); i++) {
      for (int j = 0; j < numbers.size(); j++) {
        if (j != i) {
          subsets[i].push_back(numbers[j]);
        }
      }
    }

    for (int i = 0; i < subsets.size(); i++) {
      if (isValid(subsets[i])) {
        validCount++;
        break;
      }
    }
  }

  cout << validCount << "\n";

  return 0;
}
