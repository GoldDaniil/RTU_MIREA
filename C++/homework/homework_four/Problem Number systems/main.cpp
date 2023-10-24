#include <iostream>
#include <string>

using namespace std;

// Функция для конвертации числа из одной системы счисления в другую
string convert_base(const string& number, int source_base, int target_base) {
    long long decimal = 0;
    long long power = 1;


    if ((source_base <= 0) || (target_base <= 0)) {
        return "error! radix cannot be zero or negative! ";
    }

    for (int i = number.size() - 1; i >= 0; --i) {
        int digit = number[i] - '0';

        if ((number[i] >= 'A') && (number[i] <= 'Z')) {
            digit = number[i] - 'A' + 10;
        }
        if ((digit < 0) || (digit >= source_base)) {
            return "error! invalid number for this number system! ";
        }

        decimal += static_cast<long long>(digit) * power;
        power *= source_base;
    }

    string result = "";
    while (decimal > 0) {
        int digit = decimal % target_base;
        char digitChar = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        result = digitChar + result;
        decimal /= target_base;
    }

    return result;
}

int main() {

    string number;
    int source_base, target_base;

    /*while (true) {
        cout << "enter the number: " << endl;
        cout << "enter old base: " << endl;
        cout << "enter a new base: " << endl;
        if (!(cin >> number) and !(cin >> source_base) and !(cin >> target_base)) {
            cin.clear();
            cin.ignore();
            cout << "error";
            continue;
        }
        break;
    }*/

    // Проверка на тип данных херовая проверка - надо по новой
    if (cin.fail()) {
        cout << "error " << endl;
        return 1;
    }

    string result = convert_base(number, source_base, target_base);

    cout << "result: " << result << endl;

    return 0;
}
