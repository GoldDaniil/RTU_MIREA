// Homework 4 blocks of Procedural programming.
// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes.

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cmath>
#include<Windows.h>

using namespace std;

class FunctionHolder {
public:
    //void past_glory();   // обьявление функции
    //void comment_output(); // обьявление функции

    void file_task() {  //правильно
        ofstream file("numbers.txt");
        if (file.is_open()) {
            cout << "\nif you want to stop typing, enter 'exit' \nenter 10 numbers: \n";
            double num;
            for (int i = 0; i < 10; ++i) {
                while (true) {
                    if (!(cin >> num)) {
                        cin.clear();
                        cin.ignore();
                        cout << "you need to enter the data type integer \n";
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
                double num, sum = 0;
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
        if (length_rectangle <= 0 or width_rectangle <= 0) {
            cout << "error\n\n";
        }
        else {
            double s_rectangle = length_rectangle * width_rectangle;

            cout << "the area of the rectangle = " << s_rectangle << endl << "\n";
        }

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
        if (height_triangle <= 0 or base_triangle <= 0) {
            cout << "error\n\n";
        }
        else {
            double area_of_triangle = (height_triangle * base_triangle) / 2;
            cout << "the area of the triangle = " << area_of_triangle << endl << "\n";
        }

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
        if (radius_circle <= 0) {
            cout << "error\n\n";
        }
        else {
            const int PI = 3.14159265359;
            double area_of_circle = PI * pow(radius_circle, 2);
            cout << "the area of the circle = " << area_of_circle << endl << "\n";
        }
    }

    void automatic_recognizer() {  //проверить  //
        string roman_numeral;
        int decoded_number = 0;

        cout << "enter: ";
        cin >> roman_numeral;

        for (int i = 0; i < roman_numeral.length(); i++) {
            char current_digit = roman_numeral[i];

            switch (current_digit) {
            case 'I':
                decoded_number += 1;
                break;
            case 'V':
                decoded_number += 5;
                break;
            case 'X':
                decoded_number += 10;
                break;
            case 'L':
                decoded_number += 50;
                break;
            case 'C':
                decoded_number += 100;
                break;
            case 'D':
                decoded_number += 500;
                break;
            case 'M':
                decoded_number += 1000;
                break;
            default:
                cout << "error \n";
                return; // доделать
                break;
            }

            if (i > 0 && roman_numeral[i - 1] > current_digit) {
                decoded_number -= 2 * current_digit;
            }
        }

        cout << "good: " << decoded_number << endl;
    }

    void random_number_generator() {    //правильно   ТОЛЬКО ЦЕЛЫЕ И ПОЛОЖИТЕЛЬНЫЕ ЗНАЧНИЕЯ
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
    //!ДИНАМИЧЕСКИЙ ДВУМЕРНЫЙ МАССИВ - 
    //! ДИНАМИЧЕСКОЕ ВЫДЕЛЕНИЕ ПАМЯТИ
    void dynamic_matrix_multiplication() {
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
        //if (rows == "end") {
        //сделать так - чтобы при вводе end
        // компилятор закрывался.
        //}

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
        cout << "table A \n";
        SetConsoleTextAttribute(back_color, 0x0f);
        cout << "enter two-dimensional array - matrix :\n" << endl;
        SetConsoleTextAttribute(back_color, 0x07);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl << endl;
        }

        delete matrix;
    }
    //!НЕ ТРОГАТЬ 
    //! фукнция НЕ принадлежит лаунчеру
    void static_dimensional_arrays() {
        const int seller_string = 3;
        const int product_column = 4;

        const int price_string = 4;
        const int commission_column = 2;

        double table_A[seller_string][product_column]{ {5, 2, 0, 10}, {3, 5, 2, 5}, {20, 0, 0, 0} };
        double table_B[price_string][commission_column]{ {1.20, 0.50}, {2.80, 0.40}, {5.00, 1.00}, {2.00, 1.50} };

        cout << "table A: \n";
        for (int i = 0; i < seller_string; i++) {
            for (int j = 0; j < product_column; j++) {
                cout << table_A[i][j] << " ";
            }
            cout << "\n";
        }
        cout << endl;
        cout << "table B: \n";
        for (int i = 0; i < price_string; i++) {
            for (int j = 0; j < commission_column; j++) {
                cout << table_B[i][j] << " ";
            }
            cout << "\n";
        }
        cout << endl;

        double multiplication_result[seller_string][commission_column] = {};
        for (int i = 0; i < seller_string; i++) {
            for (int j = 0; j < commission_column; j++) {
                for (int k = 0; k < product_column; k++) {
                    multiplication_result[i][j] += table_A[i][k] * table_B[k][j];
                }
            }
        }
        if (product_column != price_string) {
            cout << "error \n"; //проверка на возможность перемножения матриц
            return;
        }

        cout << "result two-dimensional array \ntable C: \n";
        for (int i = 0; i < seller_string; i++) {
            for (int j = 0; j < commission_column; j++) {
                cout << multiplication_result[i][j] << " ";
            }
            cout << "\n";
        }
        cout << endl;
        double max_sales = multiplication_result[0][0];
        double min_sales = multiplication_result[0][0];
        double max_commission = multiplication_result[0][1];
        double min_commission = multiplication_result[0][1];
        double total_sales = 0;
        double total_commission = 0;
        double total_money_through_sellers = 0;

        for (int i = 0; i < seller_string; i++) {
            double seller_sales = 0;
            double seller_commission = 0;
            for (int j = 0; j < commission_column; j++) {
                seller_sales += multiplication_result[i][j];
                seller_commission += multiplication_result[i][j];
                total_money_through_sellers += multiplication_result[i][j];
                if (j == 0) {
                    if (seller_sales > max_sales) {
                        max_sales = seller_sales;
                    }
                    if (seller_sales < min_sales) {
                        min_sales = seller_sales;
                    }
                }
                if (j == 1) {
                    if (seller_commission > max_commission) {
                        max_commission = seller_commission;
                    }
                    if (seller_commission < min_commission) {
                        min_commission = seller_commission;
                    }
                }
                total_commission += multiplication_result[i][j];
            }
            total_sales += seller_sales;
        }

        cout << "highest sales: " << max_sales << ", lowest sales: \n" << min_sales << "high commission " << max_commission << ", low commission: " << min_commission << endl;
        cout << "total amount of money received from sales " << total_sales << endl;
        cout << "total commission amount " << total_commission << endl;
        cout << "sum money " << total_money_through_sellers;
    }

    void static_dimensional() {
        const int seller_string = 3;
        const int product_column = 4;

        const int price_string = 4;
        const int commission_column = 2;

        double table_A[seller_string][product_column]{ {5, 2, 0, 10}, {3, 5, 2, 5}, {20, 0, 0, 0} };
        double table_B[price_string][commission_column]{ {1.20, 0.50}, {2.80, 0.40}, {5.00, 1.00}, {2.00, 1.50} };
    }

    void convert_base() {
        string hex_number;
        cout << "enter : "; //ввод в 16 сист счисления
        cin >> hex_number;

        string octal_number = "";

        string hexTable[16] = { "000", "001", "010", "011", "100", "101", "110", "111",
                                    "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" };

        for (int i = 0; i < hex_number.length(); i++) {

            if ((hex_number[i] >= '0') && (hex_number[i] <= '9')) {
                int index = hex_number[i] - '0';
                octal_number += hexTable[index];
            }
            else if ((hex_number[i] >= 'A') && (hex_number[i] <= 'F')) {
                int index = hex_number[i] - 'A' + 10;
                octal_number += hexTable[index];
            }
        }

        int pos = octal_number.find_first_not_of('0');
        if (pos != string::npos) {
            octal_number = octal_number.substr(pos);
        }
        else {
            octal_number = "0";
        }

        cout << "result: " << octal_number << "010" << endl;
    }///тест
    //тест
    void arr() {
        int massiv[4]{ 1, 2, 3, 4 };
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


        int* local = &massiv[0];
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
    //тест
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
        HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE);
        int task_number;

        while (true) {
            comment_output();
            cout << endl;
            cout << "(if you want to exit the program, enter 'exit') \n";
            cout << "enter task_number: ";

            if (!(cin >> task_number)) {
                cin.clear();
                string input;
                cin >> input;
                if (input == "exit") {
                    break;
                }
                cout << "error \n" << endl;
                continue;
            }

            switch (task_number) {
            case 1:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "first task - 'File task' \n";
                SetConsoleTextAttribute(back_color, 0x07);
                file_task();
                break;
            case 2:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "second task - 'Problem Number sign' \n";
                SetConsoleTextAttribute(back_color, 0x07);
                number_sign();
                break;
            case 3:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "third task - 'Geometric figures' \n";
                SetConsoleTextAttribute(back_color, 0x07);
                geometric_figures();
                break;
            case 4:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "fourth task - 'Past Glory\n' \n";
                SetConsoleTextAttribute(back_color, 0x07);
                past_glory();
                break;
            case 5:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "fifth task - 'Sine wave' \n";
                SetConsoleTextAttribute(back_color, 0x07);
                //  
                break;
            case 6:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "sixth task - 'Automatic recognizer' \n";
                SetConsoleTextAttribute(back_color, 0x07);
                automatic_recognizer();
                break;
            case 7:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "seventh task - 'Pseudo-random number generator' \n";
                SetConsoleTextAttribute(back_color, 0x07);
                random_number_generator();
                break;
            case 8:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "eighth task - 'Matrix multiplication' \n";
                SetConsoleTextAttribute(back_color, 0x07);
                static_dimensional_arrays();
                break;
            case 9:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "ninth task - 'Number systems' \n";
                SetConsoleTextAttribute(back_color, 0x07);
                convert_base();
                break;
            default:
                cout << "\nerror! \n";
                break;
            }
        }
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
        cout << endl << endl;
    } //обьявление функции

    void comment_output() {
        HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE);
        //SetConsoleTextAttribute(back_color, 0xf1); - синий на белом   
        // a - зеленый
        SetConsoleTextAttribute(back_color, 0x0a);
        cout << "---------------------------------------------\n TASK NUMBER:  \n 1 task - 'File' \n 2 task - 'Number sign' \n 3 task - 'Geometric shapes' \n 4 task - 'Past glory' \n 5 task - 'Sine wave' \n 6 task - 'Automatic recognizer' \n 7 task - 'Pseudorandom number generator' \n 8 task - 'Matrix multiplication' \n 9 task - 'Number systems' " << endl;
        SetConsoleTextAttribute(back_color, 0x07);

    }  //обьявление функции
};

int main() {
    FunctionHolder combining_function;
    combining_function.task_launcher();

    return 0;
}

