#include <bits/stdc++.h>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

// O(|patterns|)
trie build_trie(vector<string>& patterns) {
  trie t;
  t.resize(1);
  for (string& pattern : patterns) {
    int node = 0;
    for (char ch : pattern) {
      if (t[node].count(ch) == 0) {
        int new_node = t.size();
        t[node].insert(make_pair(ch, new_node));
        t.push_back(edges());
        node = new_node;
      } else {
        node = t[node][ch];
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto& j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}