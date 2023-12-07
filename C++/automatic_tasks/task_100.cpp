#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <Windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

enum CellState { DEAD = 0, ALIVE = 1, MAX_AGE = 12 };

class GameOfLife {
public:
    GameOfLife(int size, int max_years, const vector<char>& symbols) : size(size), max_years(max_years), symbols(symbols) {
        srand(time(0));
        grid.resize(size, vector<int>(size, 0));
        initialize_grid_manually();
    }
   
    void initialize_grid_manually() {
        cout << "\nenter the initial state:" << endl;

        // Выводим строку символов для удобства пользователя
        for (char ch : symbols) {
            cout << ch << " ";
        }
        cout << endl;

        // Случайным образом выбираем один из символов и обновляем основную матрицу
        int random_symbol_index = rand() % symbols.size();
        selected_symbol = symbols[random_symbol_index];

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                grid[i][j] = (symbols[j] == selected_symbol) ? 1 : 0;
            }
        }

        cout << "\nselected symbol for adaptation: " << selected_symbol << endl << endl;
    }

    //void print_grid() const {
    //    for (int i = 0; i < size; ++i) {
    //        for (int j = 0; j < size; ++j) {
    //            if (grid[i][j] > 0) {
    //                // Зеленый цвет для живых клеток
    //                cout << "\033[42m  \033[0m";
    //            }
    //            else {
    //                cout << "\033[47;90m  \033[0m"; // gray 
    //            }
    //        }
    //        cout << endl;
    //    }
    //    cout << endl;

    //    for (int i = 0; i < size; ++i) {
    //        for (int j = 0; j < size; ++j) {
    //            cout << grid[i][j] << "  ";
    //        }

    //        cout << endl;
    //    }
    //    cout << endl;
    //}

    void print_grid() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] > 0) {
                    cout << "\033[42m  \033[0m"; // Green for alive cells
                }
                else {
                    cout << "\033[47;90m  \033[0m"; // Gray for dead cells
                }
            }
            cout << endl;
        }
        cout << endl;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << grid[i][j] << "  ";
            }

            cout << endl;
        }
        cout << endl;
    }

    

    void simulate_life() {
        for (int year = 1; year <= max_years; ++year) {
            cout << "generation " << year << ":" << endl;
            print_grid();
            evolve();

            if (is_game_over()) {
                cout << "\nGame over!\nAll microbes are dead!\n" << endl;
                break;
            }
        }
    }
    /*void simulate_life() {
        for (int year = 1; year <= max_years; ++year) {
            cout << "generation " << year << ":" << endl;
            print_grid();

            evolve();

            if (is_game_over()) {
                cout << "\nGame over!\nAll microbes are dead!\n" << endl;
                break;
            }
        }
    }*/


private:
    void evolve() {
        vector<vector<int>> new_grid(size, vector<int>(size, 0));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int neighbors = count_neighbors(grid, i, j);

                if (grid[i][j] == ALIVE) {
                    if (neighbors == 2 || neighbors == 3) {
                        new_grid[i][j] = ALIVE;
                    }
                }
                else {
                    if (neighbors == 3) {
                        new_grid[i][j] = ALIVE;
                    }
                }
            }
        }

        grid = new_grid;
    }

    int count_neighbors(const vector<vector<int>>& board, int x, int y) const {
        int live_neighbors = 0;

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newX = x + i;
                int newY = y + j;

                if ((i != 0 || j != 0) && (newX >= 0) && (newX < size) && (newY >= 0) && (newY < size)) {
                    live_neighbors += board[newX][newY];
                }
            }
        }

        return live_neighbors;
    }

    bool is_game_over() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] > 0) {
                    return false;
                }
            }
        }
        return true;
    }

    int size;
    int max_years;
    vector<vector<int>> grid;
    vector<char> symbols;
    char selected_symbol;
};

vector<char> generate_alphabet_symbols(int count) {
    vector<char> symbols;
    for (char ch = 'a'; ch < 'a' + count; ++ch) {
        symbols.push_back(ch);
    }
    return symbols;
}

int main() {
    const WORD textColor = 0xE;
    const WORD bgColor = 0x70;
    SetConsoleTextAttribute(console, textColor | (bgColor << 4));
    cout << "Welcome to the game of 'LIFE'!\n\n";
    SetConsoleTextAttribute(console, textColor);
    cout << "Once upon a time there were microbes. They lived happily ever after,\nbut there was one problem: after life there was always death comes.\nWe have the opportunity to look at the development of microbes with our own eyes!\n\n";
    SetConsoleTextAttribute(console, 15);

    int size, max_years;
    cout << "Enter matrix size: ";
    while (true) {
        if (!(cin >> size)) {
            cin.clear();
            cin.ignore();
            cout << "\nerror!\n\n";
            continue;
        }
        break;
    }

    int unique_symbol_count;
    cout << "Enter the number of unique symbols: ";
    while (true) {
        if (!(cin >> unique_symbol_count)) {
            cin.clear();
            cin.ignore();
            cout << "\nerror!\n\n";
            continue;
        }
        break;
    }

    vector<char> symbols = generate_alphabet_symbols(unique_symbol_count);

    cout << "Enter the maximum number of generations: ";
    while (true) {
        if (!(cin >> max_years)) {
            cin.clear();
            cin.ignore();
            cout << "\nerror!\n\n";
            continue;
        }
        break;
    }

    GameOfLife game(size, max_years, symbols);
    game.simulate_life();

    return 0;
}
