/*
  Stack implementation using an array
*/

#include <iostream>
#include <string>

using namespace std;

// Basic operations: push(), top(), pop(), and empty()
// Additional: size(), max_size();

// Stack of ints
class MyStack {
 public:
  // Constructor
  MyStack(size_t max_size)
    : sz{0},
      max_sz{max_size} {
        arr = new int[max_size];
      }
  
  // Destructor
  ~MyStack() { delete[] arr; }

  // Member functions
  void push(int n);
  int top();
  void pop();

  // Const member functions
  bool empty() const { return sz == 0; } 
  size_t size() const { return sz; }
  size_t max_size() const { return max_sz; }

 private:
  int* arr;
  size_t sz;
  size_t max_sz;
};

void MyStack::push(int n) {
  if (sz == max_sz) {
    cout << "The stack is full. Cannot push another element." << endl;
    throw "ERROR";
  }

  arr[sz] = n;
  ++sz;
}

int MyStack::top() {
  if (empty()) {
    cout << "The stack is empty." << endl;
    throw "ERROR";
  }

  return arr[sz - 1];
}

void MyStack::pop() {
  if (empty()) {
    cout << "The stack is empty." << endl;
    throw "ERROR";
  }

  --sz;
}

void test_my_stack() {
  // Create a stack
  MyStack stack(5);

  // Common messages
  string is_empty = "The stack is empty.";
  string not_empty = "The stack is not empty.";
  string cur_size = "The current size of the stack: ";
  string max_size = "The maximum size of the stack: ";
  string top_elem = "The top element is: ";

  // Test functions: empty(), size(), and max_size();
  cout << "Initial stack:" << endl;
  cout << (stack.empty() ? is_empty : not_empty) << endl;
  cout << cur_size << stack.size() << endl;
  cout << max_size << stack.max_size() << endl;
  cout << endl;

  // Test push()
  stack.push(1);
  stack.push(2);
  cout << "After pushing 1 and 2:" << endl;
  cout << (stack.empty() ? is_empty : not_empty) << endl;
  cout << cur_size << stack.size() << endl;
  cout << max_size << stack.max_size() << endl;
  cout << top_elem << stack.top() << endl;
  cout << endl;

  // Test push() & pop()
  stack.push(3);
  cout << top_elem << stack.top() << endl;
  stack.pop();
  cout << top_elem << stack.top() << endl;
  stack.push(4);
  stack.push(5);
  stack.push(6);
  cout << top_elem << stack.top() << endl;
  cout << cur_size << stack.size() << endl;
  cout << max_size << stack.max_size() << endl;
  try {
    stack.push(7); // expect ERROR
  } catch (char const*) {
    cout << "ERROR caught." << endl;
  }
  cout << endl;

  // More testing
  stack.pop();
  cout << top_elem << stack.top() << endl; // should be 5
  stack.push(8);
  cout << top_elem << stack.top() << endl; // should be 8
  cout << cur_size << stack.size() << endl;
  cout << endl;
  
  // Pop all the elements
  size_t cur_stack_size = stack.size();
  for (int i = 0; i < cur_stack_size; ++i) {
    stack.pop();
  }
  cout << cur_size << stack.size() << endl;
  cout << (stack.empty() ? is_empty : not_empty) << endl;
}

int main() {
  test_my_stack();

  return 0;
}