#include <iostream>
#include <vector>

using namespace std;

int get_change(int m) {
  // Variables
  vector<int> coins = {10, 5, 1};
  int n = 0;

  // Change the money by greedy algorithm
  while (m > 0) {
    for (int coin : coins) {
      if (m >= coin) {
        m -= coin;
        ++n;
        break;
      }
    }
  }

  return n;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
