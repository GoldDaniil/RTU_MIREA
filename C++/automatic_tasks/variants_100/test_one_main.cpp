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
