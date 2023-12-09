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
int herbivorePopulation = 30;
int grassPopulation = 400;
//const double grassRegrowthRate = 0.031; // Например, 20%

const int DAYS_IN_STEP = 15;
const int STEPS_IN_SEASON = 6;
const int MONTHS_IN_SEASON = STEPS_IN_SEASON / 2;
const int MONTHS_IN_YEAR = 12;
const int SUMMER = 0;
const int FALL = 1;
const int WINTER = 2;
const int SPRING = 3;

int currentMonth = 0;
int currentSeason = SUMMER;


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

void updateSeasonAndMonth() {
    static int daysCounter = 0;

    if (daysCounter == 45) {  // Change season every 45 days (3 months)
        currentMonth = (currentMonth + 1) % MONTHS_IN_YEAR;
        if (currentMonth % MONTHS_IN_SEASON == 0) {
            currentSeason = (currentSeason + 1) % 4;
        }
        daysCounter = 0;
    }
    else {
        ++daysCounter;
    }
}

void displayDayAndSeason() {
    std::cout << "\033[1;37m";  // Set color to white
    std::cout << "Day " << currentMonth * MONTHS_IN_SEASON + 1 << " - Season: ";
    switch (currentSeason) {
    case SUMMER:
        std::cout << "Summer  ";
        break;
    case FALL:
        std::cout << "Fall   ";
        break;
    case WINTER:
        std::cout << "Winter   ";
        break;
    case SPRING:
        std::cout << "Spring   ";
        break;
    }
    std::cout << "\033[0m";  // Reset color
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

    while (true) {
        system(CLEAR_SCREEN);
        displayDayAndSeason();
        printGrid(grid, herbivoreCount, predatorCount, deadHerbivoreCount, remainingGrassCount);

        std::cout << "Press Enter to move animals and advance 15 days...";
        std::cin.get(); // Wait for Enter key

        for (int step = 0; step < STEPS_IN_SEASON; ++step) {

            for (int day = 0; day < DAYS_IN_STEP; ++day) {

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
                double regrowthRate = 0.0;
                switch (currentSeason) {
                case SUMMER:
                    regrowthRate = 0.005;
                    break;
                case FALL:
                case SPRING:
                    regrowthRate = 0.0025; // Reduced by half
                    break;
                case WINTER:
                    regrowthRate = 0.0; // No regrowth
                    break;
                }

                int regrowthAmount = static_cast<int>(remainingGrassCount * regrowthRate);
                placeRandomGrass(grid, regrowthAmount);
                remainingGrassCount += regrowthAmount;

                // Update the season and month after each day
                updateSeasonAndMonth();
            }
        }

        // Recalculate counts
        herbivoreCount = herbivorePopulation - deadHerbivoreCount;
        predatorCount = predatorPopulation;
    }
    return 0;
}
