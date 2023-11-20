// Homework 5 blocks of Procedural programming.
// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes.

#include<iostream>
#include<string>
#include<Windows.h>
#include<sstream>
#include<fstream>
#include<time.h>

using namespace std;
HANDLE back_col = GetStdHandle(STD_OUTPUT_HANDLE);
void comment_output() {
	SetConsoleTextAttribute(back_col, 0x0a);
	cout << "----------------------------------------------\n TASK NUMBER:  \n 1 task - 'Euclid's algorithm' \n 2 task - 'Sieve of Eratosthenes' \n 3 task - Task 'Processing text files' \n 4 task - '-'" << endl;
	SetConsoleTextAttribute(back_col, 0x07);
}

namespace TaskOneVarTwo {
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

namespace SieveOfEratosthenes {
	bool is_prime(int num) {
		if (num < 2) {
			return false;
		}

		for (int i = 2; i < num; i++) {
			if ((num % i) == 0) {
				return false;
			}
		}

		return true;
	}

	void find_primes() {
		int upper_limit;
		while (true) {
			cout << "enter limit: \n";
			if (!(cin >> upper_limit)) {
				cin.clear();
				cin.ignore();
				cerr << "error\n";
				continue;
			}
			break;
		}

		if (upper_limit < 2) {
			cout << "error!" << endl;
			return;
		} ///исключения добавить!

		cout << "prime numbers from 2 to " << upper_limit << ": ";
		for (int j = 2; j <= upper_limit; j++) {
			if (is_prime(j)) {
				cout << j << " ";
			}
		}
		cout << endl;
	}
}

namespace ProcessingTextFiles {
	void converting_delimiters() {
		string input_string;
		cout << "enter input string: ";
		cin >> input_string;
		getline(cin, input_string);

		char replace_char;
		cout << "enter the character(symbol) you want to insert in place of the blanks: ";
		cin >> replace_char;

		for (char &i_symbol : input_string) {
			if (i_symbol == ' ') {
				i_symbol = replace_char;
			} 

		}
		cout << input_string << endl << endl;
	}
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
				cout << "ohhhh, okay;(\n";
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
			TaskOneVarTwo::FindTheGDBDivisionByDivision gcdCalculator_one;
			gcdCalculator_one.euclidean_algorithm_division();
			cout << "\n\nsubtraction method: \n";
			TaskOneVarTwo::FindTheGDBDivisionBySubtraction gcdCalculator_two;
			gcdCalculator_two.euclidean_algorithm_subtraction();
			cout << "\n";
			break;
		case 2:
			cout << "\n";
			SetConsoleTextAttribute(back_col, 0x0a);
			cout << "'The Sieve of Eratosthenes' task. Find all prime numbers in the range from 2 to the number you enter natural number\n";
			SetConsoleTextAttribute(back_col, 0x07);
			SieveOfEratosthenes::find_primes();
			cout << "\n";
			break;
		case 3:

			cout << "\nAssignments on the topic 'Processing text files'\n\ntask 1 : Converting delimiters = replacing spaces with other (specific) characters.\ntask 4 : Searching for a word of maximum length in the text.\ntask 19 : Statistical processing of a text file = searching for the most frequently occurring character\n";
			cout << "\nenter the number of a specific task : ";
			int local_switch_tree;
			while (true) {
				if (!(cin >> local_switch_tree)) {
					cin.clear();
					cin.ignore();
					cout << "error!\n";
					continue;
				}
				break;
			}

			switch (local_switch_tree) {
			case 1:
				ProcessingTextFiles::converting_delimiters();
				break;
			case 4:
				cout << "coming soon\n";
				break;
			case 19:
				cout << "coming soon\n";
				break;
			default:
				cout << "error!\n";
				break;
			}
			//SetConsoleTextAttribute(back_col, 0x0a);
			//cout << "Task 'Processing text files' task.\nTASK 1: Delimiter conversion: replacing spaces with other (specific) characters\n";
			//SetConsoleTextAttribute(back_col, 0x07);
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
