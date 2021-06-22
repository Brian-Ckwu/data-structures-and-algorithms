#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> optimal_sequence_wrong(int n) {
  vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

vector<int> reconstruct_sequence(int n, const vector<int>& choices) {
  vector<int> sequence = {n};

  int choice = 0;
  while (n > 1) {
    choice = choices[n];

    if (choice == 1) {
      n -= 1;
    } else if (choice == 2) {
      n /= 2;
    } else if (choice == 3) {
      n /= 3;
    } else {
      cout << "Invalid choice.\n";
      break;
    }
    sequence.push_back(n);
  }

  reverse(sequence.begin(), sequence.end());

  return sequence;
}

vector<int> optimal_sequence_dp(int n) {
  vector<int> operations = {-1, 0};
  vector<int> choices = {0, 1};
  vector<int> sequence;

  int min_oper_num;
  int oper_num;
  int choice; // Three choices: 1 -> +1; 2 -> *2; 3 -> *3;

  for (int i = 2; i <= n; ++i) {
    // Default: +1 operation
    min_oper_num = operations[i - 1] + 1;
    choice = 1;

    if (i % 3 == 0) {
      oper_num = operations[i / 3] + 1;
      if (oper_num < min_oper_num) {
        min_oper_num = oper_num;
        choice = 3;
      }
    }

    if (i % 2 == 0) {
      oper_num = operations[i / 2] + 1;
      if (oper_num < min_oper_num) {
        min_oper_num = oper_num;
        choice = 2;
      }
    }

    operations.push_back(min_oper_num);
    choices.push_back(choice);
  }

  sequence = reconstruct_sequence(n, choices);
  return sequence;
}

int main() {
  int n;
  cin >> n;
  vector<int> sequence = optimal_sequence_dp(n);
  cout << sequence.size() - 1 << endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    cout << sequence[i] << " ";
  }
}
