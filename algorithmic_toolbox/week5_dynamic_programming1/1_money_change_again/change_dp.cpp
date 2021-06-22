#include <iostream>
#include <functional>
#include <cassert>

using namespace std;

int get_change_dp(int m) {
  // Arrays
  int coins[3] = {1, 3, 4};
  int min_coins_nums[m + 1] = {0};

  // DP algorithm
  int coins_num = 0;
  for (int i = 1; i <= m; ++i) {
    min_coins_nums[i] = m; // Equivalent of setting to infinity
    for (int j = 0; j < 3; ++j) {
      if (i >= coins[j]) {
        coins_num = min_coins_nums[i - coins[j]] + 1;
        if (coins_num < min_coins_nums[i]) {
          min_coins_nums[i] = coins_num;
        }
      }
    }
  }

  return min_coins_nums[m];
}

int get_change_recur(int m) {
  if (m == 0) {
    return 0;
  }

  int coins[3] = {1, 3, 4};
  int min_coins_num = m;

  int coins_num = 0;
  for (int i = 0; i < 3; ++i) {
    if (m >= coins[i]) {
      coins_num = get_change_recur(m - coins[i]) + 1;
      if (coins_num < min_coins_num) {
        min_coins_num = coins_num;
      }
    }
  }

  return min_coins_num;
}

void stress_test(int max_ncoins, function<int (int)> func_recur, function<int (int)> func_dp) {
  // Manual test
  assert(func_dp(2) == 2);
  assert(func_dp(6) == 2);
  assert(func_dp(8) == 2);

  for (int ncoins = 1; ncoins <= max_ncoins; ++ncoins) {
    assert(func_recur(ncoins) == func_dp(ncoins));
    cout << "#coins: " << ncoins << " " << "OK\n";
  }
}

int main() {
  // stress_test(40, get_change_recur, get_change_dp);

  int m;
  cin >> m;
  cout << get_change_dp(m) << '\n';
}
