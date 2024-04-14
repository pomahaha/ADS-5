// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int Priority(char x) {
    switch (x) {
        case '(': return 0;
        case ')': return 1;
        case '+': case '-': return 2;
        case '*': case '/': return 3;
        default: return -1;
    }
}

std::string infx2pstfx(std::string inf) {
    std::string result, tempResult;
    TStack<char, 100> stack;
    for (auto& x : inf) {
        int p = Priority(x);
        if (p == -1) {
            result += x + ' ';
        } else {
            char element = stack.get();
            if (p == 0 || Priority(element) < p || stack.isEmpty()) {
                stack.push(x);
            } else {
                if (x == ')') {
                    while (Priority(element) >= p) {
                        result += element + ' ';
                        stack.pop();
                        element = stack.get();
                    }
                    stack.pop();
                } else {
                    while (Priority(element) >= p) {
                        result += element + ' ';
                        stack.pop();
                        element = stack.get();
                    }
                    stack.push(x);
                }
            }
        }
    }
    while (!stack.isEmpty()) {
        result += stack.get() + ' ';
        stack.pop();
    }
    for (int i = 0; i < result.size() - 1; i++) {
        tempResult += result[i];
    }
    return tempResult;
}

int calculate(const int& operand1, const int& operand2, const int& operatorSymbol) {
    switch (operatorSymbol) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '/': return operand1 / operand2;
        case '*': return operand1 * operand2;
        default: return 0;
    }
}

int eval(std::string pref) {
    TStack<int, 100> stack;
    std::string result = "";
    for (int i = 0; i < pref.size(); i++) {
        char element = pref[i];
        if (Priority(element) == -1) {
            if (pref[i] == ' ') {
                continue;
            } else if (isdigit(pref[i+1])) {
                result += pref[i];
                continue;
            } else {
                result += pref[i];
                stack.push(atoi(result.c_str()));
                result = "";
            }
        } else {
            int operand2 = stack.get();
            stack.pop();
            int operand1 = stack.get();
            stack.pop();
            stack.push(calculate(operand1, operand2, element));
        }
    }
    return stack.get();
}
