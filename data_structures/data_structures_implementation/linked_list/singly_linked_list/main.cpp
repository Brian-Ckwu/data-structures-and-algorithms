#include <iostream>
#include <string>
#include <forward_list>
#include <chrono>
#include <climits>

using namespace std;
using namespace std::chrono;

struct Node {
  Node(int val, Node* next = nullptr)
    : val{val},
      next{next} {}

  int val;
  Node* next;
};

class List {
 public:
  List() {
    head = nullptr;
    tail = nullptr;
  }

  // Time complexity: O(1)
  void push_front(int n) {
    Node* new_node = new Node(n, head);
    head = new_node;
    if (tail == nullptr) {
      tail = new_node;
    }
  }

  // Time complexity: O(1)
  int top_front() {
    if (!empty()) {
      return head->val;
    }

    cout << "This is an empty list." << endl;
    throw "ERROR: EMPTY LIST";
  }

  // Time complexity: O(1)
  void pop_front() {
    if (!empty()) {
      Node* del_node = head;
      head = del_node->next;
      delete del_node;

      if (head == nullptr) {
        tail = nullptr;
      }

      return;
    }

    cout << "This is an empty list." << endl;
    throw "ERROR: EMPTY LIST";
  }

  // Time complexity: O(1) with tail / O(n) without tail
  void push_back(int n) {
    Node* new_node = new Node(n);

    if (empty()) {
      head = new_node;
      tail = new_node;
      return;
    }

    tail->next = new_node;
    tail = new_node;
  }

  // Imitate singly-linked list with no tail (O(n))
  void push_back_no_tail(int n) {
    Node* new_node = new Node(n);

    if (empty()) {
      head = new_node;
      tail = new_node;
      return;
    }

    Node* node = head;
    while (node->next) {
      node = node->next;
    }

    node->next = new_node;
    tail = new_node;
  }

  // Time complexity: O(1) with tail / O(n) without tail
  int top_back() {
    if (!empty()) {
      return tail->val;
    }

    cout << "This is an empty list." << endl;
    throw "ERROR: EMPTY LIST";    
  }

  // O(n)
  int top_back_no_tail() {
    if (!empty()) {
      Node* node = head;
      while (node->next) {
        node = node->next;
      }
      return node->val;
    }

    cout << "This is an empty list." << endl;
    throw "ERROR: EMPTY LIST";     
  }

  // Time complexity: O(n) no matter there is a tail pointer or not
  void pop_back() {
    if (!empty()) {
      Node dummy(INT_MIN, head);
      Node* prev = &dummy;

      while (prev->next->next) {
        prev = prev->next;
      }

      if (prev == &dummy) {
        delete head;
        head = nullptr;
        tail = nullptr;
      } else {
        delete prev->next;
        prev->next = nullptr;
        tail = prev;
      }

      return;
    }

    cout << "This is an empty list." << endl;
    throw "ERROR: EMPTY LIST";
  }

  // Time complexity: O(n)
  bool find(int n) {
    Node* node = head;

    while (node) {
      if (node->val == n) {
        return true;
      }
      node = node->next;
    }

    return false;
  }

  // Time complexity: O(n)
  void erase(int n) {
    Node* node = head;
    while (node) {
      if (node->val == n) {
        // Delete node
        return;
      }
    }

    cout << "There is no such node." << endl;
  }

  // Time complexity: O(1)
  bool empty() {
    if (head == nullptr) {
      return true;
    }
    return false;
  }

  // O(n)
  void add_before(int n);

  // O(1)
  void add_after(int n);

  void print_list() {
    Node* node = head;
    while (node) {
      cout << node->val << " ";
      node = node->next;
    }
    cout << endl;
  }

 private:
  Node* head;
  Node* tail;
};

// O(1) vs. O(n)
void tail_versus_no_tail() {
  // Initialize a list
  List list;

  int list_size = 100000000;
  for (int i = 0; i < list_size; ++i) {
    list.push_front(i);
  }

  // Execution time of push_back_no_tail
  auto start_1 = high_resolution_clock::now();
  list.push_back_no_tail(-1);
  auto end_1 = high_resolution_clock::now();

  // of push_back
  auto start_2 = high_resolution_clock::now();
  list.push_back(-1);
  auto end_2 = high_resolution_clock::now();

  // of top_back_no_tail
  auto start_3 = high_resolution_clock::now();
  list.top_back_no_tail();
  auto end_3 = high_resolution_clock::now();

  // of top_back
  auto start_4 = high_resolution_clock::now();
  list.top_back();
  auto end_4 = high_resolution_clock::now();

  // Display execution time
  cout << "Execution time:" << endl;
  cout << "push_back_no_tail() - O(n): " << duration_cast<microseconds>(end_1 - start_1).count() << endl;
  cout << "push_back() - O(1): " << duration_cast<microseconds>(end_2 - start_2).count() << endl;
  cout << "top_back_no_tail() - O(n): " << duration_cast<microseconds>(end_3 - start_3).count() << endl;
  cout << "top_back() - O(1): " << duration_cast<microseconds>(end_4 - start_4).count() << endl;
}

void test_self_list() {
  List list;

  list.push_front(2);
  list.push_front(4);
  list.push_front(6);
  list.push_back(8);
  list.print_list();
  cout << list.find(4) << endl;
  cout << list.find(8) << endl;
  cout << list.find(1) << endl;
  cout << list.find(6) << endl;

  list.pop_front();
  list.pop_front();
  list.pop_front();
  list.pop_front();
  
  cout << list.find(8) << endl;

}

void test_standard_list() {
  forward_list<int> list;

  list.push_front(2);
  list.push_front(4);
  list.push_front(6);
  list.pop_front();
  list.push_front(8);

  for (int& x : list) {
    cout << x << " ";
  }
}

int main() {
  // test_standard_list();
  test_self_list();
  // tail_versus_no_tail();

  return 0;
}