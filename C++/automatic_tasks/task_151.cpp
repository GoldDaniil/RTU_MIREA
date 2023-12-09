#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

const char predatorSymbol = 'P';
const char herbivoreSymbol = 'H';
const char grassSymbol = '#';
const int screenWidth = 180;
const int screenHeight = 40;

void initializeGrid(char grid[][screenWidth]) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            grid[i][j] = ' ';
        }
    }
}

void printGrid(const char grid[][screenWidth], int herbivoreCount, int predatorCount, int deadHerbivoreCount, int remainingGrassCount) {
    std::cout << "Herbivores: " << herbivoreCount
        << " | Predators: " << predatorCount
        << " | Dead Herbivores: " << deadHerbivoreCount
        << " | Remaining Grass: " << remainingGrassCount << std::endl << std::endl << std::endl << std::endl;

    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}

void placeRandomAnimals(char grid[][screenWidth], char animalSymbol, int population) {
    for (int i = 0; i < population; ++i) {
        int x = rand() % screenHeight;
        int y = rand() % screenWidth;
        grid[x][y] = animalSymbol;
    }
}

void placeRandomGrass(char grid[][screenWidth], int population) {
    for (int i = 0; i < population; ++i) {
        int x = rand() % screenHeight;
        int y = rand() % screenWidth;
        grid[x][y] = grassSymbol;
    }
}

void moveRandomly(char grid[][screenWidth], char animalSymbol) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j] == animalSymbol) {
                grid[i][j] = ' '; // Clear current position

                // Move in a random direction
                int direction = rand() % 4;
                switch (direction) {
                case 0: // Move up
                    if (i > 0) {
                        --i;
                    }
                    break;
                case 1: // Move down
                    if (i < screenHeight - 1) {
                        ++i;
                    }
                    break;
                case 2: // Move left
                    if (j > 0) {
                        --j;
                    }
                    break;
                case 3: // Move right
                    if (j < screenWidth - 1) {
                        ++j;
                    }
                    break;
                }

                grid[i][j] = animalSymbol; // Update position
            }
        }
    }
}

void eatGrass(char grid[][screenWidth], int x, int y, int& remainingGrassCount) {
    grid[x][y] = ' '; // Clear grass
    --remainingGrassCount;
}

bool isAdjacent(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1;
}

void herbivoreEatGrass(char grid[][screenWidth], int herbivoreX, int herbivoreY, int& remainingGrassCount) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j] == grassSymbol && isAdjacent(i, j, herbivoreX, herbivoreY)) {
                eatGrass(grid, i, j, remainingGrassCount);
            }
        }
    }
}

void predatorEatHerbivore(char grid[][screenWidth], int predatorX, int predatorY, int herbivoreX, int herbivoreY, int& deadHerbivoreCount) {
    if (isAdjacent(predatorX, predatorY, herbivoreX, herbivoreY)) {
        grid[herbivoreX][herbivoreY] = ' '; // Clear herbivore
        ++deadHerbivoreCount;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    char grid[screenHeight][screenWidth];
    initializeGrid(grid);

    int predatorPopulation = 60;
    int herbivorePopulation = 40;
    int grassPopulation = 200;

    placeRandomAnimals(grid, predatorSymbol, predatorPopulation);
    placeRandomAnimals(grid, herbivoreSymbol, herbivorePopulation);
    placeRandomGrass(grid, grassPopulation);

    int herbivoreCount = herbivorePopulation;
    int predatorCount = predatorPopulation;
    int deadHerbivoreCount = 0;
    int remainingGrassCount = grassPopulation;

    while (true) {
        system(CLEAR_SCREEN);
        printGrid(grid, herbivoreCount, predatorCount, deadHerbivoreCount, remainingGrassCount);

        std::cout << "Press Enter to move animals...";
        std::cin.ignore(); // Wait for Enter key

        moveRandomly(grid, predatorSymbol);
        moveRandomly(grid, herbivoreSymbol);
        herbivoreEatGrass(grid, 0, 0, remainingGrassCount); // Assuming there is only one herbivore at position (0, 0)

        for (int i = 0; i < screenHeight; ++i) {
            for (int j = 0; j < screenWidth; ++j) {
                if (grid[i][j] == predatorSymbol) {
                    for (int k = 0; k < screenHeight; ++k) {
                        for (int l = 0; l < screenWidth; ++l) {
                            if (grid[k][l] == herbivoreSymbol) {
                                predatorEatHerbivore(grid, i, j, k, l, deadHerbivoreCount);
                            }
                        }
                    }
                }
            }
        }

        // Recalculate counts
        herbivoreCount = herbivorePopulation - deadHerbivoreCount;
        predatorCount = predatorPopulation;
    }

    return 0;
}
