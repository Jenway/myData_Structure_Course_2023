#include "Stack.h"
#include <iostream>

using namespace std;

typedef struct symbol {
    bool isOperator;
    union {
        char op;
        double num;
    } data;

    symbol()
    {
        isOperator = false;
        data.num = 0;
    }

    symbol(double num)
    {
        isOperator = false;
        data.num = num;
    }

    symbol(char c)
    {
        // 输入数学表达式，输出表达式的计算结果。数学表达式由单个数字和运算符 +、-、*、/、(、)  构成，例如 2+3*(4+5)-6/4。假定表达式输入格式合法

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
            isOperator = true;
            data.op = c;
        } else {
            isOperator = false;
            data.num = atof(&c);
        }
    }

    friend ostream& operator<<(ostream& os, const symbol& data);

} symbol;

using Stack = my_stack<symbol>;

class Solution {
private:
    int n;

    double applyOperator(double num1, double num2, char op);
    int precedence(char op);

    void getInput(Stack& s);
    void convert_infix_to_prefix(Stack& reversedInfix);
    double calculate(Stack& prefix);

public:
    void runTest();

    Solution() = delete;
    Solution(int n)
        : n(n) {};
    ~Solution() = default;
};

// 输入数学表达式，输出表达式的计算结果。数学表达式由单个数字和运算符 +、-、*、/、(、)  构成，例如 2+3*(4+5)-6/4。假定表达式输入格式合法

// 输入
// 第一行一个整数 n(1<=n<=100)，代表表达式的个数。
// 接下来 n 行，每行一个表达式，保证表达式内的数字为单个整数，表达式内各运算符和数字间没有空格，且表达式的长度不超过 2000。

// 输出
// 每行表达式输出一个浮点数，要求保留两位小数，保证输入表达式合法。

int main(void)
{
    int n;
    cin >> n;
    Solution* solution = new Solution(n);
    solution->runTest();
    delete solution;
    return 0;
}

void Solution::runTest()
{
    for (int i = 0; i < n; i++) {
        Stack expressionStack = Stack();
        getInput(expressionStack);
        convert_infix_to_prefix(expressionStack);
        double ans = calculate(expressionStack);
        printf("%.2f\n", ans);
    }
}

void Solution::getInput(Stack& s)
{
    char* buffer = new char[2000];
    cin >> buffer;
    for (int j = 0; buffer[j] != '\0'; j++) {
        if (buffer[j] == '(') {
            s.push(symbol(')'));
        } else if (buffer[j] == ')') {
            s.push(symbol('('));
        } else {
            s.push(symbol(buffer[j]));
        }
    }
    delete[] buffer;
}

void Solution::convert_infix_to_prefix(Stack& reversedInfix)
{
    /*
     * original input may like this: 2+3*(4+5)-6/4
     * param may like this in its array: 2+3*)4+5(-6/4
     * get by pop() may like : 4/6-(5+4)*3+2 ( reversedInfix.top() == 4)
     * should return prefix like this: -+2*3+45/64 ( prefix.top() == 4 )
     */

    Stack postfix = Stack();
    Stack opStack = Stack();
    while (!reversedInfix.empty()) {
        if (!reversedInfix.top().isOperator) {
            // if it's an operand push it to the postfix stack
            postfix.push(reversedInfix.top());
            reversedInfix.pop();
        } else {
            switch (reversedInfix.top().data.op) {
            case '(':
                opStack.push(reversedInfix.top());
                reversedInfix.pop();
                break;
            case ')':
                while (opStack.top().data.op != '(') {
                    postfix.push(opStack.top());
                    opStack.pop();
                }
                opStack.pop();
                reversedInfix.pop();
                break;
            default:
                while (!opStack.empty() && precedence(reversedInfix.top().data.op) < precedence(opStack.top().data.op)) {
                    postfix.push(opStack.top());
                    opStack.pop();
                }
                opStack.push(reversedInfix.top());
                reversedInfix.pop();
                break;
            }
        }
    }
    while (!opStack.empty()) {
        postfix.push(opStack.top());
        opStack.pop();
    }
    /*
     * now the postfix stack should be like this: 46/54+3*2+- ( postfix.top() == '-' )
     * Reverse the postfix expression.
     */
    Stack prefix = Stack();
    while (!postfix.empty()) {
        prefix.push(postfix.top());
        postfix.pop();
    }
    reversedInfix = std::move(prefix);
}

int Solution::precedence(char op)
{
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

double Solution::calculate(Stack& prefix)
{
    /*
     * original input may like this: 2+3*(4+5)-6/4
     * param may like this: -+2*3+45/64 ( prefix.top() == 4 )
     * if prefix.top() is an operand, push it to the result stack
     * if prefix.top() is an operator, pop two operands from the result stack, calculate the result, push it to the result stack
     */
    Stack result = Stack();
    while (!prefix.empty()) {
        if (!prefix.top().isOperator) {
            result.push(prefix.top());
            prefix.pop();
        } else {
            double num1 = result.top().data.num;
            result.pop();
            double num2 = result.top().data.num;
            result.pop();
            result.push(symbol(applyOperator(num1, num2, prefix.top().data.op)));
            prefix.pop();
        }
    }
    return result.top().data.num;
}

double Solution::applyOperator(double num1, double num2, char op)
{
    switch (op) {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    default:
        return 0;
    }
}

ostream& operator<<(ostream& os, const symbol& s)
{
    if (s.isOperator) {
        os << s.data.op;
    } else {
        os << s.data.num;
    }
    return os;
}