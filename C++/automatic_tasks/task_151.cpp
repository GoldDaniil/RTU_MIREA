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
int predatorPopulation = 10;
int herbivorePopulation = 10;
int grassPopulation = 800;
const double grassRegrowthRateSummer = 0.031; // Summer regrowth rate, e.g., 20%
const double grassRegrowthRateSpringFall = 0.0155; // Spring and fall regrowth rate, half of summer
const double grassRegrowthRateWinter = 0.0; // Winter regrowth rate, no regrowth
const double deathProbabilityPerStep = 0.1; // Adjust the probability as needed
int naturalDeathPredatorCount = 0;

struct Animal {
    char symbol;
    int age;
    int stepsWithoutEating; // New member variable
};

void initializeGrid(Animal grid[][screenWidth]) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            grid[i][j].symbol = ' ';
            grid[i][j].age = 0;
            grid[i][j].stepsWithoutEating = 0; // Initialize stepsWithoutEating
        }
    }
}


void printGrid(const Animal grid[][screenWidth], int herbivoreCount, int predatorCount, int youngHerbivoreCount, int youngPredatorCount, int oldHerbivoreCount, int oldPredatorCount, int deadHerbivoreCount, int remainingGrassCount, int currentStep, int currentSeason, int naturalDeathPredatorCount) {
    std::cout << "Herbivores: " << std::max(0, herbivoreCount)
        << " | Predators: " << std::max(0, predatorCount)
        << " | Young Herbivores (< 10 years): " << youngHerbivoreCount
        << " | Young Predators (< 10 years): " << youngPredatorCount
        << " | Old Herbivores (>= 10 years): " << oldHerbivoreCount
        << " | Old Predators (>= 10 years): " << oldPredatorCount
        << " | Dead Herbivores: " << deadHerbivoreCount
        << " | Natural Deaths (Predators): " << naturalDeathPredatorCount
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

void countAnimals(const Animal grid[][screenWidth], int& herbivoreCount, int& predatorCount, int& youngHerbivoreCount, int& youngPredatorCount, int& oldHerbivoreCount, int& oldPredatorCount) {
    herbivoreCount = 0;
    predatorCount = 0;
    youngHerbivoreCount = 0;
    youngPredatorCount = 0;
    oldHerbivoreCount = 0;
    oldPredatorCount = 0;

    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == herbivoreSymbolYoung) {
                ++herbivoreCount;
                ++youngHerbivoreCount;
            }
            else if (grid[i][j].symbol == herbivoreSymbolOld) {
                ++herbivoreCount;
                ++oldHerbivoreCount;
            }
            else if (grid[i][j].symbol == predatorSymbolYoung) {
                ++predatorCount;
                ++youngPredatorCount;
            }
            else if (grid[i][j].symbol == predatorSymbolOld) {
                ++predatorCount;
                ++oldPredatorCount;
            }
        }
    }
}

void placeRandomAnimals(Animal grid[][screenWidth], char youngSymbol, char oldSymbol, int totalPopulation) {
    for (int i = 0; i < totalPopulation; ++i) {
        int x = rand() % screenHeight;
        int y = rand() % screenWidth;
        int age = rand() % 20 + 1; // Set age randomly between 1 and 20

        if (age <= 10) {
            grid[x][y].symbol = youngSymbol;
        }
        else {
            grid[x][y].symbol = oldSymbol;
        }

        grid[x][y].age = age;
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
                    grid[newI][newJ].stepsWithoutEating = 0;
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


void predatorEatHerbivore(Animal grid[][screenWidth], int predatorX, int predatorY, int herbivoreX, int herbivoreY, int& deadHerbivoreCount, int& predatorCount) {
    if (isAdjacent(predatorX, predatorY, herbivoreX, herbivoreY)) {
        // Check the age of the predator and herbivore
        bool isYoungPredator = (grid[predatorX][predatorY].symbol == predatorSymbolYoung);
        bool isYoungHerbivore = (grid[herbivoreX][herbivoreY].symbol == herbivoreSymbolYoung);

        if ((isYoungPredator && isYoungHerbivore) || (!isYoungPredator && !isYoungHerbivore)) {
            // Predator and herbivore have the same age group, predator eats herbivore
            grid[herbivoreX][herbivoreY].symbol = ' '; // Clear herbivore
            ++deadHerbivoreCount;
            grid[predatorX][predatorY].stepsWithoutEating = 0; // Reset hunger counter
        }
        else {
            // Predator and herbivore have different age groups
            if (grid[predatorX][predatorY].stepsWithoutEating >= 2) {
                // Predator dies if not enough prey
                --predatorCount;  // Use the parameter passed from the main function
                grid[predatorX][predatorY].symbol = ' '; // Clear predator
                grid[predatorX][predatorY].stepsWithoutEating = 0; // Reset hunger counter
            }
            else {
                // Predator eats herbivore and resets hunger counter
                grid[predatorX][predatorY].symbol = ' '; // Clear predator
                grid[predatorX][predatorY].stepsWithoutEating = 0; // Reset hunger counter
            }
        }
    }
}


void ageAnimals(Animal grid[][screenWidth], int& herbivoreCount, int& predatorCount, int& deadHerbivoreCount, int currentStep) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == herbivoreSymbolYoung) {
                // Increment age and hunger counters every 24 steps (1 year)
                if ((currentStep + 1) % 24 == 0) {
                    grid[i][j].age += 1;
                    grid[i][j].stepsWithoutEating += 1;

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

void countYoungAnimals(const Animal grid[][screenWidth], int& youngHerbivoreCount, int& youngPredatorCount) {
    youngHerbivoreCount = 0;
    youngPredatorCount = 0;

    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == herbivoreSymbolYoung && grid[i][j].age < 10) {
                ++youngHerbivoreCount;
            }
            else if (grid[i][j].symbol == predatorSymbolYoung && grid[i][j].age < 10) {
                ++youngPredatorCount;
            }
        }
    }
}

