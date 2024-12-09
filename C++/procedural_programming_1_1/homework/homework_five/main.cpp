// Homework 5 blocks of Procedural programming.
// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes.

//ОШИБКИ : 17 = 3 БЛОК - КОДА НЕТ (не срочно)\ 20 = 4 БЛОК - ОШИБКА В КОДЕ (не срочно)

#include<iostream>
#include<string>
#include<Windows.h>
#include<sstream>
#include<fstream>
#include<time.h>
#include<iterator>
#include<algorithm>
#include<vector>

//using namespace std;

HANDLE back_col = GetStdHandle(STD_OUTPUT_HANDLE);

void comment_output() {
	SetConsoleTextAttribute(back_col, 0x0a);
	std::cout << "----------------------------------------------\n TASK NUMBER:  \n 1 task - 'Euclid's algorithm' \n 2 task - 'Sieve of Eratosthenes' \n 3 task - Task 'Processing text files' \n 4 task - Task 'Rows'\n 5 task - Task 'Files'\n" << std::endl;
	SetConsoleTextAttribute(back_col, 0x07);
}


// Задание «Алгоритм Евклида»
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
			catch (const std::exception& err) {
				std::cerr << "error: " << err.what() << std::endl;
				return 0;
			}
		}

		void euclidean_algorithm_division() {
			int num_one, num_two;
			while (true) {
				std::cout << "enter first number: ";
				if (!(std::cin >> num_one)) {
					std::cin.clear();
					std::cin.ignore();
					std::cerr << "return 1\n";
					continue;
				}
				break;
			}
			while (true) {
				std::cout << "enter second number: ";
				if (!(std::cin >> num_two)) {
					std::cin.clear();
					std::cin.ignore();
					std::cerr << "return 1\n";
					continue;
				}
				break;
			}

			int gcd_return = GDBByDivision(num_one, num_two);
			if (gcd_return != -0) {
				std::cout << "GCD by subtraction method: " << gcd_return << std::endl;
			}
			else {
				std::cerr << "failed to calculate GCD - gcd_return \n";
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
			catch (const std::exception& err) {
				std::cerr << "error! " << err.what() << std::endl;
				return 0;
			}
		}

		void euclidean_algorithm_subtraction() {
			int num_one, num_two;
			while (true) {
				std::cout << "enter first number: ";
				if (!(std::cin >> num_one)) {
					std::cin.clear();
					std::cin.ignore();
					std::cerr << "return 1\n";
					continue;
				}
				break;
			}
			while (true) {
				std::cout << "enter second number: ";
				if (!(std::cin >> num_two)) {
					std::cin.clear();
					std::cin.ignore();
					std::cerr << "return 1\n";
					continue;
				}
				break;
			}

			int gcd_return = GDBBySubtraction(num_one, num_two);
			if (gcd_return != -0) {
				std::cout << "GCD by subtraction method: " << gcd_return << std::endl;
			}
			else {
				std::cerr << "failed to calculate GCD - gcd_return \n";
			}
		}
	};
}

// Задание «Решето Эратосфена» 
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
			std::cout << "enter limit: \n";
			if (!(std::cin >> upper_limit)) {
				std::cin.clear();
				std::cin.ignore();
				std::cerr << "error\n";
				continue;
			}
			break;
		}

		if (upper_limit < 2) {
			std::cout << "error!" << std::endl;
			return;
		} ///исключения добавить!

		std::cout << "prime numbers from 2 to " << upper_limit << ": ";
		for (int j = 2; j <= upper_limit; j++) {
			if (is_prime(j)) {
				std::cout << j << " ";
			}
		}
		std::cout << std::endl;
	}
}

// Задания «Обработка текстовых файлов» : 
namespace ProcessingTextFiles {

	// задача  1. Преобразование разделителей: замена пробелов на другие(определенные) символы
	void converting_delimiters_spaces() {
		std::string input_string;
		std::cout << "enter input std::string: ";
		//std::cin >> input_string;
		std::cin.clear(); //перед гитлайном надо очистить буфер обмена
		std::cin.ignore();
		getline(std::cin, input_string);

		char replace_char;
		std::cout << "enter the character(symbol) you want to insert in place of the blanks: ";
		std::cin >> replace_char;

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
		std::cout << "     test : " << spent_time_test << std::endl;

		double average_time = total_spent_time / size;
		std::cout << input_string << std::endl;

		SetConsoleTextAttribute(back_col, 0x0b);
		std::cout << "test average time " << total_spent_time << std::endl;;
		std::cout << "\naverage time = " << average_time << " ml\n\n";
		SetConsoleTextAttribute(back_col, 0x0a);

	}

