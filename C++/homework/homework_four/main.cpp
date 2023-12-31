// Homework 4 blocks of Procedural programming.
// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes.

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cmath>
#include<Windows.h>
#include<time.h>
#include<thread>
#include<chrono>
#include<stdexcept>
#include<string>

using namespace std;

HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE);

void comment_output() {
    SetConsoleTextAttribute(back_color, 0x0a);
    cout << "-------------------------------------------------\n TASK NUMBER:  \n 1 task - 'File' \n 2 task - 'Number sign' \n 3 task - 'Geometric shapes' \n 4 task - 'Past glory' \n 5 task - 'Sine wave' \n 6 task - 'Automatic recognizer' \n 7 task - 'Pseudorandom number generator' \n 8 task - 'Matrix multiplication' \n 9 task - 'Number systems' " << endl;
    SetConsoleTextAttribute(back_color, 0x07);

}  //обьявление функции

// Задача «Файл».
void file_task() {  //правильно
    try {
        ofstream file("numbers.txt");

        if (file.is_open()) {   // использованы исключения с помощью try catch 
            cout << "\nif you want to stop typing, enter 'exit' \n";
            double num;
            for (int i = 0; i < 10; ++i) {
                cout << "enter " << i + 1 << " number:\n";
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

            const int size = 300;
            double total_spent_time = 0, reserch_time;
            for (int i = 0; i < size; i++) {
                clock_t start_time = clock();

                ifstream read_file("numbers.txt");
                if (read_file.is_open()) {
                    double num, sum = 0;
                    while (read_file >> num) {
                        sum += num;
                    }
                    reserch_time = sum;
                    read_file.close();
                }
                else {
                    cout << "error!" << endl;
                }

                clock_t end_time = clock();
                double spent_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
                total_spent_time += spent_time;
            }
            cout << "sum of numbers: " << reserch_time << endl;
            ///НАЙТИ МАКСИМАЛЬНО ОПТИМИЗИРОВАННЫЙ ВАРИАНТ СЧЕТА - ЭТОТ НЕ ПОДХОДИТ
            double average_time = total_spent_time / size;
            cout << "\naverage time = " << average_time << " ml\n";

        }
        else {
            cout << "error!\n";
        }

    }
    catch (const exception& err) {
        cerr << "\nan exception occurred!\n" << err.what() << endl;

        ofstream new_file("text.txt");

        if (!new_file.is_open()) {
            cerr << "failed to create new file!\n";
            return;
        }
        cerr << "new file created successfully!\n";
    }
}

// Задача «Знак числа»
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

    clock_t start_time = clock();

    if (variable_x > 0) {
        cout << 1 << endl << endl;
    }
    else if (variable_x < 0) {
        cout << -1 << endl << endl;
    }
    else if (variable_x == 0) {
        cout << 0 << endl << endl;
    }

    clock_t end_time = clock();
    double spent_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    SetConsoleTextAttribute(back_color, 0x0b); //бирюзовый
    cout << "function execution time in milliseconds: " << spent_time << " ml \n\n";
    SetConsoleTextAttribute(back_color, 0x07);

}

// Задача «Геометрические фигуры»
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

// Задача «Былая слава»
void past_glory() {
    clock_t start_time = clock();

    cout << "Past Glory 1912 " << endl;
    for (int i = 0; i < 6; i++) {
        SetConsoleTextAttribute(back_color, 0x1f);
        for (int j = 0; j < 8; j++) {
            cout << "* ";
        }
        if ((i % 2) == 0) {
            SetConsoleTextAttribute(back_color, 0x44);
        }
        else {
            SetConsoleTextAttribute(back_color, 0xff);
        }

        for (int j = 0; j < 15; j++) {
            cout << "- ";
        }
        SetConsoleTextAttribute(back_color, 0x00);

        cout << endl;
    }

    for (int i = 0; i < 6; i++) {
        if ((i % 2) == 0) {
            SetConsoleTextAttribute(back_color, 0x44);
        }
        else {
            SetConsoleTextAttribute(back_color, 0xff);
        }
        for (int j = 0; j < 23; j++) {
            cout << "- ";
        }
        SetConsoleTextAttribute(back_color, 0x00);

        cout << endl;
    }
    SetConsoleTextAttribute(back_color, 0x07);
    cout << endl << endl;

    clock_t end_time = clock();
    double spent_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    SetConsoleTextAttribute(back_color, 0x0b); //бирюзовый
    cout << "function execution time in milliseconds: " << spent_time << " ml \n\n";
    SetConsoleTextAttribute(back_color, 0x07);
}