// Update hunger thresholds
const int youngHerbivoreHungerThreshold = 3; // Number of steps a young herbivore can go without eating
const int youngPredatorHungerThreshold = 1; // Number of steps a young predator can go without eating
const int oldHerbivoreHungerThreshold = 6; // Number of steps an old herbivore can go without eating
const int oldPredatorHungerThreshold = 2; // Number of steps an old predator can go without eating
int predatorCount = 0;
const int predatorStarvationThreshold = 2; // Number of steps a predator can go without successfully hunting


void checkStarvation(Animal grid[][screenWidth], int& herbivoreCount, int& predatorCount, int& deadHerbivoreCount, int& naturalDeathPredatorCount) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == predatorSymbolOld) {
                int hungerThreshold = (grid[i][j].symbol == predatorSymbolYoung) ? youngPredatorHungerThreshold : oldPredatorHungerThreshold;
                int starvationCounter = (grid[i][j].symbol == predatorSymbolYoung) ? predatorStarvationThreshold : predatorStarvationThreshold * 2;

                if (grid[i][j].stepsWithoutEating >= hungerThreshold) {
                    // Predator died of starvation
                    --predatorCount;
                    ++naturalDeathPredatorCount;  // Increment the new counter
                    grid[i][j].symbol = ' ';
                    grid[i][j].stepsWithoutEating = 0;
                }
                else if (grid[i][j].stepsWithoutEating >= starvationCounter) {
                    // Predator died of starvation without successful predation
                    --predatorCount;
                    grid[i][j].symbol = ' ';
                    grid[i][j].stepsWithoutEating = 0;
                }
                else {
                    // Check if the predator has successfully hunted in the last month
                    bool hasHunted = false;

                    for (int k = 0; k < screenHeight; ++k) {
                        for (int l = 0; l < screenWidth; ++l) {
                            if (grid[k][l].symbol == herbivoreSymbolYoung || grid[k][l].symbol == herbivoreSymbolOld) {
                                if (isAdjacent(i, j, k, l)) {
                                    // Predator successfully hunted a herbivore
                                    hasHunted = true;
                                    grid[i][j].stepsWithoutEating = 0; // Reset hunger counter
                                    break;
                                }
                            }
                        }
                        if (hasHunted) {
                            break;
                        }
                    }

                    // If the predator hasn't hunted, increase the starvation counter
                    if (!hasHunted) {
                        grid[i][j].stepsWithoutEating++;
                    }
                }
            }
            // ... (rest of the existing code remains unchanged)
        }
    }
}

