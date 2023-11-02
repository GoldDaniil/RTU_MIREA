#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <iomanip>

using namespace std;

void CommentOutput();
void Launcher();

void Loan() { // правильно
    double loan_S, monthly_payment_m, date_n, procent_p, object_r;
    while (true) {
        cout << "enter procent_p : " << endl;
        if (!(cin >> procent_p)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
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

    if ((12 * (pow((1 + object_r), object_r) - 1)) != 0 && (loan_S > 0 && object_r > 0 && date_n > 0)) {
        monthly_payment_m = (loan_S * object_r * pow((1 + object_r), date_n)) / (12 * (pow((1 + object_r), date_n) - 1));
        cout << "monthly_payment_m : " << monthly_payment_m << " in rubles for " << date_n << " months" << endl << endl;
    }
    else {
        cout << "function m cannot be calculated" << endl << endl;
    }
}

int Advance() {
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
    return 0; // Added return statement
}

void WorkingWFiles() { //правильно
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

void LetterSorting() { //правильно
    SetConsoleCP(65001); // Changed from 1251 to 65001
    SetConsoleOutputCP(65001); // Changed from 1251 to 65001
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
    Launcher();
    return 0;
}

void Launcher() { // Fixed function name
    HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE);
    int task_number;

    while (true) {
        CommentOutput();
        cout << endl;
        cout << "(if you want to exit the program, enter 'exit') \n";
        cout << "enter task_number: ";

        if (!(cin >> task_number)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n'); // Changed from cin.ignore() to cin.ignore(INT_MAX, '\n')
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
            cout << "first task - 'Loan' \n";
            SetConsoleTextAttribute(back_color, 0x07);
            Loan();
            break;
        case 2:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "second task - 'Advance' \n";
            Advance(); // Function name corrected
            break;
        case 3:
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "third task - 'Copying a file' \n";
            SetConsoleTextAttribute(back_color, 0x07);
            WorkingWFiles();
            break;
        case 4: // Changed from 5 to 4
            cout << "\n";
            SetConsoleTextAttribute(back_color, 0x0a);
            cout << "fourth task - 'Filter' \n' \n";
            SetConsoleTextAttribute(back_color, 0x07);
            LetterSorting();
            break;
        default:
            cout << "\nerror! \n";
            break;
        }
    }
}

void CommentOutput() {
    HANDLE back_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(back_color, 0x0a);
    cout << "-----------------------------------------------\n TASK NUMBER:  \n 1 task - 'Loan' \n 2 task - 'Advance' \n 3 task - 'WorkingWFiles' \n 4 task - 'LetterSorting'" << endl;
    SetConsoleTextAttribute(back_color, 0x07);
}
