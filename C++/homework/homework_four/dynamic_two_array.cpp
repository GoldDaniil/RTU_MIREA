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

    int number_lines, number_elements;

    double*** all_matrices = new double** [number_matrices]; // создаем массив для
    //хранения всех двумерных массивов

    for (int k = 0; k < number_matrices; k++) { // создание матриц

        while (true) {
            cout << "\nenter the number of rows of matrix " << k + 1 << ": \n";
            if (!(cin >> number_lines) or (number_lines <= 1)) {
                cin.clear();
                cin.ignore();
                cout << "error\n";
                continue;
            }
            cout << "enter the number of elements in each row " << k + 1 << ": \n";
            if (!(cin >> number_elements) or (number_elements <= 1)) {
                cin.clear();
                cin.ignore();
                cout << "error\n";
                continue;
            }
            break;
        }

        double** array = new double* [number_lines];
        all_matrices[k] = array;
        string arr_exit;

        for (int i = 0; i < number_lines; i++) { // строим матрицу A с выделением памяти
            array[i] = new double[number_elements];

            for (int j = 0; j < number_elements; j++) {
                cout << "enter element " << j + 1 << " of row " << i + 1 << " of matrix " << k + 1 << ": \n";
                while (true) {
                    if (!(cin >> array[i][j])) {
                        cin.clear();
                        cin.ignore();
                        cout << "error!\n";
                        continue;
                    }
                    break;
                    //if (arr_exit == "exit" or arr_exit == "end") {
                    //    return;
                    //}
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

    int actions_matrix;

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
