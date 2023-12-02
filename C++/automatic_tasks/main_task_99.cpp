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

    setColor(14); // Set color to yellow
    cout << "Welcome to the game 'Bulls and Cows!'\n";
    cout << "The computer guessed a four-digit number. Try to guess!\n\n";
    setColor(15); // Set color back to white

    do {
        do {
            setColor(11); // Set color to light cyan
            cout << "Enter number: ";
            setColor(15); // Set color back to white
            cin >> user_number;

            if (!is_valid_input(user_number)) {
                setColor(12); // Set color to red
                cout << "\nError!\n";
                setColor(15); // Set color back to white
            }
        } while (!is_valid_input(user_number));

        check_guess(secret_number, user_number, pluses, minuses);

        setColor(13); // Set color to purple
        cout << "\nResult: " << pluses << " pluses and " << minuses << " minuses! \n";
        setColor(15); // Set color back to white

        ++attempts;
    } while (pluses < 4);

    setColor(10); // Set color to light green
    cout << "\nCongratulations! You guessed the number " << secret_number << " in " << attempts << " attempts!\n";
    setColor(15); // Set color back to white

    return 0;
}
