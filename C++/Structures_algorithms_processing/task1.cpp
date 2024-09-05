
#include <iostream>
#include <bitset>
#include <Windows.h>

using namespace std;

HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(back_color, 0x0a);
//SetConsoleTextAttribute(back_color, 0x07);

    void one_a() {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        unsigned int x = 25; // Число 25 в двоичном виде: 00000000000000000000000000011001
        const int n = sizeof(int) * 8; // 32 - количество разрядов в числе типа unsigned int
        unsigned int maska = (1 << (n - 1)); // 1 в старшем бите 32-разрядной сетки: 10000000000000000000000000000000

        cout << "Начальный вид маски: " << bitset<n>(maska) << endl;
        cout << "Результат: ";

        for (int i = 1; i <= n; i++) {
            cout << ((x & maska) >> (n - i));
            maska = maska >> 1; // Смещение 1 в маске на разряд вправо
        }

        cout << endl;
        system("pause");
    }
    void one_b() {
        unsigned char x = 255; // 8-разрядное двоичное число 11111111
        unsigned char maska = 1; // 1 = 00000001

        // Установка 5-го бита в 0
        x = x & (~(maska << 4)); // 4, потому что нумерация начинается с 0

        cout << "результат: " << static_cast<int>(x) << endl; // Ожидаем 239
        cout << "бинарное представление: " << bitset<8>(x) << endl;

    }
    void one_c() {
        unsigned char x = 127; // 8-разрядное двоичное число 01111111
        unsigned char maska = 1; // 1 = 00000001

        // Установка 7-го бита в 1
        x = x | (maska << 6); // 6, потому что нумерация начинается с 0

        cout << "результат: " << static_cast<int>(x) << endl; // Ожидаем 191
        cout << "Бинарное представление: " << bitset<8>(x) << endl;
    }

int main() {
    int choice;
    while (true) {
        
        cin >> choice;
        switch (choice) {
            case 1: 
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "Реализуйте вышеприведённый пример, проверьте правильность результата в том числе и на других значениях х" << endl;
                one_a();
                SetConsoleTextAttribute(back_color, 0x07);
                break;
            case 2:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "Реализуйте вышеприведённый пример, проверьте правильность результата в том числе и на других значениях х" << endl;
                one_b();
                SetConsoleTextAttribute(back_color, 0x07);
                break;
            case 3:
                cout << "\n";
                SetConsoleTextAttribute(back_color, 0x0a);
                cout << "Реализуйте вышеприведённый пример, проверьте правильность результата в том числе и на других значениях х" << endl;
                one_c();
                SetConsoleTextAttribute(back_color, 0x07);
                break;
            default:
                cout << "error!";
                break;
        }

    }

    return 0;
}
