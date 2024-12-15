#include <bits/stdc++.h>

using namespace std;

void printGrid(vector<vector<char>> &grid) {
  for (int i = 0; i < 140; i++) {
    for (int j = 0; j < 140; j++) {
      cout << grid[i][j];
    }
    cout << "\n";
  }
}

bool hasXmas(vector<vector<char>> &grid, int x, int y) {

  if (x == 0 || y == 0 || x == 139 || y == 139) {
    return false;
  }

  set<char> uldr;
  set<char> urdl;

  uldr.insert(grid[y - 1][x - 1]);
  uldr.insert(grid[y + 1][x + 1]);

  urdl.insert(grid[y - 1][x + 1]);
  urdl.insert(grid[y + 1][x - 1]);

  if (uldr.contains('M') && uldr.contains('S') && (uldr == urdl)) {
    return true;
  }

  return false;
}

int countXmas(vector<vector<char>> &grid) {
  int count = 0;
  for (int y = 0; y < 140; y++) {
    for (int x = 0; x < 140; x++) {
      if (grid[y][x] == 'A' && hasXmas(grid, x, y)) {
        count++;
      }
    }
  }

  return count;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);

  vector<vector<char>> grid(140, vector<char>(140, '.'));
  string line;

  for (int y = 0; y < 140; y++) {
    getline(cin, line);

    for (int x = 0; x < 140; x++) {
      grid[y][x] = line[x];
    }
  }

  printGrid(grid);

  cout << countXmas(grid) << "\n";

  return 0;
}
