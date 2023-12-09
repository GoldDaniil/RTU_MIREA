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
int predatorPopulation = 100;
int herbivorePopulation = 300;
int grassPopulation = 400;
const double grassRegrowthRateSummer = 0.031; // Summer regrowth rate, e.g., 20%
const double grassRegrowthRateSpringFall = 0.0155; // Spring and fall regrowth rate, half of summer
const double grassRegrowthRateWinter = 0.0; // Winter regrowth rate, no regrowth

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
            if (grid[i][j] == grassSymbol) {
                std::cout << "\033[1;32m" << grid[i][j] << "\033[0m"; // Set color to green for grass
            }
            else {
                std::cout << grid[i][j];
            }
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
                int newI = i;
                int newJ = j;

                switch (direction) {
                case 0: // Move up
                    if (i > 0) {
                        newI = i - 1;
                    }
                    break;
                case 1: // Move down
                    if (i < screenHeight - 1) {
                        newI = i + 1;
                    }
                    break;
                case 2: // Move left
                    if (j > 0) {
                        newJ = j - 1;
                    }
                    break;
                case 3: // Move right
                    if (j < screenWidth - 1) {
                        newJ = j + 1;
                    }
                    break;
                }

                // Check if the new position is grass, and if so, revert the changes
                if (grid[newI][newJ] == grassSymbol) {
                    newI = i;
                    newJ = j;
                }

                grid[newI][newJ] = animalSymbol; // Update position
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
    for (int i = std::max(0, herbivoreX - 1); i < std::min(screenHeight, herbivoreX + 2); ++i) {
        for (int j = std::max(0, herbivoreY - 1); j < std::min(screenWidth, herbivoreY + 2); ++j) {
            if (grid[i][j] == grassSymbol && (i != herbivoreX || j != herbivoreY)) {
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

    placeRandomAnimals(grid, predatorSymbol, predatorPopulation);
    placeRandomAnimals(grid, herbivoreSymbol, herbivorePopulation);
    placeRandomGrass(grid, grassPopulation);

    int herbivoreCount = herbivorePopulation;
    int predatorCount = predatorPopulation;
    int deadHerbivoreCount = 0;
    int remainingGrassCount = grassPopulation;

    int steps = 0;
    int currentSeason = 0; // 0: Summer, 1: Spring, 2: Fall, 3: Winter

    while (steps < 24) {
        system(CLEAR_SCREEN);
        printGrid(grid, herbivoreCount, predatorCount, deadHerbivoreCount, remainingGrassCount);

        std::cout << "Step: " << steps + 1 << "/24 (Enter to continue)...";
        std::cin.ignore(); // Wait for Enter key

        moveRandomly(grid, predatorSymbol);
        moveRandomly(grid, herbivoreSymbol);

        // Herbivores eat grass after moving
        for (int i = 0; i < screenHeight; ++i) {
            for (int j = 0; j < screenWidth; ++j) {
                if (grid[i][j] == herbivoreSymbol) {
                    herbivoreEatGrass(grid, i, j, remainingGrassCount);
                }
            }
        }

        // Predators eat herbivores
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

        // Calculate regrowth of grass based on the current season
        double currentRegrowthRate;
        switch (currentSeason) {
        case 0: // Summer
            currentRegrowthRate = grassRegrowthRateSummer;
            break;
        case 1:
            currentRegrowthRate = grassRegrowthRateSpringFall;
            break;
        case 2:
            currentRegrowthRate = grassRegrowthRateSpringFall;
            break;
        case 3: // Winter
            currentRegrowthRate = grassRegrowthRateWinter;
            break;
        }

        int regrowthAmount = static_cast<int>(grassPopulation * currentRegrowthRate);
        placeRandomGrass(grid, regrowthAmount);

        // Recalculate counts
        herbivoreCount = herbivorePopulation - deadHerbivoreCount;
        predatorCount = predatorPopulation;
        remainingGrassCount += regrowthAmount;

        // Update season every 6 steps
        if ((steps + 1) % 6 == 0) {
            currentSeason = (currentSeason + 1) % 4;
        }

        ++steps;
    }


    return 0;
}
