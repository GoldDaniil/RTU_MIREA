#include<iostream>
#include<cmath>
#include<stdio.h>
#include<fstream>
#include<string>
#include<algorithm>


using namespace std;

void loan() {
    double loan_S, monthly_payment_m, date_n, procent_p, object_r;
    while (true) {
        cout << "enter procent_p : " << endl;
        if (!(cin >> procent_p)) {
            cin.clear();
            cin.ignore();
            cout << "Error, you entered a non-numeric value!" << endl;
            continue;
        }
        break;
    }

    object_r = procent_p / 100;
    cout << "object_r : " << object_r << endl;

    while (true) {
        cout << "enter loan_S in rubles : " << endl;
        if (!(cin >> loan_S)) {
            cin.clear();
            cin.ignore();
            cout << "Error, you entered a non-numeric value!" << endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "enter date_n : " << endl;
        if (!(cin >> date_n)) {
            cin.clear();
            cin.ignore();
            cout << "Error, you entered a non-numeric value!" << endl;
            continue;
        }
        break;
    }

    if ((12 * (pow((1 + object_r), object_r) - 1)) != 0 and (loan_S > 0 and object_r > 0 and date_n > 0)) {
        monthly_payment_m = (loan_S * object_r * pow((1 + object_r), date_n)) / (12 * (pow((1 + object_r), date_n) - 1));
        cout << "monthly_payment_m : " << monthly_payment_m << " in rubles for " << date_n << " months" << endl << endl;
    }
    else {
        cout << "function m cannot be calculated" << endl << endl;
    }
}

int advance() {
    double S = 100000; // Сумма кредита
    int n = 10; // Количество лет
    double m = 10000; // Месячная выплата

    // Проверка входных данных
    switch (S <= 0 || n <= 0 || m <= 0) {
    case true:
        cout << "error 0." << endl;
        return 0;
    }

    // Перебор процентов
    for (double p = 0; p <= 100; p += 0.01) {
        // Расчет ежемесячного платежа по формуле
        double monthlyPayment = S * (1 + p / 100) * pow(1 + p / 12, -12 * n) / (12 * (1 + p / 100) * pow(1 + p / 12, -12 * n) - 1);

        // Сравнение рассчитанного платежа с заданным
        int percent = static_cast<int>(p);
        if (monthlyPayment == m) {
            // Нашли подходящий процент
            cout << "Procent: " << percent << endl;
            return 1;
        }
    }

    // Если процент не найден
    return 0;
}

void working_w_files() {
    string line, line_two, out_two;

    ofstream out_file("text.txt");
    out_file << "asdkasodkaoskdpaskdoakspdkasodkpaosdkaposdkapsodkaopskd";

    out_file.close();

    ifstream myText("text.txt");
    while (getline(myText, line)) {
        cout << line << endl;
    }
    myText.close();

    ofstream out("text.txt");
    out << "34a43a34atf3gfd";
    out.close();

    ifstream myText_two("text.txt");

    while (getline(myText_two, line_two)) {
        for (char one_character : line_two) {
            if (one_character >= '0' && one_character <= '9') {
                cout << one_character;
            }
        }
    }
    myText_two.close();

    cout << endl << endl;
}

void letter_sorting() {
    char str[] = "osdgkdsofkorkokspadkpadsdasda";

    char arr[30];
    copy(str, str + strlen(str), arr);

    sort(arr, arr + 30);

    string line(arr);

    cout << line << endl;
}

int main() {
    loan(); // задача заем
    advance(); //задача ссуда
    working_w_files(); // задача копирование файла и фильтр
    letter_sorting(); // задача сортировка букв
    return 0;
}
