//Using snake_case! Using camelCase for class!
#include<iostream>
#include<Windows.h>

using namespace std;

void two_dimensional_array() {
    HANDLE matrix_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(matrix_color, 0x0a);
    int number_matrices;
    while (true) {
        cout << "enter the number of matrices: \n";
        if (!(cin >> number_matrices)) {
            cin.clear();
            cin.ignore();
            cout << "error\n";
            continue;
        }
        break;
    }
    SetConsoleTextAttribute(matrix_color, 0x07);

    for (int k = 0; k < number_matrices; k++) { // создание матриц

        int number_lines;
        double number_elements;
        while (true) {
            cout << "\nenter the number of rows of matrix: \n";
            if (!(cin >> number_lines)) {
                cin.clear();
                cin.ignore();
                cout << "error\n";
                continue;
            }
            cout << "enter the number of elements in each row: \n";
            if (!(cin >> number_elements)) {
                cin.clear();
                cin.ignore();
                cout << "error\n";
                continue;
            }
            break;
        }

        double** array = new double* [number_lines];

        for (int i = 0; i < number_lines; i++) { // строим матрицу A с выделением памяти

            array[i] = new double[number_elements];
            for (int j = 0; j < number_elements; j++) {
                string arr_exit;
                cout << "enter element " << j + 1 << " of row " << i + 1 << " of matrix " << k + 1 << ": \n";
                while (true) {
                    if (arr_exit == "exit" or arr_exit == "end") {
                        return;
                    }
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

        SetConsoleTextAttribute(matrix_color, 0x0a);
        cout << endl << "matrix " << k + 1 << ":\n";
        SetConsoleTextAttribute(matrix_color, 0x07);

        const int Z = number_matrices;
        double** array_mas = new double*[Z]; //ВЫДЕЛЯЕМ АДРЕСА ЯЧЕЙКИ В ПАМЯТИ НА number_matrices МЕСТ
        
        for (int i = 0; i < Z; i++) {
            array_mas[i] = new double[number_lines * number_elements];
            for (int j = 0; j < number_lines; j++) {
                for (int k = 0; k < number_elements; k++) {
                    cout << array_mas[i][j * number_elements + k] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
                                    //СОХРАНЯЕМ КАЖДЫЙ ДВУМЕРНЫЙ МАССИВ В ОДИНАРНЫЙ МАССИВ array_mas
                                    // ВЫЗОВ ПО ИНДЕКСАМ

        for (int i = 0; i < number_matrices; i++) {
            cout << array_mas[i+1];
        }
    }

    char actions_matrix;

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



    while (true) {
        cin >> actions_matrix;
        switch (actions_matrix) {
        case '+':
            cout << "sum of matrices: \n";

            break;
        case '-':
            cout << "matrix difference: \n";

            break;
        case '/':
            cout << "quotient of matrices: \n";

            break;
        case '*':
            cout << "product of matrices: \n";

            break;
        case 'exit':
            cout << "asdsda \n";
            return;
            break;
        default:
            cout << "error!\n";
            break;
        }
    }
}


int main() {
    two_dimensional_array();
    return 0;
}
