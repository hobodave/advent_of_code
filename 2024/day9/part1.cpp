#include <bits/stdc++.h>

using namespace std;

void printDisk(const vector<int> &disk) {
  for (int i = 0; i < disk.size(); i++) {
    if (disk[i] == -1) {
      cout << '.';
    } else {
      cout << disk[i];
    }
  }
  cout << endl;
}

int main(int argc, char **argv) {
  cin.tie(0);
  ios::sync_with_stdio(0);

  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <input file>" << endl;
    return 1;
  }

  string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);

  vector<int> disk;
  int id = 0;

  bool diskMode = true;
  char c;
  while (cin.get(c)) {
    int n = c - '0';

    if (diskMode) {
      for (int i = 0; i < n; i++) {
        disk.push_back(id);
      }

      id++;
      diskMode = false;
    } else {
      for (int i = 0; i < n; i++) {
        disk.push_back(-1);
      }

      diskMode = true;
    }
  }

  printDisk(disk);

  for (auto it = disk.rbegin(); it != disk.rend(); it++) {
    if (*it == -1)
      continue;

    auto jt = find(disk.begin(), disk.end(), -1);
    if (jt >= it.base())
      break;

    *jt = *it;
    *it = -1;
  }

  printDisk(disk);

  uint64_t checksum = 0;

  for (int i = 0; i < disk.size(); i++) {
    if (disk[i] == -1)
      continue;

    checksum += i * disk[i];
  }

  cout << checksum << endl;

  return 0;
}
