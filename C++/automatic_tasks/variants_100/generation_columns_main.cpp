#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <Windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

vector<char> generate_alphabet_symbols(int count);

enum CellState { DEAD = 0, ALIVE = 1, MAX_AGE = 12 };

struct Cell {
    int state;
    int age;

    Cell() : state(DEAD), age(0) {}
};

class GameOfLife {
public:
    GameOfLife(int size, int max_years, int unique_symbols)
        : size(size), max_years(max_years), unique_symbols(unique_symbols) {
        srand(time(0));
        symbols = generate_alphabet_symbols(unique_symbols);
        grid.resize(size, vector<Cell>(size, Cell()));
        initialize_grid_manually();
    }

    void initialize_grid_manually() {
        cout << "\nunique symbols:\n";

        for (char ch : symbols) {
            cout << ch << " ";
        }
        cout << endl;

        selected_symbol = symbols[0];

        cout << "\nselected symbol for adaptation: " << selected_symbol << endl << endl;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                grid[i][j].state = (j % symbols.size() == 0) ? ALIVE : DEAD;
            }
        }
    }

    void print_grid() const {
        cout << endl;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j].state == ALIVE) {
                    cout << "\033[42m    \033[0m";
                }
                else {
                    cout << "\033[47;90m    \033[0m";
                }
            }
            cout << endl;
        }
        cout << endl;

        cout << endl << "age:" << endl;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j].state == ALIVE) {
                    if (grid[i][j].age > 0) {
                        cout << " " << grid[i][j].age << " ";
                    }
                    else {
                        cout << " 1 ";
                    }
                }
                else {
                    cout << " . ";
                }
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

private:
    void evolve() {
        vector<vector<Cell>> new_grid(size, vector<Cell>(size, Cell()));

        for (int i = 0; size_t(i) < size; ++i) {
            for (int j = 0; size_t(j) < size; ++j) {
                int neighbors = count_neighbors(i, j);

                if (grid[i][j].state == 1) {
                    if (neighbors == 2 || neighbors == 3) {
                        new_grid[i][j].state = 1;
                        new_grid[i][j].age = grid[i][j].age + 1;

                        if (new_grid[i][j].age >= 12) {
                            new_grid[i][j].state = 0;
                            new_grid[i][j].age = 0;
                        }
                    }
                }
                else {
                    if (neighbors == 3) {
                        new_grid[i][j].state = 1;
                        new_grid[i][j].age = 1;
                    }
                }
            }
        }

        grid = new_grid;
    }

    int count_neighbors(int x, int y) const {
        int count = 0;

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newX = x + i;
                int newY = y + j;

                if ((i == 0) && (j == 0)) {
                    continue;
                }

                if ((newX >= 0) && (newX < size) && (newY >= 0) && (newY < size)) {
                    count += grid[newX][newY].state == ALIVE ? 1 : 0;
                }
            }
        }

        return count;
    }

    bool is_game_over() const {
        for (int i = 0; size_t(i) < size; ++i) {
            for (int j = 0; size_t(j) < size; ++j) {
                if (grid[i][j].state == ALIVE) {
                    return false;
                }
            }
        }
        return true;
    }

    int size;
    int max_years;
    int unique_symbols;
    vector<vector<Cell>> grid;
    vector<char> symbols;
    char selected_symbol;
};

vector<char> generate_alphabet_symbols(int count) {
    vector<char> symbols;
    for (char ch = 'a'; size_t(symbols.size()) < count; ++ch) {
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

    int size, max_years, unique_symbols;

    while (true) {
        // ввод размера матрицы
        cout << "Enter matrix size: ";
        while (true) {
            if (!(cin >> size)) {
                cin.clear();
                cin.ignore();
                cout << "\nerror! Invalid input. Please enter a valid number.\n\n";
                continue;
            }
            break;
        }

        // ввод количества уникальных символов
        cout << "Enter the number of unique symbols: ";
        while (true) {
            if (!(cin >> unique_symbols)) {
                cin.clear();
                cin.ignore();
                cout << "\nerror! Invalid input. Please enter a valid number.\n\n";
                continue;
            }
            break;
        }

        // ввод максимального числа поколений
        cout << "Enter the maximum number of generations: ";
        while (true) {
            if (!(cin >> max_years)) {
                cin.clear();
                cin.ignore();
                cout << "\nerror! Invalid input. Please enter a valid number.\n\n";
                continue;
            }
            break;
        }

        GameOfLife game(size, max_years, unique_symbols);
        game.simulate_life();

        // создается объект игры и затем запускают симуляцию "Жизнь микроба(бактерий)" - 
        // выводя информацию о состоянии игры на каждом поколении

        char playAgain;
        cout << "do you want to play again? (y/n): ";
        cin >> playAgain;

        if (playAgain != 'y' && playAgain != 'Y') {
            break; // Exit the loop if the user doesn't want to play again
        }
    }

    return 0;
}
