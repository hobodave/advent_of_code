#include <bits/stdc++.h>

using namespace std;

struct File {
  int id;
  int start;
  int size;
};

struct FreeBlock {
  int start;
  int size;
};

void printDisk(const list<File> &files) {
  int index = 0;

  for (auto it = files.begin(); it != files.end(); it++) {
    if (it->start > index) {
      for (int i = index; i < it->start; i++) {
        cout << '.';
        index++;
      }
    }

    for (int i = 0; i < it->size; i++) {
      cout << it->id;
      index++;
    }
  }

  cout << endl;
}

// Sum of the product of the ID and each of the consecutive bytes is the same as
// the product of the ID and the sum of each of the bytes
//
// Sum of y consecutive integers starting at x is captured by the formula:
//
// x * y + (y * (y - 1)) / 2
long long checksum(const File &file) {
  long long blocks = file.size * file.start + (file.size * (file.size - 1)) / 2;
  return file.id * blocks;
}

long long checksum(const list<File> &files) {
  long long sum = 0;
  for (auto it = files.begin(); it != files.end(); it++) {
    sum += checksum(*it);
  }
  return sum;
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

  list<File> files;
  list<FreeBlock> freeBlocks;

  int id = 0, index = 0;
  bool isFileMode = true;
  char c;

  while (cin.get(c)) {
    int n = c - '0';

    if (isFileMode) {
      files.push_back({id, index, n});
      index += n;
      id++;
      isFileMode = false;
    } else {
      freeBlocks.push_back({index, n});
      index += n;
      isFileMode = true;
    }
  }

  // printDisk(files);
  // cout << checksum(files) << endl;

  // Iterate files backward
  for (auto it = files.rbegin(); it != files.rend(); it++) {
    // find earliest free block
    auto jt = find_if(freeBlocks.begin(), freeBlocks.end(),
                      [&it](const FreeBlock &fb) {
                        return fb.size >= it->size && fb.start < it->start;
                      });

    // no free block found
    if (jt == freeBlocks.end())
      continue;

    // "move" it to free block
    it->start = jt->start;

    if (it->size == jt->size) {
      // delete freeblock
      freeBlocks.erase(jt);
    } else if (it->size < jt->size) {
      // split freeblock
      jt->size -= it->size;
      jt->start += it->size;
    }
  }

  // Sort only needed if you want to print the disk
  // files.sort([](const File &a, const File &b) { return a.start < b.start; });
  // printDisk(files);
  cout << checksum(files) << endl;

  return 0;
}
