#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

int generate_number() {
    srand(time(0));
    int number;
    bool digits[10] = { false };

    do {
        number = rand() % 9000 + 1000;
    } while (digits[number % 10] || digits[(number / 10) % 10] || digits[(number / 100) % 10] || digits[number / 1000]);

    return number;
}

bool is_valid_input(int number) {
    if (number < 1000 || number > 9999) {
        return false; // не четырехзначное число
    }

    return true;
}

void check_guess(int secret_number, int user_number, int& pluses, int& minuses) {
    pluses = minuses = 0;

    for (int i = 0; i < 4; ++i) {
        int secret_digit = (secret_number / static_cast<int>(pow(10, 3 - i))) % 10;
        int user_digit = (user_number / static_cast<int>(pow(10, 3 - i))) % 10;

        if (secret_digit == user_digit) {
            ++pluses;
        }
        else {
            for (int j = 0; j < 4; ++j) {
                int temp_secret_digit = (secret_number / static_cast<int>(pow(10, 3 - j))) % 10;
                if (temp_secret_digit == user_digit && i != j) {
                    ++minuses;
                    break;
                }
            }
        }
    }
}

void setColor(int color) {
    SetConsoleTextAttribute(console, color);
}

int main() {
    int secret_number = generate_number();
    int user_number, pluses, minuses, attempts = 0;

    //setColor(14);
    const WORD textColor = 0xE; 
    const WORD bgColor = 0x70;   

    SetConsoleTextAttribute(console, textColor | (bgColor << 4));
    
    cout << "Welcome to the game 'Bulls and Cows!'\n\n";
    cout << "The computer guessed a four-digit number. Try to guess!\n\n";
    SetConsoleTextAttribute(console, 15);
    setColor(15);

    do {
        do {
            setColor(11);
            cout << "enter number: ";
            setColor(15);
            cin >> user_number;

            if (!is_valid_input(user_number)) {
                setColor(12);
                cout << "\nerror!\n";
                setColor(15);
            }
        } while (!is_valid_input(user_number));

        check_guess(secret_number, user_number, pluses, minuses);

        setColor(13);
        cout << "\nresult: " << pluses << " pluses and " << minuses << " minuses! \n";
        setColor(15);

        ++attempts;
    } while (pluses < 4);

    setColor(10);
    cout << "\ncongratulations! U guessed the number " << secret_number << " in " << attempts << " attempts!\n";
    setColor(15);

    return 0;
}
