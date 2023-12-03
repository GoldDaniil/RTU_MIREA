// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes and namespace.


#include<iostream>
#include<algorithm>
#include<cstdlib>

using namespace std;

const int MAX_SIZE = 100;

void generate_random_order(char symbols[], int num_symbols) {
    for (int i = 0; i < num_symbols; ++i) {
        symbols[i] = 'a' + i;
    }

    random_shuffle(symbols, symbols + num_symbols);
}

void fill_matrix_randomly(char matrix[MAX_SIZE][MAX_SIZE], char symbols[], int num_rows, int num_cols, int num_symbols) {
    for (int i = 0; i < num_symbols; ++i) {
        int row = rand() % num_rows;
        int col = rand() % num_cols;

        matrix[row][col] = symbols[i];
    }
}

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
    int num_rows, num_cols, num_symbols, max_generations;

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
                cout << "Error!\n";
                continue;
            }
            break;
        }
        while (true) {
            cout << "\nenter the number of unique characters: ";
            if (!(cin >> num_symbols)) {
                cin.clear();
                cin.ignore();
                cout << "Error!\n";
                continue;
            }
            break;
        }
        while (true) {
            cout << "\nenter the maximum number of generations: ";
            if (!(cin >> max_generations)) {
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

    char symbols[MAX_SIZE];
    generate_random_order(symbols, num_symbols);

    cout << "\nunique characters: \n";
    for (int i = 0; i < num_symbols; ++i) {
        cout << symbols[i] << " ";
    }
    cout << endl;

    char matrix[MAX_SIZE][MAX_SIZE] = { '0' };
    fill_matrix_randomly(matrix, symbols, num_rows, num_cols, num_symbols);

    cout << "\ndynamic two-dimensional array (matrix): \n";
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    adapt_matrix(matrix, num_rows, num_cols);

    cout << "\nadapted dynamic two-dimensional array (matrix):\n";
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}


//#include<iostream>
//#include<algorithm>
//#include<cstdlib> // для использования rand()
//
//using namespace std;
//
//const int MAX_SIZE = 100;
//
//// функция для генерации случайного порядка уникальных символов
//void generate_random_order(char symbols[], int num_symbols) {
//	for (int i = 0; i < num_symbols; ++i) {
//		symbols[i] = 'a' + i;
//	}
//
//	random_shuffle(symbols, symbols + num_symbols);
//}
//
// // функция для заполнения матрицы случайными символами
//void fill_matrix_randomly(char matrix[MAX_SIZE][MAX_SIZE], char symbols[], int num_rows, int num_cols, int num_symbols) {
//	for (int i = 0; i < num_symbols; ++i) {
//		int row = rand() % num_rows;
//		int col = rand() % num_cols;
//
//		matrix[row][col] = symbols[i];
//	}
//}
//
// // функция для адаптации матрицы к виду 0 и 1
//void adapt_matrix(char matrix[MAX_SIZE][MAX_SIZE], int num_rows, int num_cols) {
//	for (int i = 0; i < num_rows; ++i) {
//		for (int j = 0; j < num_cols; ++j) {
//			if (matrix[i][j] == 'a') {
//				matrix[i][j] = 1;
//			}
//			else {
//				matrix[i][j] = 0;
//			}
//		}
//	}
//}
//
//int main() {
//	int num_rows, int num_cols, num_symbols, max_generations;
//
//	try {
//		while (true) {
//			cout << "\nenter the number of matrix rows: ";
//			if (!(cin >> num_rows)) {
//				cin.clear();
//				cin.ignore();
//				cout << "error!\n";
//				continue;
//			}
//			break;
//		}
//		while (true) {
//			cout << "\nenter the number of matrix columns: ";
//			if (!(cin >> num_cols)) {
//				cin.clear();
//				cin.ignore();
//				cout << "error!\n";
//				continue;
//			}
//			break;
//		}
//		while (true) {
//			cout << "\nenter number of unique characters : ";
//			if (!(cin >> num_symbols)) {
//				cin.clear();
//				cin.ignore();
//				cout << "error!\n";
//				continue;
//			}
//			break;
//		}
//	}
//	catch (const exception& err) {
//		cerr << "error: " << err.what() << endl;
//	}
//
//	// генерация случайного порядка уникальных символов
//	char symbols[MAX_SIZE];
//	generate_random_order(symbols, num_symbols);
//
//	// вывод уникальных символов
//	cout << "\nunique characters: \n";
//	for (int i = 0; i < num_symbols; ++i) {
//		cout << symbols[i] << " ";
//	}
//	cout << endl;
//
//	// создание матрицы и заполнение случайными символами 
//	char matrix[MAX_SIZE][MAX_SIZE] = { '0' };
//	fill_matrix_randomly(matrix, symbols, num_rows, num_cols, num_symbols);
//
//	// вывод начальной матрицы 
//	cout << "\ndynamic two-dimensional array (matrix): \n";
//	for (int i = 0; i < num_rows; ++i) {
//		for (int j = 0; j < num_rows; ++j) {
//			cout << matrix[i][j] << " ";
//		}
//		cout << endl;
//	}
//
//	// ввод макс числа поколений
//	cin >> max_generations;
//
//	// адаптация матрицы к виду 0 и 1
//	adapt_matrix(matrix, num_rows, num_cols);
//
//	// вывод адапт матрицы
//	cout << "\nAdapted dynamic two-dimensional array (matrix):\n";
//	for (int i = 0; i < num_rows; ++i) {
//		for (int j = 0; j < num_cols; ++j) {
//			cout << matrix[i][j] << " ";
//		}
//		cout << endl;
//	}
//	
//	return 0;
//}

