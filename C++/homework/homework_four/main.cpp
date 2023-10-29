#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cmath>
#include<Windows.h>

using namespace std;

void past_glory();   // обьявление функции
void comment_output(); // обьявление функции

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
    double variable_x;
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
    double length_rectangle, width_rectangle;
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
    double s_rectangle = length_rectangle * width_rectangle;
    cout << "the area of the rectangle = " << s_rectangle << endl << "\n";

    double height_triangle, base_triangle;
    while (true) {
        cout << "enter height triangle, base triangle: " << endl;
        if (!(cin >> height_triangle)) {
            cin.clear();
            cin.ignore();
            cout << "error!" << "\n";
            continue;
        }
        if (!(cin >> base_triangle)) {
            cin.clear();
            cin.ignore();
            cout << "error" << "\n";
            continue;
        }
        break;
    }
    double area_of_triangle = (height_triangle * base_triangle) / 2;
    cout << "the area of the triangle = " << area_of_triangle << endl << "\n";

    double radius_circle;
    while (true) {
        cout << "enter radius circle: " << endl;
        if (!(cin >> radius_circle)) {
            cin.clear();
            cin.ignore();
            cout << "error!" << "\n";
            continue;
        }
        break;
    }
    const int PI = 3.14159265359;
    double area_of_circle = PI * pow(radius_circle, 2);
    cout << "the area of the circle = " << area_of_circle << endl << "\n";
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
            cout << "error!" << endl << endl;
            continue;
        }
        if (variable_n == 0) {
            cin.clear();
            cin.ignore();
            cout << "error!" << endl << endl;
            continue;
        }
        break;
    }
    for (int i = 0; i < variable_n; i++) {
        variable_s = (variable_m * variable_s + variable_b) % variable_c;
        cout << variable_s << " ";
    }
    cout << endl << endl;
}

void matrix_multiplication() {
    HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE);
    int rows;
    while (true) {
        cout << "enter amount rows: \n";
        if (!(cin >> rows)) {
            cin.clear();
            cin.ignore();
            cout << "error \n";
            continue;
        }
        break;
    }
    int cols;
    while (true) {
        cout << "enter amount column: \n";
        if (!(cin >> cols)) {
            cin.clear();
            cin.ignore();
            cout << "error \n" << endl;
            continue;
        }
        break;
    }

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "enter amout elements " << i << " and " << j << "\n" << endl;
            while (true) {
                if (!(cin >> matrix[i][j])) {
                    cin.clear();
                    cin.ignore();
                    cout << "error \n";
                    continue;
                }
                break;
            }
        }
    
    }

    cout << "enter two-dimensional array - matrix :\n" << endl;
    SetConsoleTextAttribute(back_color, 0x04);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl << endl;
    }
    SetConsoleTextAttribute(back_color, 0x07);


    //for (int i = 0; i < rows; i++) {
    //    delete[] matrix[i];
    //}
    delete matrix;
}

///тест
void arr() {
    int massiv[4]{ 1, 2, 3, 4};
    cout << massiv << endl;
    cout << &massiv << endl;
    cout << *massiv << endl;
    cout << &massiv[0] << endl;
    //cout << *(massiv[0]) << endl;
    cout << &massiv[1] << endl;
    //cout << *(massiv[1]) << endl;
    cout << &massiv[2] << endl;
    cout << &massiv[3] << endl;

    //int matrix[3][4] ; //3 массива в каждом из которых 4 элемента- итого двумерный массив 
    

    int *local = &massiv[0];
    cout << local << endl;
    cout << (local + 2) << endl;
    
    cout << *(local + 2) << endl;

    //delete massiv;
    //cout << " \n";
    //
    //cout << massiv << endl;
    //cout << &massiv << endl;
    //cout << *massiv << endl;
    //cout << &massiv[0] << endl;
    ////cout << *(massiv[0]) << endl;
    //cout << &massiv[1] << endl;
    ////cout << *(massiv[1]) << endl;
    //cout << &massiv[2] << endl;
    //cout << &massiv[3] << endl;

    //cout << *(massiv[2]) << endl;  //разница между адресами 4 байта
}
///тест

