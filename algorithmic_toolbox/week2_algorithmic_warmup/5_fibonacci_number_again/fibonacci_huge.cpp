#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <cstdlib>

using namespace std;

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long long get_fibonacci_huge_fast(long long n, long long m) {
    if (n <= 1) {
        return n;
    }

    long long pre = 0;
    long long cur = 1;
    vector<long long> remainders = {0, 1};

    long long temp = 0;
    for (int i = 2; i <= n; ++i) {
        temp = cur;
        cur = (pre + cur) % m;
        pre = temp;

        if (pre == 1 && cur == 0) {
            break;
        }

        remainders.push_back(cur);
    }

    return remainders[n % remainders.size()];
}

vector<long long> GenTestCase() {
  vector<long long> test_case;

  test_case.push_back(rand() % 80);
  test_case.push_back(rand());

  return test_case;
}

void StressTest(function<long long (long long, long long)> func_naive,function<long long (long long, long long)> func_fast) {
  // Manual test
  assert(func_fast(3, 5) == 2);
  assert(func_fast(5, 2) == 1);

  // Stress test
  vector<long long> test_case;
  long long n = 0, m = 0;
  long long res_naive = 0, res_fast = 0;
  int ntest = 1;

  while (true) {
    test_case = GenTestCase();
    n = test_case[0];
    m = test_case[1];
    
    cout << "Test case #" << ntest << ": (" << n << ", " << m << ")" << "\n";

    res_naive = func_naive(n, m);
    res_fast = func_fast(n, m);

    if (res_naive == res_fast) {
        cout << "Same results: " << res_fast << "\n";
    } else {
        cout << "res_naive: " << res_naive << " res_fast: " << res_fast << "\n";
        break;
    }

    ++ntest;
  }
}

int main() {
    long long n, m;
    cin >> n >> m;
    cout << get_fibonacci_huge_fast(n, m) << '\n';
}
