#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<thread>
#include<Windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

const int rows = 20;
const int cols = 60;

void initialize_board(bool board[rows][cols]) {
    // инициализация доски случайным образом
   
    srand(time(nullptr));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            board[i][j] = rand() % 2 == 1;
        }

    }
    SetConsoleTextAttribute(console, 0x07);
}

void print_board(bool board[rows][cols]) {
    SetConsoleTextAttribute(console, 0x0f);
    // вывод текущего состояния доски
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
    // обновление доски в соответствии с правилами
    bool newBoard[rows][cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int neighbors = count_neighbors(board, i, j);
            newBoard[i][j] = (board[i][j] && (neighbors == 2 || neighbors == 3)) || (!board[i][j] && neighbors == 3);
        }
    }
    // копирование нового состояния обратно в оригинальную доску
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            board[i][j] = newBoard[i][j];
        }
    }
}

int main() {
    bool board[rows][cols];
    initialize_board(board);

    for (int generation = 0; generation < 100; ++generation) {
        SetConsoleTextAttribute(console, 0x0a);
        cout << " generation: " << generation << endl << endl << endl;
        print_board(board);
        update_board(board);
        this_thread::sleep_for(chrono::milliseconds(400));  // пауза между поколениями
        system("cls");  // очистка экрана 
        SetConsoleTextAttribute(console, 0x07);
    }
    return 0;
}
