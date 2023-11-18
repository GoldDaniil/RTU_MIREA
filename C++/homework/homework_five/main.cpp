// Homework 5 blocks of Procedural programming.
// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes.

#include<iostream>
#include<string>
#include<Windows.h>
#include<sstream>

using namespace std;
HANDLE back_col = GetStdHandle(STD_OUTPUT_HANDLE);
void comment_output() {
	SetConsoleTextAttribute(back_col, 0x0a);
	cout << "----------------------------------------------\n TASK NUMBER:  \n 1 task - 'Euclid's algorithm' \n 2 task - 'Sieve of Eratosthenes' \n 3 task - '-' \n 4 task - '-'" << endl;
	SetConsoleTextAttribute(back_col, 0x07);
}

namespace TaskOne {
	//метод деления
	class FindTheGDBDivisionByDivision {
	public:
		int GDBByDivision(int parametr_a, int parametr_b) {
			try {
				while (parametr_b != 0) {
					int temp = parametr_b;
					parametr_b = parametr_a % parametr_b;
					parametr_a = temp;
				}
				return parametr_a;
			}
			catch (const exception& err) {
				cerr << "error: " << err.what() << endl;
				return -0; //возвращаем минус 0 в случае ошибки
			}
		}

		void euclidean_algorithm_division() {
			int num_one, num_two;
			while (true) {
				cout << "enter first number: ";
				if (!(cin >> num_one)) {
					cin.clear();
					cin.ignore();
					cerr << "return 1\n";
					continue;
				}
				break;
			}
			while (true) {
				cout << "enter second number: ";
				if (!(cin >> num_two)) {
					cin.clear();
					cin.ignore();
					cerr << "return 1\n";
					continue;
				}
				break;
			}

			int gcd_return = GDBByDivision(num_one, num_two);
			if (gcd_return != -0) {
				cout << "GCD by subtraction method: " << gcd_return << endl;
			}
			else {
				cerr << "failed to calculate GCD - gcd_return \n";
			}
		}
	};
	//метод вычитания
	class FindTheGDBDivisionBySubtraction {
	public:
		int GDBBySubtraction(int parametr_a, int parametr_b) {
			try {
				while (parametr_a != parametr_b) {
					if (parametr_a > parametr_b) {
						parametr_a -= parametr_b;
					}
					else {
						parametr_b -= parametr_a;
					}
				}
				return parametr_a;
			}
			catch (const exception& err) {
				cerr << "error! " << err.what() << endl;
				return -0;
			}
		}

		void euclidean_algorithm_subtraction() {
			int num_one, num_two;
			while (true) {
				cout << "enter first number: ";
				if (!(cin >> num_one)) {
					cin.clear();
					cin.ignore();
					cerr << "return 1\n";
					continue;
				}
				break;
			}
			while (true) {
				cout << "enter second number: ";
				if (!(cin >> num_two)) {
					cin.clear();
					cin.ignore();
					cerr << "return 1\n";
					continue;
				}
				break;
			}

			int gcd_return = GDBBySubtraction(num_one, num_two);
			if (gcd_return != -0) {
				cout << "GCD by subtraction method: " << gcd_return << endl;
			}
			else {
				cerr << "failed to calculate GCD - gcd_return \n";
			}
		}
	};
}

void sieve_eratosthenes() {

}

void launcher() {
	char task_number_char;
	int task_number_int;

	while (true) {
		comment_output();
		while (true) {
			string task_number_str;

			cout << "if you want to exit the program, enter 'exit' \nenter task_number : ";
			cin >> task_number_str;

			if (task_number_str == "exit") {
				cout << "program completed!\n";
				return;
			}

			bool has_non_degit = false; //has_non_degit = 1;
			for (char type_degit : task_number_str) {
				if (!isdigit(type_degit)) {
					has_non_degit = true; //has_non_degit = 0;
					break;
				}
			}

			if (has_non_degit) {
				cerr << "error, enter only numbers!\n";
				cin.clear();
				cin.ignore();
			}
			else {
				stringstream(task_number_str) >> task_number_int;
				break;
			}
		}

		switch (task_number_int) {
		case 1:
			cout << "\n";
			SetConsoleTextAttribute(back_col, 0x0a);
			cout << "Task 'Euclidean Algorithm'. Give 2 numbers and find their most common divisor methods : division and subtraction.\n";
			SetConsoleTextAttribute(back_col, 0x07);
			cout << "division method: \n";
			TaskOne::FindTheGDBDivisionByDivision gcdCalculator_one;
			gcdCalculator_one.euclidean_algorithm_division();
			cout << "\n\nsubtraction method: \n";
			TaskOne::FindTheGDBDivisionBySubtraction gcdCalculator_two;
			gcdCalculator_two.euclidean_algorithm_subtraction();
			cout << "\n";
			break;
		case 2:
			cout << "\n";
			SetConsoleTextAttribute(back_col, 0x0a);
			cout << "'The Sieve of Eratosthenes' task. Find all prime numbers in the range from 2 to the number you enter natural number\n";
			SetConsoleTextAttribute(back_col, 0x07);
			//sieve_eratosthenes();
			cout << "\n";
			break;
		case 3:
			cout << "\n";
			SetConsoleTextAttribute(back_col, 0x0a);
			cout << "' ' task. \n";
			SetConsoleTextAttribute(back_col, 0x07);
			//sieve_eratosthenes();
			break;
		case 4:
			cout << "\n";
			SetConsoleTextAttribute(back_col, 0x0a);
			cout << "'' task.\n";
			SetConsoleTextAttribute(back_col, 0x07);
			//sieve_eratosthenes();
			break;
		default:
			cerr << "error!\n";
			break;
		}
	}
}

int main() {
	launcher();
	return 0;
}
