// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes and namespace.

#include <iostream>
#include <algorithm>
#include <cstdlib>

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
    char new_matrix[MAX_SIZE][MAX_SIZE] = { 0 };

    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < order; ++j) {
            int live_neighbors = 0;

            for (int ni = i - 1; ni <= i + 1; ++ni) {
                for (int nj = j - 1; nj <= j + 1; ++nj) {
                    if (ni >= 0 && ni < order && nj >= 0 && nj < order && !(ni == i && nj == j)) {
                        live_neighbors += (matrix[ni][nj] == selected_symbol) ? 1 : 0;
                    }
                }
            }

            if (matrix[i][j] == selected_symbol) {
                new_matrix[i][j] = (live_neighbors == 2 || live_neighbors == 3) ? selected_symbol : '0';
            }
            else {
                new_matrix[i][j] = (live_neighbors == 3) ? selected_symbol : '0';
            }
        }
    }

    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < order; ++j) {
            matrix[i][j] = new_matrix[i][j];
        }
    }
}

void print_matrix(char matrix[MAX_SIZE][MAX_SIZE], int order) {
    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < order; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int order, num_symbols, max_generations;

    try {
        while (true) {
            cout << "\nenter the order of the matrix (2, 3, or 4): ";
            if (!(cin >> order) || (order < 2 || order > 4)) {
                cin.clear();
                cin.ignore();
                cout << "error!\n";
                continue;
            }
            break;
        }
        while (true) {
            cout << "\nenter the number of unique characters: ";
            if (!(cin >> num_symbols) || num_symbols > 26) {
                cin.clear();
                cin.ignore();
                cout << "error!\n";
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
        return 1; 
    }

    char symbols[MAX_SIZE];
    generate_unique_symbols(symbols, num_symbols);

    cout << "\nunique characters: \n";
    for (int i = 0; i < num_symbols; ++i) {
        cout << symbols[i] << " ";
    }
    cout << endl;

    char matrix[MAX_SIZE][MAX_SIZE] = { 0 };
    fill_matrix_randomly(matrix, symbols, order, num_symbols);

    cout << "\ninitial two-dimensional array (matrix): \n";
    print_matrix(matrix, order);

    char selected_symbol = symbols[rand() % num_symbols];

    cout << "\nselected Symbol for Adaptation: " << selected_symbol << endl;

    for (int generation = 1; generation <= max_generations; ++generation) {
        adapt_matrix(matrix, order, selected_symbol);

        cout << "\ngeneration " << generation << ":\n";
        print_matrix(matrix, order);
    }

    return 0;
}


////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

//#include <iostream>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//
//class GameOfLife {
//public:
//    GameOfLife(int size, int maxYears) : size(size), maxYears(maxYears) {
//        // Инициализация матрицы случайными значениями 0 и 1
//        srand(time(0));
//        grid.resize(size, std::vector<int>(size, 0));
//        for (int i = 0; i < size; ++i) {
//            for (int j = 0; j < size; ++j) {
//                grid[i][j] = rand() % 2;
//            }
//        }
//    }
//
//    void printGrid() const {
//        for (int i = 0; i < size; ++i) {
//            for (int j = 0; j < size; ++j) {
//                std::cout << grid[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
//    }
//
//    void simulateLife() {
//        for (int year = 1; year <= maxYears; ++year) {
//            std::cout << year << " год:" << std::endl;
//            printGrid();
//            std::cout << std::endl;
//
//            evolve();
//        }
//    }
//
//private:
//    void evolve() {
//        std::vector<std::vector<int>> newGrid(size, std::vector<int>(size, 0));
//
//        for (int i = 0; i < size; ++i) {
//            for (int j = 0; j < size; ++j) {
//                int liveNeighbors = countLiveNeighbors(i, j);
//
//                if (grid[i][j] == 1) {
//                    // Живая клетка
//                    if (liveNeighbors == 2 || liveNeighbors == 3) {
//                        newGrid[i][j] = 1;
//                    }
//                    else {
//                        newGrid[i][j] = 0;
//                    }
//                }
//                else {
//                    // Мертвая клетка
//                    if (liveNeighbors == 3) {
//                        newGrid[i][j] = 1;
//                    }
//                }
//            }
//        }
//
//        grid = newGrid;
//    }
//
//    int countLiveNeighbors(int x, int y) const {
//        int liveNeighbors = 0;
//
//        for (int i = -1; i <= 1; ++i) {
//            for (int j = -1; j <= 1; ++j) {
//                int newX = x + i;
//                int newY = y + j;
//
//                if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
//                    liveNeighbors += grid[newX][newY];
//                }
//            }
//        }
//
//        // Исключаем текущую клетку
//        liveNeighbors -= grid[x][y];
//
//        return liveNeighbors;
//    }
//
//    int size;
//    int maxYears;
//    std::vector<std::vector<int>> grid;
//};
//
//int main() {
//    int size, maxYears;
//
//    std::cout << "enter size matrix ";
//    std::cin >> size;
//
//    std::cout << "enter years: ";
//    std::cin >> maxYears;
//
//    GameOfLife game(size, maxYears);
//    game.simulateLife();
//
//    return 0;
//}


////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////


//
//
//
//
//
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
//    random_shuffle(symbols, symbols + num_symbols);
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            matrix[i][j] = symbols[j];
//        }
//    }
//}
//
//void adapt_matrix(char matrix[MAX_SIZE][MAX_SIZE], int order, char selected_symbol) {
//    int neighbors[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
//    char new_matrix[MAX_SIZE][MAX_SIZE] = { 0 };
//
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            int live_neighbors = 0;
//
//            // проверяем соседей
//            for (int k = 0; k < 12; ++k) {
//                int ni = (i + (k % 3) - 1 + order) % order; // соседний индекс по строкам 
//                int nj = (j + (k / 3) - 1 + order) % order; // соседний индекс по столбцам 
//
//                live_neighbors += (matrix[ni][nj] == selected_symbol) ? 1 : 0;
//            }
//
//            // вносим правила игры про жизнь клетки
//            if (matrix[i][j] == selected_symbol) {
//                new_matrix[i][j] = (live_neighbors == 2 || live_neighbors == 3) ? selected_symbol : '0';
//            }
//            else {
//                new_matrix[i][j] = (live_neighbors == 3) ? selected_symbol : '0';
//            }
//        }
//    }
//
//    // копируем
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            matrix[i][j] = new_matrix[i][j];
//        }
//    }
//}
//
//void print_matrix(char matrix[MAX_SIZE][MAX_SIZE], int order) {
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            cout << matrix[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
//int main() {
//    int order, num_symbols, max_generations;
//
//    try {
//        while (true) {
//            cout << "\nenter the order of the matrix (2, 3, or 4): ";
//            if (!(cin >> order) || (order < 2 || order > 4)) {
//                cin.clear();
//                cin.ignore();
//                cout << "error!\n";
//                continue;
//            }
//            break;
//        }
//        while (true) {
//            cout << "\nenter the number of unique characters: ";
//            if (!(cin >> num_symbols) || num_symbols > 26) {
//                cin.clear();
//                cin.ignore();
//                cout << "error!\n";
//                continue;
//            }
//            break;
//        }
//        while (true) {
//            cout << "\nenter the maximum number of generations: ";
//            if (!(cin >> max_generations)) {
//                cin.clear();
//                cin.ignore();
//                cout << "error!\n";
//                continue;
//            }
//            break;
//        }
//    }
//    catch (const exception& err) {
//        cerr << "error: " << err.what() << endl;
//        return 1; // Exit with an error code
//    }
//
//    char symbols[MAX_SIZE];
//    generate_unique_symbols(symbols, num_symbols);
//
//    cout << "\nunique characters: \n";
//    for (int i = 0; i < num_symbols; ++i) {
//        cout << symbols[i] << " ";
//    }
//    cout << endl;
//
//    char matrix[MAX_SIZE][MAX_SIZE] = { 0 };
//    fill_matrix_randomly(matrix, symbols, order, num_symbols);
//
//    cout << "\ninitial two-dimensional array (matrix): \n";
//    print_matrix(matrix, order);
//
//    // рандомно выбираем уникальный символ для генерации
//    char selected_symbol = symbols[rand() % num_symbols];
//
//    cout << "\nselected Symbol for Adaptation: " << selected_symbol << endl;
//
//    for (int generation = 1; generation <= max_generations; ++generation) {
//        adapt_matrix(matrix, order, selected_symbol);
//
//        cout << "\ngeneration " << generation << ":\n";
//        print_matrix(matrix, order);
//    }
//
//    return 0;
//}



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

