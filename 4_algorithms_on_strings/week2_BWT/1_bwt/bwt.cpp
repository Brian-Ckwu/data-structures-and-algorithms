#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::sort;

string BWT(const string& text) {
  int n = text.size();
  // make the text cycle
  string text_cycle = text + string(text.begin(), text.end() - 1);
  // make the matrix
  vector<string> matrix;
  for (int i = 0; i < n; ++i) {
    matrix.push_back(string(text_cycle.begin() + i, text_cycle.begin() + i + n));
  }
  // sort the matrix
  sort(matrix.begin(), matrix.end());
  // append the characters in the last column of the matrix to result
  string result = "";
  for (int i = 0; i < n; ++i) {
    result.push_back(matrix[i][n - 1]);
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}