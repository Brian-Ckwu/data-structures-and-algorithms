#include <iostream>
#include <cassert>
#include <functional>

using namespace std;

// The following code calls a naive algorithm for computing a Fibonacci number.
//
// What to do:
// 1. Compile the following code and run it on an input "40" to check that it is slow.
//    You may also want to submit it to the grader to ensure that it gets the "time limit exceeded" message.
// 2. Implement the fibonacci_fast procedure.
// 3. Remove the line that prints the result of the naive algorithm, comment the lines reading the input,
//    uncomment the line with a call to test_solution, compile the program, and run it.
//    This will ensure that your efficient algorithm returns the same as the naive one for small values of n.
// 4. If test_solution() reveals a bug in your implementation, debug it, fix it, and repeat step 3.
// 5. Remove the call to test_solution, uncomment the line with a call to fibonacci_fast (and the lines reading the input),
//    and submit it to the grader.

int fibonacci_naive(int n) {
    if (n <= 1)
        return n;

    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

int fibonacci_fast(int n) {
    // Base cases
    if (n <= 1) {
        return n;
    }

    // Variables
    int a = 0;
    int b = 1;
    int temp = 0;

    for (int i = 2; i <= n; ++i) {
        temp = b;
        b = a + b;
        a = temp;
    }

    return b;
}

void test_solution(int n_max, function<int (int)> func_naive, function<int (int)> func_fast) {
    // Manual test
    assert(func_fast(3) == 2);
    assert(func_fast(10) == 55);

    // Test if the two algorithms come up with the same solution
    int res_naive = 0;
    int res_fast = 0;
    for (int n = 0; n < n_max; ++n) {
        res_naive = func_naive(n);
        res_fast = func_fast(n);
        cout << "res_naive: " << res_naive << " res_fast: " << res_fast << "\n";
        assert(res_naive == res_fast);
        cout << "OK\n";
    }
}

int main() {
    int n = 0;
    cin >> n;

    // cout << fibonacci_naive(n) << '\n';
    // test_solution(30, fibonacci_naive, fibonacci_fast);
    cout << fibonacci_fast(n) << '\n';
    return 0;
}
