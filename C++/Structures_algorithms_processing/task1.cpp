#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset>
#include <fstream>
#include <chrono>

using namespace std;

HANDLE back_col = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(back_col, 0x0a); green
//SetConsoleTextAttribute(back_col, 0x07); default
//SetConsoleTextAttribute(back_col, 0x0C); red


// 1 первая задача
void one_first_task() {
    unsigned char x = 255; // 11111111
    unsigned char maska = 1; // 00000001

    // установка 5ого бита (4-я позиция) в 0
    x = x & (~(maska << 4)); // 11111111 & 11101111 = 11101111 (239)

    cout << "result: " << static_cast<int>(x) << " (bit representation: " << bitset<8>(x) << ")" << endl;

}

// 2 вторая задача
void one_second_task() {
    unsigned char x = 175; // 10101111
    unsigned char maska = 1; // 00000001

    // установка 7ого бита (6-я позиция) в 1
    x = x | (maska << 6); // 10101111 | 01000000 = 11101111 (239)

    cout << "result: " << static_cast<int>(x) << " (bit representation: " << bitset<8>(x) << ")" << endl;
    return;
}

// 3 третья задача
void one_third_task() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned int x = 25; // Число 25 в двоичном виде: 00000000000000000000000000011001
    const int n = sizeof(int) * 8; // 32 бита для типа int
    unsigned int maska = (1 << (n - 1)); // 1 в старшем бите 32-разрядного числа

    cout << "initial view of the mask: " << bitset<n>(maska) << endl; // Выводим маску: 10000000000000000000000000000000

    cout << "result: ";
    for (int i = 1; i <= n; i++) {
        cout << ((x & maska) >> (n - i)); // Проверяем каждый бит x, начиная с самого старшего
        maska = maska >> 1; // Сдвигаем маску вправо на 1 бит
    }

    cout << endl;
    return;
}


// 2 первая задача
void two_first_task() {
    unsigned char array_bit = 0; 
    int number_digits, number;

    cout << "enter the number of numbers (no more than 8): ";

    while (!(cin >> number_digits) || number_digits > 8 || number_digits < 1) {
        SetConsoleTextAttribute(back_col, 0x0C);
        cout << "error!!! enter a valid number (1 to 8): ";
        SetConsoleTextAttribute(back_col, 0x07);
        cin.clear();
        cin.ignore();
    }

    cout << "enter a number from 0 to 7: ";
    for (int i = 0; i < number_digits; i++) {
        while (!(cin >> number) || number < 0 || number > 7) {
            SetConsoleTextAttribute(back_col, 0x0C);
            cout << "error!!! the numbers must be in the range from 0 to 7: ";
            SetConsoleTextAttribute(back_col, 0x07);
            cin.clear();
            cin.ignore();
        }
        array_bit |= (1 << number); // установка соответствующего бита
    }

    cout << "\nsorted numbers: ";
    for (int i = 0; i < 8; i++) {
        if (array_bit & (1 << i)) { // проверка каждого бита
            cout << i << " ";
        }
    }
    cout << endl << endl;
}

// 2 вторая задача
void two_second_task() {
    unsigned long long array_bit = 0;
    int number_digits, number;

    cout << "enter the number of numbers (no more than 64): ";
    cin >> number_digits;

    if (number_digits > 64) {
        cout << "error!!! the number of numbers must not exceed 64!" << endl;

        return;
    }

    cout << "enter a number from 0 to 63: ";
    for (int i = 0; i < number_digits; i++) {
        cin >> number;
        if (number < 0 || number > 63) {
            cout << "error!!! the numbers must be in the range from 0 to 63!" << endl;
            return;
        }
        array_bit |= (1ULL << number); // установка соответствующего бита
    }

    cout << "\nsorted numbers: ";
    for (int i = 0; i < 64; i++) {
        if (array_bit & (1ULL << i)) { // проверка каждого бита
            cout << i << " ";
        }
    }
    cout << endl << endl;

    return;
}

// 2 третья задача
void two_third_task() {
    const int number_bytes = 8; // 64 числа по 8 бит на байт
    unsigned char array_bit[number_bytes] = { 0 }; 
    int number_digits, number;

    cout << "enter the number of numbers (no more than 64): ";
    cin >> number_digits;

    if (number_digits > 64) {
        cout << "error!!! the number of numbers must not exceed 64" << endl;
        return;
    }

    // установка соответствующих битов
    cout << "enter a number from 0 to 63: ";
    for (int i = 0; i < number_digits; i++) {
        cin >> number;
        if (number < 0 || number > 63) {
            cout << "error!!! the numbers must be in the range from 0 to 63!" << endl;
            return;
        }
        array_bit[number / 8] |= (1 << (number % 8)); // установка соответсутющего бита
    }

    // выводим индексы единичных битов
    cout << "\nsorted numbers: ";

    for (int i = 0; i < 64; i++) {
        if (array_bit[i / 8] & (1 << (i % 8))) { // проходимся по каждому биту
            cout << i << " ";   
        }
    }
    cout << endl;

}


void three_task() {
    const int MAX_NUMBERS = 8388608; 

    const int BIT_ARRAY_SIZE = MAX_NUMBERS / 8; // 8 388 608 / 8 = 1 048 576 байт - 1мб

    bitset<MAX_NUMBERS> bit_array; // битовый массив с 1 битом на каждое число

    ifstream input_file("input.txt"); 

    ofstream output_file("output.txt");

    if (!input_file.is_open()) {
        cerr << "error open input.txt!" << endl; 
        return;
    }

    int number; // текущие число

    auto start = chrono::high_resolution_clock::now(); 

    // чтение из входа
    while (input_file >> number) { 
        if (number >= 0 && number < MAX_NUMBERS) {
            bit_array.set(number); // установка бита у данного числа в 1 
        }
    }
    input_file.close(); 

    // проходка по битмасс
    for (int i = 0; i < MAX_NUMBERS; i++) {
        if (bit_array[i]) { // если 1 - число было в input data
            output_file << i << endl; 
        }
    }
    output_file.close();

    auto end = chrono::high_resolution_clock::now(); 

    chrono::duration<double> duration = end - start; 

    cout << "time: " << duration.count() << " sec" << endl;

    return; 
}


// лаунчер
int main() {
    int user_choice;

    while (true) {
        SetConsoleTextAttribute(back_col, 0x0a);
        cout << "select task:" << endl;
        cout << "1 - " << endl;
        cout << "2 - " << endl;
        cout << "3 - " << endl;
        cout << "4 - sorting up to 8 numbers" << endl;
        cout << "5 - sorting up to 64 numbers (unsigned long long)" << endl;
        cout << "6 - sorting up to 64 numbers (unsigned char array)" << endl;
        cout << "7 - last task\n";
        cout << "8 - exit;(" << endl;
        cout << "enter u choice: ";
        SetConsoleTextAttribute(back_col, 0x07);
        cin >> user_choice;

        switch (user_choice) {
        case 1:
            one_first_task();
            break;
        case 2:
            one_second_task();
            break;
        case 3:
            one_third_task();
            break;
        case 4:
            two_first_task();
            break;
        case 5:
            two_second_task();
            break;
        case 6:
            two_third_task();
            break;
        case 7:
            three_task();
            break;
        case 8:
            cout << "oh...okay:(" << endl;
            return 0;
        default:
            cout << "error!" << endl;
        }
    }

    return 0;
}
