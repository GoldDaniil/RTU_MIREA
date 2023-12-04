#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include<algorithm>

using namespace std;

class GameOfLife {
public:
    GameOfLife(int size, int maxYears) : size(size), maxYears(maxYears) {
        srand(time(0));

        int numUniqueSymbols;
        cout << "Enter the number of unique symbols (English lowercase letters): ";
        cin >> numUniqueSymbols;

        generateUniqueSymbols(numUniqueSymbols); 

        grid.resize(size, vector<int>(size, 0));

        fillMatrixRandomly();
    }

    void printGrid() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    void simulateLife() {
        for (int year = 1; year <= maxYears; ++year) {
            cout << year << " year:" << endl;
            printGrid();
            cout << endl;

            evolve();

            if (isGameOver()) {
                cout << "\nGame over" << endl;
                break;
            }
        }
    }

private:
    void generateUniqueSymbols(int numSymbols) {
        uniqueSymbols.clear();
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            uniqueSymbols.insert(ch);
            if (uniqueSymbols.size() >= numSymbols) {
                break;
            }
        }
    }

    void fillMatrixRandomly() {
        // преобразование уникальных символов в вектор для удобства перемешивания
        vector<char> symbolsVector(uniqueSymbols.begin(), uniqueSymbols.end());

        // перемешивание символов случайным образом
        random_shuffle(symbolsVector.begin(), symbolsVector.end());

        // заполнение матрицы уникальными символами
        int symbolIndex = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                grid[i][j] = (symbolsVector[symbolIndex % symbolsVector.size()] == 'b') ? 1 : 0;
                ++symbolIndex;
            }
        }
    }

    void evolve() {
        vector<vector<int>> newGrid(size, vector<int>(size, 0));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int liveNeighbors = countLiveNeighbors(i, j);

                if (grid[i][j] == 1) {
                    // живая клетка
                    if (liveNeighbors == 2 || liveNeighbors == 3) {
                        newGrid[i][j] = 1;
                    }
                    // else - клетка умирает
                }
                else {
                    // мертвая клетка
                    if (liveNeighbors == 3) {
                        newGrid[i][j] = 1;
                    }
                    // else - клетка остается мертвой
                }
            }
        }

        grid = newGrid;
    }

    int countLiveNeighbors(int x, int y) const {
        int liveNeighbors = 0;

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newX = x + i;
                int newY = y + j;

                if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
                    liveNeighbors += grid[newX][newY];
                }
            }
        }

        // исключаем текущую клетку
        liveNeighbors -= grid[x][y];

        return liveNeighbors;
    }

    bool isGameOver() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] == 1) {
                    return false;
                }
            }
        }
        return true;
    }

    int size;
    int maxYears;
    vector<vector<int>> grid;
    set<char> uniqueSymbols;
};

int main() {
    int size, maxYears;

    cout << "Enter matrix size: ";
    cin >> size;

    cout << "Enter years: ";
    cin >> maxYears;

    GameOfLife game(size, maxYears);
    game.simulateLife();

    return 0;
}









#include <iostream>
//#include <algorithm>
//#include <cstdlib>
//#include <vector>
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
//    char new_matrix[MAX_SIZE][MAX_SIZE] = { 0 };
//
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            int live_neighbors = 0;
//
//            for (int ni = i - 1; ni <= i + 1; ++ni) {
//                for (int nj = j - 1; nj <= j + 1; ++nj) {
//                    if (ni >= 0 && ni < order && nj >= 0 && nj < order && !(ni == i && nj == j)) {
//                        live_neighbors += (matrix[ni][nj] == selected_symbol) ? 1 : 0;
//                    }
//                }
//            }
//
//            if (matrix[i][j] == selected_symbol) {
//                new_matrix[i][j] = (live_neighbors == 2 || live_neighbors == 3) ? selected_symbol : '0';
//            }
//            else {
//                new_matrix[i][j] = (live_neighbors == 3) ? selected_symbol : '0';
//            }
//        }
//    }
//
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
//void evolve(char matrix[MAX_SIZE][MAX_SIZE], int order) {
//    char new_matrix[MAX_SIZE][MAX_SIZE] = { 0 };
//
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            int live_neighbors = 0;
//
//            for (int ni = i - 1; ni <= i + 1; ++ni) {
//                for (int nj = j - 1; nj <= j + 1; ++nj) {
//                    if (ni >= 0 && ni < order && nj >= 0 && nj < order && !(ni == i && nj == j)) {
//                        live_neighbors += (matrix[ni][nj] > '0') ? 1 : 0;
//                    }
//                }
//            }
//
//            if (matrix[i][j] > '0' && matrix[i][j] < '9') {
//                if (live_neighbors == 2 || live_neighbors == 3) {
//                    new_matrix[i][j] = matrix[i][j] + 1;
//                }
//                else {
//                    new_matrix[i][j] = '0';
//                }
//            }
//            else if (matrix[i][j] == '0') {
//                new_matrix[i][j] = '1';
//            }
//            else if (matrix[i][j] == '9') {
//                new_matrix[i][j] = '0';
//            }
//        }
//    }
//
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < order; ++j) {
//            matrix[i][j] = new_matrix[i][j];
//        }
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
//        return 1;
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
//    char selected_symbol = symbols[rand() % num_symbols];
//
//    cout << "\nselected Symbol for Adaptation: " << selected_symbol << endl;
//
//    for (int generation = 1; generation <= max_generations; ++generation) {
//        adapt_matrix(matrix, order, selected_symbol);
//        evolve(matrix, order);
//
//        cout << "\ngeneration " << generation << ":\n";
//        print_matrix(matrix, order);
//    }
//
//    return 0;
//}

