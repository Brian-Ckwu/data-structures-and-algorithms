#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>

using namespace std;

long long MaxPairwiseProduct(const vector<int>& numbers) {
    long long max_product = 0;
    int n = numbers.size();

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = max(max_product, (long long) numbers[first] * numbers[second]);
        }
    }

    return max_product;
}

long long MaxPairWiseProductFast(const vector<int>& numbers) {
    long long max_product = 0;
    int n = numbers.size();

    // Get the first max index
    int max_index1 = -1;
    for (int i = 0; i < n; ++i) {
        if ((max_index1 == -1) || (numbers[i] > numbers[max_index1])) {
            max_index1 = i;
        }
    }

    // Get the second max index
    int max_index2 = -1;
    for (int i = 0; i < n; ++i) {
        if ((i != max_index1) && ((max_index2 == -1) || (numbers[i] > numbers[max_index2]))) {
            max_index2 = i;
        }
    }

    max_product = ((long long) numbers[max_index1]) * numbers[max_index2];

    return max_product;
}

vector<int> GenTestCase() {
    vector<int> test_case;

    // Determine the number of elements
    int n = rand() % 1000 + 2;

    // Push the elements into the vector
    for (int i = 0; i <= n; ++i) {
        test_case.push_back(rand());
    }

    return test_case;
}

void StressTest(function<long long (const vector<int>&)> func1, function<long long (const vector<int>&)> func2) {
    vector<int> test_case;
    long long res1 = 0, res2 = 0;
    
    // While loop
    int test = 1;
    while (true) {
        test_case = GenTestCase();
        res1 = func1(test_case);
        res2 = func2(test_case);

        // Display the test case and the result
        cout << "Test #" << test << "\n";
        for (int num : test_case) {
            cout << num << " ";
        }
        if (res1 == res2) {
            cout << "\nTest passed!\n";
        } else {
            cout << "\nResult 1: " << res1 << " " << "Result 2: " << res2 << "\n";
            break;
        }

        ++test;
    }
}

int main() {
    // StressTest(MaxPairwiseProduct, MaxPairWiseProductFast);

    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairWiseProductFast(numbers) << "\n";
    return 0;
}
