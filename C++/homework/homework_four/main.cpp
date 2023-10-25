#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cmath>

using namespace std;

void file_task() {  //нужно доработать
    ofstream file("number.txt");
    if (!file) {
        cout << "error, failed to create file" << endl;
    }

    for (int i = 1; i <= 10; ++i) {
        file << i << endl;
    }
    file.close();

    ifstream in_file("number.txt");
    if (!in_file) {
        cout << "failed to open file" << endl;
    }

    int number, sum = 0;
    while (in_file >> number) {
        sum += number;
    }

    cout << "sum of numbers" << endl;
    in_file.close();

}

void number_sign() {    //правильно
    double variable_x, variable_result;
    while (true) {
        cout << "enter variable x : " << endl;
        if (!(cin >> variable_x)) {
            cin.clear();
            cin.ignore();
            cout << "error!" << endl;
            continue;
        }
        break;
    }
    if (variable_x > 0) {
        cout << 1 << endl << endl;
    }
    else if (variable_x < 0) {
        cout << -1 << endl << endl;
    }
    else if (variable_x == 0) {
        cout << 0 << endl << endl;
    }
}

void geometric_figures() {  //правильно
    double length_rectangle, width_rectangle, height_triangle, base_triangle, radius_circle;
    while (true) {
        cout << "enter length_rectangle, width_rectangle: " << endl;
        if (!(cin >> length_rectangle)) {
            cin.clear();
            cin.ignore();
            cout << "error!" << "\n";
            continue;
        }
        if (!(cin >> width_rectangle)) {
            cin.clear();
            cin.ignore();
            cout << "error" << "\n";
            continue;
        }
        break;
    }
    double s_rectangle;
    s_rectangle = length_rectangle * width_rectangle;
    cout << "the area of the rectangle = " << s_rectangle << endl;
}

void random_number_generator() {    //правильно
    int variable_m, variable_b, variable_c, variable_n, variable_s = 0, option;
    while (true) {
        cout << "select parameter option: (1 / 2) " << endl;
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore();
            cout << "error";
            continue;
        }
        break;
    }
    switch (option) {
    case 1:
        variable_m = 37;
        variable_b = 3;
        variable_c = 64;
        break;
    case 2:
        variable_m = 25173;
        variable_b = 13849;
        variable_c = 65537;
        break;
    default:
        cout << "error !" << endl;
        return;
    }

    while (true) {
        cout << "amount of elements: " << endl;
        if (!(cin >> variable_n)) {
            cin.clear();
            cin.ignore();
            cout << "error!";
            continue;
        }
        break;
    }
    for (int i = 0; i < variable_n; i++) {
        variable_s = (variable_m * variable_s + variable_b) % variable_c;
        cout << variable_s << " ";
    }
}

string number_systems(const string& number, int source_base, int target_base) { //ошибка - нужно исправить
    long long decimal = 0;
    long long power = 1;

    if ((source_base <= 0) || (target_base <= 0)) {
        return "error! radix cannot be zero or negative! ";
    }

    for (int i = number.size() - 1; i >= 0; --i) {
        int digit = number[i] - '0';

        if ((number[i] >= 'A') && (number[i] <= 'Z')) {
            digit = number[i] - 'A' + 10;
        }
        if ((digit < 0) || (digit >= source_base)) {
            return "error! invalid number for this number system! ";
        }

        decimal += static_cast<long long>(digit) * power;
        power *= source_base;
    }

    string result = "";
    while (decimal > 0) {
        int digit = decimal % target_base;
        char digitChar = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        result = digitChar + result;
        decimal /= target_base;
    }

    //return result;
    if (cin.fail()) {
        cout << "error " << endl;
        return;
    }

    string result = number_systems(number, source_base, target_base);

    cout << "result: " << result << endl;
}

int main() {
    file_task(); // задача номер 1 - Файл - нужно доработать
    number_sign(); // задача номер 2 - Знак числа
    geometric_figures(); // задача номер 3 - Геометрические фигуры
    random_number_generator(); // задача номер 7 - Генератор псевдослучайных чисел

    //продолжение number_systems();
    /*if (cin.fail()) {                                ОШИБКА!
        cout << "error " << endl;
        return;
    }

    string number;
    int source_base, target_base;
    string result = number_systems(number, source_base, target_base);

    cout << "result: " << result << endl;*/ // задача номер 9 - Системы счисления

    return 0;
}
