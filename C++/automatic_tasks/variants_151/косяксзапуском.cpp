#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

double currentTemperature = 20.0; // не вводим
const double grassRegrowthRateSummer = 0.031; // не вводим
const double grassRegrowthRateSpringFall = 0.0155; // не вводим 
const double grassRegrowthRateWinter = 0.0; // не вводим

int no_predator_population; // вводим
int herbivorePopulation;    // вводим
int age_predators_herbivores; // вводим
int grassPopulation;         // вводим
int reproductive_animals_min, reproductive_animals_max; // вводим
int probability_reproduce;   // вводим
double tsunami_probability; // вводим

int screenWidth; // вводим
int screenHeight; // вводим

char predatorSymbolYoung; // вводим
char predatorSymbolOld;   // вводим
char herbivoreSymbolYoung; // вводим
char herbivoreSymbolOld;   // вводим
char grassSymbol;          // вводим
char riverSymbol;          // вводим

int predatorPopulation;            // вводим
double deathProbabilityPerStep;   // вводим
int youngHerbivoreHungerThreshold; // вводим
int youngPredatorHungerThreshold;  // вводим
int oldHerbivoreHungerThreshold;   // вводим
int oldPredatorHungerThreshold;    // вводим
int predatorStarvationThreshold;   // вводим

struct Animal {
    char symbol;
    int age;
    int stepsWithoutEating;
};

int naturalDeathPredatorCount = 0;
int predatorCount = 0;

void initializeGrid(Animal**& grid, int rows, int cols) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            grid[i][j].symbol = ' ';
            grid[i][j].age = 0;
            grid[i][j].stepsWithoutEating = 0;
        }
    }
}

void placeRandomRivers(Animal**& grid, int riverCount) {
    for (int i = 0; i < riverCount; ++i) {
        int riverSize = rand() % 4 + 6;

        int riverX = rand() % (screenHeight - riverSize);
        int riverY = rand() % (screenWidth - riverSize);

        for (int x = riverX; x < riverX + riverSize; ++x) {
            for (int y = riverY; y < riverY + riverSize; ++y) {
                grid[x][y].symbol = riverSymbol;
            }
        }
    }
}

void printGrid(Animal**& grid, int herbivoreCount, int predatorCount,
    int youngHerbivoreCount, int youngPredatorCount, int oldHerbivoreCount, int oldPredatorCount,
    int deadHerbivoreCount, int remainingGrassCount, int currentStep, int currentSeason,
    int naturalDeathPredatorCount, double currentTemperature, int& oldAgeDeathCount) {

    std::cout << "Herbivores: " << std::max(0, herbivoreCount)
        << " | Predators: " << std::max(0, predatorCount)
        << " | Young Herbivores (< 10 years): " << youngHerbivoreCount
        << " | Young Predators (< 10 years): " << youngPredatorCount
        << " | Old Herbivores (>= 10 years): " << oldHerbivoreCount
        << " | Old Predators (>= 10 years): " << oldPredatorCount
        << " | Dead Herbivores: " << deadHerbivoreCount
        << " | Natural Deaths (Predators): " << naturalDeathPredatorCount
        << " | Old Age Deaths: " << oldAgeDeathCount
        << " | Remaining Grass: " << remainingGrassCount
        << " | Step: " << currentStep + 1
        << " | Current Temperature: " << currentTemperature << "^C"
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
        std::cout << "+";
        break;
    }

    std::cout << std::endl << std::endl;

    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == grassSymbol) {
                if (currentSeason == 1) {
                    std::cout << "\033[1;33m" << grid[i][j].symbol << "\033[0m";
                }
                else if (currentSeason == 2) {
                    std::cout << "\033[1;37m" << grid[i][j].symbol << "\033[0m";
                }
                else {
                    std::cout << "\033[1;32m" << grid[i][j].symbol << "\033[0m";
                }
            }
            else if (grid[i][j].symbol == riverSymbol) {
                std::cout << "\033[1;34m" << grid[i][j].symbol << "\033[0m";
            }
            else if (grid[i][j].symbol == herbivoreSymbolYoung) {
                std::cout << "\033[1;31m" << grid[i][j].symbol << "\033[0m";
            }
            else if (grid[i][j].symbol == predatorSymbolYoung) {
                std::cout << "\033[1;31m" << grid[i][j].symbol << "\033[0m";
            }
            else {
                std::cout << grid[i][j].symbol;
            }
        }
        std::cout << std::endl;
    }
}

