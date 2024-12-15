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

int hasXmas(vector<vector<char>> &grid, int x, int y) {
  int matches = 0;

  if (x + 3 < 140) { // right}
    if (grid[y][x + 1] == 'M' && grid[y][x + 2] == 'A' &&
        grid[y][x + 3] == 'S') {
      matches++;
    }

    if (y + 3 < 140) { // down right
      if (grid[y + 1][x + 1] == 'M' && grid[y + 2][x + 2] == 'A' &&
          grid[y + 3][x + 3] == 'S') {
        matches++;
      }
    }
  }

  if (y + 3 < 140) { // down
    if (grid[y + 1][x] == 'M' && grid[y + 2][x] == 'A' &&
        grid[y + 3][x] == 'S') {
      matches++;
    }
    if (x - 3 >= 0) { // down left
      if (grid[y + 1][x - 1] == 'M' && grid[y + 2][x - 2] == 'A' &&
          grid[y + 3][x - 3] == 'S') {
        matches++;
      }
    }
  }

  if (x - 3 >= 0) { // left
    if (grid[y][x - 1] == 'M' && grid[y][x - 2] == 'A' &&
        grid[y][x - 3] == 'S') {
      matches++;
    }
    if (y - 3 >= 0) { // up left
      if (grid[y - 1][x - 1] == 'M' && grid[y - 2][x - 2] == 'A' &&
          grid[y - 3][x - 3] == 'S') {
        matches++;
      }
    }
  }

  if (y - 3 >= 0) { // up
    if (grid[y - 1][x] == 'M' && grid[y - 2][x] == 'A' &&
        grid[y - 3][x] == 'S') {
      matches++;
    }
    if (x + 3 < 140) { // up right
      if (grid[y - 1][x + 1] == 'M' && grid[y - 2][x + 2] == 'A' &&
          grid[y - 3][x + 3] == 'S') {
        matches++;
      }
    }
  }

  return matches;
}

int countXmas(vector<vector<char>> &grid) {
  int count = 0;
  for (int y = 0; y < 140; y++) {
    for (int x = 0; x < 140; x++) {
      if (grid[y][x] == 'X') {
        count += hasXmas(grid, x, y);
      }
    }
  }

  return count;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);

  // initialize a 140x140 grid of chars
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
