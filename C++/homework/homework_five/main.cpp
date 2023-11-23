// Homework 5 blocks of Procedural programming.
// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes.

#include<iostream>
#include<string>
#include<Windows.h>
#include<sstream>
#include<fstream>
#include<time.h>
#include<iterator>
#include<algorithm>

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
	void converting_delimiters_spaces() {
		string input_string;
		cout << "enter input string: ";
		cin >> input_string;
		getline(cin, input_string);

		char replace_char;
		cout << "enter the character(symbol) you want to insert in place of the blanks: ";
		cin >> replace_char;

		const int size = 300;
		double total_spent_time = 0, research_time;

		clock_t start_time_test = clock();
		for (int j = 0; j < size; j++) {
			clock_t start_time = clock();

			for (char& i_symbol : input_string) {
				if (i_symbol == ' ') {
					i_symbol = replace_char;
				}

			}
			clock_t end_time = clock();
			double spent_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
			total_spent_time += spent_time;
		}
		clock_t end_time_test = clock();
		double spent_time_test = (double)(end_time_test - start_time_test) / CLOCKS_PER_SEC;
		cout << "     test : " << spent_time_test << endl;

		double average_time = total_spent_time / size;
		cout << input_string << endl;

		SetConsoleTextAttribute(back_col, 0x0b);
		cout << "test average time " << total_spent_time << endl;;
		cout << "\naverage time = " << average_time << " ml\n\n";
		SetConsoleTextAttribute(back_col, 0x0a);

	}

	void convert_rows_columns() {
		string input_string;
		cout << "enter text: ";
		cin >> input_string;

		while (getline(cin, input_string) && !input_string.empty()) {
			string word;
			for (char& symbol : input_string) {
				if (symbol != ' ') {
					word += symbol;
				}
				else {
					cout << word << endl;
					word.clear();
				}
			}

			if (!word.empty()) {
				cout << word << endl;
			}
			break;
		}
		cout << endl;
	}

	void max_word_length() {
		try {
			cout << "enter text: ";
			string text;
			cin >> text;
			getline(cin, text);

			stringstream subject_w(text);
			string word, longest_word;
			while (subject_w >> word) {
				if (word.length() > longest_word.length()) {
					longest_word = word;
				}
			}

			if (!longest_word.empty()) {
				cout << "longest word in text: " << longest_word << endl;
			}
			else {
				cout << "error, text is empty!\n";
			}
		}
		catch (const exception& err) {
			cerr << "error : " << err.what() << endl;
		}
	}

	void most_occurring_character() {
		try {
			ifstream file("example.txt");

			if (!file.is_open()) {
				cerr << "error\n";
				return;
			}

			const int ASCII_SIZE = 128;
			int char_frequency[ASCII_SIZE] = { 0 };

			char symbol;
			while (file.get(symbol)) {
				char_frequency[symbol]++;
			}

			for (char i = 0; i < ASCII_SIZE; ++i) {
				if (char_frequency[i] > 0) {
					cout << "symbol '" << i << "': " << char_frequency[i] << " once\n";
				}
			}

			file.close();
		}
		catch (const exception& err) {
			cerr << "error : " << err.what() << endl;
		}
	}

	class SearchSpecificWord {
	public:
		void display_file_contents(const string& filename) {
			try {
				ifstream input_file(filename);
				if (!input_file.is_open()) {
					cerr << "error opening file! " << filename << endl;
					return;
				}

				string line;
				cout << "\ncontents of the file '" << filename << "': \n\n";
				while (getline(input_file, line)) {
					cout << line << endl;
				}

				input_file.close();
			}
			catch (const exception& err) {
				cerr << "error : " << err.what() << endl;
			}
		}

		void search_word(const string& filename, string& target_word) {
			try {
				ifstream input_file(filename);

				if (!input_file.is_open()) {
					cerr << "error opening file! " << filename << endl;
					return;
				}

				string line;
				bool word_found = false;
				int line_number = 0;

				while (getline(input_file, line)) {
					line_number++;
					size_t pos = line.find(target_word);
					if (pos != string::npos) {
						cout << "\nword: " << target_word << " found in line " << line_number << " at position " << pos << endl << endl;
						word_found = true;
					}
				}

				input_file.close();

				if (!word_found) {
					cout << "\nword: " << target_word << " not found in the file! \n\n";
				}
			}
			catch (const exception& err) {
				cerr << "error : " << err.what() << endl;
			}

		}

		void cout_search_specific_word() {
			try {
				string filename = "text.txt";

				display_file_contents(filename);

				string target_word;
				cout << "\nenter the word you want to find in the text: ";
				cin >> target_word;

				search_word(filename, target_word);
			}
			catch (const exception& err) {
				cerr << "error : " << err.what() << endl;
			}
		}
	};

	/*void search_specific_word() {
		try {
			ofstream input_file("text.txt");
			input_file << "asdiah sdihaisdh iashd";



			if (!input_file.is_open()) {
				cerr << "error!\n";
				return;
			}

			string target_word, line;
			cout << "enter the word you want to find in the text: ";
			cin >> target_word;

			bool word_found = false;
			while (getline(input_file, line)) {
				if (line.find(target_word) != string::npos) {
					cout << "word: " << target_word << " found in line: " << line << endl;
					word_found = true;
				}
			}
			input_file.close();

			if (!word_found) {
				cout << "word: " << target_word << " not found in the file\n";
			}
		}
		catch (const exception& err) {
			cerr << "rrror: " << err.what() << endl;
		}
	}*/

	void sort_word_text() {
		//доделать завтра

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
				SetConsoleTextAttribute(back_col, 0x0b);
				cout << "ohhhh, okay;(\n";
				SetConsoleTextAttribute(back_col, 0x07);
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

		string local_switch_tree_str;
		int local_switch_tree;

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
			// Задания обработка текстовых файлов
			SetConsoleTextAttribute(back_col, 0x0a);
			cout << "\nAssignments on the topic 'Processing text files'\n";
			SetConsoleTextAttribute(back_col, 0x07);

			cout << "(if you want to exit the program, enter 'exit') \n\ntask 1 : Converting delimiters = replacing spaces with other(specific) characters.\ntask 2 : Convert Delimiters = convert rows to columns of words.\ntask 4 : Searching for a word of maximum length in the text.\ntask 15 : Find a specific word in a text file. \ntask 17 : Sort words in a text file alphabetically.\ntask 19 : Statistical processing of a text file = searching for the most frequently occurring character\n";

			
			while (true) {
				cout << "\nenter the number of a specific task or enter 'exit' : ";
				cin >> local_switch_tree_str;

				if (local_switch_tree_str == "exit") {
					cout << " ;( \n";
					return;
				}

				bool has_no_digit_tree = false;
				for (char type : local_switch_tree_str) {
					if (!isdigit(type)) {
						has_no_digit_tree = true;
						break;
					}
				}

				if (has_no_digit_tree) {
					cerr << "error! enter only members!\n";
					cin.clear();
					cin.ignore();
				}
				else {
					stringstream(local_switch_tree_str) >> local_switch_tree;
					break;
				}
			}

			switch (local_switch_tree) {
			case 1:
				ProcessingTextFiles::converting_delimiters_spaces();
				break;
			case 2:
				ProcessingTextFiles::convert_rows_columns();
				break;
			case 4:
				ProcessingTextFiles::max_word_length();
				break;
			case 15:
				ProcessingTextFiles::SearchSpecificWord TestLaunch;
				TestLaunch.cout_search_specific_word();
				break;
			case 17:
				ProcessingTextFiles::sort_word_text();
				break;
			case 19:
				ProcessingTextFiles::most_occurring_character();
				break;
			default:
				cerr << "error!\n";
				break;
			}
			break;
		case 4:
			cout << "\n";
			SetConsoleTextAttribute(back_col, 0x0a);
			cout << "'' task.\n";
			SetConsoleTextAttribute(back_col, 0x07);
			// sieve_eratosthenes();
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