void countAnimals(Animal**& grid, int& herbivoreCount, int& predatorCount,
    int& youngHerbivoreCount, int& youngPredatorCount, int& oldHerbivoreCount, int& oldPredatorCount) {
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

void placeRandomAnimals(Animal**& grid, char youngSymbol, char oldSymbol, int totalPopulation) {
    for (int i = 0; i < totalPopulation; ++i) {
        int x = rand() % screenHeight;
        int y = rand() % screenWidth;
        int age = rand() % 20 + 1;

        if (age <= 10) {
            grid[x][y].symbol = youngSymbol;
        }
        else {
            grid[x][y].symbol = oldSymbol;
        }

        grid[x][y].age = age;
    }
}

void placeRandomGrass(Animal**& grid, int population) {
    for (int i = 0; i < population; ++i) {
        int x = rand() % screenHeight;
        int y = rand() % screenWidth;
        grid[x][y].symbol = grassSymbol;
        grid[x][y].age = 0;
    }
}

void moveRandomly(Animal**& grid, char animalSymbol) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == animalSymbol) {
                grid[i][j].symbol = ' ';

                int direction = rand() % 4;
                int newI = i;
                int newJ = j;

                switch (direction) {
                case 0:
                    if (i > 0 && grid[i - 1][j].symbol != riverSymbol) {
                        newI = i - 1;
                    }
                    break;
                case 1:
                    if (i < screenHeight - 1 && grid[i + 1][j].symbol != riverSymbol) {
                        newI = i + 1;
                    }
                    break;
                case 2:
                    if (j > 0 && grid[i][j - 1].symbol != riverSymbol) {
                        newJ = j - 1;
                    }
                    break;
                case 3:
                    if (j < screenWidth - 1 && grid[i][j + 1].symbol != riverSymbol) {
                        newJ = j + 1;
                    }
                    break;
                }

                if (grid[newI][newJ].symbol == grassSymbol) {
                    grid[newI][newJ].stepsWithoutEating = 0;
                }

                grid[newI][newJ].symbol = animalSymbol;
                grid[newI][newJ].age = grid[i][j].age + 1;
            }
        }
    }
}

void eatGrass(Animal**& grid, int x, int y, int& remainingGrassCount) {
    grid[x][y].symbol = ' ';
    --remainingGrassCount;
}

void updateTemperature(double& currentTemperature, int steps, int currentSeason) {
    int randomTemperatureChange = 0;

    switch (currentSeason) {
    case 0:
        randomTemperatureChange = (steps / 3) % 2 == 0 ? rand() % 13 + 18 : -(rand() % 13 + 1);
        break;

    case 1:
        randomTemperatureChange = (steps / 3) % 2 == 0 ? std::min(rand() % 11, 10) : -(rand() % 14 + 4);

        if (currentTemperature + randomTemperatureChange > 10) {
            randomTemperatureChange = std::max(-10.0, 10.0 - currentTemperature);
        }
        break;
    case 2:
        randomTemperatureChange = (steps / 3) % 2 == 0 ? std::max(-(rand() % 21 + 10), -30) : std::min(rand() % 26 - 25, -10);
        break;
    case 3:
        randomTemperatureChange = (steps / 3) % 2 == 0 ? std::min(rand() % 11 + 5, 15) : std::max(-(rand() % 11 + 5), -10);

        if (currentTemperature + randomTemperatureChange > 20) {
            randomTemperatureChange = std::max(-10.0, 20.0 - currentTemperature);
        }
        break;
    }

    currentTemperature += randomTemperatureChange;

    currentTemperature = std::max(-10.0, std::min(30.0, currentTemperature));
}

