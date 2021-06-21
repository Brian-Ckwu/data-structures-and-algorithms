#include <iostream>
#include <functional>
#include <cassert>
#include <vector>
#include <cstdlib>

using namespace std;

int GCDNaive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int GCDFast(int a, int b) {
  // Base case
  if (b == 0) {
    return a;
  }

  // Euclidean algorithm
  return GCDFast(b, a % b);
}

vector<int> GenTestCase() {
  vector<int> test_case;

  for (int i = 0; i < 2; ++i) {
    test_case.push_back(rand());
  }

  return test_case;
}

void StressTest(function<int (int, int)> func_naive,function<int (int, int)> func_fast) {
  // Manual test
  assert(func_fast(3, 5) == 1);
  assert(func_fast(0, 15) == 15);
  assert(func_fast(25, 35) == 5);

  // Stress test
  vector<int> test_case;
  int num1 = 0, num2 = 0;
  int res_naive = 0, res_fast = 0;
  int ntest = 1;

  while (true) {
    test_case = GenTestCase();
    num1 = test_case[0];
    num2 = test_case[1];
    
    cout << "Test case #" << ntest << ": (" << num1 << ", " << num2 << ")" << "\n";

    res_naive = func_naive(num1, num2);
    res_fast = func_fast(num1, num2);

    assert(res_naive == res_fast);
    cout << "Same results: " << res_fast << "\n";
    cout << "OK\n";

    ++ntest;
  }
}

int main() {
  // StressTest(GCDNaive, GCDFast);

  int a, b;
  cin >> a >> b;
  cout << GCDFast(a, b) << endl;
  return 0;
}

// Notebook upload
