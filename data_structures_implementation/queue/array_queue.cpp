/*
  Implementation of a queue using an array

  Advantage: no need to store pointers
  Limitation: fixed size
*/

#include <iostream>
#include <string>

using namespace std;

class MyQueue {
 public:
  // functions: push(), pop(), front(), back(), empty(), and size()
  MyQueue(size_t max_size);
  ~MyQueue() { delete[] arr; }

  int add_index(int n) const { return (n < max_sz - 1) ? (n + 1) : 0; }
  void push(int n);
  void pop();
  int& front();
  int& back();
  bool empty() const { return read == write; }
  size_t size() const { return (read <= write) ? (write - read) : (max_sz - read + write) ;}
  size_t max_size() const { return max_sz; }

  void print_queue() const;

 private:
  int read; // read index
  int write;  // write index
  int* arr;
  size_t max_sz;
  
};

MyQueue::MyQueue(size_t max_size)
  : read{0},
    write{0},
    max_sz{max_size} {
      arr = new int[max_size];
    }

void MyQueue::push(int n) {
  if (size() < max_sz - 1) {
    arr[write] = n;
    write = add_index(write);
    return;
  }

  cout << "The queue is already full." << endl;
  throw "ERROR";
}

void MyQueue::pop() {
  if (!empty()) {
    read = add_index(read);
    return;
  }

  cout << "The queue is empty." << endl;
  throw "ERROR";
}

int& MyQueue::front() {
  if (empty()) {
    cout << "The queue is empty." << endl;
    throw "ERROR";
  }

  return arr[read];
}

int& MyQueue::back() {
  if (empty()) {
    cout << "The queue is empty." << endl;
    throw "ERROR";
  }

  return arr[(write > 0) ? (write - 1) : (max_sz - 1)];
}

void MyQueue::print_queue() const {
  if (empty()) {
    cout << "The queue is empty." << endl;
    return;
  }

  cout << "Queue (front to back): ";
  for (int i = read; i != write; i = add_index(i)) { // Be careful: do not modify read or write
    cout << arr[i] << " ";
  }
  cout << endl;
}

void test_my_queue() {
  MyQueue q(5);

  // Messages
  string sep = "--------------------------\n";
  string front_elem = "The front element: ";
  string back_elem = "The back element: ";

  cout << q.empty() << endl;

  cout << sep;

  q.push(1);
  q.push(2);
  q.print_queue();
  cout << front_elem << q.front() << endl;
  cout << back_elem << q.back() << endl;
  q.print_queue();
  q.front() = 3;
  q.print_queue();
  q.back() = 4;
  q.print_queue();
  cout << front_elem << q.front() << endl;
  cout << back_elem << q.back() << endl;

  cout << q.empty() << endl;

  cout << sep;

  q.push(5);
  q.pop();
  q.pop();
  q.push(6);
  q.push(7);
  q.push(8);
  q.print_queue();
  cout << front_elem << q.front() << endl;
  cout << back_elem << q.back() << endl;
  try {
    q.push(9);
  } catch (char const*) {}

  cout << sep;

  q.pop();
  q.pop();
  q.pop();
  q.print_queue();
  cout << front_elem << q.front() << endl;
  cout << back_elem << q.back() << endl;
  
  cout << sep;

  q.pop();
  cout << q.empty() << endl;
  cout << front_elem << q.front() << endl;
  cout << back_elem << q.back() << endl;

}

int main() {
  test_my_queue();

  return 0;
}