// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes and namespace.

#include<iostream>
#include<algorithm>
#include<cstdlib> // для использования rand()

using namespace std;

const int MAX_SIZE = 100;

// функция для генерации случайного порядка уникальных символов
void generate_random_order(char symbols[], int num_symbols) {
	for (int i = 0; i < num_symbols; ++i) {
		symbols[i] = 'a' + i;
	}

	random_shuffle(symbols, symbols + num_symbols);
}

 // функция для заполнения матрицы случайными символами
void fill_matrix_randomly(char matrix[MAX_SIZE][MAX_SIZE], char symbols[], int num_rows, int num_cols, int num_symbols) {
	for (int i = 0; i < num_symbols; ++i) {
		int row = rand() % num_rows;
		int col = rand() % num_cols;

		matrix[row][col] = symbols[i];
	}
}

 // функция для адаптации матрицы к виду 0 и 1
void adapt_matrix(char matrix[MAX_SIZE][MAX_SIZE], int num_rows, int num_cols) {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			if (matrix[i][j] == 'a') {
				matrix[i][j] = 1;
			}
			else {
				matrix[i][j] = 0;
			}
		}
	}
}

int main() {
	int num_rows, int num_cols, num_symbols, max_generations;

	try {
		while (true) {
			cout << "\nenter the number of matrix rows: ";
			if (!(cin >> num_rows)) {
				cin.clear();
				cin.ignore();
				cout << "error!\n";
				continue;
			}
			break;
		}
		while (true) {
			cout << "\nenter the number of matrix columns: ";
			if (!(cin >> num_cols)) {
				cin.clear();
				cin.ignore();
				cout << "error!\n";
				continue;
			}
			break;
		}
		while (true) {
			cout << "\nenter number of unique characters : ";
			if (!(cin >> num_symbols)) {
				cin.clear();
				cin.ignore();
				cout << "error!\n";
				continue;
			}
			break;
		}
	}
	catch (const exception& err) {
		cerr << "error: " << err.what() << endl;
	}

	// генерация случайного порядка уникальных символов
	char symbols[MAX_SIZE];
	generate_random_order(symbols, num_symbols);

	// вывод уникальных символов
	cout << "\nunique characters: \n";
	for (int i = 0; i < num_symbols; ++i) {
		cout << symbols[i] << " ";
	}
	cout << endl;

	// создание матрицы и заполнение случайными символами 
	char matrix[MAX_SIZE][MAX_SIZE] = { '0' };
	fill_matrix_randomly(matrix, symbols, num_rows, num_cols, num_symbols);

	// вывод начальной матрицы 
	cout << "\ndynamic two-dimensional array (matrix): \n";
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_rows; ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	// ввод макс числа поколений
	while (true) {
		cout << "\nenter max generations: ";
		if (!(cin >> max_generations)) {
			cin.clear();
			cin.ignore();
			cout << "error!";
			continue;
		}
		break;
	}

}

//первый вариант
//#include <iostream>
//#include <fstream>
//#include <cstring>
////разработка
//using namespace std;
//
//#ifndef GAME_OF_LIFE_H
//#define GAME_OF_LIFE_H
//
//const int SIZE = 21;
//const int MAX_LIFE_LEVEL = 12;
//
//void displayGeneration(int generation[SIZE][SIZE]) {
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//            if (generation[i][j] == 0) {
//                cout << ".";
//            }
//            else {
//                cout << char('0' + generation[i][j]);
//            }
//        }
//        cout << endl;
//    }
//}
//
//void generateNextGeneration(int current[SIZE][SIZE], int next[SIZE][SIZE]) {
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//            if (current[i][j] > 0 && current[i][j] < MAX_LIFE_LEVEL) {
//                int neighbors = 0;
//                for (int x = -1; x <= 1; ++x) {
//                    for (int y = -1; y <= 1; ++y) {
//                        int ni = i + x;
//                        int nj = j + y;
//                        if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE && !(x == 0 && y == 0)) {
//                            neighbors += (current[ni][nj] > 0 && current[ni][nj] < MAX_LIFE_LEVEL);
//                        }
//                    }
//                }
//
//                if (neighbors == 2 || neighbors == 3) {
//                    next[i][j] = current[i][j] + 1;
//                }
//                else {
//                    next[i][j] = 0;
//                }
//            }
//            else if (current[i][j] == 0) {
//                next[i][j] = 1;
//            }
//            else if (current[i][j] == MAX_LIFE_LEVEL) {
//                next[i][j] = 0;
//            }
//        }
//    }
//}
//
//int countLivingCells(int generation[SIZE][SIZE]) {
//    int count = 0;
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//            count += (generation[i][j] > 0 && generation[i][j] < MAX_LIFE_LEVEL);
//        }
//    }
//    return count;
//}
//
//void initializeGenerationFromFile(ifstream& file, int generation[SIZE][SIZE]) {
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//            char symbol;
//            file >> symbol;
//            if (symbol == 'X') {
//                generation[i][j] = 1;
//            }
//            else {
//                generation[i][j] = 0;
//            }
//        }
//    }
//}
//
//int main() {
//    ofstream workDat("work.dat");
//    if (!workDat.is_open()) {
//        cerr << "Error opening work.dat" << endl;
//        return 1;
//    }
//    // You can fill the work.dat file with necessary symbols here
//
//    ifstream workDatReader("work.dat");
//    if (!workDatReader.is_open()) {
//        cerr << "Error opening work.dat for reading" << endl;
//        return 1;
//    }
//
//    int currentGeneration[SIZE][SIZE];
//    int nextGeneration[SIZE][SIZE];
//
//    memset(currentGeneration, 0, sizeof(currentGeneration));
//    memset(nextGeneration, 0, sizeof(nextGeneration));
//
//    initializeGenerationFromFile(workDatReader, currentGeneration);
//    workDatReader.close();
//
//    int numGenerations;
//    cout << "Enter the number of generations: ";
//    if (!(cin >> numGenerations) || numGenerations <= 0) {
//        cerr << "Invalid input for the number of generations." << endl;
//        return 1;
//    }
//
//    for (int generationCount = 1; generationCount <= numGenerations; ++generationCount) {
//        cout << "Generation " << generationCount << endl;
//        displayGeneration(currentGeneration);
//
//        ofstream workOut("work.out");
//        if (!workOut.is_open()) {
//            cerr << "Error opening work.out" << endl;
//            return 1;
//        }
//
//        for (int i = 0; i < SIZE; ++i) {
//            for (int j = 0; j < SIZE; ++j) {
//                if (currentGeneration[i][j] == 1) {
//                    workOut << 'X';
//                }
//                else {
//                    workOut << '.';
//                }
//            }
//            workOut << endl;
//        }
//        workOut.close();
//
//        generateNextGeneration(currentGeneration, nextGeneration);
//
//        int livingCells = countLivingCells(nextGeneration);
//        cout << "Number of microorganisms in generation: " << livingCells << endl;
//
//        if (livingCells == 0) {
//            cout << "All microorganisms have died. The program is terminated." << endl;
//            break;
//        }
//
//        memcpy(currentGeneration, nextGeneration, sizeof(currentGeneration));
//    }
//
//    return 0;
//}
//
//#endif // GAME_OF_LIFE_H
