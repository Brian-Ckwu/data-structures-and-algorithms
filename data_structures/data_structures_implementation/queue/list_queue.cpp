/*
  Implementation of a queue using a linked-list

  Advantage: no pre-allocated maximum size limitation
  Limitation: additional space for storing pointers
*/

#include <iostream>
#include <list>
#include <string>

using namespace std;

class MyQueue {
 public:
  // functions: push(), pop(), front(), back(), empty(), and size()
  MyQueue() {};
  ~MyQueue() { q_list.clear(); }

  void push(int n);
  void pop();
  int& front();
  int& back();
  bool empty() const { return q_list.empty(); }
  size_t size() const { return q_list.size();}
  size_t max_size() const { return q_list.max_size(); }

  void print_queue() const;

 private:
  list<int> q_list;
  
};

void MyQueue::push(int n) {
  if (size() == max_size()) {
    cout << "The queue is already full." << endl;
    throw "ERROR";
  }

  q_list.push_back(n);
}

void MyQueue::pop() {
  if (!empty()) {
    q_list.pop_front();
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

  return q_list.front();
}

int& MyQueue::back() {
  if (empty()) {
    cout << "The queue is empty." << endl;
    throw "ERROR";
  }

  return q_list.back();
}

void MyQueue::print_queue() const {
  if (empty()) {
    cout << "The queue is empty." << endl;
    return;
  }

  cout << "Queue (front to back): ";
  for (int i : q_list) { // Be careful: do not modify read or write
    cout << i << " ";
  }
  cout << endl;
}

void test_my_queue() {
  MyQueue q;

  // Messages
  string sep = "--------------------------\n";
  string front_elem = "The front element: ";
  string back_elem = "The back element: ";
  string the_max_size = "The max size of the queue: ";

  cout << the_max_size << q.max_size() << endl;
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
  q.print_queue();
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