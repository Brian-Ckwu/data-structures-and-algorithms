/*
  Implementation of a queue using an array

  Advantage: no need to store pointers
  Limitation: fixed size
*/

#include <iostream>

using namespace std;

class MyQueue {
 public:
  // functions: push(), pop(), front(), back(), empty(), and size()
  MyQueue(size_t max_size);
  ~MyQueue() { delete[] arr; }

  int add_index(int n) { return (n < max_sz - 1) ? (n + 1) : 0; }
  void push(int n);
  void pop();
  int& front() { return arr[front]; }
  int& back() { return arr[back]; }
  bool empty() { return front == back; }
  size_t size() const { return (front <= back) ? (back - front) : (max_sz - front + back) ;}
  size_t max_size() const { return max_sz; }

 private:
  int front; // front index
  int back;  // back index
  int* arr;
  size_t max_sz;
  
};

MyQueue::MyQueue(size_t max_size)
  : front{0},
    back{0},
    max_sz{max_size} {
      arr = new int[max_size];
    }

void MyQueue::push(int n) {
  if (size() < max_sz - 1) {
    arr[back] = n;
    back = add_index(back);
    return;
  }

  cout << "The queue is already full." << endl;
  throw "ERROR";
}

void MyQueue::pop() {
  if (!empty()) {
    front = add_index(front);
    return;
  }

  cout << "The queue is empty." << endl;
  throw "ERROR";
}

void test_my_queue() {

}

int main() {
  test_my_queue();

  return 0;
}