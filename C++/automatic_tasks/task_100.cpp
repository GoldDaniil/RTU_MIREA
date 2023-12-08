#include <iostream>            
#include <vector>              
#include <cstdlib>             
#include <ctime>               
#include <algorithm>           
#include <Windows.h>           

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

enum CellState { DEAD = 0, ALIVE = 1, MAX_AGE = 12 };    // перечисление возможных состояний ячейки

struct Cell {
    int state;    // состояние ячейки (мертвая или живая)
    int age;      // возраст ячейки

    Cell() : state(DEAD), age(0) {}    // конструктор для инициализации ячейки
};

class GameOfLife {
public:
    GameOfLife(int size, int max_years, const vector<char>& symbols)
        : size(size), max_years(max_years), symbols(symbols) {
        srand(time(0));    // генератор случайных чисел текущим временем
        grid.resize(size, vector<Cell>(size, Cell()));    // инициализация игровой сетки заданного размера
        initialize_grid_manually();    // инициализация игровой сетки вручную
    }

    void initialize_grid_manually() {
        cout << "\nunique symbols:\n";

        // вывод уникальных символов для удобства
        for (char ch : symbols) {
            cout << ch << " ";
        }
        cout << endl;

        // случайным образом выбираем один из символов и обновляем основной двумерный массив
        int random_symbol_index = rand() % symbols.size();
        selected_symbol = symbols[random_symbol_index];

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                grid[i][j].state = (symbols[j] == selected_symbol) ? ALIVE : DEAD;
            }
        }

        cout << "\nselected symbol for adaptation: " << selected_symbol << endl << endl;
    }

    void print_grid() const {
        cout << endl;

        // вывод текущего состояния игровой сетки в консоль
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j].state == ALIVE) {
                    cout << "\033[42m    \033[0m";    // зеленый цвет для живых клеток
                }
                else {
                    cout << "\033[47;90m    \033[0m"; // серый цвет для мертвых клеток
                }
            }
            cout << endl;
        }
        cout << endl;

        cout << endl << "age:" << endl;

        // вывод возраста живых клеток
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
                    cout << " 0 ";
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
            evolve();    // эволюция игры на один шаг

            if (is_game_over()) {
                cout << "\nGame over!\nAll microbes are dead!\n" << endl;
                break;
            }
        }
    }

private:
    void evolve() {
        vector<vector<Cell>> new_grid(size, vector<Cell>(size, Cell()));

        // процесс эволюции игры
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int neighbors = count_neighbors(grid, i, j);

                // проверка состояния текущей клетки (живая или мертвая)
                if (grid[i][j].state == ALIVE) {
                    // правила для живой клетки:
                    // 1. если у клетки 2 или 3 соседа, она остается живой, иначе она умирает
                    new_grid[i][j].state = (neighbors == 2 || neighbors == 3) ? ALIVE : DEAD;

                    // если клетка осталась живой, увеличиваем её возраст на 1
                    if (new_grid[i][j].state == ALIVE) {
                        new_grid[i][j].age = grid[i][j].age + 1;
                    }
                }
                else {
                    // правила для мертвой клетки:
                    // 2. если у мертвой клетки ровно 3 соседа, она оживает
                    if (neighbors == 3) {
                        new_grid[i][j].state = ALIVE;
                        new_grid[i][j].age = 1; // устанавливаем возраст в 1 для новой живой клетки
                    }
                }
            }
        }

        grid = new_grid;    // Обновление текущей игровой сетки
    }

    int count_neighbors(const vector<vector<Cell>>& board, int x, int y) const {
        int count = 0;

        // подсчет количества соседей для заданной клетки
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newX = x + i;
                int newY = y + j;
                //вычисляем новые координаты для проверки соседних клеток относительно текущей

                // пропустить проверку для текущей клетки (i=0, j=0) - так как не учитываем текущую клетку
                //  в подсчете живых соседей
                if ((i == 0) && (j == 0)) {
                    continue;
                }

                // проверка, находится ли сосед в пределах границ игровой сетки
                if ((newX >= 0) && (newX < size) && (newY >= 0) && (newY < size)) {
                    // если сосед жив - увеличиваем счетчик
                    count += board[newX][newY].state == ALIVE ? 1 : 0;
                }
            }
        }

        return count;
    }

    bool is_game_over() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j].state == ALIVE) {
                    return false; // если найдена хотя бы одна живая клетка - игра не завершена
                }
            }
        }
        return true; // если все клетки мертвы - то игра завершена
    }

    int size;                   // размер игровой сетки
    int max_years;              // максимальное количество поколений
    vector<vector<Cell>> grid;  // игровая сетка
    vector<char> symbols;       // уникальные символы для инициализации
    char selected_symbol;       // выбранный символ для адаптации
};

vector<char> generate_alphabet_symbols(int count) {
    vector<char> symbols;
    for (char ch = 'a'; ch < 'a' + count; ++ch) { //цикл - в котором переменная ch принимает 
        // значения от 'a' до 'a' + count - 1.
        symbols.push_back(ch); // добавление текущего символа в вектор
    }
    return symbols; // возврат вектора уникальных символов
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

    while (true) {
        // ввод размера матрицы
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

        // ввод количества уникальных символов
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
        // вызов функции generate_alphabet_symbols с аргументом unique_symbol_count - которая создает 
        // вектор символов алфавита от 'a' до 'a' + unique_symbol_count - 1
        // vector<char> symbols = ...: создает вектор symbols типа char и инициализирует его значениями -
        // возвращенными из функции generate_alphabet_symbols

        // ввод максимального числа поколений
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

        // создается объект игры и затем запускают симуляцию "Жизнь микроба(бактерий)" - 
        // выводя информацию о состоянии игры на каждом поколении
    }

    return 0;
}