bool isAdjacent(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1;
}

void herbivoreEatGrass(Animal**& grid, int herbivoreX, int herbivoreY, int& remainingGrassCount) {
    for (int i = std::max(0, herbivoreX - 1); i < std::min(screenHeight, herbivoreX + 2); ++i) {
        for (int j = std::max(0, herbivoreY - 1); j < std::min(screenWidth, herbivoreY + 2); ++j) {
            if (grid[i][j].symbol == grassSymbol && (i != herbivoreX || j != herbivoreY) && grid[i][j].symbol != riverSymbol) {
                eatGrass(grid, i, j, remainingGrassCount);
            }
        }
    }
}

void predatorEatHerbivore(Animal**& grid, int predatorX, int predatorY, int herbivoreX,
    int herbivoreY, int& deadHerbivoreCount, int& predatorCount) {
    if (isAdjacent(predatorX, predatorY, herbivoreX, herbivoreY)) {
        bool isYoungPredator = (grid[predatorX][predatorY].symbol == predatorSymbolYoung);
        bool isYoungHerbivore = (grid[herbivoreX][herbivoreY].symbol == herbivoreSymbolYoung);

        if ((isYoungPredator && isYoungHerbivore) || (!isYoungPredator && !isYoungHerbivore)) {
            grid[herbivoreX][herbivoreY].symbol = ' ';
            ++deadHerbivoreCount;
            grid[predatorX][predatorY].stepsWithoutEating = 0;
        }
        else {
            if (grid[predatorX][predatorY].stepsWithoutEating >= 2) {
                --predatorCount;
                grid[predatorX][predatorY].symbol = ' ';
                grid[predatorX][predatorY].stepsWithoutEating = 0;
            }
            else {
                grid[predatorX][predatorY].symbol = ' ';
                grid[predatorX][predatorY].stepsWithoutEating = 0;
            }
        }
    }
}