// начало задачи синусоида
void move_сursor(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}
void clear_сonsole(int height) {
    for (int i = 1; i <= height; i++) {
        move_сursor(1, i);
        cout << string(100, ' ');
    }
}
void sine_wave() {
    const int width = 100;
    const int height = 29;
    const double amplitude = height / 2.0;
    const double frequency = 0.1;
    const int num_frames = 40;

    for (int frame = 0; frame <= num_frames; frame++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                double value = amplitude * sin(frequency * (x + frame));

                if (y == height / 2) {
                    cout << '-';
                }
                else if (x == 0 || x == width - 1) {
                    cout << '+';
                }
                else if (x % static_cast<int>(1 / frequency) == 0) {
                    cout << '|';
                }
                else {
                    if (abs(y - amplitude + value) < 0.5 || (y == height - 1 && abs(y - amplitude + value) <= 0.5)) {
                        cout << '*';
                    }
                    else {
                        cout << ' ';
                    }
                }
            }
            cout << endl;
        }

        move_сursor(1, 1);

        if (frame == num_frames) {
            clear_сonsole(height);
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << endl << endl;
}
// конец задачи синусоида

// Задача «Автоматный распознаватель»
void automatic_recognizer() {
    string roman_numeral;
    int decoded_number = 0;

    cout << "enter: ";
    cin >> roman_numeral;

    clock_t start_time = clock();

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

    clock_t end_time = clock();
    double spent_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    SetConsoleTextAttribute(back_color, 0x0b); //бирюзовый
    cout << "function execution time in milliseconds: " << spent_time << " ml \n\n";
    SetConsoleTextAttribute(back_color, 0x07);

}

// Задача «Генератор псевдослучайных чисел»
void random_number_generator() {    //правильно
    while (true) {
        int variable_n, option;

        cout << "select parameter option: (1 / 2) \n";
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore();
            cout << "error\n";
            continue;
        }

        clock_t start_time = clock();
        srand(static_cast<unsigned>(time(0))); 

        int variable_m, variable_b, variable_c;
        switch (option) {
        case 1:
            variable_m = rand() % 100 + 1;  // задание диапазона для variable_m в пределах [1, 100]
            variable_b = rand() % 10 + 1;   // задание диапазона для variable_b в пределах [1, 10]
            variable_c = rand() % 901 + 100;  // задание диапазона для variable_c в пределах [100, 1000]
            break;
        case 2:
            variable_m = rand() % 40001 + 10000;  // задание диапазона для variable_m в пределах [10000, 50000]
            variable_b = rand() % 15001 + 5000;   // задание диапазона для variable_b в пределах [5000, 20000]
            variable_c = rand() % 50001 + 50000;  // задание диапазона для variable_c в пределах [50000, 100000]
            break;
        default:
            cout << "error!\n";
            return;
        }

        while (true) {
            cout << "amount of elements: \n";
            if (!(cin >> variable_n) || variable_n <= 1) {
                cin.clear();
                cin.ignore();
                cout << "error\n";
                continue;
            }
            break;
        }

        for (int i = 0; i < variable_n; i++) {
            int variable_s = (variable_m * i + variable_b) % variable_c;
            cout << variable_s << " ";
        }

        cout << endl << endl;
        clock_t end_time = clock();
        double spent_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        SetConsoleTextAttribute(back_color, 0x0b); //бирюзовый
        cout << "function execution time in milliseconds: " << spent_time << " ml \n\n";
        SetConsoleTextAttribute(back_color, 0x07);
        break;
    }
}

