#include <iostream>

using namespace std;

class Node {
 public:
  Node(string str)
    : data{str} {}

  string data;
  Node* next = nullptr;
};

// Helper functions
// List traversal: print after the passed node*
void print_list(Node* node) {
  while (node) {
    cout << node->data << " ";
    node = node->next;
  }
}

// push, insert_after, append
// Time complexity: O(1)
void push(Node** head_ptr, string data) {
  Node* new_node = new Node(data);

  new_node->next = *head_ptr;
  *head_ptr = new_node;
}

// Time complexity: O(1)
void insert_after(Node* prev_node, string data) { // use prev_node would be clearer
  if (prev_node == nullptr) {
    cout << "Cannot insert after an empty node." << endl;
    return;
  }

  Node* new_node = new Node(data);
  new_node->next = prev_node->next;
  prev_node->next = new_node;
}

// Time complexity: O(n) (no tail pointer)
void append(Node** head_ptr, string data) {
  Node* new_node = new Node(data);

  if (*head_ptr == nullptr) { // If not passing pointer-to-head or reference-to-head, this step would be a problem
    *head_ptr = new_node;
    return;
  }

  Node* last = *head_ptr; // last will point to the last node eventually
  while (last->next) {
    last = last->next;
  }
  last->next = new_node;
}

// Testing functions
void test_direct_alloc() {
  cout << "Inside test_direct_alloc():" << endl;

  Node* first = new Node("Brian");
  Node* second = new Node("Nini");
  Node* third = new Node("Fifi");

  first->next = second;
  second->next = third;

  print_list(first);
}

void test_helper_funcs() {
  cout << "Inside test_helper_funcs():" << endl;

  Node* head = nullptr;
  // Push three nodes
  push(&head, "Brian");
  push(&head, "Nini");
  push(&head, "Fifi");
  insert_after(head, "Yepi");
  insert_after(head->next->next, "Hippie");
  append(&head, "LastSecond");
  append(&head, "LastOne");

  print_list(head);
}

int main() {
  // Test with three nodes
  test_helper_funcs();

  return 0;
}