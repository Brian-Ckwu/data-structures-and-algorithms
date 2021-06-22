#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <cstdlib>

using namespace std;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}


int fibonacci_sum_fast(long long n) {
    if (n <= 1) {
        return n;
    }

    int presum = 0;
    int cursum = 1;
    vector<int> sums = {0, 1};

    int temp = 0;
    for (long long i = 2; i <= n; ++i) {
        temp = cursum;
        cursum = (presum + cursum + 1) % 10;
        presum = temp;
        
        if (presum == 0 && cursum == 0)
            break;
        
        sums.push_back(cursum);
    }

    return sums[n % sums.size()];
}

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    int sum_before_from = fibonacci_sum_fast(from > 0 ? from - 1 : 0);
    int total_sum = fibonacci_sum_fast(to);

    return (total_sum + 10 - sum_before_from) % 10;
}

void stress_test(function<long long (long long, long long)> func_naive, function<long long (long long, long long)> func_fast) {
    assert(func_fast(0, 0) == 0);
    assert(func_fast(0, 1) == 1);
    assert(func_fast(0, 3) == 4);
    assert(func_fast(2, 5) == 1);

    int from = 0;
    int to = 0;
    int ntest = 1;
    while (true) {
        from = rand() % 50;
        to = rand() % 30 + from;

        cout << "Test #" << ntest << ": (from, to) = " << "(" << from << ", " << to << ")\n";
        assert(func_naive(from, to) == func_fast(from, to));

        ++ntest;
    }
}

int main() {
    // stress_test(get_fibonacci_partial_sum_naive, get_fibonacci_partial_sum_fast);

    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
