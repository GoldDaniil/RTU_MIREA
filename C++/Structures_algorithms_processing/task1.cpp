#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset>

using namespace std;

HANDLE back_col = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(back_col, 0x0a);
//SetConsoleTextAttribute(back_col, 0x07);



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
    system("pause");
    return;
}



// 2 первая задача
void two_first_task() {
    unsigned char array_bit = 0; // битовый массив для хранения чисел (0-7)
    int number_digits, number;

    cout << "enter the number of numbers (no more than 8): ";

    while (!(cin >> number_digits) || number_digits > 8 || number_digits < 1) {
        cout << "error!!! enter a valid number (1 to 8): ";
        cin.clear();
        cin.ignore(); // очищаем буфер
    }

    cout << "enter a number from 0 to 7: ";
    for (int i = 0; i < number_digits; i++) {
        while (!(cin >> number) || number < 0 || number > 7) {
            cout << "error!!! the numbers must be in the range from 0 to 7: ";
            cin.clear();
            cin.ignore(); // очищаем буфер
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
    unsigned long long array_bit = 0; // битовый массив для хранения чисел (0-63)
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
    unsigned char array_bit[number_bytes] = { 0 }; // массив для хранения 64 чисел
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
        cout << "10 - exit;(" << endl;
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
        case 10:
            cout << "oh...okay:(" << endl;
            return 0;
        default:
            cout << "error!" << endl;
        }
    }

    return 0;
}
