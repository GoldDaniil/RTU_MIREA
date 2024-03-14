// игра Stone-Scissors-Paper-Lizard-Spock
// правила простые: ножницы режут бумагу, 
// бумага покрывает камень, камень давит ящерицу, 
// ящерица отравляет Спока, Спок ломает ножницы, 
// ножницы обезглавливают ящерицу, ящерица съедает 
// бумагу, на бумаге улики против спока, 
// Спок испаряет камень, и, как всегда, 
// камень разбивает ножницы. 

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>

using namespace std;

int main() {
    string user_choice_str;
    int user_choice;

    cout << "welcome to the game 'Stone-Scissors-Paper-Lizard-Spock'!\n";

    while (true) {
        srand(time(0));

        cout << "\nselect: 1 - Stone, 2 - Scissors, 3 - Paper, 4 - Lizard, 5 - Spock\n";

        cin >> user_choice_str;

        if (user_choice_str == "exit") {
            cout << "ohhhh, okay;(\n";
            return 1;
        }

        bool has_non_degit = false;
        for (char type_degit : user_choice_str) {
            if (!isdigit(type_degit)) {
                has_non_degit = true;
                break;
            }
        }

        if (has_non_degit) {
            cerr << "error!\n";
            cin.clear();
            cin.ignore();
        }
        else {
            stringstream(user_choice_str) >> user_choice;
        }
        
        if (user_choice < 1 || user_choice > 5) {
            cout << "wrong choice. please enter a number from 1 to 5.\n";
            return 1;
        }

        int computer_choice = rand() % 5 + 1;

        cout << "you choosed: ";
        switch (user_choice) {
        case 1:
            cout << "stone\n";
            break;
        case 2:
            cout << "scissors\n";
            break;
        case 3:
            cout << "paper\n";
            break;
        case 4:
            cout << "lizard\n";
            break;
        case 5:
            cout << "spock\n";
            break;
        default:
            cout << "wrong choice\n";
            return 1;
        }

        cout << "\nthe computer has chosen: ";
        switch (computer_choice) {
        case 1:
            cout << "stone\n";
            break;
        case 2:
            cout << "scissors\n";
            break;
        case 3:
            cout << "paper\n";
            break;
        case 4:
            cout << "lizard\n";
            break;
        case 5:
            cout << "spock\n";
            break;
        }

        if (user_choice == computer_choice) {
            cout << "draw!\n";
        }
        else if ((user_choice == 1 && (computer_choice == 2 || computer_choice == 4)) ||
            (user_choice == 2 && (computer_choice == 3 || computer_choice == 4)) ||
            (user_choice == 3 && (computer_choice == 1 || computer_choice == 5)) ||
            (user_choice == 4 && (computer_choice == 3 || computer_choice == 5)) ||
            (user_choice == 5 && (computer_choice == 1 || computer_choice == 2))) {
            cout << "you win!\n";
        }
        else {
            cout << "you lose!\n";
        }
    }

    return 0;
}

