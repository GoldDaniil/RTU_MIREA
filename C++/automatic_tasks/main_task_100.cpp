// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes and namespace.

#include<iostream>
#include<algorithm>
#include<cstdlib>

using namespace std;

const int MAX_SIZE = 100;

void generate_unique_symbols(char symbols[], int num_symbols) {
    for (int i = 0; i < num_symbols; ++i) {
        symbols[i] = 'a' + i;
    }
}

void fill_matrix_randomly(char matrix[MAX_SIZE][MAX_SIZE], char symbols[], int order, int num_symbols) {
    random_shuffle(symbols, symbols + num_symbols);
    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < order; ++j) {
            matrix[i][j] = symbols[j];
        }
    }
}

void adapt_matrix(char matrix[MAX_SIZE][MAX_SIZE], int order, char selected_symbol) {
    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < order; ++j) {
            matrix[i][j] = (matrix[i][j] == selected_symbol) ? 1 : 0;
        }
    }
}

int main() {
    int order, num_symbols, max_generations;

    try {
        while (true) {
            cout << "\nEnter the order of the matrix (2, 3, or 4): ";
            if (!(cin >> order) || (order < 2 || order > 4)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Please enter 2, 3, or 4.\n";
                continue;
            }
            break;
        }
        while (true) {
            cout << "\nEnter the number of unique characters: ";
            if (!(cin >> num_symbols) || num_symbols > 26) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Please enter a valid number of characters (up to 26).\n";
                continue;
            }
            break;
        }
        while (true) {
            cout << "\nEnter the maximum number of generations: ";
            if (!(cin >> max_generations)) {
                cin.clear();
                cin.ignore();
                cout << "Error!\n";
                continue;
            }
            break;
        }
    }
    catch (const exception& err) {
        cerr << "Error: " << err.what() << endl;
        return 1; // Exit with an error code
    }

    char symbols[MAX_SIZE];
    generate_unique_symbols(symbols, num_symbols);

    cout << "\nUnique characters: \n";
    for (int i = 0; i < num_symbols; ++i) {
        cout << symbols[i] << " ";
    }
    cout << endl;

    char matrix[MAX_SIZE][MAX_SIZE] = { 0 }; // Initialize matrix with 0
    fill_matrix_randomly(matrix, symbols, order, num_symbols);

    cout << "\nDynamic two-dimensional array (matrix): \n";
    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < order; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Randomly select a symbol from the generated unique symbols
    char selected_symbol = symbols[rand() % num_symbols];

    cout << "\nSelected Symbol for Adaptation: " << selected_symbol << endl;

    adapt_matrix(matrix, order, selected_symbol);

    cout << "\nAdapted dynamic two-dimensional array (matrix):\n";
    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < order; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}



//#include<iostream>
//#include<algorithm>
//#include<cstdlib>
//
//using namespace std;
//
//const int MAX_SIZE = 100;
//
//void generate_unique_symbols(char symbols[], int num_symbols) {
//    for (int i = 0; i < num_symbols; ++i) {
//        symbols[i] = 'a' + i;
//    }
//}
//
//void fill_matrix_randomly(char matrix[MAX_SIZE][MAX_SIZE], char symbols[], int order, int num_symbols) {
//    for (int i = 0; i < order; ++i) {
//        random_shuffle(symbols, symbols + num_symbols);
//        for (int j = 0; j < order; ++j) {
//            matrix[i][j] = symbols[j];
//        }
//    }
//}
//
//void adapt_matrix(char matrix[MAX_SIZE][MAX_SIZE], int order, char selected_symbol) {
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            matrix[i][j] = (matrix[i][j] == selected_symbol) ? 1 : 0;
//        }
//    }
//}
//
//int main() {
//    int order, num_symbols, max_generations;
//
//    try {
//        while (true) {
//            cout << "\nEnter the order of the matrix (2, 3, or 4): ";
//            if (!(cin >> order) || (order < 2 || order > 4)) {
//                cin.clear();
//                cin.ignore();
//                cout << "Invalid input. Please enter 2, 3, or 4.\n";
//                continue;
//            }
//            break;
//        }
//        while (true) {
//            cout << "\nEnter the number of unique characters: ";
//            if (!(cin >> num_symbols) || num_symbols > 26) {
//                cin.clear();
//                cin.ignore();
//                cout << "Invalid input. Please enter a valid number of characters (up to 26).\n";
//                continue;
//            }
//            break;
//        }
//        while (true) {
//            cout << "\nEnter the maximum number of generations: ";
//            if (!(cin >> max_generations)) {
//                cin.clear();
//                cin.ignore();
//                cout << "Error!\n";
//                continue;
//            }
//            break;
//        }
//    }
//    catch (const exception& err) {
//        cerr << "Error: " << err.what() << endl;
//        return 1; // Exit with an error code
//    }
//
//    char symbols[MAX_SIZE];
//    generate_unique_symbols(symbols, num_symbols);
//
//    cout << "\nUnique characters: \n";
//    for (int i = 0; i < num_symbols; ++i) {
//        cout << symbols[i] << " ";
//    }
//    cout << endl;
//
//    char matrix[MAX_SIZE][MAX_SIZE] = { 0 }; // Initialize matrix with 0
//    fill_matrix_randomly(matrix, symbols, order, num_symbols);
//
//    cout << "\nDynamic two-dimensional array (matrix): \n";
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            cout << matrix[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//    // Randomly select a symbol from the generated unique symbols
//    char selected_symbol = symbols[rand() % num_symbols];
//
//    cout << "\nSelected Symbol for Adaptation: " << selected_symbol << endl;
//
//    adapt_matrix(matrix, order, selected_symbol);
//
//    cout << "\nAdapted dynamic two-dimensional array (matrix):\n";
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            cout << matrix[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//    return 0;
////}



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

