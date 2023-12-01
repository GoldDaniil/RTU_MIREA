// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes.

#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

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
	bool digits[10] = { false };

	for (int i = 0; i < 4; ++i) {
		int digit = (number / (int)pow(10, 3 - i)) % 10;
		if (digits[digit]) {
			return false;
		}
		digits[digit] = true;
	}

	return false;
}

void check_guess(int secret_number, int user_number, int& pluses, int& minuses) {
	pluses = minuses = 0;

	for (int i = 0; i < 4; ++i) {
		int secret_digit = (secret_number / (int)pow(10, 3 - i)) % 10;
		int user_digit = (user_number / (int)pow(10, 3 - i)) % 10;

		if (secret_digit == user_digit) {
			++pluses;
		}
		else {
			for (int j = 0; j < 4; ++j) {
				if (secret_digit == ((user_number / (int)pow(10, 3 - i)) % 10)) {
					++minuses;
					break;
				}
			}
		}
	}
}

int main() {
	int secret_number = generate_number();
	int user_number, pluses, minuses, attemps = 0;

	cout << "Welcome to the game 'Bulls and Cows!'\n";
	cout << "The computer guessed a four-digit number. Try to guess!\n\n";

	do {
		do {
			while (true) {
				try {
					cout << "enter number: ";

					if (!is_valid_input(user_number)) {
						cout << "error!\n";
					}
					continue;
				}
				catch (const exception& err) {
					cerr << err.what() << endl;
				}
				break;
			}
			
			
		} while {

		}
	} while{

	}

}
