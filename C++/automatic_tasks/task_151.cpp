#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

const char predatorSymbolYoung = 'p';
const char predatorSymbolOld = 'P';
const char herbivoreSymbolYoung = 'h';
const char herbivoreSymbolOld = 'H';
const char grassSymbol = '#';
const int screenWidth = 180;
const int screenHeight = 40;
int predatorPopulation = 100;
int herbivorePopulation = 300;
int grassPopulation = 400;
const double grassRegrowthRateSummer = 0.031; // Summer regrowth rate, e.g., 20%
const double grassRegrowthRateSpringFall = 0.0155; // Spring and fall regrowth rate, half of summer
const double grassRegrowthRateWinter = 0.0; // Winter regrowth rate, no regrowth

struct Animal {
    char symbol;
    int age;
};

void initializeGrid(Animal grid[][screenWidth]) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            grid[i][j].symbol = ' ';
            grid[i][j].age = 0;
        }
    }
}

void printGrid(const Animal grid[][screenWidth], int herbivoreCount, int predatorCount, int deadHerbivoreCount, int remainingGrassCount, int currentStep, int currentSeason) {
    std::cout << "Herbivores: " << herbivoreCount
        << " | Predators: " << predatorCount
        << " | Dead Herbivores: " << deadHerbivoreCount
        << " | Remaining Grass: " << remainingGrassCount
        << " | Step: " << currentStep + 1
        << " | Season: ";

    switch (currentSeason) {
    case 0:
        std::cout << "Summer";
        break;
    case 1:
        std::cout << "Autumn";
        break;
    case 2:
        std::cout << "Winter";
        break;
    case 3:
        std::cout << "Spring";
        break;
    default:
        std::cout << "Spring";
        break;
    }

    std::cout << std::endl << std::endl << std::endl;

    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == grassSymbol) {
                std::cout << "\033[1;32m" << grid[i][j].symbol << "\033[0m"; // Set color to green for grass
            }
            else {
                std::cout << grid[i][j].symbol;
            }
        }
        std::cout << std::endl;
    }
}

void placeRandomAnimals(Animal grid[][screenWidth], char animalSymbol, int population) {
    for (int i = 0; i < population; ++i) {
        int x = rand() % screenHeight;
        int y = rand() % screenWidth;
        grid[x][y].symbol = animalSymbol;
        grid[x][y].age = rand() % 20 + 1; // Set age randomly between 1 and 20
    }
}

void placeRandomGrass(Animal grid[][screenWidth], int population) {
    for (int i = 0; i < population; ++i) {
        int x = rand() % screenHeight;
        int y = rand() % screenWidth;
        grid[x][y].symbol = grassSymbol;
        grid[x][y].age = 0; // Grass age is irrelevant, set to 0
    }
}

void moveRandomly(Animal grid[][screenWidth], char animalSymbol) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == animalSymbol) {
                grid[i][j].symbol = ' '; // Clear current position

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
                if (grid[newI][newJ].symbol == grassSymbol) {
                    newI = i;
                    newJ = j;
                }

                grid[newI][newJ].symbol = animalSymbol; // Update position
                grid[newI][newJ].age = grid[i][j].age + 1; // Increment age
            }
        }
    }
}

void eatGrass(Animal grid[][screenWidth], int x, int y, int& remainingGrassCount) {
    grid[x][y].symbol = ' '; // Clear grass
    --remainingGrassCount;
}

bool isAdjacent(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1;
}

void herbivoreEatGrass(Animal grid[][screenWidth], int herbivoreX, int herbivoreY, int& remainingGrassCount) {
    for (int i = std::max(0, herbivoreX - 1); i < std::min(screenHeight, herbivoreX + 2); ++i) {
        for (int j = std::max(0, herbivoreY - 1); j < std::min(screenWidth, herbivoreY + 2); ++j) {
            if (grid[i][j].symbol == grassSymbol && (i != herbivoreX || j != herbivoreY)) {
                eatGrass(grid, i, j, remainingGrassCount);
            }
        }
    }
}

