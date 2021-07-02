/*
  Improve the linked-list with insert function
*/

#include <iostream>

using namespace std;

// For storing norse gods
struct Node {
  // Constructor (can the constructor access the data members declared after it?)
  Node(const string& name, Node* prev = nullptr, Node* next = nullptr)
    : god_name{name},
      prev{prev},
      next{next} {}
  // Data member
  string god_name;
  Node* prev;
  Node* next;
};

// For inserting node before a certain node (don't forget to handle nullptr)
Node* insert(Node* old_node, Node* new_node) {
  if (new_node == nullptr) { return old_node; }
  if (old_node == nullptr) { return new_node; }
  if (old_node->prev != nullptr) {
    new_node->prev = old_node->prev;
    old_node->prev->next = new_node;
  }
  new_node->next = old_node;
  old_node->prev = new_node;

  return new_node;
}

int main() {
  // Practice using self-defined linked-list
  Node* norse_gods = nullptr;
  // Insert Thor, Odin, and Freia respectively
  norse_gods = insert(nullptr, new Node("Thor"));
  norse_gods = insert(norse_gods, new Node("Odin"));
  norse_gods = insert(norse_gods, new Node("Freia"));

  // Display the names
  while (norse_gods) {
    cout << norse_gods->god_name << " ";
    norse_gods = norse_gods->next;
  }

  return 0;
}