void ageAnimals(Animal**& grid, int& herbivoreCount, int& predatorCount, int& deadHerbivoreCount,
    int& currentStep, int& oldAgeDeathCount) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == herbivoreSymbolYoung) {
                if ((currentStep + 1) % 24 == 0) {
                    grid[i][j].age += 2;
                    grid[i][j].stepsWithoutEating += 1;

                    if (grid[i][j].age >= 480) {
                        if (rand() % 100 < 10) {
                            --predatorCount;
                            grid[i][j].symbol = ' ';
                            grid[i][j].age = 0;
                            ++oldAgeDeathCount;
                        }
                    }

                    else if (grid[i][j].age >= 350) {
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

void countYoungAnimals(Animal**& grid, int& youngHerbivoreCount, int& youngPredatorCount) {
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

void reproduce(Animal**& grid, int x1, int y1, int x2, int y2, char youngSymbol, char oldSymbol,
    int& herbivoreCount, int& predatorCount) {
    if ((grid[x1][y1].symbol == grid[x2][y2].symbol) && isAdjacent(x1, y1, x2, y2)) {
        if (rand() % 100 < 0.0005) {
            for (int i = std::max(0, x1 - 1); i < std::min(screenHeight, x1 + 2); ++i) {
                for (int j = std::max(0, y1 - 1); j < std::min(screenWidth, y1 + 2); ++j) {
                    if (grid[i][j].symbol == ' ') {
                        if (grid[x1][y1].symbol == predatorSymbolYoung || grid[x1][y1].symbol == herbivoreSymbolYoung) {
                            grid[i][j].symbol = (grid[x1][y1].age <= 10) ? youngSymbol : oldSymbol;
                            grid[i][j].age = 0;
                            grid[i][j].stepsWithoutEating = 0;

                            if (grid[i][j].symbol == youngSymbol) {
                                if (grid[i][j].symbol == herbivoreSymbolYoung) {
                                    ++herbivoreCount;
                                }
                                else {
                                    ++predatorCount;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

void checkStarvation(Animal**& grid, int& herbivoreCount, int& predatorCount, int& deadHerbivoreCount, int& naturalDeathPredatorCount) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == predatorSymbolOld) {
                int hungerThreshold = (grid[i][j].symbol == predatorSymbolYoung) ? youngPredatorHungerThreshold : oldPredatorHungerThreshold;
                int starvationCounter = (grid[i][j].symbol == predatorSymbolYoung) ? predatorStarvationThreshold : predatorStarvationThreshold * 2;

                if (grid[i][j].stepsWithoutEating >= hungerThreshold) {
                    --predatorCount;
                    ++naturalDeathPredatorCount;
                    grid[i][j].symbol = ' ';
                    grid[i][j].stepsWithoutEating = 0;
                }
                else if (grid[i][j].stepsWithoutEating >= starvationCounter) {
                    --predatorCount;
                    grid[i][j].symbol = ' ';
                    grid[i][j].stepsWithoutEating = 0;
                }
                else {
                    bool hasHunted = false;

                    for (int k = 0; k < screenHeight; ++k) {
                        for (int l = 0; l < screenWidth; ++l) {
                            if (grid[k][l].symbol == herbivoreSymbolYoung || grid[k][l].symbol == herbivoreSymbolOld) {
                                if (isAdjacent(i, j, k, l)) {
                                    hasHunted = true;
                                    grid[i][j].stepsWithoutEating = 0;
                                    break;
                                }
                            }
                        }
                        if (hasHunted) {
                            break;
                        }
                    }

                    if (!hasHunted) {
                        grid[i][j].stepsWithoutEating++;
                    }
                }
            }
        }
    }
}

void checkStarvationHerbivores(Animal**& grid, int& herbivoreCount, int& deadHerbivoreCount,
    int& remainingGrassCount) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == herbivoreSymbolYoung || grid[i][j].symbol == herbivoreSymbolOld) {
                int hungerThreshold = (grid[i][j].symbol == herbivoreSymbolYoung) ? youngHerbivoreHungerThreshold : oldHerbivoreHungerThreshold;

                if (grid[i][j].stepsWithoutEating >= hungerThreshold) {
                    --herbivoreCount;
                    ++deadHerbivoreCount;
                    grid[i][j].symbol = ' ';
                    grid[i][j].stepsWithoutEating = 0;
                }
                else {
                    bool hasEaten = false;

                    for (int k = std::max(0, i - 1); k < std::min(screenHeight, i + 2); ++k) {
                        for (int l = std::max(0, j - 1); l < std::min(screenWidth, j + 2); ++l) {
                            if (grid[k][l].symbol == grassSymbol && (k != i || l != j)) {
                                hasEaten = true;
                                grid[i][j].stepsWithoutEating = 0;
                                eatGrass(grid, k, l, remainingGrassCount);
                                break;
                            }
                        }
                        if (hasEaten) {
                            break;
                        }
                    }

                    if (!hasEaten) {
                        grid[i][j].stepsWithoutEating++;
                    }
                }
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    string user_input;
    cout << "Start the game with default values and parameters? (yes/no): ";
    getline(cin, user_input);

    if (user_input == "no" || user_input == "NO" || user_input == "nO" || user_input == "No") {
        cout << "\nEnter custom settings: \n";

        cout << "\nEnter the number of predators: ";
        cin >> no_predator_population;

        cout << "\nEnter the screen width: ";
        cin >> screenWidth;

        cout << "\nEnter the screen height: ";
        cin >> screenHeight;

        cout << "\nEnter the symbol for a young predator: ";
        cin >> predatorSymbolYoung;

        cout << "\nEnter the symbol for an old predator: ";
        cin >> predatorSymbolOld;

        cin >> herbivoreSymbolYoung;

    }
    else if (user_input == "yes" || user_input == "YES" || user_input == "Yes" || user_input == "yeS") {
        char predatorSymbolYoung = 'p';
        char predatorSymbolOld = 'P';
        char herbivoreSymbolYoung = 'h';
        char herbivoreSymbolOld = 'H';
        char grassSymbol = '#';
        char riverSymbol = '~';
        int screenWidth = 200;
        int screenHeight = 30;
        int predatorPopulation = 1200;
        int herbivorePopulation = 1200;
        int grassPopulation = 4000;
        double grassRegrowthRateSummer = 0.031;
        double grassRegrowthRateSpringFall = 0.0155;
        double grassRegrowthRateWinter = 0.0;
        double deathProbabilityPerStep = 0.1;
        double currentTemperature = 20.0; // Начальная температура
        double tsunami_probability = 0.3;
        int youngHerbivoreHungerThreshold = 3; // Сколько шагов молодое травоядное животное может пройти без еды
        int youngPredatorHungerThreshold = 3; // Сколько шагов молодой хищник может пройти без еды
        int oldHerbivoreHungerThreshold = 6; // Сколько шагов старое травоядное животное может пройти без еды
        int oldPredatorHungerThreshold = 6; // Сколько шагов старый хищник может пройти без еды
        int predatorStarvationThreshold = 4; // Number of steps a predator can go without successfully hunting
    }

    Animal** grid;
    initializeGrid(grid, screenHeight, screenWidth);

    placeRandomAnimals(grid, predatorSymbolYoung, predatorSymbolOld, predatorPopulation);
    placeRandomAnimals(grid, herbivoreSymbolYoung, herbivoreSymbolOld, herbivorePopulation);
    placeRandomGrass(grid, grassPopulation);
    placeRandomRivers(grid, 5);

    int herbivoreCount = 0;
    int youngHerbivoreCount = 0;
    int youngPredatorCount = 0;
    int oldHerbivoreCount = 0;
    int oldPredatorCount = 0;
    int deadHerbivoreCount = 0;
    int remainingGrassCount = grassPopulation;
    int steps = 0;
    int currentSeason = 0;
    double currentRegrowthRate = 0.0;
    int oldAgeDeathCount = 0;

    bool isTsunami = false;
    bool gameEnded = false;
    std::string userInput;

    while (steps < 576 && !gameEnded) {
        system(CLEAR_SCREEN);

        if (rand() % 100 < tsunami_probability) {
            isTsunami = true;
        }

        if (isTsunami) {
            std::cout << "\033[1;34m";


            for (int i = 0; i < screenHeight; ++i) {
                for (int j = 0; j < screenWidth; ++j) {
                    if (grid[i][j].symbol == ' ') {
                        std::cout << ' ';
                    }
                    else {
                        std::cout << grid[i][j].symbol;
                    }
                }
                std::cout << std::endl;
            }

            std::cout << "\033[0m";

            for (int i = 0; i < screenHeight; ++i) {
                for (int j = 0; j < screenWidth; ++j) {
                    if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == predatorSymbolOld ||
                        grid[i][j].symbol == herbivoreSymbolYoung || grid[i][j].symbol == herbivoreSymbolOld) {
                        grid[i][j].symbol = ' ';
                    }
                }
            }

            gameEnded = true;
        }
        else {

            printGrid(grid, herbivoreCount, predatorCount, youngHerbivoreCount, youngPredatorCount, oldHerbivoreCount,
                oldPredatorCount, deadHerbivoreCount, remainingGrassCount, steps, currentSeason,
                naturalDeathPredatorCount, currentTemperature, oldAgeDeathCount);


            std::cout << "\nEnter 'exit'/'EXIT' to exit the game. Or press Enter move animals... ";
            std::getline(std::cin, userInput);

            if (userInput == "exit" or userInput == "EXIT") {
                std::cout << "\nokay. goodbye :( \n";
                break;
            }

            // Движение животных и размножение
            moveRandomly(grid, predatorSymbolYoung);
            moveRandomly(grid, predatorSymbolOld);
            moveRandomly(grid, herbivoreSymbolYoung);
            moveRandomly(grid, herbivoreSymbolOld);

            for (int i = 0; i < screenHeight; ++i) {
                for (int j = 0; j < screenWidth; ++j) {
                    if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == predatorSymbolOld) {
                        for (int k = 0; k < screenHeight; ++k) {
                            for (int l = 0; l < screenWidth; ++l) {
                                if (grid[k][l].symbol == predatorSymbolYoung || grid[k][l].symbol == predatorSymbolOld) {
                                    reproduce(grid, i, j, k, l, predatorSymbolYoung, predatorSymbolOld, herbivoreCount, predatorCount);
                                }
                            }
                        }
                    }
                    else if (grid[i][j].symbol == herbivoreSymbolYoung || grid[i][j].symbol == herbivoreSymbolOld) {
                        for (int k = 0; k < screenHeight; ++k) {
                            for (int l = 0; l < screenWidth; ++l) {
                                if (grid[k][l].symbol == herbivoreSymbolYoung || grid[k][l].symbol == herbivoreSymbolOld) {
                                    reproduce(grid, i, j, k, l, herbivoreSymbolYoung, herbivoreSymbolOld, herbivoreCount, predatorCount);
                                }
                            }
                        }
                    }
                }
            }

            // Проверка на голод перед тем, как животные поедят
            checkStarvation(grid, herbivoreCount, predatorCount, deadHerbivoreCount, naturalDeathPredatorCount);

            for (int i = 0; i < screenHeight; ++i) {
                for (int j = 0; j < screenWidth; ++j) {
                    if (grid[i][j].symbol == herbivoreSymbolYoung || grid[i][j].symbol == herbivoreSymbolOld) {
                        herbivoreEatGrass(grid, i, j, remainingGrassCount);
                    }
                }
            }

            for (int i = 0; i < screenHeight; ++i) {
                for (int j = 0; j < screenWidth; ++j) {
                    if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == predatorSymbolOld) {
                        for (int k = 0; k < screenHeight; ++k) {
                            for (int l = 0; l < screenWidth; ++l) {
                                if (grid[k][l].symbol == herbivoreSymbolYoung || grid[k][l].symbol == herbivoreSymbolOld) {
                                    predatorEatHerbivore(grid, i, j, k, l, deadHerbivoreCount, predatorCount);
                                }
                            }
                        }
                    }
                }
            }

            ageAnimals(grid, herbivoreCount, predatorCount, deadHerbivoreCount, steps, oldAgeDeathCount);

            countYoungAnimals(grid, youngHerbivoreCount, youngPredatorCount);

            checkStarvationHerbivores(grid, herbivoreCount, deadHerbivoreCount, remainingGrassCount);

            double currentRegrowthRate = 0.0;

            switch (currentSeason) {
            case 0:
                currentRegrowthRate = grassRegrowthRateSummer;
                break;
            case 1:
                currentRegrowthRate = grassRegrowthRateSpringFall;
                break;
            case 2:
                currentRegrowthRate = grassRegrowthRateWinter;
                break;
            case 3:
                currentRegrowthRate = grassRegrowthRateSpringFall;
                break;
            }

            if (currentRegrowthRate > 0.0) {
                int regrowthAmount = static_cast<int>(grassPopulation * currentRegrowthRate);
                placeRandomGrass(grid, regrowthAmount);

                remainingGrassCount += regrowthAmount;
            }

            if ((steps + 1) % 6 == 0) {
                currentSeason = (currentSeason + 1) % 4;
            }

            countAnimals(grid, herbivoreCount, predatorCount, youngHerbivoreCount, youngPredatorCount, oldHerbivoreCount, oldPredatorCount);

            updateTemperature(currentTemperature, steps, currentSeason);

            ++steps;
        }
    }

    return 0;
}