//void matrix_multiplication() {
//    int matrix_buffer_lines;
//    cout << "enter number of lines: \n";
//    while (true) {
//        if (!(cin >> matrix_buffer_lines)) {
//            cin.clear();
//            cin.ignore();
//            cout << "error \n";
//            continue;
//        }
//        break;
//    }
//    int matrix_buffer_column;
//    cout << "enter number of column: \n";
//    while (true) {
//        if (!(cin >> matrix_buffer_column)) {
//            cin.clear();
//            cin.ignore();
//            cout << "error \n";
//            continue;
//        }
//        break;
//    }
//
//    const int matrix_line = matrix_buffer_lines;
//    const int matrix_column = matrix_buffer_column;
//    int matrix[matrix_line][matrix_column];  //почему ошибка
//
//    //
//     Выделяем память для массива
//    int** matrix = new int* [matrix_buffer_lines];
//    for (int i = 0; i < matrix_buffer_lines; i++) {
//        matrix[i] = new int[matrix_buffer_column];
//    }
//
//     Используйте массив matrix здесь
//
//     Не забудьте освободить память после использования массива
//    for (int i = 0; i < matrix_buffer_lines; i++) {
//        delete[] matrix[i];
//    }
//    delete[] matrix;
//    //
//}

void task_launcher() {  
    int task_number;

    while (true) {
        comment_output();
  
        cout << endl;
        cout << "(if you want to exit the program, enter 'end') \n";
        cout << "enter task_number: "; 

        if (!(cin >> task_number)) {
            cin.clear();
            string input;
            cin >> input;
            if (input == "end") {
                break;
            }
            cout << "error \n" << endl;
            continue;
        }
        
        switch (task_number) {
        case 1:
            cout << "\n";
            cout << "first task - 'File task' \n";
            file_task();
            break;
        case 2:
            cout << "\n";
            cout << "second task - 'Problem Number sign' \n";
            number_sign();
            break;
        case 3:
            cout << "\n";
            cout << "third task - 'Geometric figures' \n";
            geometric_figures();
            break;
        case 4:
            cout << "\n";
            cout << "fourth task - 'Past Glory' \n";
            past_glory();
            break;
        case 5:
            cout << "\n";
            cout << "fifth task - 'Sine wave' \n";
            //  
            break;
        case 6:
            cout << "\n";
            cout << "sixth task - 'Automatic recognizer' \n";
            //
            break;
        case 7:
            cout << "\n";
            cout << "seventh task - 'Pseudo-random number generator' \n";
            random_number_generator();
            break;
        case 8:
            cout << "\n";
            cout << "eighth task - 'Matrix multiplication' \n";
            matrix_multiplication();
            break;
        case 9:
            cout << "\n";
            cout << "ninth task - 'Number systems' \n";
            //convert_base(); - доработать
            break;
        default:
            cout << "\n";
            cout << "error! \n";
            break;
        }
    }
}

int main() {
    task_launcher(); // - лаунчер
    //arr();
    return 0;
}

void past_glory() {       //правильно
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
} //обьявление функции

void comment_output() {
    HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE); 
    //SetConsoleTextAttribute(back_color, 0xf1); - синий на белом   
    // a - зеленый
    SetConsoleTextAttribute(back_color, 0x0a);
    cout << "---------------------------------------------\n TASK NUMBER:  \n 1 task - 'File' \n 2 task - 'Number sign' \n 3 task - 'Geometric shapes' \n 4 task - 'Past glory' \n 5 task - 'Sine wave' \n 6 task - 'Automatic recognizer' \n 7 task - 'Pseudorandom number generator' \n 8 task - 'Matrix multiplication' \n 9 task - 'Number systems' " << endl;
    SetConsoleTextAttribute(back_color, 0x07);

}  //обьявление функции

