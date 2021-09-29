#include <bits/stdc++.h>

using namespace std;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

const int kCharacters = 5;

int ch2id(char ch) {
  switch(ch) {
    case '$': return 0; break;
    case 'A': return 1; break;
    case 'C': return 2; break;
    case 'G': return 3; break;
    case 'T': return 4; break;
    default: assert (false); return -1;
  }
}

vector<int> sort_characters(const string& text) {
  int n = text.size();
  vector<int> order(n);
  vector<int> count(kCharacters, 0);
  // counting
  for (int i = 0; i < n; ++i) {
    ++count[ch2id(text[i])];
  }
  // partial sum
  for (int i = 1; i < kCharacters; ++i) {
    count[i] = count[i - 1] + count[i];
  }
  // sort
  for (int i = n - 1; i >= 0; --i) {
    int chid = ch2id(text[i]);
    --count[chid];
    order[count[chid]] = i;
  }
  return order;
}

vector<int> build_equi_classes(const string& text, const vector<int>& order) {
  int n = text.size();
  vector<int> classes(n, 0);
  for (int i = 1; i < n; ++i) {
    int cur = order[i], prev = order[i - 1];
    if (text[cur] == text[prev]) {
      classes[cur] = classes[prev];
    } else {
      classes[cur] = classes[prev] + 1;
    }
  }
  return classes;
}

vector<int> sort_doubled(const vector<int>& order, const vector<int>& classes, int L) {
  int n = order.size();
  vector<int> new_order(n);
  vector<int> count(n, 0);
  // counting
  for (int i = 0; i < n; ++i) {
    ++count[classes[order[i]]];
  }
  // partial sum
  for (int i = 1; i < n; ++i) {
    count[i] = count[i - 1] + count[i];
  }
  // sort doubled
  for (int i = n - 1; i >= 0; --i) {
    int chid = (order[i] - L + n) % n;
    int cl = classes[chid];
    --count[cl];
    new_order[count[cl]] = chid;
  }
  return new_order;
}

vector<int> update_classes(const vector<int>& new_order, const vector<int>& classes, int L) {
  int n = new_order.size();
  vector<int> new_classes(n);
  new_classes[new_order[0]] = 0;
  for (int i = 1; i < n; ++i) {
    int lcur = new_order[i], lprev = new_order[i - 1];
    int rcur = (lcur + L) % n, rprev = (lprev + L) % n;
    if (classes[lcur] == classes[lprev] && classes[rcur] == classes[rprev]) {
      new_classes[lcur] = new_classes[lprev];
    } else {
      new_classes[lcur] = new_classes[lprev] + 1;
    }
  }
  return new_classes;
}

vector<int> BuildSuffixArray(const string& text) {
  int n = text.size();
  vector<int> order = sort_characters(text);
  vector<int> classes = build_equi_classes(text, order);
  int L = 1;
  while (L < n) {
    order = sort_doubled(order, classes, L);
    classes = update_classes(order, classes, L);
    L = 2 * L;
  }
  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