void predatorEatHerbivore(Animal grid[][screenWidth], int predatorX, int predatorY, int herbivoreX, int herbivoreY, int& deadHerbivoreCount) {
    if (isAdjacent(predatorX, predatorY, herbivoreX, herbivoreY)) {
        grid[herbivoreX][herbivoreY].symbol = ' '; // Clear herbivore
        ++deadHerbivoreCount;
    }
}

void ageAnimals(Animal grid[][screenWidth], int& herbivoreCount, int& predatorCount, int& deadHerbivoreCount, int currentStep) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == herbivoreSymbolYoung) {
                // Increment age every 24 steps (1 year)
                if ((currentStep + 1) % 24 == 0) {
                    grid[i][j].age += 1;

                    if (grid[i][j].age >= 480) {
                        // If the individual reaches the age of 20, it dies
                        if (grid[i][j].symbol == predatorSymbolYoung) {
                            --predatorCount;
                        }
                        else {
                            --herbivoreCount;
                            ++deadHerbivoreCount;
                        }

                        grid[i][j].symbol = ' '; // Clear the position
                        grid[i][j].age = 0; // Reset age
                    }
                    else if (grid[i][j].age >= 230) {
                        // If the individual reaches the age of 10, it becomes old
                        if (grid[i][j].symbol == predatorSymbolYoung) {
                            grid[i][j].symbol = predatorSymbolOld;
                        }
                        else {
                            grid[i][j].symbol = herbivoreSymbolOld;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    Animal grid[screenHeight][screenWidth];
    initializeGrid(grid);

    placeRandomAnimals(grid, predatorSymbolYoung, predatorPopulation);
    placeRandomAnimals(grid, herbivoreSymbolYoung, herbivorePopulation);
    placeRandomGrass(grid, grassPopulation);

    int herbivoreCount = herbivorePopulation;
    int predatorCount = predatorPopulation;
    int deadHerbivoreCount = 0;
    int remainingGrassCount = grassPopulation;

    int steps = 0;
    int currentSeason = 0; // 0: Summer, 1: Spring, 2: Fall, 3: Winter

    while (steps < 576) { // Run for 576 steps (288 months)
        system(CLEAR_SCREEN);
        printGrid(grid, herbivoreCount, predatorCount, deadHerbivoreCount, remainingGrassCount, steps, currentSeason);

        std::cout << "Press Enter to move animals...";
        std::cin.ignore(); // Wait for Enter key

        moveRandomly(grid, predatorSymbolYoung);
        moveRandomly(grid, herbivoreSymbolYoung);

        // Herbivores eat grass after moving
        for (int i = 0; i < screenHeight; ++i) {
            for (int j = 0; j < screenWidth; ++j) {
                if (grid[i][j].symbol == herbivoreSymbolYoung) {
                    herbivoreEatGrass(grid, i, j, remainingGrassCount);
                }
            }
        }

        // Predators eat herbivores
        for (int i = 0; i < screenHeight; ++i) {
            for (int j = 0; j < screenWidth; ++j) {
                if (grid[i][j].symbol == predatorSymbolYoung) {
                    for (int k = 0; k < screenHeight; ++k) {
                        for (int l = 0; l < screenWidth; ++l) {
                            if (grid[k][l].symbol == herbivoreSymbolYoung) {
                                predatorEatHerbivore(grid, i, j, k, l, deadHerbivoreCount);
                            }
                        }
                    }
                }
            }
        }

        // Age animals every 24 steps
        ageAnimals(grid, herbivoreCount, predatorCount, deadHerbivoreCount, steps);

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
        remainingGrassCount += regrowthAmount;

        // Update season every 6 steps
        if ((steps + 1) % 6 == 0) {
            currentSeason = (currentSeason + 1) % 4;
        }

        ++steps;
    }

    return 0;
}
