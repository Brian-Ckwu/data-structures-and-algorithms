/*
  https://www.geeksforgeeks.org/linked-list-set-1-introduction/
*/

#include <iostream>

using namespace std;

class Node {
 public:
  int data;
  Node* next;
};

void print_list(Node* nptr) {
  while (nptr) {
    cout << nptr->data << " ";
    nptr = nptr->next;
  }
}

int main() {
  // Allocate memory for three nodes and have three pointers point to them
  Node* head = new Node();
  Node* second = new Node();
  Node* third = new Node();

  // Assign data and link three nodes
  head->data = 1;
  head->next = second;
  
  second->data = 2;
  second->next = third;

  third->data = 3;
  third->next = nullptr;

  // Traversal
  print_list(head);

  return 0;
}