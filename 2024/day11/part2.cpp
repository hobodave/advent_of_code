#include <bits/stdc++.h>

using namespace std;

struct Count {
  uint64_t value = 0;
};

int numDigits(uint64_t n) {
  if (n == 0)
    return 1;
  return floor(log10(n)) + 1;
}

bool evenDigits(uint64_t n) { return numDigits(n) % 2 == 0; }

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

void const printStoneData(const unordered_map<uint64_t, Count> &stones) {
  size_t oneDigit = 0, twoDigits = 0, moreDigits = 0;
  for (auto it = stones.begin(); it != stones.end(); it++) {
    if (numDigits(it->first) == 1) {
      oneDigit += it->second.value;
    } else if (numDigits(it->first) == 2) {
      twoDigits += it->second.value;
    } else {
      moreDigits += it->second.value;
    }
  }

  cout << "Total stones: " << (oneDigit + twoDigits + moreDigits)
       << ", 1-digit: " << oneDigit << ", 2-digit: " << twoDigits
       << ", 3-digit+: " << moreDigits << endl;
}

void blink(unordered_map<uint64_t, Count> &stones, int times) {
  for (int i = 0; i < times; i++) {
    unordered_map<uint64_t, Count> newStones;
    for (auto it = stones.begin(); it != stones.end(); it++) {
      if (0 == it->first) {
        newStones[1].value += it->second.value;
      } else if (evenDigits(it->first)) {
        int digits = numDigits(it->first);
        auto dv = lldiv(it->first, pow(10, digits / 2));
        newStones[dv.quot].value += it->second.value;
        newStones[dv.rem].value += it->second.value;
      } else {
        newStones[it->first * 2024].value += it->second.value;
      }
    }

    stones = newStones;
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

  unordered_map<uint64_t, Count> stones;
  uint64_t value;

  while (cin >> value) {
    stones[value].value++;
  }
  printStoneData(stones);

  blink(stones, blinks);
  printStoneData(stones);

  return 0;
}
