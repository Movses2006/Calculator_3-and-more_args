#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

double performCalculating(char operation, double operand1, double operand2) {
    switch (operation) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        if (operand2 != 0.0) {
            return operand1 / operand2;
        }
        else {
            cerr << "Error: Divaded by zero\n";
            return NAN;
        }
    default:
        cerr << "Invalid operation\n";
        return NAN;
    }
}

double evaluateExpression(const string& expression) {
    vector<double> values;
    vector<char> operations;

    int i = 0;
    while (i < expression.length()) {
        while (i < expression.length() && isspace(expression[i])) {
            i++;
        }

        if (isdigit(expression[i]) || (expression[i] == '-' && (i == 0 || (!isdigit(expression[i - 1]) && i + 1 < expression.length() && isdigit(expression[i + 1]))))) {
            int j = i;
            while (j < expression.length() && (isdigit(expression[j]) || expression[j] == '.')) {
                j++;
            }
            values.push_back(stod(expression.substr(i, j - i)));
            i = j;
        }
        else {
            if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
                operations.push_back(expression[i]);
                i++;
            }
            else {
                cerr << "Invalid character in the expression\n";
                return NAN;
            }
        }
    }

    for (int k = 0; k < operations.size();) {
        if (operations[k] == '*' || operations[k] == '/') {
            double result = performCalculating(operations[k], values[k], values[k + 1]);

            values.erase(values.begin() + k, values.begin() + k + 2);
            values.insert(values.begin() + k, result);
            operations.erase(operations.begin() + k);
        }
        else {
            k++;
        }
    }

    double result = values[0];
    for (int k = 0; k < operations.size(); ++k) {
        result = performCalculating(operations[k], result, values[k + 1]);
    }

    return result;
}

int main() {
    string expression;

    cout << "Expression: ";
    getline(cin, expression);

    double result = evaluateExpression(expression);
    if (!isnan(result)) {
        cout << "Result: " << result << endl;
    }
    else {
        cout << "Error.\n";
    }

    return 0;
}