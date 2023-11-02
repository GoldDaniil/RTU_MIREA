#include<iostream>
#include<cmath>
#include<stdio.h>
#include<fstream>
#include<string>
#include<algorithm>
#include<Windows.H>

using namespace std;

void loan() {   //правильно
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
    double S, m, n, p = 0, eps, monthly_payment;
    cout << "enter (S): ";
    cin >> S;
    cout << "enter (m): ";
    cin >> m;
    cout << "enter (n): ";
    cin >> n;

    if (S <= 0) {
        cout << "error!" << endl;
        return 1;
    }
    if (n <= 0) {
        cout << "error!" << endl;
        return 1;
    }

    eps = 0.00001;

    while (p <= 100) {
        double r = p / 1200; // процентная ставка в месяц
        monthly_payment = (S * r * pow(1 + r, n * 12)) / (12 * (pow(1 + r, n * 12) - 1));

        if (fabs(m - monthly_payment) < eps) {
            break;
        }
        else if (monthly_payment < m) {
            p += 0.01;
        }
        else {
            p -= 0.01;
            eps += 0.01; // увеличиваем точность
        }
    }

    if (p > 100) {
        cout << "error!" << endl;
        return 1;
    }
    else {
        cout << fixed << setprecision(4);
        cout << "procent p: " << p << "%" << endl;
    }
}

void working_w_files() { //правильно
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

void letter_sorting() { //правильно
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string lum;
    cin >> lum;
    //cout << lum;

    for (int i = 0; i < lum.length(); i++) {
        for (int j = (i + 1); j < lum.length(); j++) {
            if (tolower(lum[i]) > tolower(lum[j])) {
                char local = lum[i];
                lum[i] = lum[j];
                lum[j] = local;
            }
        }
    }
    cout << lum << endl;
}

int main() {
    loan(); // задача заем
    advance(); //задача ссуда
    working_w_files(); // задача копирование файла и фильтр 3 и 4 вместе
    letter_sorting(); // задача сортировка 
    return 0;
}
