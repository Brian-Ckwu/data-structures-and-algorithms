#include <iostream>

using namespace std;

// For storing norse gods
struct Node {
  // Constructor (can the constructor access the data members declared after it?)
  Node(const string& name, Node* prev, Node* next)
    : god_name{name},
      prev{prev},
      next{next} {}
  // Data member
  string god_name;
  Node* prev;
  Node* next;
};

int main() {
  // Create three nodes: "Freia", "Odin", and "Thor"
  Node* norse_gods = new Node("Freia", nullptr, nullptr);
  norse_gods->next = new Node("Odin", norse_gods, nullptr);
  norse_gods->next->next = new Node("Thor", norse_gods->next, nullptr);

  // Display the names of the three nodes
  Node* node_iterator = norse_gods; // point to the first node
  while (node_iterator) {
    cout << node_iterator->god_name << " ";
    node_iterator = node_iterator->next;
  }

  return 0;
}