	// задача 2. Преобразование разделителей: превращение строк в столбцы слов
	void convert_rows_columns() {
		std::string input_string;
		std::cout << "enter text: ";
		getline(std::cin, input_string);

		std::string word;
		while (getline(std::cin, input_string) && !input_string.empty()) {
			for (char& symbol : input_string) {
				if (symbol != ' ') {
					word += symbol;
				}
				else {
					std::cout << word << std::endl;
					word.clear();
				}
			}

			if (!word.empty()) {
				std::cout << word << std::endl;
			}
			break;
		}
		std::cout << std::endl;
	}

	// задача 4. Поиск в тексте слова максимальной длины.
	void max_word_length() {
		try {
			std::cout << "enter text: ";
			std::string text;
			std::cin >> text;
			getline(std::cin, text);

			std::stringstream subject_w(text);
			std::string word, longest_word;
			while (subject_w >> word) {
				if (word.length() > longest_word.length()) {
					longest_word = word;
				}
			}

			if (!longest_word.empty()) {
				std::cout << "longest word in text: " << longest_word << std::endl;
			}
			else {
				std::cout << "error, text is empty!\n";
			}
		}
		catch (const std::exception& err) {
			std::cerr << "error : " << err.what() << std::endl;
		}
	}

	// задача 19. Статистическая обработка текстового файла : поиск наиболее часто встречающегося символа.
	void most_occurring_character() {
		std::cout << "\n";
		try {
			std::ifstream file("example.txt");

			if (!file.is_open()) {
				std::cerr << "error\n";
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
					std::cout << "symbol '" << static_cast<char>(i) << "': " << char_frequency[i] << " times\n";
					if (char_frequency[i] > max_frequency) {
						max_frequency = char_frequency[i];
						most_occurred_symbol = i;
					}
				}
			}

			if (most_occurred_symbol != -1) {
				std::cout << "\nmost occurring symbol: '" << static_cast<char>(most_occurred_symbol) << "' with frequency: " << max_frequency << " times\n\n";
			}

			file.close();
		}
		catch (const std::exception& err) {
			std::cerr << "error : " << err.what() << std::endl;
		}
	}

	// задача 15. Поиск определенного слова в текстовом файле.
	class SearchSpecificWord {
	public:
		void display_file_contents(const std::string& filename) {
			try {
				std::ifstream input_file(filename);
				if (!input_file.is_open()) {
					std::cerr << "error opening file! " << filename << std::endl;
					return;
				}

				std::string line;
				std::cout << "\ncontents of the file '" << filename << "': \n\n";
				while (getline(input_file, line)) {
					std::cout << line << std::endl;
				}

				input_file.close();
			}
			catch (const std::exception& err) {
				std::cerr << "error : " << err.what() << std::endl;
			}
		}

		void search_word(const std::string& filename, std::string& target_word) {
			try {
				std::ifstream input_file(filename);

				if (!input_file.is_open()) {
					std::cerr << "error opening file! " << filename << std::endl;
					return;
				}

				std::string line;
				bool word_found = false;
				int line_number = 0;

				while (getline(input_file, line)) {
					//line_number++;
					size_t pos = line.find(target_word);
					if (pos != std::string::npos) {
						line_number++;
						std::cout << "\nword: " << target_word << " found in line " << line_number << " at position " << pos << std::endl << std::endl;
						word_found = true;
					}
				}

				input_file.close();

				if (!word_found) {
					std::cout << "\nword: " << target_word << " not found in the file! \n\n";
				}
			}
			catch (const std::exception& err) {
				std::cerr << "error : " << err.what() << std::endl;
			}
		}

		void cout_search_specific_word() {
			try {
				std::string filename = "text.txt";

				display_file_contents(filename);

				std::string target_word;
				std::cout << "\nenter the word you want to find in the text: ";
				std::cin >> target_word;

				search_word(filename, target_word);
			}
			catch (const std::exception& err) {
				std::cerr << "error : " << err.what() << std::endl;
			}
		}
	};

	// нету
	void sort_word_text() {

		//сложная задача - исправить 
	}

	// 38. Проверка баланса скобок в текстовом файле
	class CheckingBalance {
	public:
		void balance_brackets_cout() {
			try {
				std::ifstream input_file("input_task_38.txt");
				if (!input_file.is_open()) {
					std::cerr << "\nthe file could not be opened\n" << std::endl;
					return;
				}

				std::string text;
				char ch;
				while (input_file.get(ch)) {
					text += ch;
				}

				input_file.close();

				int open_count = 0;
				int close_count = 0;

				for (char c : text) {
					if (c == '(') {
						open_count++;
					}
					else if (c == ')') {
						close_count++;
					}
				}

				std::cout << "\nsource text: \n" << text << std::endl << std::endl;

				std::cout << "number of opening brackets: " << open_count << std::endl;
				std::cout << "number of closing brackets: " << close_count << std::endl << std::endl;

				int diff = open_count - close_count;

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

				std::cout << "text after checking the balance of brackets: \n" << text << std::endl << std::endl;
			}
			catch (const std::exception& err) {
				std::cout << "error ! :" << err.what();
			}
		}
	};
}

