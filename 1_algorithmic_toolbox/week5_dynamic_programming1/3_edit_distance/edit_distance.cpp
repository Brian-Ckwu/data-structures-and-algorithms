#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int edit_distance(const string& str1, const string& str2) {
  // Variables for storing length of str1 & str2
  int m = str1.size();
  int n = str2.size();
  // 2D array for storing edit distances (is there a better data structure?)
  int ed[m + 1][n + 1];

  // Initialize the 2D array
  ed[0][0] = 0;
  for (int i = 1; i <= m; ++i)
    ed[i][0] = i;
  for (int j = 1; j <= n; ++j)
    ed[0][j] = j;

  // Compute edit distance using DP algorithm
  int in, del, match, mismatch;
  for (int j = 1; j <= n; ++j) { // Fill the column first. Is it okay to fill the row first? --> Yes.
    for (int i = 1; i <= m; ++i) {
      in = ed[i][j - 1] + 1;
      del = ed[i - 1][j] + 1;
      match = ed[i - 1][j - 1];
      mismatch = ed[i - 1][j - 1] + 1;
      
      if (str1[i - 1] == str2[j - 1]) {
        ed[i][j] = min(min(in, del), match);
      } else {
        ed[i][j] = min(min(in, del), mismatch);
      }
    }
  }

  return ed[m][n];
}

void manual_test() {
  assert(edit_distance("ab", "ab") == 0);
  assert(edit_distance("short", "ports") == 3);
  assert(edit_distance("editing", "distance") == 5);
}

int main() {
  // manual_test();

  string str1;
  string str2;
  cin >> str1 >> str2;
  cout << edit_distance(str1, str2) << endl;
  return 0;
}
