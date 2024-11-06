#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

void display_menu();
void print_name();
void sum_difference_product();
void solve_linear_equation();
void solve_quadratic_equation();
void clear_input();

int main() {
    int choice;

    while (true) {
        display_menu();

        if (!(cin >> choice)) {
            cout << "ошибка ввода - введите число от 0 до 4\n";
            clear_input();
            continue;
        }

        switch (choice) {
        case 1: print_name(); break;
        case 2: sum_difference_product(); break;
        case 3: solve_linear_equation(); break;
        case 4: solve_quadratic_equation(); break;
        case 0: cout << "ну зачем...\n"; return 0;
        default: cout << "от 0 до 4 ток\n";
        }
    }
}

void display_menu() {
    cout << "\n=== лаунчер ===\n";
    cout << "1 - вывести имя\n";
    cout << "2 - сумма - разность - произведение\n";
    cout << "3 - решить линейное уравнение\n";
    cout << "4 - решить квадратное уравнение\n";
    cout << "0 - выход\n";
    cout << "выберите задачу: ";
}

void print_name() {
    string my_name = "asdasd";
    cout << "\nваше имя: " << my_name << "\n\n";
}

void sum_difference_product() {
    double num1, num2;

    cout << "\n--- сумма, разность, произведение ---\n";
    cout << ": ";
    while (!(cin >> num1)) {
cout << "error!
";
        clear_input();
    }

    cout << "введите второе число: ";
    while (!(cin >> num2)) {
cout << "error!
";
        clear_input();
    }

    cout << "сумма: " << num1 + num2 << "\n";
    cout << "разность: " << num1 - num2 << "\n";
    cout << "произведение: " << num1 * num2 << "\n";

    if (num2 != 0) {
        cout << "частное: " << num1 / num2 << "\n\n";
    }
    else {
        cout << "деление на ноль невозможно\n\n";
    }
}

void solve_linear_equation() {
    double b, c;

    cout << "\n--- линейное уравнение ---\n";
    cout << "введите значение b (не равное нулю): ";
    while (!(cin >> b) || b == 0) {
        cout << "ошибка - 'b' не должно быть нулём - повторите ввод: ";
        clear_input();
    }

    cout << "введите значение c: ";
    while (!(cin >> c)) {
        cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    double x = -c / b;
    cout << "решение уравнения: x = " << x << "\n\n";
}

void solve_quadratic_equation() {
    double a, b, c;

    cout << "\n--- квадратное уравнение ---\n";

    cout << "введите значение a: ";
    while (!(cin >> a)) {
        cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    cout << "введите значение b: ";
    while (!(cin >> b)) {
        cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    cout << "введите значение c: ";
    while (!(cin >> c)) {
        cout << "ошибка ввода - повторите ввод: ";
        clear_input();
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << "два действительных корня: x1 = " << root1 << ", x2 = " << root2 << "\n\n";
    }
    else if (discriminant == 0) {
        double root = -b / (2 * a);
        cout << "один действительный корень: x = " << root << "\n\n";
    }
    else {
        double real_part = -b / (2 * a);
        double imaginary_part = sqrt(-discriminant) / (2 * a);
        cout << "два комплексных корня: x1 = " << real_part << " + " << imaginary_part << "i, "
            << "x2 = " << real_part << " - " << imaginary_part << "i\n\n";
    }
}

void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
