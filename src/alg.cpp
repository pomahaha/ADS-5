// Copyright 2021 NNTU-CS
#include "tstack.h"
#include "vector"
#include <string>

bool isNumeric(char c) {
  return (c >= '0' && c <= '9');
}

int fetchPriority(char op) {
  switch (op) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;

    default: return -1;
  }
}

std::vector<std::string> getTokens(std::string input) {
  std::vector<std::string> tokens;
  std::string buffer = "";
  for (int i = 0; i < input.length(); i++) {
    if (!isNumeric(input[i])) {
      if (!buffer.empty()) {
        tokens.push_back(buffer);
      }
      std::string temp = "";
      tokens.push_back(temp + input[i]);
      buffer = "";
    } else {
      buffer += input[i];
    }
  }
  tokens.push_back(buffer);

  return tokens;
}

std::string infx2pstfx(std::string inf) {
  std::vector<std::string> tokenArray = getTokens(inf);
  TStack<std::string, 300> stack;
  std::string result;
  for (auto token : tokenArray) {
    if (isNumeric(token[0])) {
      result += token;
      result += ' ';
      continue;
    }
    if (token[0] == ')') {
      while (stack.get() != "(") {
        result += stack.pop();
        result += ' ';
      }
      stack.pop();
      continue;
    }
    if (!isNumeric(token[0])) {
      if (stack.isEmpty()
          || token[0] == '('
          || (fetchPriority(token[0]) > fetchPriority(stack.get()[0]))) {
        stack.push(token);
      } else {
        while (!stack.isEmpty() &&
        fetchPriority(token[0]) <= fetchPriority(stack.get()[0])) {
          result += stack.pop();
          result += ' ';
        }
        stack.push(token);
      }
      continue;
    }
  }
  while (!stack.isEmpty()) {
    result += stack.pop();
    result += ' ';
  }
  while (result[result.length() - 1] == ' ') {
    result.pop_back();
  }
  return result;
}

int doMaths(int num1, int num2, char op) {
  switch (op) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    default: return num1 / num2;
  }
}

int eval(std::string pref) {
  std::string temp;
  TStack<int, 300> stack;
  for (int i = 0; i < pref.length(); i++) {
    if (isNumeric(pref[i])) {
      temp += pref[i];
      continue;
    }
    if (pref[i] == ' ') {
      if (temp.empty()) {
        continue;
      }
      stack.push(std::stoi(temp));
      temp = "";
      continue;
    }
    if (!isNumeric(pref[i])) {
      int num1 = stack.pop();
      int num2 = stack.pop();
      int result = doMaths(num2, num1, pref[i]);
      stack.push(result);
    }
  }
  return stack.get();
}
