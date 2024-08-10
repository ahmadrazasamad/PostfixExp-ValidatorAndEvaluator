#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

bool isOperator(char c)
{
    return c == '+' || c == '*' || c == '/' || c == '-' || c == '%' || c == '^';
}

bool validatePostfix(string postFixExp, stack<int> &stack)
{
    int operandCount = 0;
    int operatorCount = 0;

    for (int i = 0; i < postFixExp.length(); i++)
    {
        char character = postFixExp[i];
        if (isspace(character))
            continue;
        else if (!isOperator(character))
        { // means it is an operand
            operandCount++;

            int numA = (int)character - 48; // converting character into number
            while (i < postFixExp.length() && !isspace(postFixExp[i + 1]) && !isOperator(postFixExp[i + 1]))
            { // checking the next character, for two-digit, or three-digit, and so-on digit numbers
                numA = numA * 10 + (postFixExp[i + 1] - 48);
                i++;
            }
            stack.push(numA);
        }
        else if (isOperator(character))
        { // character is operator
            operatorCount++;

            if (stack.size() < 2)
                return false; // Not enough operands for the operator
            // Otherwise
            int operandB = stack.top();
            stack.pop();
            int operandA = stack.top();
            stack.pop();

            int result = 0;
            switch (character)
            {
            case '+':
                result = operandA + operandB;
                break;
            case '-':
                result = operandA - operandB;
                break;
            case '*':
                result = operandA * operandB;
                break;
            case '/':
                if (operandB == 0)
                {
                    cout << "Error: Division by zero.\nThe postfix expression is not valid.";
                    return false;
                }
                result = operandA / operandB;
                break;
            case '%':
                if (operandB == 0)
                {
                    cout << "Error: Division by zero.\nThe postfix expression is not valid.";
                    return false;
                }
                result = operandA % operandB;
                break;
            case '^':
                result = pow(operandA, operandB);
                break;
            }
            stack.push(result);
        }
        else // Invalid character in the expression
            return false;
    }
    return stack.size() == 1 && (operandCount == operatorCount + 1); // as a valid postfix expression should have exactly one result on the stack, and the number of operands should be exactly one more than the operators
}

int main()
{
    string postFixExp = "";
    cout << "Enter a postfix expression: ";
    getline(cin, postFixExp);

    stack<int> stack;

    if (validatePostfix(postFixExp, stack))
    {
        int value = stack.top();
        cout << "The postfix expression: '" << postFixExp << "' is valid.\nThe result evaluated of this postfix expression: '" << postFixExp << "' is " << value << endl;
    }
    else
        cout << "The postfix expression is invalid.\n";

    system("pause");
    return 0;
}