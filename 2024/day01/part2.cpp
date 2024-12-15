#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);

  array<long long, 1000> left;

  unordered_map<long long, long long> frequency;

  string line;
  int i = 0;

  while (getline(cin, line)) {
    istringstream iss(line);
    long long right;

    iss >> left[i];

    while (iss >> right) {
      frequency[right]++;
    }

    i++;
  }

  long long similarityScore = 0;

  for (int i = 0; i < 1000; i++) {
    similarityScore += left[i] * frequency[left[i]];
  }

  cout << similarityScore << endl;

  return 0;
}
