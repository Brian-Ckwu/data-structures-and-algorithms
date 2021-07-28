#include <iostream>
#include <functional>

using namespace std;

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
    if (n <= 1) {
        return n;
    }

    // Declare variables
    int pre = 0;
    int cur = 1;

    // Calculate the last digit
    int temp = 0;
    for (int i = 2; i <= n; ++i) {
        temp = cur;
        cur = (pre + cur) % 10;
        pre = temp;
    }

    return cur;
}

void StressTest(int n_max, function<int (int)> func_naive, function<int (int)> func_fast) {
    int res_naive = 0;
    int res_fast = 0;

    for (int n = 0; n <= n_max; ++n) {
        cout << "# Now testing f" << n << "\n";

        res_naive = func_naive(n);
        res_fast = func_fast(n);

        if (res_naive == res_fast) {
            cout << "OK\n";
        } else {
            cout << "res_naive: " << res_naive << " " << "res_fast: " << res_fast;
            break;
        }
    }
}

int main() {
    int n;
    cin >> n;
    int c = get_fibonacci_last_digit_fast(n);
    cout << c << '\n';
}

// Notebook upload
