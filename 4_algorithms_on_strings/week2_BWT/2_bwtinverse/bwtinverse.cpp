#include <bits/stdc++.h>

using namespace std;

string InverseBWT(const string& bwt) {
  int n = bwt.size();
  string lcol(bwt.begin(), bwt.end());
  string fcol(bwt.begin(), bwt.end());
  sort(fcol.begin(), fcol.end());
  // storing positions
  unordered_map<char, vector<int>> lcol_pos;
  vector<pair<char, int>> lcol_pair;
  for (int i = 0; i < n; ++i) {
    char ch = lcol[i];
    if (lcol_pos.count(ch)) {
      lcol_pos[ch].push_back(i);
    } else {
      lcol_pos[ch] = vector<int>(1, i);
    }
    lcol_pair.push_back(make_pair(ch, lcol_pos[ch].size() - 1));
  }
  unordered_map<char, vector<int>> fcol_pos; // this data structure is not required actually
  vector<pair<char, int>> fcol_pair;
  for (int i = 0; i < n; ++i) {
    char ch = fcol[i];
    if (fcol_pos.count(ch)) {
      fcol_pos[ch].push_back(i);
    } else {
      fcol_pos[ch] = vector<int>(1, i);
    }
    fcol_pair.push_back(make_pair(ch, fcol_pos[ch].size() - 1));
  }
  // reconstructing the text
  // finding the $ symbol
  int symbol_pos;
  for (int i = 0; i < n; ++i) {
    if (lcol[i] == '$') {
      symbol_pos = i;
    }
  }
  // start reconstructing
  string text = "";
  for (int j = 0, pos = symbol_pos; j < n; ++j) {
    pair<char, int> ch_pair = fcol_pair[pos];
    char ch = ch_pair.first;
    int i = ch_pair.second;
    text.push_back(ch);
    pos = lcol_pos[ch][i];
  }

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
