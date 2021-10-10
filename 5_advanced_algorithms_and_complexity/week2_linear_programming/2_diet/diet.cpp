#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<double>> matrix;

struct Position {
  Position(int col, int row):
    col(col),
    row(row) {}
  
  int col;
  int row;
};

const double kUpperBound = 1000000000.0;
const double kErrMargin = 0.001;

void add_restrictions(matrix& A, vector<double>& b) {
  int m = A[0].size();
  for (int i = 0; i < m; ++i) {
    vector<double> inequality(m, 0);
    inequality[i] = -1;
    A.push_back(inequality);
    b.push_back(0);
  }
  // add upper bound
  A.push_back(vector<double>(m, 1));
  b.push_back(kUpperBound);
}

void display_matrix(const matrix& A, const vector<double>& b) {
  assert(A.size() == b.size());
  int rows = b.size();
  for (int row = 0; row < rows; ++row) {
    for (double c : A[row]) {
      printf("%f ", c);
    }
    printf("%f\n", b[row]);
  }
  printf("\n");
}

void add_combination(vector<vector<int>>& combs, vector<int>& comb, int a, int b, int s) {
  if (comb.size() == b) {
    combs.push_back(comb);
    return;
  }
  for (int i = s; i < a; ++i) {
    comb.push_back(i);
    add_combination(combs, comb, a, b, i + 1);
    comb.pop_back();
  }
}

// for checking if the combinations are correct
void display_combinations(const vector<vector<int>>& combs) {
  for (auto& comb : combs) {
    for (int i : comb) {
      printf("%d ", i);
    }
    printf("\n");
  }
}

matrix construct_matrix(const matrix& A, const vector<int>& comb) {
  int m = A[0].size();
  matrix AA;
  for (int row : comb) {
    AA.push_back(A[row]);
  }
  return AA;
}

vector<double> construct_column(const vector<double>& b, const vector<int>& comb) {
  vector<double> bb;
  for (int row : comb) {
    bb.push_back(b[row]);
  }
  return bb;
}

Position select_pivot(const matrix& a, const vector<bool>& used_rows, const vector<bool>& used_cols) {
  Position pivot(0, 0);
  while (used_rows[pivot.row]) {
    ++pivot.row;
    ++pivot.col;
  }
  while (pivot.row < used_rows.size() && a[pivot.row][pivot.col] == 0) { // find the first non-zero pivot element
    ++pivot.row;
  }
  if (pivot.row == used_rows.size()) {
    return Position(-1, -1);
  }
  return pivot;
}

void swap_lines(matrix& a, vector<double>& b, Position& pivot) {
  swap(a[pivot.col], a[pivot.row]);
  swap(b[pivot.col], b[pivot.row]);
  pivot.row = pivot.col;
}

void process_pivot(matrix& a, vector<double>& b, const Position& pivot) {
  assert(a.size() == a[0].size());
  int n = a.size();
  // scale the pivot to 1
  double mul = a[pivot.row][pivot.col]; assert(mul != 0);
  for (int col = 0; col < n; ++col) {
    a[pivot.row][col] /= mul;
  }
  b[pivot.row] /= mul;
  // row reduction
  for (int row = 0; row < n; ++row) {
    if (row != pivot.row) {
      // reduce the "row" by the pivot row
      double mul = a[row][pivot.col];
      if (mul != 0) {
        for (int col = 0; col < n; ++col) {
          a[row][col] += -(a[pivot.row][col] * mul);
        }
        b[row] += -(b[pivot.row] * mul);
      }
    }
  }
}

void mark_used_pivot(const Position& pivot, vector<bool>& used_rows, vector<bool>& used_cols) {
  assert(pivot.row == pivot.col);
  used_rows[pivot.row] = true;
  used_cols[pivot.col] = true;
}

vector<double> solve_equations(matrix& AA, vector<double>& bb) {
  assert(AA.size() == AA[0].size());
  int n = AA.size();
  // for bookkeeping used columns or rows
  vector<bool> used_rows(n, false);
  vector<bool> used_cols(n, false);
  // Gaussian elimination
  for (int step = 0; step < n; ++step) {
    Position pivot = select_pivot(AA, used_rows, used_cols);
    if (pivot.row == -1 && pivot.col == -1) { // if not the only solution
      return vector<double>();
    }
    swap_lines(AA, bb, pivot);
    process_pivot(AA, bb, pivot);
    mark_used_pivot(pivot, used_rows, used_cols);
  }
  return bb;
}

bool is_valid(const matrix& A, const vector<double>& b, const vector<double>& sol) {
  assert(A.size() == b.size());
  assert(A[0].size() == sol.size());
  int rows = A.size();
  int cols = A[0].size();
  for (int row = 0; row < rows; ++row) { // check each row for validity of the solution
    double left = 0.0;
    double right = b[row];
    for (int col = 0; col < cols; ++col) {
      left += A[row][col] * sol[col];
    }
    if (left > right + kErrMargin) {
      return false;
    }
  }
  return true;
}

double compute_value(const vector<double>& sol, const vector<double>& c) {
  assert(sol.size() == c.size());
  double value = 0.0;
  for (int i = 0; i < sol.size(); ++i) {
    value += sol[i] * c[i];
  }
  return value;
}

pair<int, vector<double>> solve_diet_problem(int n, int m, const matrix& A, const vector<double>& b, const vector<double>& c) {
  vector<vector<int>> combs;
  vector<int> comb;
  add_combination(combs, comb, n + m + 1, m, 0); // find all combinations of C(n+m, m)
  // display_combinations(combs);
  vector<vector<double>> sols; // for storing all possible solutions
  // iterate through the combinations and solve the corresponding equations by Gaussian elimination
  for (const vector<int>& comb : combs) {
    matrix AA = construct_matrix(A, comb);
    vector<double> bb = construct_column(b, comb);
    // display_matrix(AA, bb);
    vector<double> sol = solve_equations(AA, bb);
    if (!sol.empty()) {
      if (is_valid(A, b, sol)) {
        sols.push_back(sol);
      }
    }
  }
  // find the optimal solution among all possible solutions
  double max_value = -DBL_MAX;
  vector<double> max_sol;
  for (const vector<double>& sol : sols) {
    double value = compute_value(sol, c);
    if (value > max_value) {
      max_value = value;
      max_sol = sol;
    }
  }
  if (sols.empty()) {
    return {-1, max_sol};
  } else if (max_value >= kUpperBound) {
    return {1, max_sol};
  } else {
    return {0, max_sol};
  }
}

int main(){
  int n, m;
  // read input
  cin >> n >> m;
  matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  // add the non-negative restriction to each variable
  add_restrictions(A, b);
  // display_matrix(A, b);

  // find the optimal solution
  pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

  // display output
  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}
