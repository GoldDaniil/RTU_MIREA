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
        int* array_mas = new int[Z]; //ВЫДЕЛЯЕМ АДРЕСА ЯЧЕЙКИ В ПАМЯТИ НА number_matrices МЕСТ
        
        for (int Z = 0; Z < number_matrices; Z++) {
            for (int i = 0; i < number_lines; i++) {
                for (int j = 0; j < number_elements; j++) {
                    cout << array[i][j] << " ";
                    cout << endl;
                    cout << "exit\n";
                    array_mas[Z] == array[i][j];  //СОХРАНЯЕМ КАЖДЫЙ ДВУМЕРНЫЙ МАССИВ В ОДИНАРНЫЙ МАССИВ array_mas
                }                                 // ВЫЗОВ ПО ИНДЕКСАМ
                cout << endl;
            }
            
        }

        for (int i = 0; i < number_matrices; i++) {
            cout << array_mas[i+1];
        }

        //  a/b == a * b**-1 
        ///// 
        ///                 СОХРАНЯЕМ КАЖДУЮ МАТРИЦУ С ПОМОЩЬЮ ЦИКЛА ДО N (ВВЕДЕНОЕ КОЛВА МАТРИЦ) 
        ///                 ЗАТЕМ ХРАНИМ НО !НЕ! ВЫВОДИМ ЭТИ МАТРИЦЫ (КОТОРЫЕ СОХРАНИЛИ)
        ///                 ЗАТЕМ В SWITCH CASE в ЦИКЛЕ (СКЛАДЫВАЕМ ВСЕ МАТРИЦЫ)



        //int storage_rows, storage_cols;
        //int** storage_array = new int* [storage_rows];
        //for (int i = 0; i < storage_rows; i++) {
        //    storage_array = new int* [storage_cols];
        //} //двумерный массив для хранения всех матриц до n

        //for (int i = 0; i < number_lines; i++) {
        //    delete[] array[i];
        //}
        //delete[] array;
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

    //  ИСПОЛЬЗОВАТЬ ИСКЛЮЧЕНИЯ НА ПРЕДМЕТ ПРОВЕРКИ ДВУМЕРНЫХ-МАССИВОВ

    //int storage_rows, storange_cols;
    //int** storage_array = new int*[storage_rows];
    //for (int i = 0; i < storage_rows; i++) {
    //    storage_array[i] = new int[storange_cols];
    //} //создали динамический двумерный массив, в котором будут храниться 
    //результаты + - / * матриц    - после каждого окончательного действия 
    // очищать память

    while (true) {
        cin >> actions_matrix;
        switch (actions_matrix) {
        case '+':
            cout << "sum of matrices: \n";




            //try {
      





            //    if (number_matrices <= 1) {
            //        throw std::logic_error("Недостаточно матриц для выполнения сложения.");
            //    }

            //    cout << "Введите размеры первой матрицы:\n";
            //    int number_lines, number_elements;
            //    cout << "Количество строк: ";
            //    if (!(cin >> number_lines) || number_lines <= 0) {
            //        throw std::invalid_argument("Ошибка ввода размера матрицы.");
            //    }
            //    cout << "Количество элементов в каждой строке: ";
            //    if (!(cin >> number_elements) || number_elements <= 0) {
            //        throw std::invalid_argument("Ошибка ввода размера матрицы.");
            //    }

            //    double** storage_array = new double* [number_lines];
            //    for (int i = 0; i < number_lines; i++) {
            //        storage_array[i] = new double[number_elements];
            //    }

            //    cout << "Введите элементы первой матрицы:\n";
            //    for (int i = 0; i < number_lines; i++) {
            //        for (int j = 0; j < number_elements; j++) {
            //            cout << "Элемент " << j + 1 << " строки " << i + 1 << ": ";
            //            if (!(cin >> storage_array[i][j])) {
            //                throw std::invalid_argument("Ошибка ввода элемента матрицы.");
            //            }
            //        }
            //    }

            //    for (int k = 1; k < number_matrices; k++) {


            //        if (number_lines != storage_rows || number_elements != storange_cols) {
            //            throw std::invalid_argument("Несовместимые размеры матриц для сложения.");
            //        }

            //        // Выполняем сложение матриц
            //        for (int i = 0; i < number_lines; i++) {
            //            for (int j = 0; j < number_elements; j++) {
            //                storage_array[i][j] += array[i][j];
            //            }
            //        }
            //    }

            //    // Выводим результат сложения
            //    cout << "Результат сложения:\n";
            //    for (int i = 0; i < number_lines; i++) {
            //        for (int j = 0; j < number_elements; j++) {
            //            cout << storage_array[i][j] << " ";
            //        }
            //        cout << endl;
            //    }

            //    // Освобождаем память для входных матриц
            //    for (int i = 0; i < number_lines; i++) {
            //        delete[] array[i];
            //    }
            //    delete[] array;

            //    // Освобождаем память для storage_array
            //    for (int i = 0; i < number_lines; i++) {
            //        delete[] storage_array[i];
            //    }
            //    delete[] storage_array;

            //    // По желанию, сбрасываем storage_array для будущих операций
            //    // (в зависимости от логики вашей программы)
            //    // ...
            //}
            //catch (const std::exception& e) {
            //    cerr << "Ошибка: " << e.what() << endl;
            //    // Обрабатываем ошибку, например, очищаем память и выходим из программы
            //}
            

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
