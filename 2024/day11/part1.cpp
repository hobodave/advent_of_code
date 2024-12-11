#include <bits/stdc++.h>

using namespace std;

int numDigits(uint64_t n) {
  if (n == 0)
    return 1;
  return floor(log10(n)) + 1;
}

bool evenDigits(uint64_t n) { return numDigits(n) % 2 == 0; }

void const printStones(const list<uint64_t> &stones) {
  for (auto it = stones.begin(); it != stones.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

void const printStoneData(const list<uint64_t> &stones) {
  int oneDigit = 0, twoDigits = 0, moreDigits = 0;
  for (auto it = stones.begin(); it != stones.end(); it++) {
    if (numDigits(*it) == 1) {
      oneDigit++;
    } else if (numDigits(*it) == 2) {
      twoDigits++;
    } else {
      moreDigits++;
    }
  }
  cout << "Total stones: " << stones.size() << ", 1-digit: " << oneDigit
       << ", 2-digit: " << twoDigits << ", 3-digit+: " << moreDigits << endl;
}

void blink(list<uint64_t> &stones, int times) {
  for (int i = 0; i < times; i++) {
    for (auto it = stones.begin(); it != stones.end();) {
      if (0 == *it) {
        *it = 1;
        ++it;
      } else if (evenDigits(*it)) {
        int digits = numDigits(*it);
        auto dv = lldiv(*it, pow(10, digits / 2));
        *it = dv.quot;
        it = stones.insert(next(it), dv.rem);
        ++it;
      } else {
        *it = *it * 2024;
        ++it;
      }
    }
    cout << "After blink " << i + 1 << ": " << endl;
    printStoneData(stones);
    printStones(stones);
    cout << endl;
  }
}

int main(int argc, char **argv) {
  cin.tie(0);
  ios::sync_with_stdio(0);

  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " <input file> <# of blinks>" << endl;
    return 1;
  }

  string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);

  int blinks = atoi(argv[2]);

  list<uint64_t> stones;
  uint64_t value;

  while (cin >> value) {
    stones.push_back(value);
  }

  cout << "Initial stones: " << endl;
  printStones(stones);
  cout << endl;

  blink(stones, blinks);

  return 0;
}
