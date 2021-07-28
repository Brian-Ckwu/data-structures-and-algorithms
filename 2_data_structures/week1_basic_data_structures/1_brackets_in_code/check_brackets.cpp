#include <iostream>
#include <stack>
#include <string>

struct Bracket {
  Bracket(char type, int position):
    type(type),
    position(position)
  {}

  bool Matchc(char c) {
    if (type == '[' && c == ']')
      return true;
    if (type == '{' && c == '}')
      return true;
    if (type == '(' && c == ')')
      return true;
    return false;
  }

  char type;
  int position;
};

int main() {
  std::string text;
  getline(std::cin, text);

  std::stack <Bracket> opening_brackets_stack;
  std::string answer = "";
  for (int position = 0; position < text.length(); ++position) {
    char next = text[position];

    if (next == '(' || next == '[' || next == '{') {
      opening_brackets_stack.push(Bracket(next, position + 1));
    }

    if (next == ')' || next == ']' || next == '}') {
      if (opening_brackets_stack.empty() || !opening_brackets_stack.top().Matchc(next)) {
        answer = std::to_string(position + 1);
        break;
      } else {
        opening_brackets_stack.pop();
      }
    }
  }

  // Check answer & stack
  if (answer != "") {
    // do nothing
  } else if (opening_brackets_stack.empty()) {
    answer = "Success";
  } else {
    while (!opening_brackets_stack.empty()) {
      answer = std::to_string(opening_brackets_stack.top().position);
      opening_brackets_stack.pop();
    }
  }

  // Display answer
  std::cout << answer;

  return 0;
}
