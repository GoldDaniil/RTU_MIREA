#include <iostream>
#include <cmath>
#include <limits>
#include <string>

void display_menu();

void handleMenuChoice(int choice);

void print_name();
void calculate_sum_difference_product();
void solve_linear_equation();
void solve_quadratic_equation();

void clear_input();

int main() {
    int choice;

    while (true) {
        display_menu();
        if (!(std::cin >> choice)) {
            std::cout << "ошибка ввода: введите число от 0 до 4\n";
            clear_input();
            continue;
        }

        if (choice == 0) {
            std::cout << "зачем...\n";
            return 0;
        }

        handleMenuChoice(choice);
    }
}

void display_menu() {
    std::cout << "\n=== лаунчер ===\n";
    std::cout << "1 - вывести имя\n";
    std::cout << "2 - сумма, разность, произведение\n";
    std::cout << "3 - решить линейное уравнение\n";
    std::cout << "4 - решить квадратное уравнение\n";
    std::cout << "0 - выход\n";
    std::cout << "выберите задачу: ";
}

void handleMenuChoice(int choice) {
    switch (choice) {
    case 1: print_name(); break;
    case 2: calculate_sum_difference_product(); break;
    case 3: solve_linear_equation(); break;
    case 4: solve_quadratic_equation(); break;
    default:
        std::cout << "ошибка: введите число от 0 до 4\n";
        break;
    }
}

void print_name() {
    const std::string name = "asdasd";
    std::cout << "\nваше имя: " << name << "\n\n";
}

void calculate_sum_difference_product() {
    double num1, num2;

    std::cout << "\n--- сумма, разность, произведение ---\n";
    std::cout << "введите первое число: ";
    while (!(std::cin >> num1)) {
        std::cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    std::cout << "введите второе число: ";
    while (!(std::cin >> num2)) {
        std::cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    std::cout << "сумма: " << num1 + num2 << "\n";
    std::cout << "разность: " << num1 - num2 << "\n";
    std::cout << "произведение: " << num1 * num2 << "\n";

    if (num2 != 0) {
        std::cout << "частное: " << num1 / num2 << "\n\n";
    }
    else {
        std::cout << "деление на ноль невозможно\n\n";
    }
}

void solve_linear_equation() {
    double b, c;

    std::cout << "\n--- линейное уравнение (b * x + c = 0) ---\n";

    std::cout << "введите значение b (не равное нулю): ";
    while (!(std::cin >> b) || b == 0) {
        std::cout << "ошибка: b не должно быть равно нулю. повторите ввод: ";
        clear_input();
    }

    std::cout << "введите значение c: ";
    while (!(std::cin >> c)) {
        std::cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    double x = -c / b;
    std::cout << "решение уравнения: x = " << x << "\n\n";
}

void solve_quadratic_equation() {
    double a, b, c;

    std::cout << "\n--- квадратное уравнение (a * x^2 + b * x + c = 0) ---\n";

    std::cout << "введите значение a: ";
    while (!(std::cin >> a)) {
        std::cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    std::cout << "введите значение b: ";
    while (!(std::cin >> b)) {
        std::cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    std::cout << "введите значение c: ";
    while (!(std::cin >> c)) {
        std::cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double root1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double root2 = (-b - std::sqrt(discriminant)) / (2 * a);
        std::cout << "2 действительных корня: x1 = " << root1 << ", x2 = " << root2 << "\n\n";
    }
    else if (discriminant == 0) {
        double root = -b / (2 * a);
        std::cout << "1 действительный корень: x = " << root << "\n\n";
    }
    else {
        double realPart = -b / (2 * a);
        double imaginaryPart = std::sqrt(-discriminant) / (2 * a);
        std::cout << "2 комплексных корня: x1 = " << realPart << " + " << imaginaryPart << "i, "
            << "x2 = " << realPart << " - " << imaginaryPart << "i\n\n";
    }
}

void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
