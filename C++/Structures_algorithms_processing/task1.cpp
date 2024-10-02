#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <ctime>
#include <set>

#include <cstdint>

using namespace std;

HANDLE back_col = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(back_col, 0x0a); green
//SetConsoleTextAttribute(back_col, 0x07); default
//SetConsoleTextAttribute(back_col, 0x0C); red

const int MAX_NUM = 100000;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// 1 первая задача
void one_first_task() {
    unsigned char x = 255; // 11111111
    unsigned char maska = 1; // 00000001

    x = x & (~(maska << 4)); // 11111111 & 11101111 = 11101111 (239)

    cout << "result: " << static_cast<int>(x) << " (bit representation: " << bitset<8>(x) << ")" << endl;

}

// 2 вторая задача
void one_second_task() {
    unsigned char x = 175; // 10101111
    unsigned char maska = 1; // 00000001

    x = x | (maska << 6); // 10101111 | 01000000 = 11101111 (239)

    cout << "result: " << static_cast<int>(x) << " (bit representation: " << bitset<8>(x) << ")" << endl;
    return;
}

// 3 третья задача
void one_third_task() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned int x = 25; // 00000000000000000000000000011001
    const int n = sizeof(int) * 8; // 32 бита для типа int
    unsigned int maska = (1 << (n - 1)); // 32 - 1 = 31 

    cout << "initial view of the mask: " << bitset<n>(maska) << endl; // Выводим маску: 10000000000000000000000000000000

    cout << "result: ";
    for (int i = 1; i <= n; i++) {
        cout << ((x & maska) >> (n - i)); // Проверяем каждый бит x, начиная с самого старшего
        maska = maska >> 1; // Сдвигаем маску вправо на 1 бит
    }

    cout << endl;
    return;
}


// 4 задача
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

// 5 задача
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

// 6 задача
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


//three task last

void fill_input_file_with_unique_numbers(const string& filename, int n) {
    ofstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "error: " << filename << endl;
        return;
    }

    set<int> unique_numbers; // множество для хранения уникальных чисел
    random_device rd; // генератор случайных чисел
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000000, 9999999); // диапазон чисел от 1_000_000 до 9_999_999

    while (unique_numbers.size() < n) {
        int num = dis(gen);
        unique_numbers.insert(num);
    }

    for (int num : unique_numbers) {
        inputFile << num << endl;
    }

    inputFile.close();
    cout << "enter file '" << filename << "' successfully filled with " << n << " unique numbers." << endl;
}

void three_task() {
    int number_of_unique_numbers = 10000000;
    fill_input_file_with_unique_numbers(INPUT_FILE, number_of_unique_numbers); // заполняем входной файл

    clock_t t0 = clock();

    // размер битового массива: делим на 8, чтобы вместить биты в char
    vector<char> ArrayBit(MAX_NUM / 8, 0); // инициализация значениями 0

    ifstream inputFile(INPUT_FILE);
    if (!inputFile.is_open()) {
        cerr << "error open file" << INPUT_FILE << endl;
        return;
    }

    int number;
    while (inputFile >> number) {
        if (number >= 0 && number < MAX_NUM) {
            // устанавливаем соответствующий бит в 1
            ArrayBit[number / 8] |= (1 << (number % 8)); // находим правильный байт и устанавливаем бит
        }
    }
    inputFile.close();

    ofstream outputFile(OUTPUT_FILE);
    if (!outputFile.is_open()) {
        cerr << "error open file" << OUTPUT_FILE << endl;
        return;
    }

    // проходим по массиву и записываем индексы установленных битов в выходной файл
    for (int i = 0; i < MAX_NUM; ++i) {
        if (ArrayBit[i / 8] & (1 << (i % 8))) { // проверяем, установлен ли бит
            outputFile << i << endl; // запись уникального числа
        }
    }
    outputFile.close();

    clock_t t1 = clock();

    cout << "numbers from the file " << INPUT_FILE << " sorted and placed in " << OUTPUT_FILE << endl;
    cout << "program execution time: " << (double)(t1 - t0) / CLOCKS_PER_SEC << " seconds" << endl;

    return;
}

// лаунчер
int main() {
    int user_choice;

    while (true) {
        SetConsoleTextAttribute(back_col, 0x0a);
        cout << "\nselect task:" << endl;
        cout << "1 - first task" << endl;
        cout << "2 - second task" << endl;
        cout << "3 - third task" << endl;
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
