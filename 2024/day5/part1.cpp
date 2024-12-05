#include <bits/stdc++.h>

using namespace std;

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::set<T> &set) {
  if (set.empty())
    return out << "{}";
  out << "{ " << *set.begin();
  std::for_each(std::next(set.begin()), set.end(),
                [&out](const T &element) { out << ", " << element; });
  return out << " }";
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &vec) {
  if (vec.empty())
    return out << "[]";
  out << "[ " << vec[0];
  std::for_each(std::next(vec.begin()), vec.end(),
                [&out](const T &element) { out << ", " << element; });
  return out << " ]";
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);

  map<int, set<int>> afters;
  int sum = 0;

  string line;
  while (getline(cin, line)) {
    if (line.empty())
      break;

    istringstream iss(line);
    string page;
    int before, after;

    getline(iss, page, '|');
    before = stoi(page);

    getline(iss, page, '|');
    after = stoi(page);

    afters[after].insert(before);
  }

  while (getline(cin, line)) {
    istringstream iss(line);
    vector<int> pages;

    for (string page; getline(iss, page, ',');) {
      pages.push_back(stoi(page));
    }

    bool valid = true;
    // cout << "Pages: " << pages << endl;

    for (int i = 0; i < pages.size(); i++) {
      int page = pages[i];
      // cout << "Page: " << page << endl;
      // cout << "Must come after: " << afters[page] << endl;

      for (int j = (i + 1); j < pages.size(); j++) {
        if (afters[page].contains(pages[j])) {
          valid = false;
          break;
        }
      }

      if (!valid)
        break;
    }

    if (valid)
      sum += pages[pages.size() / 2];
  }

  cout << sum << endl;

  return 0;
}
