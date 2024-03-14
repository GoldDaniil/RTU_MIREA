//Using snake_case! Using camelCase for class!
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<string>
#include<sstream>
#include<algorithm>
#include<cmath>

using namespace std;

void test_zero() {
    while (true) {
        string test_array_str;
        int test_array;

        cout << "enter a number or 'exit' to exit:\n";
        cin >> test_array_str;

        if (test_array_str == "exit") {
            cout << "program completed!\n";
            return;
        }

        bool has_non_digit = false;
        for (char type : test_array_str) {
            if (!isdigit(type)) {
                has_non_digit = true;
                break;
            }
        }

        if (has_non_digit) {
            cerr << "error, enter only numbers!\n";
            cin.clear();
            cin.ignore();
        }
        else {
            stringstream(test_array_str) >> test_array;
            cout << "u enter : " << test_array << endl;
            break;
        }
    }
}

void two_dimensional_array() {
    HANDLE matrix_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(matrix_color, 0x0a);

    string number_matrices_str;
    int number_matrices;
    while (true) {
        //проверка на тип переменной number_matrices - количество матриц
        cout << "enter the number of matrices! Or if you want to stop entering, enter 'exit': \n";
        SetConsoleTextAttribute(matrix_color, 0x07);

        cin >> number_matrices_str;

        SetConsoleTextAttribute(matrix_color, 0x0a);
        if (number_matrices_str == "exit") {
            cout << "program completed!\n";
            return;
        }
        SetConsoleTextAttribute(matrix_color, 0x07);

        bool has_non_digit = false;
        for (char type : number_matrices_str) {
            if (!isdigit(type)) {
                has_non_digit = true;
                break;
            }
        }

        if (has_non_digit) {
            cerr << "error, enter only numbers!\n";
            cin.clear();
            cin.ignore();
        }
        else {
            stringstream(number_matrices_str) >> number_matrices;
            cout << "u enter : " << number_matrices << endl;
            break;
        }

    }

    SetConsoleTextAttribute(matrix_color, 0x07);

    double*** all_matrices = new double** [number_matrices]; // создаем массив для хранения всех двумерных массивов

    string number_elements_str, number_lines_str;
    int number_lines, number_elements;

    for (int k = 0; k < number_matrices; k++) { // создание матриц

        while (true) {
            //проверка на тип переменной number_lines - количество строк - подмассивов
            cout << "\nif you want to exit stop typing, enter 'exit'\nenter the number of rows of matrix " << k + 1 << ": \n";
            cin >> number_lines_str;

            if (number_lines_str == "exit") {
                cout << "program completed!\n";
                return;
            }

            bool has_non_digit = false;
            for (char type : number_lines_str) {
                if (!isdigit(type)) {
                    has_non_digit = true;
                    break;
                }
            }

            if (has_non_digit) {
                cerr << "error, enter only numbers!\n";
                cin.clear();
                cin.ignore();
            }
            else {
                stringstream(number_lines_str) >> number_lines;
                cout << "u enter : " << number_lines << endl;
                break;
            }
        }

        while (true) {
            //проверка на тип переменной number_elements - количество элементов в строках - подмассивах
            cout << "enter the number of elements in each row " << k + 1 << ": \n";
            cin >> number_elements_str;

            if (number_elements_str == "exit") {
                cout << "program completed!\n";
                return;
            }

            bool has_non_digit = false;
            for (char type : number_elements_str) {
                if (!isdigit(type)) {
                    has_non_digit = true;
                    break;
                }
            }

            if (has_non_digit) {
                cerr << "error, enter only numbers!\n";
                cin.clear();
                cin.ignore();
            }
            else {
                stringstream(number_elements_str) >> number_elements;
                cout << "u enter : " << number_elements << endl;
                break;
            }
        }

        double** array = new double* [number_lines];
        all_matrices[k] = array;

        for (int i = 0; i < number_lines; i++) { // строим матрицу A с выделением памяти
            array[i] = new double[number_elements];

            for (int j = 0; j < number_elements; j++) {
                cout << "enter element " << j + 1 << " of row " << i + 1 << " of matrix " << k + 1 << ": \n";

                //
                // ПОДУМАТЬ ПРО ПРОВЕРКУ НА ТИП ЗДЕСЬ - вводим i и j
                //

                while (true) {
                    if (!(cin >> array[i][j])) {
                        cin.clear();
                        cin.ignore();
                        cout << "error!\n";
                        continue;
                    }
                    break;
                }
            }
        }
    }

    // Вывод всех матриц
    SetConsoleTextAttribute(matrix_color, 0x0a);
    for (int k = 0; k < number_matrices; k++) {
        cout << "\nMatrix " << k + 1 << ":\n";
        SetConsoleTextAttribute(matrix_color, 0x07);

        for (int i = 0; i < number_lines; i++) {
            for (int j = 0; j < number_elements; j++) {
                cout << all_matrices[k][i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    SetConsoleTextAttribute(matrix_color, 0x07);

    SetConsoleTextAttribute(matrix_color, 0x0a);
    cout << "\nwhat to do with matrices?\n";
    SetConsoleTextAttribute(matrix_color, 0x07);
    cout << "if not, then enter ";
    SetConsoleTextAttribute(matrix_color, 0x0a);
    cout << "'exit'";
    SetConsoleTextAttribute(matrix_color, 0x07);
    cout << "!";
    cout << "\nif yes, enter the action sign : ";
    SetConsoleTextAttribute(matrix_color, 0x0a);
    cout << "' + ', ' - ', ' / ', ' * '";
    SetConsoleTextAttribute(matrix_color, 0x07);
    cout << "!\n";

    //начало действия с двумерными массивами
    char actions_matrix;
    while (true) {
        cin >> actions_matrix;
        switch (actions_matrix) {
        case '+':
            cout << "the result of adding two-dimensional arrays (matrices): \n\ntwo-dimensional array (matrix):\n";
            if (number_matrices >= 2) {
                try {
                    double** result_matrix = new double* [number_lines];

                    for (int i = 0; i < number_lines; i++) {
                        result_matrix[i] = new double[number_elements];

                        for (int j = 0; j < number_elements; j++) {
                            result_matrix[i][j] = 0;

                            for (int k = 0; k < number_matrices; k++) {
                                result_matrix[i][j] += all_matrices[k][i][j];
                            }

                            cout << result_matrix[i][j] << " ";
                        }
                        cout << endl;
                    }
                }
                catch (const exception& err) {
                    cout << "error! failed to allocate memory!\n" << err.what() << endl;
                }
            }
            else {
                cout << "error! not enough matrices to add!\n";
            }
            break;

        case '-':
            cout << "the result of difference two-dimensional arrays (matrices): \n\ntwo-dimensional array (matrix):\n";
            if (number_matrices >= 2) {
                cout << "\ndifference of matrices:\n";
                try {
                    double** result_matrix = new double* [number_lines];

                    for (int i = 0; i < number_lines; i++) {
                        result_matrix[i] = new double[number_elements];

                        for (int j = 0; j < number_elements; j++) {
                            result_matrix[i][j] = all_matrices[0][i][j];

                            try {
                                for (int k = 1; k < number_matrices; k++) {
                                    result_matrix[i][j] -= all_matrices[k][i][j];
                                }
                            }
                            catch (const exception& e) {
                                cout << "error: " << e.what() << endl;
                            }

                            cout << result_matrix[i][j] << " ";
                        }
                        cout << endl;
                    }
                }
                catch (const exception& rr) {
                    cout << "error!" << endl;
                }
            }
            else {
                cout << "error!\n";
            }
            break;

        case '/':
            cout << "quotient of matrices: \n";

            break;

        case '*':
            if (number_matrices >= 2) {
                cout << "\nproduct of matrices :\n";
                if (number_matrices >= 2) {
                    try {
                        double** result_matrix = new double* [number_lines];

                        for (int i = 0; i < number_lines; i++) {
                            result_matrix[i] = new double[number_elements];

                            for (int j = 0; j < number_elements; j++) {
                                result_matrix[i][j] = 0;

                                for (int k = 0; k < number_matrices; k++) {
                                    result_matrix[i][j] = result_matrix[i][j]*all_matrices[k][i][j];
                                }

                                cout << result_matrix[i][j] << " ";
                            }
                            cout << endl;
                        }
                    }
                    catch (const exception& err) {
                        cout << "error! failed to allocate memory!\n" << err.what() << endl;
                    }
                }
            }
            break;

            //case "exit":
        default:
            cout << "error!\n";
            break;
        }
    }
}

int main() {
    two_dimensional_array();
    //test_zero();

    return 0;
}
