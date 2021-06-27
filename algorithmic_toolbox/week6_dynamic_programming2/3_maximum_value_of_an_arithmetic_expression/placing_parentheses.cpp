#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

long long eval(long long a, long long b, char op) {
  long long result = 0;

  if (op == '*') {
    result = a * b;
  } else if (op == '+') {
    result = a + b;
  } else if (op == '-') {
    result = a - b;
  } else {
    assert(0);
  }

  return result;
}

long long get_maximum_value(const string& exp) {
  // Extract the digits and operations from the expression (string)
  vector<int> d;
  vector<char> op;

  for (int i = 0; i < exp.size(); ++i) {
    if (i % 2 == 0) {
      assert(isdigit(exp[i]));
      d.push_back(exp[i] - '0');
    } else {
      assert(!isdigit(exp[i]));
      op.push_back(exp[i]);
    }
  }

  // 2D arrays for storing the minimum and maximum values of expression(i, j)
  int n = d.size();
  long long mins[n][n];
  long long maxs[n][n];
  memset(mins, 0, sizeof(long long) * n * n);
  memset(maxs, 0, sizeof(long long) * n * n);

  // Initialize the 2D arrays (i.e. array[i][i] = d[i])
  for (int i = 0; i < n; ++i) {
    mins[i][i] = d[i];
    maxs[i][i] = d[i];
  }

  // DP algorithm (fill both 2D arrays in increasing order of j - i)
  long long MM, Mm, mM, mm;
  long long min_value, max_value;
  for (int k = 1; k < n; ++k) {
    for (int i = 0; i < n - k; ++i) {
      min_value = LLONG_MAX;
      max_value = LLONG_MIN;
      for (int op_num = 0; op_num < k; ++op_num) {
        MM = eval(maxs[i][i + op_num], maxs[i + op_num + 1][i + k], op[i + op_num]);
        Mm = eval(maxs[i][i + op_num], mins[i + op_num + 1][i + k], op[i + op_num]);
        mM = eval(mins[i][i + op_num], maxs[i + op_num + 1][i + k], op[i + op_num]);
        mm = eval(mins[i][i + op_num], mins[i + op_num + 1][i + k], op[i + op_num]);

        min_value = min(min(min_value, min(MM, Mm)), min(mM, mm));
        max_value = max(max(max_value, max(MM, Mm)), max(mM, mm));
      }
      mins[i][i + k] = min_value;
      maxs[i][i + k] = max_value;
    }
  }

  return maxs[0][n - 1];
}

int main() {
  string s;
  cin >> s;
  cout << get_maximum_value(s) << '\n';
}