// Задание «Ряды». Выполнить два варианта задания
namespace TaskRows {
	// задача 1) Дано целое число n (вводится с клавиатуры). Вычислить:
	void task_one() {
		int n;
		while (true) {
			std::cout << "\nenter n: ";
			if (!(std::cin >> n)) {
				std::cin.clear();
				std::cin.ignore();
				std::cout << "error \n";
				continue;
			}
			break;
		}

		std::cout << "\nexample: \n";
		long double result_sum = 0.0, sin_sum = 0.0;

		for (int i = 1; i <= n; ++i) {
			long double denominator = 0.0;
			for (int j = 1; j <= i; ++j) {
				denominator += sin(j);
			}
			result_sum += i / denominator;

			std::cout << i << "/(";
			for (int k = 1; k <= i; ++k) {
				std::cout << "sin(" << k << ")";
				if (k < i) {
					std::cout << " + ";
				}
			}
			std::cout << ")";

			if (i < n) {
				std::cout << " + ";
			}
		}
		std::cout << "\n\nresult : " << result_sum << std::endl << std::endl;
	}

	// задача 4 Дано натуральное число n. Вычислить:
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
				std::cout << "\nenter natural number n: ";
				if (!(std::cin >> n)) {
					std::cin.clear();
					std::cin.ignore();
					std::cout << "error \n";
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

			std::cout << "\nresult : " << y << std::endl;
		}
	};

	// задача 20 Задан массив F[1:n] из чисел в двоичной системе счисления. В другом массиве организовать перевод
	// исходного массива в четверичную систему счисления
	class TransferToFour {
	public:
		std::string binary_to_quaternary(const std::string& binary) {
			try {
				std::string quaternary;

				int binary_length = binary.length();

				while ((binary_length % 2) != 0) {
					binary_length++;
				}

				for (int i = 0; i < binary_length; i += 2) {
					std::string two_digits = binary.substr(i, 2);
					int decimal = stoi(two_digits, nullptr, 2);
					quaternary += std::to_string(decimal);
				}
				return quaternary;
			}
			catch (const std::exception& err) {
				throw std::runtime_error("Error converting binary to quaternary: " + std::string(err.what()));
			}
		}

		void cout_binary_to_quaternary() {
			int n;
			while (true) {
				std::cout << "\nEnter the number of variables (n): ";
				if (!(std::cin >> n)) {
					std::cin.clear();
					std::cin.ignore();
					std::cerr << "Error! Invalid input.\n";
					continue;
				}
				break;
			}

			std::vector<std::string> binary_array(n);
			std::vector<std::string> quaternary_array(n);

			for (int i = 0; i < n; ++i) {
				std::cout << "enter binary number " << i + 1 << ": ";
				std::cin >> binary_array[i];
			}

			for (int j = 0; j < n; ++j) {
				try {
					quaternary_array[j] = binary_to_quaternary(binary_array[j]);
				}
				catch (const std::exception& e) {
					std::cerr << e.what() << " (binary number " << j + 1 << ")\n";
				}
			}

			std::cout << "\nsource array in binary system:\n";
			for (const auto& binary : binary_array) {
				std::cout << binary << " ";
			}

			std::cout << "\n\nresult of the translation into the quaternary system:\n";
			for (const auto& quaternary : quaternary_array) {
				std::cout << quaternary << " ";
			}
		}
	};
}

// Задание «Файлы». Выполнить один вариант задания
namespace TaskFiles {
	// 13)Создать файл из N целых чисел. Найти число, повторяющееся максимальное количество раз. Если
	// таких чисел несколько, то все из них.Сохранить эти числа в другой файл и отсортировать.Все файлы
	// до и после обработки вывести на печать.

	// использую метод сортировки слиянием

	void merge(int arr[], int left, int right, int middle);
	void merge_sort(int arr[], int left, int right);
	void printArray(int arr[], int size);

