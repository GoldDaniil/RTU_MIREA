// The code uses the snake_case naming style for functions and variables.
// CamelCase is used for classes and namespace.

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<thread>
#include<Windows.h>

using namespace std;

const int rows = 30;
const int cols = 60;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void initialize_board(bool board[rows][cols]) {
    // первый столбец полностью заполнен единицами
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            board[i][j] = (j == 0) ? 1 : 0;
        }
    }
}

void print_board(bool board[rows][cols]) {
    SetConsoleTextAttribute(console, 0x0f);
    // вывод текущего массива
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j]) {
                cout << "\033[32m*\033[0m";
            }
            else {
                cout << "  ";
            }
            cout << ' ';
        }
        cout << endl;
    }
}

int count_neighbors(bool board[rows][cols], int x, int y) {
    // подсчет количества живых соседей
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int nx = x + i;
            int ny = y + j;

            // исключение текущей клетки и проверка границ
            if ((i != 0 || j != 0) && (nx >= 0) && (ny >= 0) && (nx < rows) && (ny < cols)) {
                count += board[nx][ny];
            }
        }
    }
    return count;
}

void update_board(bool board[rows][cols]) {
    // обновление массива
    bool newBoard[rows][cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int neighbors = count_neighbors(board, i, j);
            newBoard[i][j] = (board[i][j] && (neighbors == 2 || neighbors == 3)) || (!board[i][j] && neighbors == 3);
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            board[i][j] = newBoard[i][j];
        }
    }
}

int main() {
    bool board[rows][cols];
    initialize_board(board);

    int generations;
    cout << "generations: ";
    cin >> generations;

    for (int generation = 0; generation < generations; ++generation) {
        cout << "generations " << generation + 1 << ":" << endl;
        print_board(board);
        cout << endl;

        update_board(board);
        this_thread::sleep_for(chrono::milliseconds(700));
        system("cls");
    }

    return 0;
}
