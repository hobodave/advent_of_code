#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);

  array<long long, 1000> left;
  array<long long, 1000> right;

  string line;
  int i = 0;

  while (getline(cin, line)) {
    istringstream iss(line);

    iss >> left[i] >> right[i];

    i++;
  }

  sort(left.begin(), left.end());
  sort(right.begin(), right.end());

  long long cumulativeDistance = 0;

  for (int i = 0; i < 1000; i++) {
    cumulativeDistance += abs(left[i] - right[i]);
  }

  cout << cumulativeDistance << endl;

  return 0;
}