	void findMaxFrequencyNumbers(int numbers[], int size, int& max_count, int*& result_numbers) {
		max_count = 0;

		int max_number = *std::max_element(numbers, numbers + size);

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
			std::ifstream input_file(input_file_name);
			if (!input_file) {
				std::cerr << "\nerror!\n" << input_file_name << std::endl;
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
			std::copy(numbers, numbers + number, sorted_numbers);

			merge_sort(sorted_numbers, 0, number - 1);

			findMaxFrequencyNumbers(numbers, number, max_count, result_numbers);

			std::ofstream output_file(output_file_name);
			if (!output_file) {
				std::cerr << "\nerror!\n" << output_file_name << std::endl;
				delete[] numbers;
				delete[] result_numbers;
				delete[] sorted_numbers;
				return;
			}

			for (int i = 0; i < max_count; i++) {
				output_file << result_numbers[i] << std::endl;
			}

			output_file.close();

			std::cout << "original numbers: ";
			printArray(numbers, number);
			std::cout << std::endl;

			std::cout << "\nsorted numbers: ";
			printArray(sorted_numbers, number);
			std::cout << std::endl;

			for (int i = 0; i < 1; i++) {
				std::cout << "most frequently occurring number: " << result_numbers[i] << std::endl << std::endl;
			}

			delete[] numbers;
			delete[] result_numbers;
			delete[] sorted_numbers;
		}
		catch (const std::exception& err) {
			std::cerr << "error : " << err.what() << std::endl;
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

		std::cout << "merged pairs: ";
		printArray(arr + left, right - left + 1);
		std::cout << std::endl;
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
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
}

void launcher() {
	char task_number_char;
	int task_number_int;

	while (true) {
		comment_output();
		while (true) {
			std::string task_number_str;

			std::cout << "if you want to exit the program, enter 'exit' \nenter task_number : ";
			std::cin >> task_number_str;

			if (task_number_str == "exit") {
				SetConsoleTextAttribute(back_col, 0x0b);
				std::cout << "ohhhh, okay;(\n";
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
				std::cerr << "error, enter only numbers!\n";
				std::cin.clear();
				std::cin.ignore();
			}
			else {
				std::stringstream(task_number_str) >> task_number_int;
				break;
			}
		}

		std::string local_switch_tree_str, local_switch_four_str;
		int local_switch_tree, local_switch_four;

		switch (task_number_int) {
		case 1:
			std::cout << "\n";
			SetConsoleTextAttribute(back_col, 0x0a);
			std::cout << "Task 'Euclidean Algorithm'. Give 2 numbers and find their most common divisor methods : division and subtraction.\n";
			SetConsoleTextAttribute(back_col, 0x07);

			// Задание «Алгоритм Евклида». Задать 2 числа и найти их наибольший общий делитель двумя
			// способами: делением и вычитанием.

			std::cout << "division method: \n";			// 1 задание методом делением
			TaskOneVarTwo::FindTheGDBDivisionByDivision gcdCalculator_one;
			gcdCalculator_one.euclidean_algorithm_division();

			std::cout << "\n\nsubtraction method: \n";     // 1 задание методом вычитанием
			TaskOneVarTwo::FindTheGDBDivisionBySubtraction gcdCalculator_two;
			gcdCalculator_two.euclidean_algorithm_subtraction();

			std::cout << "\n";
			break;
		case 2:
			std::cout << "\n";
			SetConsoleTextAttribute(back_col, 0x0a);
			std::cout << "'The Sieve of Eratosthenes' task. Find all prime numbers in the range from 2 to the number you enter natural number\n";
			SetConsoleTextAttribute(back_col, 0x07);

			// Задание «Решето Эратосфена». Найти все простые числа в диапазоне от 2 до введенного вами
			// натурального числа

			SieveOfEratosthenes::find_primes();  // Задание «Решето Эратосфена» 

			std::cout << "\n";
			break;
		case 3:
			// Задания обработка текстовых файлов
			SetConsoleTextAttribute(back_col, 0x0a);
			std::cout << "\nAssignments on the topic 'Processing text files'\n";
			SetConsoleTextAttribute(back_col, 0x07);

			std::cout << "(if you want to exit the program, enter 'exit') \n\ntask 1 : Converting delimiters = replacing spaces with other(specific) characters.\ntask 2 : Convert Delimiters = convert rows to columns of words.\ntask 4 : Searching for a word of maximum length in the text.\ntask 15 : Find a specific word in a text file. \ntask 17 : Sort words in a text file alphabetically.\ntask 19 : Statistical processing of a text file = searching for the most frequently occurring character\ntask 38 : Checking parenthesis balance in a text file.\n";

			while (true) {
				std::cout << "\nenter the number of a specific task or enter 'exit' : ";
				std::cin >> local_switch_tree_str;

				if (local_switch_tree_str == "exit") {
					std::cout << " ;( \n";
				}

				bool has_no_digit_tree = false;
				for (char type : local_switch_tree_str) {
					if (!isdigit(type)) {
						local_switch_tree_str = true;
						break;
					}
				}

				if (has_no_digit_tree) {
					std::cerr << "error! enter only members!\n";
					std::cin.clear();
					std::cin.ignore();
				}
				else {
					std::stringstream(local_switch_tree_str) >> local_switch_tree;
					break;
				}
			}

			switch (local_switch_tree) {
			case 1:

				// задача  1. Преобразование разделителей: замена пробелов на другие(определенные) символы. 
				ProcessingTextFiles::converting_delimiters_spaces();
				break;
			case 2:

				// задача 2. Преобразование разделителей: превращение строк в столбцы слов
				ProcessingTextFiles::convert_rows_columns();
				break;
			case 4:

				// задача 4. Поиск в тексте слова максимальной длины.
				ProcessingTextFiles::max_word_length();
				break;
			case 15:

				// задача 15. Поиск определенного слова в текстовом файле.
				ProcessingTextFiles::SearchSpecificWord TestLaunch;
				TestLaunch.cout_search_specific_word();
				break;
			case 17:

				// нет нихуя 
				std::cerr << "poka netu\n"; 		//сложная задача - исправить 

				ProcessingTextFiles::sort_word_text();
				break;
			case 19:

				//19. Статистическая обработка текстового файла: поиск наиболее часто встречающегося символа.
				ProcessingTextFiles::most_occurring_character();
				break;
			case 38:

				// 38. Проверка баланса скобок в текстовом файле
				ProcessingTextFiles::CheckingBalance LocalLaunch;
				LocalLaunch.balance_brackets_cout();
				break;
			default:
				std::cerr << "error!\n";
				break;
			}

			break;
		case 4:  // Задание «Ряды». Выполнить два варианта задания
			SetConsoleTextAttribute(back_col, 0x0a);
			std::cout << "\nTask 'Row'\n";
			SetConsoleTextAttribute(back_col, 0x07);

			std::cout << "(if you want to exit the program, enter 'exit') \n\ntask 1 : An integer n is given (entered from the keyboard).\ntask 4 : Given a natural number n, calculate sigma\ntask 20 : An array of F[1:n] numbers in binary notation is given. In another array, organize the translationof the original array into the quaternary number system \n";

			while (true) {
				std::cout << "\nenter the number of a specific task or enter 'exit' : ";
				std::cin >> local_switch_four_str;

				if (local_switch_four_str == "exit") {
					std::cout << " ;( \n";
				}

				bool has_no_digit_four = false;
				for (char type : local_switch_four_str) {
					if (!isdigit(type)) {
						local_switch_four_str = true;
						break;
					}
				}

				if (has_no_digit_four) {
					std::cerr << "error! enter only members!\n";
					std::cin.clear();
					std::cin.ignore();
				}
				else {
					std::stringstream(local_switch_four_str) >> local_switch_four;
					break;
				}
			}

			switch (local_switch_four) {
			case 1:

				// задача 1) Дано целое число n (вводится с клавиатуры). Вычислить:
				TaskRows::task_one();
				break;
			case 4:

				// задача 4 Дано натуральное число n. Вычислить:
				TaskRows::TaskSigma TimeFunction;
				TimeFunction.task_sigma();
				break;
			case 20:

				// задача 20 Задан массив F[1:n] из чисел в двоичной системе счисления. В другом массиве организовать перевод
				// исходного массива в четверичную систему счисления
				TaskRows::TransferToFour LocalFunction;
				LocalFunction.cout_binary_to_quaternary();
			default:
				std::cerr << "error!\n\n";
			}
			break;
		case 5: // Задание «Файлы». Выполнить один вариант задания
			std::cout << "\ntask 13: Create a file of N integers. Find the number that repeats the maximum number of times.\nIf there are several such numbers, then all of them.Save these numbers to another file and sort. \nAll files Print before and after processing.\n\n\n";

			// Создать файл из N целых чисел. Найти число, повторяющееся максимальное количество раз. Если
			// таких чисел несколько, то все из них.Сохранить эти числа в другой файл и отсортировать.Все файлы
			// до и после обработки вывести на печать.
			TaskFiles::cout_task();
			break;
		default:
			std::cerr << "error!\n";
			break;
		}
	}
}

int main() {
	launcher();
	return 0;
}
