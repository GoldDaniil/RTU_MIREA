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

}

void placeRandomRivers(Animal**& grid, int riverCount) {

}

void printGrid(Animal**& grid, int herbivoreCount, int predatorCount,
    int youngHerbivoreCount, int youngPredatorCount, int oldHerbivoreCount, int oldPredatorCount,
    int deadHerbivoreCount, int remainingGrassCount, int currentStep, int currentSeason,
    int naturalDeathPredatorCount, double currentTemperature, int& oldAgeDeathCount) {

}

void countAnimals(Animal**& grid, int& herbivoreCount, int& predatorCount,
    int& youngHerbivoreCount, int& youngPredatorCount, int& oldHerbivoreCount, int& oldPredatorCount) {
    herbivoreCount = 0;
    predatorCount = 0;
    youngHerbivoreCount = 0;
    youngPredatorCount = 0;
    oldHerbivoreCount = 0;
    oldPredatorCount = 0;

}

void placeRandomAnimals(Animal**& grid, char youngSymbol, char oldSymbol, int totalPopulation) {

}

void placeRandomGrass(Animal**& grid, int population) {

}

void moveRandomly(Animal**& grid, char animalSymbol) {
}

void eatGrass(Animal**& grid, int x, int y, int& remainingGrassCount) {

}

void updateTemperature(double& currentTemperature, int steps, int currentSeason) {

}


void herbivoreEatGrass(Animal**& grid, int herbivoreX, int herbivoreY, int& remainingGrassCount) {

}

void predatorEatHerbivore(Animal**& grid, int predatorX, int predatorY, int herbivoreX,
    int herbivoreY, int& deadHerbivoreCount, int& predatorCount) {

}

void ageAnimals(Animal**& grid, int& herbivoreCount, int& predatorCount, int& deadHerbivoreCount,
    int& currentStep, int& oldAgeDeathCount) {

}

void countYoungAnimals(Animal**& grid, int& youngHerbivoreCount, int& youngPredatorCount) {
    youngHerbivoreCount = 0;
    youngPredatorCount = 0;

}

void reproduce(Animal**& grid, int x1, int y1, int x2, int y2, char youngSymbol, char oldSymbol,
    int& herbivoreCount, int& predatorCount) {

}

void checkStarvation(Animal**& grid, int& herbivoreCount, int& predatorCount, int& deadHerbivoreCount, int& naturalDeathPredatorCount) {
}

void checkStarvationHerbivores(Animal**& grid, int& herbivoreCount, int& deadHerbivoreCount,
    int& remainingGrassCount) {
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    string user_input;
    cout << "start the game with default values and parameters? (yes/no): ";
    getline(cin, user_input);

    if (user_input == "no" || user_input == "NO" || user_input == "nO" || user_input == "No") {
        cout << "\nenter custom settings: \n";

        cout << "\nenter the number of predators: ";
        cin >> no_predator_population;

        cout << "\nenter the screen width: ";
        cin >> screenWidth;

        cout << "\nenter the screen height: ";
        cin >> screenHeight;

        cout << "\nenter the symbol for a young predator: ";
        cin >> predatorSymbolYoung;

        cout << "\nenter the symbol for an old predator: ";
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
    string userInput;

    while (steps < 576 && !gameEnded) {
        system(CLEAR_SCREEN);

        if (rand() % 100 < tsunami_probability) {
            isTsunami = true;
        }

        if (isTsunami) {
            cout << "\033[1;34m";


            for (int i = 0; i < screenHeight; ++i) {
                for (int j = 0; j < screenWidth; ++j) {
                    if (grid[i][j].symbol == ' ') {
                        cout << ' ';
                    }
                    else {
                        cout << grid[i][j].symbol;
                    }
                }
                cout << endl;
            }

            cout << "\033[0m";

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


            cout << "\nEnter 'exit'/'EXIT' to exit the game. Or press Enter move animals... ";
            getline(cin, userInput);

            if (userInput == "exit" or userInput == "EXIT") {
                cout << "\nokay. goodbye :( \n";
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
