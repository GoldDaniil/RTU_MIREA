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
