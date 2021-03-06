#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.

vector<int> compute_prefix(const string& pnt) {
  int n = pnt.size();
  vector<int> s(n, 0);
  int border = 0;
  for (int i = 1; i < n; ++i) {
    while ((border > 0) && (pnt[i] != pnt[border])) {
      border = s[border - 1];
    }
    if (pnt[i] == pnt[border]) {
      ++border;
    } else {
      border = 0;
    }
    s[i] = border;
  }
  return s;
}

// Knuth-Morris-Pratt Algorithm: O(|pattern| + |text|)
vector<int> find_pattern(const string& pattern, const string& text) {
  string pnt = pattern + '$' + text;
  vector<int> s = compute_prefix(pnt);
  vector<int> result;
  int p = pattern.size(), n = pnt.size();
  for (int i = p + 1; i < n; ++i) {
    if (s[i] == p) {
      result.push_back(i - 2 * p);
    }
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
