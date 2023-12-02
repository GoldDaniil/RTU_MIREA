// Homework 5 blocks of Procedural programming.
// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes.


//ОШИБКИ : 17 = 3 БЛОК - КОДА НЕТ (не срочно)\ 20 = 4 БЛОК - ОШИБКА В КОДЕ (не срочно)\ 4 номер = 4 блок - ошибка

#include<iostream>
#include<string>
#include<Windows.h>
#include<sstream>
#include<fstream>
#include<time.h>
#include<iterator>
#include<algorithm>
#include <vector>

using namespace std;
HANDLE back_col = GetStdHandle(STD_OUTPUT_HANDLE);
void comment_output() {
	SetConsoleTextAttribute(back_col, 0x0a);
	cout << "----------------------------------------------\n TASK NUMBER:  \n 1 task - 'Euclid's algorithm' \n 2 task - 'Sieve of Eratosthenes' \n 3 task - Task 'Processing text files' \n 4 task - Task 'Rows'\n 5 task - Task 'Files'\n" << endl;
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
		//cin >> input_string;
		cin.clear(); //перед гитлайном надо очистить буфер обмена
		cin.ignore();
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
		getline(cin, input_string);

		string word;
		while (getline(cin, input_string) && !input_string.empty()) {
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
		cout << "\n";
		try {
			ifstream file("example.txt");

			if (!file.is_open()) {
				cerr << "error\n";
				return;
			}

			const int ASCII_SIZE = 128;
			int char_frequency[ASCII_SIZE] = { 0 };

			int symbol;
			while ((symbol = file.get()) != EOF) {
				if (symbol >= 32 && symbol <= 126) {
					char_frequency[symbol]++;
				}
			}

			int max_frequency = 0;
			int most_occurred_symbol = -1;

			for (int i = 32; i <= 126; ++i) {
				if (char_frequency[i] > 0) {
					cout << "symbol '" << static_cast<char>(i) << "': " << char_frequency[i] << " times\n";
					if (char_frequency[i] > max_frequency) {
						max_frequency = char_frequency[i];
						most_occurred_symbol = i;
					}
				}
			}

			if (most_occurred_symbol != -1) {
				cout << "\nmost occurring symbol: '" << static_cast<char>(most_occurred_symbol) << "' with frequency: " << max_frequency << " times\n\n";
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
					//line_number++;
					size_t pos = line.find(target_word);
					if (pos != string::npos) {
						line_number++;
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

	void sort_word_text() {

		//сложная задача - исправить 
	}

	class CheckingBalance {
	public:
		void balance_brackets_cout() {
			try {
				ifstream inputFile("input_task_38.txt");
				if (!inputFile.is_open()) {
					cerr << "\nthe file could not be opened\n" << endl;
					return;
				}

				string text;
				char ch;
				while (inputFile.get(ch)) {
					text += ch;
				}

				inputFile.close();

				int openCount = 0;
				int closeCount = 0;

				for (char c : text) {
					if (c == '(') {
						openCount++;
					}
					else if (c == ')') {
						closeCount++;
					}
				}

				cout << "\nsource text: \n" << text << endl << endl;

				cout << "number of opening brackets: " << openCount << endl;
				cout << "number of closing brackets: " << closeCount << endl << endl;

				int diff = openCount - closeCount;

				if (diff > 0) {
					for (int i = 0; i < diff; i++) {
						text += ")";
					}
				}
				else if (diff < 0) {
					for (int i = 0; i < -diff; i++) {
						text = "(" + text;
					}
				}

				cout << "text after checking the balance of brackets: \n" << text << endl << endl;
			}
			catch (const exception& err) {
				cout << "error ! :" << err.what();
			}
		}
	};
}

namespace TaskRows {
	void task_one() {
		int n;
		while (true) {
			cout << "\nenter n: ";
			if (!(cin >> n)) {
				cin.clear();
				cin.ignore();
				cout << "error \n";
				continue;
			}
			break;
		}

		cout << "\nexample: \n";
		long double result_sum = 0.0, sin_sum = 0.0;

		for (int i = 1; i <= n; ++i) {
			long double denominator = 0.0;
			for (int j = 1; j <= i; ++j) {
				denominator += sin(j);
			}
			result_sum += i / denominator;

			cout << i << "/(";
			for (int k = 1; k <= i; ++k) {
				cout << "sin(" << k << ")";
				if (k < i) {
					cout << " + ";
				}
			}
			cout << ")";

			if (i < n) {
				cout << " + ";
			}
		}
		cout << "\n\nresult : " << result_sum << endl << endl;
	}

	class TaskSigma {
	public:
		int factorial_function(int n) {
			if ((n == 0) || (n == 1)) {
				return 1;
			}
			else {
				return n * factorial_function(n - 1); // рекурсивная функция для нахождения
			}											// факториала

		}

		void task_sigma() {
			int n;
			while (true) {
				cout << "\nenter natural number n: ";
				if (!(cin >> n)) {
					cin.clear();
					cin.ignore();
					cout << "error \n";
					continue;
				}
				break;
			}

			long double y = 0.0, partial_sum = 0.0;

			for (int k = 1; k <= n; ++k) {
				if ((k % 2) == 0) {
					partial_sum += -1.0 / k;
				}
				else {
					partial_sum += 1.0 / k;
				}

				y += factorial_function(k) / partial_sum;
			}

			cout << "\nresult : " << y << endl;
		}
	};

	class TransferToFour {
	public:
		string binary_to_quaternary(const string& binary) {
			try {
				string quaternary;

				int binary_length = binary.length();

				while ((binary_length % 2) != 0) {
					binary_length++;
				}

				for (int i = 0; i < binary_length; i += 2) {
					string two_digits = binary.substr(i, 2);
					int decimal = stoi(two_digits, nullptr, 2);
					quaternary += to_string(decimal);
				}
				return quaternary;
			}
			catch (const exception& err) {
				throw runtime_error("Error converting binary to quaternary: " + string(err.what()));
			}
		}

		void cout_binary_to_quaternary() {
			int n;
			while (true) {
				cout << "\nEnter the number of variables (n): ";
				if (!(cin >> n)) {
					cin.clear();
					cin.ignore();
					cerr << "Error! Invalid input.\n";
					continue;
				}
				break;
			}

			// Create vectors for storing binary and quaternary numbers
			vector<string> binary_array(n);
			vector<string> quaternary_array(n);

			for (int i = 0; i < n; ++i) {
				cout << "Enter binary number " << i + 1 << ": ";
				cin >> binary_array[i];
			}

			for (int j = 0; j < n; ++j) {
				try {
					quaternary_array[j] = binary_to_quaternary(binary_array[j]);
				}
				catch (const exception& e) {
					cerr << e.what() << " (Binary number " << j + 1 << ")\n";
				}
			}

			cout << "\nSource array in binary system:\n";
			for (const auto& binary : binary_array) {
				cout << binary << " ";
			}

			cout << "\n\nResult of the translation into the quaternary system:\n";
			for (const auto& quaternary : quaternary_array) {
				cout << quaternary << " ";
			}
		}
	};
}

namespace TaskFiles {
	void merge(int arr[], int left, int right, int middle);
	void merge_sort(int arr[], int left, int right);
	void printArray(int arr[], int size);

	void findMaxFrequencyNumbers(int numbers[], int size, int& max_count, int*& result_numbers) {
		max_count = 0;

		int max_number = *max_element(numbers, numbers + size);

		int* frequency_array = new int[max_number + 1]();

		for (int i = 0; i < size; i++) {
			frequency_array[numbers[i]]++;
			max_count = max(max_count, frequency_array[numbers[i]]);
		}

		int count = 0;
		for (int num = 0; num <= max_number; num++) {
			if (frequency_array[num] == max_count) {
				count++;
			}
		}

		result_numbers = new int[count];
		int index = 0;
		for (int num = 0; num <= max_number; num++) {
			if (frequency_array[num] == max_count) {
				result_numbers[index++] = num;
			}
		}

		delete[] frequency_array;

	}	
	
	void cout_task() {
		const char* input_file_name = "input_13.txt";
		const char* output_file_name = "output_13.txt";

		try {
			ifstream input_file(input_file_name);
			if (!input_file) {
				cerr << "\nerror!\n" << input_file_name << endl;
				return;
			}

			int number;
			input_file >> number;

			int* numbers = new int[number];
			for (int i = 0; i < number; i++) {
				input_file >> numbers[i];
			}

			input_file.close();

			int max_count;
			int* result_numbers;

			int* sorted_numbers = new int[number];
			copy(numbers, numbers + number, sorted_numbers);

			merge_sort(sorted_numbers, 0, number - 1);

			findMaxFrequencyNumbers(numbers, number, max_count, result_numbers);

			ofstream output_file(output_file_name);
			if (!output_file) {
				cerr << "\nerror!\n" << output_file_name << endl;
				delete[] numbers;
				delete[] result_numbers;
				delete[] sorted_numbers;
				return;
			}

			for (int i = 0; i < max_count; i++) {
				output_file << result_numbers[i] << endl;
			}

			output_file.close();

			cout << "original numbers: ";
			printArray(numbers, number);
			cout << endl;

			cout << "\nsorted numbers: ";
			printArray(sorted_numbers, number);
			cout << endl;

			delete[] numbers;
			delete[] result_numbers;
			delete[] sorted_numbers;
		}
		catch (const exception& err) {
			cerr << "error : " << err.what() << endl;
		}
	}

	void merge(int arr[], int left, int right, int middle) { //функция для слияния двух подмассивов arr[left, middle] и arr[middle+1, right]
		int left_sizes_subarrays = (middle - left + 1); //размер подмассива left_sizes_subarrays
		int right_sizes_subarrays = (right - middle); //размер подмассива right_sizes_subarrays

		//cоздание временных подмассивов
		int* Left_subarray = new int[left_sizes_subarrays];
		int* Right_subarray = new int[right_sizes_subarrays];

		//копирование данных во временные подмассивы Left_subarray[] и Right_subarray[]
		for (int i = 0; i < left_sizes_subarrays; i++) {
			Left_subarray[i] = arr[left + i];
		}
		for (int j = 0; j < right_sizes_subarrays; j++) {
			Right_subarray[j] = arr[middle + 1 + j];
		}

		//ю.объединение временные подмассивы обратно в arr[left...right]
		int i = 0; //индекс первого подмассива Left_subarray
		int j = 0; //индекс второго подмассива Right_subarray
		int k = left; //индекс объединенного подмассива

		while ((i < left_sizes_subarrays) and (j < right_sizes_subarrays)) {
			if (Left_subarray[i] <= Right_subarray[j]) { //если элемент в Left_subarray[i] меньше или равен элементу в Right_subarray[j] то
				arr[k] = Left_subarray[i]; //                   присваиваем значение из левого подмассива в общий массив
				i++; //увеличиваем индекс Left_subarray[i]
			}
			else {
				arr[k] = Right_subarray[j];
				j++; //увеличиваем индекс Right_subarray[j]
			}
			k++; //увеличиваем индекс общего массива
		}

		//если остались элементы то копируем их в Left_subarray[]
		while (i < left_sizes_subarrays) {
			arr[k] = Left_subarray[i];
			i++; //увеличиваем индекс Left_subarray[i]
			k++; //увеличиваем индекс общего массива
		}

		//если остались элементы то копируем их в Right_subarray[]
		while (j < right_sizes_subarrays) {
			arr[k] = Right_subarray[j];
			j++; //увеличиваем индекс Right_subarray[j]
			k++;
		}

		delete[] Left_subarray;
		delete[] Right_subarray;

		cout << "merged pairs: ";
		printArray(arr + left, right - left + 1);
		cout << endl;
	}

	void merge_sort(int arr[], int left, int right) { //функция сортировки слиянием
		if (left >= right) { //если левая граница больше или равна правой то выходим
			return;
		}

		int middle_index = left + (right - left) / 2; //находим середину 

		merge_sort(arr, left, middle_index); //рекурсивно вызываем merge_sort = сортируем левую половину
		merge_sort(arr, middle_index + 1, right); //рекурсивно вызываем merge_sort = сортируем правую половину
		merge(arr, left, right, middle_index); //вызываем merge = соединяем - сливаем две отсортированные половины
	}

	void printArray(int arr[], int size) {  //отображение элементов массива до и после сортировки слиянием
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
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

		string local_switch_tree_str, local_switch_four_str;
		int local_switch_tree, local_switch_four;

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

			cout << "(if you want to exit the program, enter 'exit') \n\ntask 1 : Converting delimiters = replacing spaces with other(specific) characters.\ntask 2 : Convert Delimiters = convert rows to columns of words.\ntask 4 : Searching for a word of maximum length in the text.\ntask 15 : Find a specific word in a text file. \ntask 17 : Sort words in a text file alphabetically.\ntask 19 : Statistical processing of a text file = searching for the most frequently occurring character\ntask 38 : Checking parenthesis balance in a text file.\n";

			while (true) {
				cout << "\nenter the number of a specific task or enter 'exit' : ";
				cin >> local_switch_tree_str;

				if (local_switch_tree_str == "exit") {
					cout << " ;( \n";
				}

				bool has_no_digit_tree = false;
				for (char type : local_switch_tree_str) {
					if (!isdigit(type)) {
						local_switch_tree_str = true;
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
				cerr << "poka netu\n"; 		//сложная задача - исправить 

				ProcessingTextFiles::sort_word_text();
				break;
			case 19: //сложная задача - исправить 
				ProcessingTextFiles::most_occurring_character();
				break;
			case 38:
				ProcessingTextFiles::CheckingBalance LocalLaunch;
				LocalLaunch.balance_brackets_cout();
				break;
			default:
				cerr << "error!\n";
				break;
			}

			break;
		case 4:
			SetConsoleTextAttribute(back_col, 0x0a);
			cout << "\nTask 'Row'\n";
			SetConsoleTextAttribute(back_col, 0x07);

			cout << "(if you want to exit the program, enter 'exit') \n\ntask 1 : An integer n is given (entered from the keyboard).\ntask 4 : Given a natural number n, calculate sigma\ntask 20 : An array of F[1:n] numbers in binary notation is given. In another array, organize the translationof the original array into the quaternary number system \n";

			while (true) {
				cout << "\nenter the number of a specific task or enter 'exit' : ";
				cin >> local_switch_four_str;

				if (local_switch_four_str == "exit") {
					cout << " ;( \n";
				}

				bool has_no_digit_four = false;
				for (char type : local_switch_four_str) {
					if (!isdigit(type)) {
						local_switch_four_str = true;
						break;
					}
				}

				if (has_no_digit_four) {
					cerr << "error! enter only members!\n";
					cin.clear();
					cin.ignore();
				}
				else {
					stringstream(local_switch_four_str) >> local_switch_four;
					break;
				}
			}

			switch (local_switch_four) {
			case 1:
				TaskRows::task_one();
				break;
			case 4:
				TaskRows::TaskSigma TimeFunction;
				TimeFunction.task_sigma();
				break;
			case 20:
				TaskRows::TransferToFour LocalFunction;
				LocalFunction.cout_binary_to_quaternary();
			default:
				cerr << "error!\n\n";
			}
			break;
		case 5:
			cout << endl;
			TaskFiles::cout_task();
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
