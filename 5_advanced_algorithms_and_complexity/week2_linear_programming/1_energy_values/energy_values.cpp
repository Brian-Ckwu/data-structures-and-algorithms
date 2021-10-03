#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-6;
const int PRECISION = 20;

typedef vector<double> Column;
typedef vector<double> Row;
typedef vector<Row> Matrix;

struct Equation {
  Equation(const Matrix& a, const Column& b):
    a(a),
    b(b) {}

  Matrix a;
  Column b;
};

struct Position {
  Position(int column, int row):
    column(column),
    row(row) {}

  int column;
  int row;
};

Equation ReadEquation() {
  int size;
  cin >> size;
  Matrix a(size, vector<double>(size, 0.0));
  Column b(size, 0.0);
  for (int row = 0; row < size; ++row) {
    for (int column = 0; column < size; ++column)
      cin >> a[row][column];
    cin >> b[row];
  }
  return Equation(a, b);
}

Position SelectPivotElement(const Matrix& a, vector<bool>& used_rows, vector<bool>& used_columns) {
  // This algorithm selects the first free non-zero element.
  Position pivot_element(0, 0);
  while (used_rows[pivot_element.row]) {
    ++pivot_element.row;
    ++pivot_element.column;
  }
  while (a[pivot_element.row][pivot_element.column] == 0) { // find the first non-zero pivot element
    ++pivot_element.row;
  }
  return pivot_element;
}

void SwapLines(Matrix& a, Column& b, vector<bool>& used_rows, Position& pivot_element) {
  swap(a[pivot_element.column], a[pivot_element.row]);
  swap(b[pivot_element.column], b[pivot_element.row]);
  // swap(used_rows[pivot_element.column], used_rows[pivot_element.row]); // is this line necessary?
  pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix& a, Column& b, const Position& pivot_element) {
  int rows = a.size();
  int cols = a[0].size();
  int p_row = pivot_element.row, p_col = pivot_element.column;
  // scale the pivot_element to 1
  double mul = a[p_row][p_col];
  for (int col = 0; col < cols; ++col) {
    a[p_row][col] /= mul;
  }
  b[p_row] /= mul;
  // assert(a[p_row][p_col] == 1);
  // row reduction
  for (int row = 0; row < rows; ++row) {
    if (row != p_row) {
      // reduce the "row" by the "p_row"
      double mul = a[row][p_col];
      if (mul != 0.0) {
        for (int col = 0; col < cols; ++col) {
          a[row][col] += -(a[p_row][col] * mul);
        }
        b[row] += -(b[p_row] * mul);
      }
    }
  }
}

void MarkPivotElementUsed(const Position &pivot_element, vector<bool>& used_rows, vector<bool>& used_columns) {
  used_rows[pivot_element.row] = true;
  used_columns[pivot_element.column] = true;
}

Column SolveEquation(Equation equation) {
  Matrix& a = equation.a;
  Column& b = equation.b;
  int size = a.size();

  vector<bool> used_columns(size, false);
  vector<bool> used_rows(size, false);
  for (int step = 0; step < size; ++step) {
    Position pivot_element = SelectPivotElement(a, used_rows, used_columns);
    SwapLines(a, b, used_rows, pivot_element);
    ProcessPivotElement(a, b, pivot_element);
    MarkPivotElementUsed(pivot_element, used_rows, used_columns);
  }

  return b;
}

void PrintColumn(const Column& column) {
  int size = column.size();
  cout.precision(PRECISION);
  for (int row = 0; row < size; ++row)
    cout << column[row] << endl;
}

int main() {
  Equation equation = ReadEquation();
  Column solution = SolveEquation(equation);
  PrintColumn(solution);
  return 0;
}
