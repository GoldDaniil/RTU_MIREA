#include<iostream>
#include<cmath>
#include<stdio.h>
#include<fstream>
#include<string>


using namespace std;

int main() {
    int i;
    ///////////////////////////////////////////
    ///Task "Loan"///
    double loan_S, monthly_payment_m, date_n, procent_p, object_r;
    ///Task "lending"///
    double loan_S2, monthly_payment_m2, date_n2, procent_p2, object_r2;
    ///Task "Copying a file"///
    string line;
    ///Task "Filter"///
    string line_two, out_two;
    ///Task "Sorting letters"///



    ///////////////////////////////////////////
    ///Task "Loan"///
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

    if ((12*(pow((1 + object_r), object_r) - 1)) != 0 and (loan_S > 0 and object_r > 0 and date_n > 0)){
        monthly_payment_m = (loan_S * object_r * pow((1 + object_r), date_n)) / (12*(pow((1 + object_r), date_n) - 1));
        cout << "monthly_payment_m : " << monthly_payment_m << " in rubles for " << date_n << " months" << endl << endl;
    } else {
        cout << "function m cannot be calculated" << endl << endl;
    }

    ///////////////////////////////////////////
    ///Task "lending"///double loan_S известно пол вводит, monthly_payment_m известно пол вводит, date_n известно пол вводит, procent_p не известно, object_r не известно;
    while (true) {
        cout << "loan_S : " << endl;
        if (!(cin >> loan_S2)) {
            cin.clear();
            cin.ignore();
            continue;  ///проверка на тип переменной - который вводит пользователь
        }
        break;
    }
    while (true) {
        cout << "monthly_payment_m : " << endl;
        if (!(cin >> monthly_payment_m2)) {
            cin.clear();
            cin.ignore();
            continue;
        }
        break;
    }
    while (true) {
        cout << "date_n : " << endl;
        if (!(cin >> date_n2)) {
            cin.clear();
            cin.ignore();
            continue;
        }
        break;
    }

    object_r2 = (loan_S2 - monthly_payment_m2 * (date_n2 - 1)) / (loan_S2 * date_n2) * 100;
//    for (procent_p == i; ; i ++) {
//  перебирать варианты p затем m
//    }

    procent_p = object_r2 * 100; ///формула дана

    cout << "object_r2 : " << object_r2 << endl;
    cout << "procent_p : " << procent_p << " %" << endl << endl;

    ///////////////////////////////////////////
    ///"Copying a file"///
    ofstream out_file("text.txt");
    out_file << "asdkasodkaoskdpaskdoakspdkasodkpaosdkaposdkapsodkaopskd";

    out_file.close();

    ifstream myText("text.txt");
    while (getline(myText, line)) {
        cout << line << endl;
    }
    myText.close();

    ///////////////////////////////////////////
    ///Task "Filter"///
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



    ///////////////////////////////////////////
    ///Task "Sorting letters"///

    string str_one = "dasdgASDIGASODjefEkzrfAFSVZX";

    sort(str_one.begin(), str_one.end(), [](char letter_one, char letter_two) {
        return tolower(letter_one) < tolower(letter_two);
    });
    cout << str_one << endl << endl;

    ////другой вариант

    string str_two = "dasdgASDIXPICrfAFSADJIXZdSVZX";

    sort(str_two.begin(), str_two.end(), [](char letter_tree, char letter_four) {
        if ((letter_tree >= 'A') && (letter_tree <= 'Z')) {
            letter_tree += 'a' - 'A';
        }
        if ((letter_four >= 'A') && (letter_four <= 'Z')) {
            letter_four += 'a' - 'A';
        }
        return letter_tree < letter_four;
    });
    cout << str_two << endl << endl;
    ///////////////////////////////////////////



    return 0;
}

