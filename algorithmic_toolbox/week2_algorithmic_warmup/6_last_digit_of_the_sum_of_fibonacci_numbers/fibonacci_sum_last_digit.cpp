#include <iostream>
#include <functional>
#include <cassert>

using namespace std;

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

int fibonacci_sum_fast(long long n) {
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
        sum = (sum + cur) % 10;
    }

    return sum;
}

void StressTest(long long n_max, function<int (long long)> func_naive,function<int (long long)> func_fast) {
    int res_naive = 0, res_fast = 0;
    
    for (long long n = 0; n <= n_max; ++n) {
        cout << "Test #" << n << "\n";

        res_naive = func_naive(n);
        res_fast = func_fast(n);

        if (res_naive == res_fast) {
            cout << "Same results: " << res_fast << "\n";
        } else {
            cout << "res_naive: " << res_naive << " res_fast: " << res_fast << "\n";
            break;
        }
    }
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n);
}