void checkStarvationHerbivores(Animal grid[][screenWidth], int& herbivoreCount, int& deadHerbivoreCount, int& remainingGrassCount) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == herbivoreSymbolYoung || grid[i][j].symbol == herbivoreSymbolOld) {
                int hungerThreshold = (grid[i][j].symbol == herbivoreSymbolYoung) ? youngHerbivoreHungerThreshold : oldHerbivoreHungerThreshold;

                if (grid[i][j].stepsWithoutEating >= hungerThreshold) {
                    // Herbivore died of starvation
                    --herbivoreCount;
                    ++deadHerbivoreCount;
                    grid[i][j].symbol = ' ';
                    grid[i][j].stepsWithoutEating = 0;
                }
                else {
                    // Check if the herbivore has successfully eaten grass in the last month
                    bool hasEaten = false;

                    for (int k = std::max(0, i - 1); k < std::min(screenHeight, i + 2); ++k) {
                        for (int l = std::max(0, j - 1); l < std::min(screenWidth, j + 2); ++l) {
                            if (grid[k][l].symbol == grassSymbol && (k != i || l != j)) {
                                // Herbivore successfully ate grass
                                hasEaten = true;
                                grid[i][j].stepsWithoutEating = 0; // Reset hunger counter
                                eatGrass(grid, k, l, remainingGrassCount);
                                break;
                            }
                        }
                        if (hasEaten) {
                            break;
                        }
                    }

                    // If the herbivore hasn't eaten, increase the starvation counter
                    if (!hasEaten) {
                        grid[i][j].stepsWithoutEating++;
                    }
                }
            }
            // ... (rest of the existing code remains unchanged)
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    Animal grid[screenHeight][screenWidth];
    initializeGrid(grid);

    placeRandomAnimals(grid, predatorSymbolYoung, predatorSymbolOld, predatorPopulation);
    placeRandomAnimals(grid, herbivoreSymbolYoung, herbivoreSymbolOld, herbivorePopulation);
    placeRandomGrass(grid, grassPopulation);

    int herbivoreCount = 0;
    int predatorCount = 0;  // Add this line
    int youngHerbivoreCount = 0;
    int youngPredatorCount = 0;
    int oldHerbivoreCount = 0;
    int oldPredatorCount = 0;
    int deadHerbivoreCount = 0;
    int remainingGrassCount = grassPopulation;

    int steps = 0;
    int currentSeason = 0; // 0: Summer, 1: Spring, 2: Fall, 3: Winter


    while (steps < 576) { // Run for 576 steps (288 months)

        system(CLEAR_SCREEN);
        printGrid(grid, herbivoreCount, predatorCount, youngHerbivoreCount, youngPredatorCount, oldHerbivoreCount, oldPredatorCount, deadHerbivoreCount, remainingGrassCount, steps, currentSeason, naturalDeathPredatorCount);

        std::cout << "Press Enter to move animals...";
        std::cin.ignore(); // Wait for Enter key

        moveRandomly(grid, predatorSymbolYoung);
        moveRandomly(grid, predatorSymbolOld);
        moveRandomly(grid, herbivoreSymbolYoung);
        moveRandomly(grid, herbivoreSymbolOld);

        // Check for starvation before eating
        checkStarvation(grid, herbivoreCount, predatorCount, deadHerbivoreCount, naturalDeathPredatorCount);

        // Herbivores eat grass after moving
        for (int i = 0; i < screenHeight; ++i) {
            for (int j = 0; j < screenWidth; ++j) {
                if (grid[i][j].symbol == herbivoreSymbolYoung || grid[i][j].symbol == herbivoreSymbolOld) {
                    herbivoreEatGrass(grid, i, j, remainingGrassCount);
                }
            }
        }

        // Predators eat herbivores
        for (int i = 0; i < screenHeight; ++i) {
            for (int j = 0; j < screenWidth; ++j) {
                if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == predatorSymbolOld) {
                    for (int k = 0; k < screenHeight; ++k) {
                        for (int l = 0; l < screenWidth; ++l) {
                            if (grid[k][l].symbol == herbivoreSymbolYoung || grid[k][l].symbol == herbivoreSymbolOld) {
                                // Call predatorEatHerbivore with predatorCount as a parameter
                                predatorEatHerbivore(grid, i, j, k, l, deadHerbivoreCount, predatorCount);
                            }
                        }
                    }
                }
            }
        }

        // Age animals every 24 steps
        ageAnimals(grid, herbivoreCount, predatorCount, deadHerbivoreCount, steps);

        // Count young animals
        countYoungAnimals(grid, youngHerbivoreCount, youngPredatorCount);

        // Check herbivores for starvation
        checkStarvationHerbivores(grid, herbivoreCount, deadHerbivoreCount, remainingGrassCount);

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
