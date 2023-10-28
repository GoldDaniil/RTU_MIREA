#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cmath>
#include<Windows.h>

using namespace std;

void past_glory(int num);    ///лаунчер заданий 

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
    cout << "the area of the rectangle = " << s_rectangle << endl << "\n";
}

void random_number_generator() {    //правильно
    int variable_m, variable_b, variable_c, variable_n, variable_s = 0, option;
    while (true) {
        cout << "select parameter option: (1 / 2) " << endl;
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore();
            cout << "error" << endl;
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
            cout << "error!" << endl;
            continue;
        }
        if (variable_n == 0) {
            cin.clear();
            cin.ignore();
            cout << "error!" << endl;
            continue;
        }
        break;
    }
    for (int i = 0; i < variable_n; i++) {
        variable_s = (variable_m * variable_s + variable_b) % variable_c;
        cout << variable_s << " ";
    }
}

void matrix_multiplication() {
    int matrix_buffer_lines;
    cout << "enter number of lines: \n";
    while (true) {
        if (!(cin >> matrix_buffer_lines)) {
            cin.clear();
            cin.ignore();
            cout << "error \n";
            continue;
        }
        break;
    }
    int matrix_buffer_column;
    cout << "enter number of column: \n";
    while (true) {
        if (!(cin >> matrix_buffer_column)) {
            cin.clear();
            cin.ignore();
            cout << "error \n";
            continue;
        }
        break;
    }

    const int matrix_line = matrix_buffer_lines;
    const int matrix_column = matrix_buffer_column;
    int matrix[matrix_line][matrix_column];  //почему ошибка


    ////
    // Выделяем память для массива
    int** matrix = new int* [matrix_buffer_lines];
    for (int i = 0; i < matrix_buffer_lines; i++) {
        matrix[i] = new int[matrix_buffer_column];
    }

    // Используйте массив matrix здесь

    // Не забудьте освободить память после использования массива
    for (int i = 0; i < matrix_buffer_lines; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    ////
}

int main() {
    //file_task(); // задача номер 1 - Файл - правильно
    //number_sign(); // задача номер 2 - Знак числа - правильно
    //geometric_figures(); // задача номер 3 - Геометрические фигуры - правильно 
    //past_glory(1); // задача номер 4 - Былая слава - правильно
    //random_number_generator(); // задача номер 7 - Генератор псевдослучайных чисел - правильно
    //matrix_multiplication(); // задача номер 8 - Умножение матриц
    //convert_base(); // задача номер 9 - Системы счисления - доработать - находится в файле main.cpp

    return 0;
}

void past_glory(int num) {       //правильно
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(h, num);
    cout << "Past Glory 1912 " << endl;
    for (int i = 0; i < 6; i++) {
        SetConsoleTextAttribute(h, 0x1f);
        for (int j = 0; j < 8; j++) {
            cout << "* ";
        }
        if ((i % 2) == 0) {
            SetConsoleTextAttribute(h, 0x44);
        }
        else {
            SetConsoleTextAttribute(h, 0xff);
        }

        for (int j = 0; j < 15; j++) {
            cout << "- ";
        }
        SetConsoleTextAttribute(h, 0x00);

        cout << endl;
    }


    for (int i = 0; i < 6; i++) {
        if ((i % 2) == 0) {
            SetConsoleTextAttribute(h, 0x44);
        }
        else {
            SetConsoleTextAttribute(h, 0xff);
        }
        for (int j = 0; j < 23; j++) {
            cout << "- ";
        }
        SetConsoleTextAttribute(h, 0x00);

        cout << endl;
    }
    SetConsoleTextAttribute(h, 0x07);
    cout << endl << endl ;
}
