#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cmath>

using namespace std;

void file_task() {  //правильно
    ofstream file("numbers.txt");
    if (file.is_open()) {
        cout << "enter 10 numbers: \n";
        for (int i = 0; i < 10; ++i) {
            int num;
            while (true) {
                if (!(cin >> num)) {
                    cin.clear();
                    cin.ignore();
                    cout << "you need to enter the data type integer\n";
                    continue;
                }
                break;
            }
            file << num << endl;
        }
        file.close();
        // повторное открытие файла и нахождение суммы чисел
        ifstream read_file("numbers.txt");
        if (read_file.is_open()) {
            int num, sum = 0;
            while (read_file >> num) {
                sum += num;
            }
            cout << "sum of numbers: " << sum << endl << endl;
            read_file.close();
        }
        else {
            cout << "error!" << endl;
        }
    }
    else {
        cout << "error!" << endl;
    }
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

void past_glory(){       //правильно
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            cout << "* ";
        }
        for (int j = 0; j < 15; j++) {
            cout << "- ";
        }
        cout << endl;
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 23; j++) {
            cout << "- ";
        }
        cout << endl;
    }
    cout << endl << endl;
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

int main() {
    file_task(); // задача номер 1 - Файл - правильно
    number_sign(); // задача номер 2 - Знак числа - правильно
    geometric_figures(); // задача номер 3 - Геометрические фигуры - правильно
    past_glory(); // задача номер 4 - Былая слава - правильно
    random_number_generator(); // задача номер 7 - Генератор псевдослучайных чисел - правильно
   // convert_base(); // задача номер 9 - Системы счисления - доработать - находится в файле main.cpp

    return 0;
}