// Задача «Умножение матриц»
void static_dimensional_arrays() {
    clock_t start_time = clock();

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


    double total_sales = 0;
    double total_commission = 0;
    double max_sales = multiplication_result[0][0];
    double min_sales = multiplication_result[0][0];
    double max_commission = multiplication_result[0][1];
    double min_commission = multiplication_result[0][1];

    int max_sales_seller = 0;
    int min_sales_seller = 0;
    int max_commission_seller = 0;
    int min_commission_seller = 0;

    for (int i = 0; i < seller_string; i++) {
        total_sales += multiplication_result[i][0];
        total_commission += multiplication_result[i][1];

        if (multiplication_result[i][0] > max_sales) {
            max_sales = multiplication_result[i][0];
            max_sales_seller = i;
        }
        if (multiplication_result[i][0] < min_sales) {
            min_sales = multiplication_result[i][0];
            min_sales_seller = i;
        }

        if (multiplication_result[i][1] > max_commission) {
            max_commission = multiplication_result[i][1];
            max_commission_seller = i;
        }
        if (multiplication_result[i][1] < min_commission) {
            min_commission = multiplication_result[i][1];
            min_commission_seller = i;
        }
    }
    cout << "result two-dimensional array: \ntable C: \n";
    for (int i = 0; i < seller_string; i++) {
        for (int j = 0; j < commission_column; j++) {
            cout << multiplication_result[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;

    cout << "1)seller " << max_sales_seller + 1 << " achieved the highest sales: " << max_sales << endl;
    cout << "  seller " << min_sales_seller + 1 << " achieved the lowest sales: " << min_sales << endl;
    cout << "2)seller " << max_commission_seller + 1 << " received the highest commission: " << max_commission << endl;
    cout << "  seller " << min_commission_seller + 1 << " received the lowest commission: " << min_commission << endl;
    cout << "3)total sales: " << total_sales << endl;
    cout << "4)total commission: " << total_commission << endl;
    cout << "5)total money passed through sellers hands: " << total_sales + total_commission << endl << endl;

    clock_t end_time = clock();
    double spent_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    SetConsoleTextAttribute(back_color, 0x0b); //бирюзовый
    cout << "function execution time in milliseconds: " << spent_time << " ml \n\n";
    SetConsoleTextAttribute(back_color, 0x07);

}

// Задача «Системы счисления»
namespace ConvertBase {
    int char_to_digit(char symbol) {
        if ((symbol >= '0') && (symbol <= '9')) {
            return symbol - '0';
        }
        else if ((symbol >= 'A') && (symbol <= 'Z')) {
            return symbol - 'A' + 10;
        }
        else if ((symbol >= 'a') && (symbol <= 'z')) {
            return symbol - 'a' + 10;
        }
        else {
            return -1;
        }
    }

    string convert_base(const string& number, int old_base, int new_base) {
        int decimal_number = 0;

        for (char digit_char : number) {
            int digit = char_to_digit(digit_char);
            if ((digit == -1) || (digit >= old_base)) {
                throw invalid_argument("invalid digit for the specified old_base");
            }

            decimal_number = decimal_number * old_base + digit;
        }

        string result = "";
        while (decimal_number > 0) {
            int remainder = decimal_number % new_base;

            char digit_char;
            if (remainder < 10) {
                digit_char = remainder + '0';
            }
            else {
                digit_char = remainder - 10 + 'A';
            }

            result = digit_char + result;
            decimal_number /= new_base;
        }

        if (result.empty()) {
            return "0";
        }
        else {
            return result;
        }
    }

    void cout_convert_base() {
        string number;
        int old_base = 0, new_base;

        cout << "enter number: ";
        cin >> number;

        while (true) {
            cout << "enter old foundation: ";
            if (!(cin >> old_base) || old_base <= 1 || old_base > 36) {
                cin.clear();
                cin.ignore();
                cerr << "error: invalid old foundation\n";
                continue;
            }
            break;
        }

        while (true) {
            cout << "enter new foundation: ";
            if (!(cin >> new_base) || new_base <= 1 || new_base > 36) {
                cin.clear();
                cin.ignore();
                cerr << "error: invalid new foundation\n";
                continue;
            }
            break;
        }

        try {
            for (char digit_char : number) {
                int digit = char_to_digit(digit_char);
                if ((digit == -1) || (digit >= old_base)) {
                    throw invalid_argument("invalid digit for the specified old_base");
                }
            }

            string result = convert_base(number, old_base, new_base);
            cout << "result : " << result << endl << endl;
        }
        catch (const exception& e) {
            cerr << "error: " << e.what() << endl;
        }
    }
}

// лаунчер заданий
void task_launcher() {
    int task_number;

    float y = 0, scl = 1, ampl = 100, yoff = 0;
    HWND hw = GetConsoleWindow();
    HDC dc = GetDC(hw);

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

            // Задача «Файл».
            file_task();
            break;
        case 2:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "second task - 'Problem Number sign' \n";
            SetConsoleTextAttribute(back_color, 0x07);
            
            // Задача «Знак числа»
            number_sign();
            break;
        case 3:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "third task - 'Geometric figures' \n";
            SetConsoleTextAttribute(back_color, 0x07);

            // Задача «Геометрические фигуры»
            geometric_figures();
            break;
        case 4:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "fourth task - 'Past Glory' \n";
            SetConsoleTextAttribute(back_color, 0x07);

            // Задача «Былая слава»
            past_glory();
            break;
        case 5:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "fifth task - 'Sine wave' \n";
            SetConsoleTextAttribute(back_color, 0x07);

            // Задача «Синусоида»
            sine_wave();
            
            /*
            for (float x = 0; x < 1000; x += 0.05) {
                yoff = sin(x / 54) * 50;
                y = 400 + yoff - sin(x / 3) * ampl * scl;
                SetPixel(dc, (int)x, (int)y, RGB(155 + yoff * 2, 0, 155 - yoff * 2));

            }
            return;*/
            break;
        case 6:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "sixth task - 'Automatic recognizer' \n";
            SetConsoleTextAttribute(back_color, 0x07);

            // Задача «Автоматный распознаватель»
            automatic_recognizer();
            break;
        case 7:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "seventh task - 'Pseudo-random number generator' \n";
            SetConsoleTextAttribute(back_color, 0x07);

            // Задача «Генератор псевдослучайных чисел»
            random_number_generator();
            break;
        case 8:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "eighth task - 'Matrix multiplication' \n";
            SetConsoleTextAttribute(back_color, 0x07);
            
            // Задача «Умножение матриц»
            static_dimensional_arrays();
            break;
        case 9:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "ninth task - 'Number systems' \n";
            SetConsoleTextAttribute(back_color, 0x07);

            // Задача «Системы счисления»
            ConvertBase::cout_convert_base();
            break;
        default:
            cout << "\nerror! \n";
            break;
        }
    }
}

int main() {
    task_launcher();
    return 0;
}
