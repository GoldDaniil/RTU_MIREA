#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class GameOfLife {
public:
    GameOfLife(int size, int maxYears) : size(size), maxYears(maxYears) {
        srand(time(0));
        grid.resize(size, vector<int>(size, 0));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                grid[i][j] = rand() % 2;
            }
        }
    }

    void printGrid() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] == 0) {
                    //cout << "\033[47;90m  \033[0m"; // gray 
                    cout << "\033[42m  \033[0m"; // green 

                    //cout << "\033[47m  \033[0m"; // white
                }
                else {
                    //cout << "\033[41m  \033[0m"; // red 
                    cout << "\033[47m  \033[0m"; // white
                }
            }
            cout << endl;
        }
        cout << endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl << endl;
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
    void evolve() {
        vector<vector<int>> newGrid(size, vector<int>(size, 0));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int liveNeighbors = countLiveNeighbors(i, j);

                if (grid[i][j] > 0 && grid[i][j] < 12) {
                    // Microbe with life level 1 to 11
                    if (liveNeighbors == 2 || liveNeighbors == 3) {
                        newGrid[i][j] = grid[i][j] + 1;
                    }
                    else {
                        newGrid[i][j] = 0; // Microbe dies
                    }
                }
                else if (grid[i][j] == 0) {
                    // New microbe is born
                    newGrid[i][j] = 1;
                }
                else if (grid[i][j] == 12) {
                    // Microbe dies from old age
                    newGrid[i][j] = 0;
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

        // Exclude the current cell
        liveNeighbors -= grid[x][y];

        return liveNeighbors;
    }

    bool isGameOver() const {
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
    int maxYears;
    vector<vector<int>> grid;
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
