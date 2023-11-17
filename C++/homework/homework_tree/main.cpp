// Homework 3 blocks of Procedural programmin.
// The code uses the snake_case naming style!

#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include<sstream>


#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

void comment_output() {
    HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(back_color, 0x0a);
    cout << "-----------------------------------------------\n TASK NUMBER:  \n 1 task - 'Loan' \n 2 task - 'Advance' \n 3 task - 'WorkingWFiles' \n 4 task - 'LetterSorting'" << endl;
    SetConsoleTextAttribute(back_color, 0x07);
}

class BinarySearch {
public:
    double calculateMonthlyPayment(double loan_S, double object_r, int date_n) {
        return (loan_S * object_r * pow((1 + object_r), date_n)) / (12 * (pow((1 + object_r), date_n) - 1));
    }

    double findInterestRate(double loan_S, double monthly_payment_mf, int date_n) {
        double left = 0.0; // левая граница интервала
        double right = 1.0; // правая граница интервала

        while (right - left > 0.000000001) {
            double mid = (left + right) / 2; //  определения середины текущего интервала поиска
            double monthly_payment_calculated = calculateMonthlyPayment(loan_S, mid, date_n);

            if (monthly_payment_calculated > monthly_payment_mf) {
                right = mid;
            }
            else {
                left = mid;
            }
        }
        return left * 100;
    }

    void calculateAndPrintInterestRate() {
        double loan_S, monthly_payment_mf;
        int date_n;

        while (true) {
            cout << "enter the loan amount (S): ";
            if (!(cin >> loan_S)) {
                cin.clear();
                cin.ignore();
                cout << "error\n";
                continue;
            }
            break;
        }

        while (true) {
            cout << "enter the monthly payment (m): ";
            if (!(cin >> monthly_payment_mf)) {
                cin.clear();
                cin.ignore();
                cout << "error\n";
                continue;
            }
            break;
        }

        while (true) {
            cout << "Enter the loan term in years (n): ";
            if (!(cin >> date_n)) {
                cin.clear();
                cin.ignore();
                cout << "error\n";
                continue;
            }
            break;
        }

        double interest_rate = findInterestRate(loan_S, monthly_payment_mf, date_n);
        cout << "interest rate on the loan: " << interest_rate << "%" << endl;
    }
};

void loan() { // правильно
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
            cin.ignore(INT_MAX, '\n');
            cout << "Error, you entered a non-numeric value!" << endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "enter date_n : " << endl;
        if (!(cin >> date_n)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
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
//предыдущий вариант 2 задания
int advance() {
    double monthly_payment_mf, procent_p, t, object_r, monthly_payment_m, loan_S, date_n;;
    bool f1 = false;
    while (!f1) {
        cout << "enter S:\n";
        if (!(cin >> loan_S)) {
            cin.clear();
            cin.ignore();
            cout << "error\n";
        }
        cout << "enter m:\n";
        if (!(cin >> monthly_payment_m)) {
            cin.clear();
            cin.ignore();
            cout << "error\n";
        }
        cout << "enter n:\n";
        if (!(cin >> date_n)) {
            cin.clear();
            cin.ignore();
            cout << "error\n";
        }
        else if (loan_S < 0 || monthly_payment_m < 0 || date_n < 0) {
            cout << "error\n";
        }
        else {
            f1 = true;
        }
    } //динамический шаг
    //бинарный поиск - сравнение по колвам шагам
    //подобрать начальный шаг

    for (procent_p = 0; procent_p <= 300; procent_p += 0.01) {

        object_r = procent_p / 100;
        monthly_payment_mf = (loan_S * object_r * pow((1 + object_r), date_n)) / (12 * (pow((1 + object_r), date_n) - 1));

        if (abs(monthly_payment_m - monthly_payment_mf) < 1) {
            break;
        }
    }

    cout << "\n" << procent_p << "%" << endl;
    return 0;
}
//предыдущий вариант 2 задания
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
            if (one_character >= '0' and one_character <= '9') {
                cout << one_character;
            }
        }
    }
    myText_two.close();

    cout << endl << endl;
}

void letter_sorting() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    string lum;
    cin >> lum;

    sort(lum.begin(), lum.end(), [](char a, char b) {
        if (islower(a) and isupper(b)) {
            return false;
        }
        else if (isupper(a) and islower(b)) {
            return true;
        }
        else {
            return a < b;
        }
        });

    cout << lum << endl;
}

void launcher() {
    HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE);
    char task_number_char;
    int task_number_int;

    while (true) {
        comment_output();
        cout << endl;

        while (true) {
            string task_number_str;

            cout << "(if you want to exit the program, enter 'exit') \n";
            cout << "enter task_number: ";
            cin >> task_number_str;

            if (task_number_str == "exit") {
                cout << "program completed!\n";
                return;
            }

            bool has_non_digit = false;
            for (char type : task_number_str) {
                if (!isdigit(type)) {
                    has_non_digit = true;
                    break;
                }
            }

            if (has_non_digit) {
                cerr << "error, enter only numbers!\n";
                cin.clear();
                cin.ignore();
            }
            else {
                stringstream(task_number_str) >> task_number_int;
                // cout << "u enter : " << task_number_int  << endl;
                break;
            }
        }

        switch (task_number_int) {
        case 1:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "first task - 'Loan' \n";
            SetConsoleTextAttribute(back_color, 0x07);
            loan();
            break;
        case 2:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "second task - 'Advance' \n";
            SetConsoleTextAttribute(back_color, 0x07);
            BinarySearch loan_task;
            loan_task.calculateAndPrintInterestRate();
            //advance();
            break;
        case 3:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "third task - 'Copying a file' \n";
            SetConsoleTextAttribute(back_color, 0x07);
            working_w_files();
            break;
        case 4:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "fourth task - 'Filter' \n' \n";
            SetConsoleTextAttribute(back_color, 0x07);
            letter_sorting();
            break;
        default:
            cout << "\nerror! \n";
            break;
        }
    }
}

int main() {
    launcher();
    return 0;
}
