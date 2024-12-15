#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);

  regex mul_regex("mul\\((\\d{1,3}),(\\d{1,3})\\)");
  int sum = 0;

  string line;

  while (getline(cin, line)) {
    auto matches_begin = sregex_iterator(line.begin(), line.end(), mul_regex);
    auto matches_end = sregex_iterator();

    for (sregex_iterator i = matches_begin; i != matches_end; ++i) {
      smatch match = *i;

      sum += stoi(match.str(1)) * stoi(match.str(2));
    }
  }

  cout << sum << "\n";

  return 0;
}
