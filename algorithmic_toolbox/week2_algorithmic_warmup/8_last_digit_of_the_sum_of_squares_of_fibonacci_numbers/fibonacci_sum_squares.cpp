#include <iostream>
#include <functional>
#include <cassert>

using namespace std;

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}

int fibonacci_sum_squares_fast(long long n) {
    if (n <= 1) {
        return n;
    }

    int pre = 0;
    int cur = 1;
    int sum = 1;

    int temp = 0;
    for (long long i = 2; i <= n; ++i) {
        temp = cur;
        cur = (pre + cur) % 10;
        pre = temp;
        sum = (sum + cur * cur) % 10;
    }

    return sum;
}

void stress_test(int n_max, function<int (long long)> func_naive, function<int (long long)> func_fast) {
    // Manual test
    assert(func_fast(2) == 2);
    assert(func_fast(3) == 6);

    for (int n = 0; n <= n_max; ++n) {
        cout << "Test #" << n << "\n";
        assert(func_naive(n) == func_fast(n));
    }
}

int main() {

    // stress_test(30, fibonacci_sum_squares_naive, fibonacci_sum_squares_fast);
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_fast(n);
}
