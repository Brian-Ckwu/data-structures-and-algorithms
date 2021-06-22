#include <iostream>
#include <vector>
#include <functional>
#include <cassert>

using namespace std;

int GCDFast(int a, int b) {
  // Base case
  if (b == 0) {
    return a;
  }

  // Euclidean algorithm
  return GCDFast(b, a % b);
}

long long LCMNaive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long long LCMFast(int a, int b) {
  return (long long) a * b / GCDFast(a, b);
}

vector<int> GenTestCase() {
  vector<int> test_case;

  for (int i = 0; i < 2; ++i) {
    test_case.push_back((rand() % 100) + 1);
  }

  return test_case;
}

void StressTest(function<int (int, int)> func_naive,function<int (int, int)> func_fast) {
  // Manual test
  assert(func_naive(3, 5) == 15);
  assert(func_naive(25, 35) == 175);

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
  // StressTest(LCMNaive, LCMFast);

  int a, b;
  std::cin >> a >> b;
  std::cout << LCMFast(a, b) << std::endl;
  return 0;
}
