#include <bits/stdc++.h>

using namespace std;

bool test(long target, const vector<long> &nums, size_t index, long current) {
  if (current > target) {
    return false;
  }

  if (index == nums.size() - 1) {
    return current == target;
  }

  // Try addition
  if (test(target, nums, index + 1, current + nums[index + 1])) {
    return true;
  }

  // Try multiplication
  if (test(target, nums, index + 1, current * nums[index + 1])) {
    return true;
  }

  return false;
};

int main(int argc, char **argv) {
  cin.tie(0);
  ios::sync_with_stdio(0);

  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <input_file>"
         << "\n";

    return 1;
  }

  char *filename = argv[1];
  freopen(filename, "r", stdin);

  long sum = 0;
  string line;

  while (getline(cin, line)) {
    istringstream iss(line);

    string part;
    getline(iss, part, ':');

    long testValue = stol(part);

    vector<long> values;

    while (iss >> part) {
      values.push_back(stol(part));
    }

    if (test(testValue, values, 0, values[0])) {
      sum += testValue;
    }
  }

  cout << sum << endl;

  return 0;
}
