#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

// Функция для вычисления выражения
double evaluate(const string& expr, size_t& index);

// Функция для выражения в скобках
double getFactor(const string& expr, size_t& index) {
    double result = 0;

    while (isspace(expr[index])) index++; // Пропускаем пробелы

    if (expr[index] == '(') {
        index++; // Пропускаем открывающую скобку
        result = evaluate(expr, index);
        index++; // Пропускаем закрывающую скобку
    }
    else {
        while (isdigit(expr[index]) || expr[index] == '.') {
            if (expr[index] == '.') {
                index++;
                double decimalPlace = 1;
                while (isdigit(expr[index])) {
                    result = result + (expr[index] - '0') * (decimalPlace / 10);
                    decimalPlace *= 10;
                    index++;
                }
                break; // Выход из цикла после обработки десятичной части
            }
            result = result * 10 + (expr[index] - '0');
            index++;
        }
    }
    return result;
}

// Функция для умножения и деления
double getTerm(const string& expr, size_t& index) {
    double result = getFactor(expr, index);
    while (expr[index] == '*' || expr[index] == '/') {
        char op = expr[index];
        index++;
        double factor = getFactor(expr, index);
        if (op == '*') {
            result *= factor;
        }
        else {
            if (factor == 0) {
                throw runtime_error("Ошибка: Деление на ноль.");
            }
            result /= factor;
        }
    }
    return result;
}

// Функция для сложения и вычитания
double evaluate(const string& expr, size_t& index) {
    double result = getTerm(expr, index);
    while (expr[index] == '+' || expr[index] == '-') {
        char op = expr[index];
        index++;
        double term = getTerm(expr, index);
        if (op == '+') {
            result += term;
        }
        else {
            result -= term;
        }
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "RU");
    cout << "Введите выражение без пробелов: ";
    string expression;
    getline(cin, expression); // Получаем выражение целиком

    size_t index = 0;
    try {
        double result = evaluate(expression, index);
        cout << "Результат: " << result << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
