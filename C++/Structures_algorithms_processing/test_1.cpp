#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int check_variable_int(string variable) {
    int result;

    while (true) {
        try {
            result = stoi(variable);
            return result;
        }
        catch (const exception& err) {
            cout << "eerror/ required type - integer/float \n\ntry entering again: ";
            getline(cin, variable);
        }
    }
}

//int check_variable_int(const string& variable) {
//    int result;
//
//    while (true) {
//        stringstream ss(variable);
//        if (!(ss >> result) || !ss.eof()) {
//            cout << "eerror/ required type - integer/float \ntry entering again: ";
//            cin.clear(); // Очищаем флаг ошибки ввода
//            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер ввода
//            cin >> variable; // Считываем ввод заново
//        }
//        else {
//            return result;
//        }
//    }
//}

// Функция для вычисления суммы цифр числа
int sumOfDigits(int number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int main() {
    string amount_numbers_str; 
    cout << "enter the number of numbers in the sequence: ";
    getline(cin, amount_numbers_str);

    int amount_numbers = check_variable_int(amount_numbers_str);

    int count = 0; // инициализируем счетчик чисел - сумма цифр которых кратна 7

    cout << "enter a sequence of numbers:\n";
    for (int i = 0; i < amount_numbers; ++i) {
        string num_str;
        getline(cin, num_str);
        int num = check_variable_int(num_str); 
        if (sumOfDigits(num) % 7 == 0) {
            count++;
        }
    }

    cout << "the number of numbers in the sequence whose sum of digits is a multiple of 7: " << count << endl;

    return 0;
}
