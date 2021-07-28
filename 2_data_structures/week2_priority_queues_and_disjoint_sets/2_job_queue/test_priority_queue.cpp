#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <class T, class S, class C>
  S& Container(priority_queue<T, S, C>& q) {
    struct HackedQueue : private priority_queue<T, S, C> {
      static S& Container(priority_queue<T, S, C>& q) {
        return q.*&HackedQueue::c;
      }
    };
  return HackedQueue::Container(q);
}

struct Thread {
  int index;
  int available_time;
};

class TestCompareClass {
 public:
  bool operator()(const int& a, const int& b) {
    return a > b;
  }
};

class CompareClass {
 public:
  bool operator()(const Thread& a, const Thread& b) {
    if (a.available_time > b.available_time) {
      return true;
    } else if (a.available_time == b.available_time) {
      return a.index > b.index;
    } else {
      return false;
    }
  }
};

void test_priority_queue() {
  priority_queue<int, vector<int>, TestCompareClass> ints;
  int to_be_pushed[10] = {4, 2, 6, 1, 4, 5, 5, 8, 7, 5};

  for (int& i : to_be_pushed) {
    ints.push(i);
  }

  vector<int>& container = Container(ints);
  for (int& i : container) {
    cout << i << " ";
  }
  cout << endl;

  int k = ints.size();
  for (int i = 0; i < k; ++i) {
    int top = ints.top(); ints.pop();
    cout << top << " ";
  }
}

void for_solving_job_queue() {
  priority_queue<Thread, vector<Thread>, CompareClass> threads;
  vector<Thread> to_be_pushed = {{0, 4}, {1, 2}, {2, 3}, {3, 2}, {4, 0}, {5, 2}};

  for (Thread& th : to_be_pushed) {
    threads.push(th);
  }

  int qsize = threads.size();
  for (int i = 0; i < qsize; ++i) {
    Thread top = threads.top(); threads.pop();
    cout << "(" << top.index << ", " << top.available_time << ")" << " ";
  }
}

void test_pushing_threads() {
  priority_queue<Thread, vector<Thread>, CompareClass> threads;
  int num_workers_ = 10;
  for (int i = 0; i < num_workers_; ++i) {
    Thread th = {i, 0};
    threads.push(th);
  }

  // test if the workers is sorted correctly
  int qsize = threads.size();
  for (int i = 0; i < qsize; ++i) {
    Thread top = threads.top(); threads.pop();
    cout << "(" << top.index << ", " << top.available_time << ")" << " ";    
  }
}

int main() {
  test_pushing_threads();

  return 0;
}