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

// косяк с хищниками - быстро умирают - размножение есть - но слишком много детей - 
double currentTemperature = 20.0; // Начальная температура
const double grassRegrowthRateSummer = 0.031;
const double grassRegrowthRateSpringFall = 0.0155;
const double grassRegrowthRateWinter = 0.0;

int no_predator_population; // вводим
int herbivorePopulation; // вводим
int age_predators_herbivores;
int grassPopulation; // вводим
int reproductive_animals_min, reproductive_animals_max; // вводим
int probability_reproduce; // вводим
double tsunami_probability; // вводим

int no_screen_width; // вводим
const int screenWidth;

int no_screen_height; // вводим
const int screenHeight;

char no_predator_symbol_young;
const char predatorSymbolYoung = 'p';

char no_predator_symbol_old;
const char predatorSymbolOld = 'P';

char no_herbivore_symbol_young;
const char herbivoreSymbolYoung = 'h';

char no_herbivore_symbol_old;
const char herbivoreSymbolOld = 'H';

char no_grass_symbol;
const char grassSymbol = '#';

char no_river_symbol;
const char riverSymbol = '~';

int no_predator_population;
const int predatorPopulation;

int no_death_probability_per_step;
const double deathProbabilityPerStep;

int no_young_herbivore_hunger_threshold;
const int youngHerbivoreHungerThreshold; // вводим // Сколько шагов молодое травоядное животное может пройти без еды

int no_young_predator_hunger_threshold;
const int youngPredatorHungerThreshold; // вводим // Сколько шагов молодой хищник может пройти без еды

int no_old_herbivore_hunger_threshold;
const int oldHerbivoreHungerThreshold; // вводим // Сколько шагов старое травоядное животное может пройти без еды

int no_old_predator_hungeg_threshold;
const int oldPredatorHungerThreshold; // вводим // Сколько шагов старый хищник может пройти без еды

int no_predator_starvation_threshold;
const int predatorStarvationThreshold; // вводим // Number of steps a predator can go without successfully hunting

struct Animal {
    char symbol;
    int age;
    int stepsWithoutEating;
};

int naturalDeathPredatorCount = 0;
int predatorCount = 0;

void initializeGrid(Animal grid[][screenWidth]) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            grid[i][j].symbol = ' ';
            grid[i][j].age = 0;
            grid[i][j].stepsWithoutEating = 0;
        }
    }
}

void placeRandomRivers(Animal grid[][screenWidth], int riverCount) {
    for (int i = 0; i < riverCount; ++i) {
        int riverSize = rand() % 4 + 6; // Random river size between 2x2 and 5x5

        int riverX = rand() % (screenHeight - riverSize);
        int riverY = rand() % (screenWidth - riverSize);

        for (int x = riverX; x < riverX + riverSize; ++x) {
            for (int y = riverY; y < riverY + riverSize; ++y) {
                grid[x][y].symbol = riverSymbol;
            }
        }
    }
}

void printGrid(const Animal grid[][screenWidth], int herbivoreCount, int predatorCount,
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
                    std::cout << "\033[1;33m" << grid[i][j].symbol << "\033[0m"; // Set color to orange for grass in autumn
                }
                // Check if it's winter and color the grass white
                else if (currentSeason == 2) {
                    std::cout << "\033[1;37m" << grid[i][j].symbol << "\033[0m"; // Set color to white for grass in winter
                }
                else {
                    std::cout << "\033[1;32m" << grid[i][j].symbol << "\033[0m"; // Set color to green for grass
                }
            }
            else if (grid[i][j].symbol == riverSymbol) {
                std::cout << "\033[1;34m" << grid[i][j].symbol << "\033[0m"; // Set color to blue for rivers
            }
            else if (grid[i][j].symbol == herbivoreSymbolYoung) {
                std::cout << "\033[1;31m" << grid[i][j].symbol << "\033[0m"; // Set color to red for young herbivores
            }
            else if (grid[i][j].symbol == predatorSymbolYoung) {
                std::cout << "\033[1;31m" << grid[i][j].symbol << "\033[0m"; // Set color to red for young predators
            }
            else {
                std::cout << grid[i][j].symbol;
            }
        }
        std::cout << std::endl;
    }
}

void countAnimals(const Animal grid[][screenWidth], int& herbivoreCount, int& predatorCount,
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
                    if (i > 0 && grid[i - 1][j].symbol != riverSymbol) {
                        newI = i - 1;
                    }
                    break;
                case 1: // Move down
                    if (i < screenHeight - 1 && grid[i + 1][j].symbol != riverSymbol) {
                        newI = i + 1;
                    }
                    break;
                case 2: // Move left
                    if (j > 0 && grid[i][j - 1].symbol != riverSymbol) {
                        newJ = j - 1;
                    }
                    break;
                case 3: // Move right
                    if (j < screenWidth - 1 && grid[i][j + 1].symbol != riverSymbol) {
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

void updateTemperature(double& currentTemperature, int steps, int currentSeason) {
    int randomTemperatureChange = 0;

    switch (currentSeason) {
    case 0: // Summer
        randomTemperatureChange = (steps / 3) % 2 == 0 ? rand() % 13 + 18 : -(rand() % 13 + 1);
        break;

    case 1: // Autumn
        randomTemperatureChange = (steps / 3) % 2 == 0 ? std::min(rand() % 11, 10) : -(rand() % 14 + 4);

        // Ensure the temperature change doesn't make the temperature go above 10 degrees Celsius
        if (currentTemperature + randomTemperatureChange > 10) {
            randomTemperatureChange = std::max(-10.0, 10.0 - currentTemperature);
        }
        break;
    case 2: // Winter
        randomTemperatureChange = (steps / 3) % 2 == 0 ? std::max(-(rand() % 21 + 10), -30) : std::min(rand() % 26 - 25, -10);
        break;
    case 3: // Spring
        randomTemperatureChange = (steps / 3) % 2 == 0 ? std::min(rand() % 11 + 5, 15) : std::max(-(rand() % 11 + 5), -10);

        // Ensure the temperature change doesn't make the temperature go above 20 degrees Celsius
        if (currentTemperature + randomTemperatureChange > 20) {
            randomTemperatureChange = std::max(-10.0, 20.0 - currentTemperature);
        }
        break;
    }

    // Update the temperature
    currentTemperature += randomTemperatureChange;

    // Ensure the temperature stays within a reasonable range (e.g., -10 to 30 degrees Celsius)
    currentTemperature = std::max(-10.0, std::min(30.0, currentTemperature));
}

bool isAdjacent(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1;
}

void herbivoreEatGrass(Animal grid[][screenWidth], int herbivoreX, int herbivoreY, int& remainingGrassCount) {
    for (int i = std::max(0, herbivoreX - 1); i < std::min(screenHeight, herbivoreX + 2); ++i) {
        for (int j = std::max(0, herbivoreY - 1); j < std::min(screenWidth, herbivoreY + 2); ++j) {
            if (grid[i][j].symbol == grassSymbol && (i != herbivoreX || j != herbivoreY) && grid[i][j].symbol != riverSymbol) {
                eatGrass(grid, i, j, remainingGrassCount);
            }
        }
    }
}

void predatorEatHerbivore(Animal grid[][screenWidth], int predatorX, int predatorY, int herbivoreX,
    int herbivoreY, int& deadHerbivoreCount, int& predatorCount) {
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

void ageAnimals(Animal grid[][screenWidth], int& herbivoreCount, int& predatorCount, int& deadHerbivoreCount,
    int& currentStep, int& oldAgeDeathCount) {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (grid[i][j].symbol == predatorSymbolYoung || grid[i][j].symbol == herbivoreSymbolYoung) {
                // Increment age and hunger counters every 24 steps (1 year)
                if ((currentStep + 1) % 24 == 0) {
                    grid[i][j].age += 2;  // Увеличьте возраст на 2 вместо 1
                    grid[i][j].stepsWithoutEating += 1;

                    if (grid[i][j].age >= age_predators_herbivores) {
                        // Если хищник достиг возраста age_predators_herbivores, он не обязательно должен умереть, уменьшим вероятность
                        if (rand() % 100 < 10) {  // Уменьшим вероятность смерти
                            --predatorCount;
                            grid[i][j].symbol = ' ';
                            grid[i][j].age = 0;
                            ++oldAgeDeathCount;
                        }
                    }

                    else if (grid[i][j].age >= 350) {  // Увеличьте возраст на 20
                        // Если хищник достиг возраста 10, он становится старым
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

void reproduce(Animal grid[][screenWidth], int x1, int y1, int x2, int y2, char youngSymbol, char oldSymbol,
    int& herbivoreCount, int& predatorCount) {
    // Check if the two animals are of the same type and are adjacent
    if ((grid[x1][y1].symbol == grid[x2][y2].symbol) && isAdjacent(x1, y1, x2, y2)) {
        // Check if the reproduction probability is met (1% chance)
        if (rand() % 100 < probability_reproduce) {
            for (int i = std::max(0, x1 - 1); i < std::min(screenHeight, x1 + 2); ++i) {
                for (int j = std::max(0, y1 - 1); j < std::min(screenWidth, y1 + 2); ++j) {
                    if (grid[i][j].symbol == ' ') {
                        // Reproduction successful, create a new offspring
                        if (grid[x1][y1].symbol == predatorSymbolYoung || grid[x1][y1].symbol == herbivoreSymbolYoung) {
                            // Limit the number of offspring created to 1
                            grid[i][j].symbol = (grid[x1][y1].age <= 10) ? youngSymbol : oldSymbol;
                            grid[i][j].age = 0;
                            grid[i][j].stepsWithoutEating = 0;

                            // Update counts based on the offspring type
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

void checkStarvation(Animal grid[][screenWidth], int& herbivoreCount, int& predatorCount, int& deadHerbivoreCount,
    int& naturalDeathPredatorCount) {
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
        }
    }
}

void checkStarvationHerbivores(Animal grid[][screenWidth], int& herbivoreCount, int& deadHerbivoreCount,
    int& remainingGrassCount) {
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
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    string user_input;
    cout << "start the game with default values ​​and parameters? (yes/no): ";
    getline(cin, user_input);

    if (user_input == "no" || user_input == "NO" || user_input == "nO" || user_input == "No") {
        cout << "\nEnter custom settings: \n";

        //ввести ограничения для вводимых значений переменных!!!!!!!!!!!!
        // разобраться с соответсвием const и cin

        cout << "\nenter the width of the screen, the playing field : ";
        cin >> no_screen_width;
        const int screenWidth = no_screen_width;

        cout << "\nenter the height of the screen, the playing field : ";
        cin >> no_screen_height;
        const int screenHeight = no_screen_height;

        cout << "\nenter the symbol, the designation on the screen of a young predator : ";
        cin >> no_predator_symbol_young;
        const char predatorSymbolYoung = no_predator_symbol_young;

        cout << "\nenter the symbol, the designation on the screen of an adult predator : ";
        cin >> no_predator_symbol_old;
        const char predatorSymbolOld = no_predator_symbol_old;

        cout << "\nenter the symbol, the designation on the screen of a young herbivore : ";
        cin >> no_herbivore_symbol_young;
        const char herbivoreSymbolYoung = no_herbivore_symbol_young;

        cout << "\nenter the symbol, the designation on the screen of an adult herbivore :";
        cin >> no_herbivore_symbol_old;
        const char herbivoreSymbolOld = no_herbivore_symbol_old;

        cout << "\nenter the symbol, the designation on the grass screen : ";
        cin >> no_grass_symbol;
        const int grassSymbol = no_grass_symbol;

        cout << "\nenter the symbol, the designation on the river screen : ";
        cin >> no_river_symbol;
        const char riverSymbol = no_river_symbol;

        cout << "\nenter the number of predators : ";
        cin >> no_predator_population;
        const int predatorPopulation = no_predator_population;

        cout << "\nenter the number of herbivores : ";
        cin >> herbivorePopulation;

        cout << "\nenter the amount of grass : ";
        cin >> grassPopulation;

        cout << "\nenter the probability of accidental death of animals at every step : (norm : 0.1)";
        cin >> no_death_probability_per_step;
        const double deathProbabilityPerStep = no_death_probability_per_step;

        cout << "\nenter the number of steps a young herbivore can take without eating food : ";
        cin >> no_young_herbivore_hunger_threshold;
        const int youngHerbivoreHungerThreshold = no_young_herbivore_hunger_threshold;

        cout << "\nenter the number of steps an adult herbivore can take without eating food : ";
        cin >> no_old_herbivore_hunger_threshold;
        const int oldHerbivoreHungerThreshold = no_old_herbivore_hunger_threshold;

        cout << "\nenter the number of steps a young predator can take without eating food : ";
        cin >> no_young_predator_hunger_threshold;
        const int youngPredatorHungerThreshold = no_young_predator_hunger_threshold;

        cout << "\nenter the number of steps an adult predator can take without eating food : ";
        cin >> no_old_predator_hungeg_threshold;
        const int oldPredatorHungerThreshold = no_old_predator_hungeg_threshold;

        cout << "\nenter the probability of natural disasters - tsunami : ";
        cin >> tsunami_probability;

        cout << "\nenter the maximum age of predators and herbivores : ";
        cin >> age_predators_herbivores;

        cout << "\nenter the minimum and maximum reproductive age of predators and herbivores : ";
        cin >> reproductive_animals_min;
        cout << endl;
        cin >> reproductive_animals_max;

        cout << "\nenter the probability of fertility of predators and herbivores : (norm = 0.0005)";
        cin >> probability_reproduce;
    } 

    Animal grid[screenHeight][screenWidth];
    initializeGrid(grid);

    // Place animals, grass, and rivers
    placeRandomAnimals(grid, predatorSymbolYoung, predatorSymbolOld, predatorPopulation);
    placeRandomAnimals(grid, herbivoreSymbolYoung, herbivoreSymbolOld, herbivorePopulation);
    placeRandomGrass(grid, grassPopulation);
    placeRandomRivers(grid, 5); // Adjust the river count as needed

    int herbivoreCount = 0;
    int youngHerbivoreCount = 0;
    int youngPredatorCount = 0;
    int oldHerbivoreCount = 0;
    int oldPredatorCount = 0;
    int deadHerbivoreCount = 0;
    int remainingGrassCount = grassPopulation;
    int steps = 0;
    int currentSeason = 0;
    double currentRegrowthRate = 0.0; // Default to no regrowth
    int oldAgeDeathCount = 0;

    bool isTsunami = false;
    bool gameEnded = false;
    std::string userInput;  // Variable to store user input

    while (steps < 576 && !gameEnded) {
        system(CLEAR_SCREEN);

        if (rand() % 100 < tsunami_probability) {     // вероятность цунами
            isTsunami = true;
        }

        if (isTsunami) {
            // Set the terminal color to blue
            std::cout << "\033[1;34m";

            // Color empty cells (cells with no animals) with blue
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

            // Reset the terminal color
            std::cout << "\033[0m";

            // Remove all living animals from the grid
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
            // Вывод информации о симуляции
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

            // Reproduce animals
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
                                    predatorEatHerbivore(grid, i, j, k, l, deadHerbivoreCount, predatorCount);
                                }
                            }
                        }
                    }
                }
            }

            // Age animals every 24 steps
            ageAnimals(grid, herbivoreCount, predatorCount, deadHerbivoreCount, steps, oldAgeDeathCount);

            // Count young animals
            countYoungAnimals(grid, youngHerbivoreCount, youngPredatorCount);

            // Check herbivores for starvation
            checkStarvationHerbivores(grid, herbivoreCount, deadHerbivoreCount, remainingGrassCount);

            // Calculate regrowth of grass based on the current season
            double currentRegrowthRate = 0.0; // Default to no regrowth

            switch (currentSeason) {
            case 0: // Summer
                currentRegrowthRate = grassRegrowthRateSummer;
                break;
            case 1: // Autumn
                currentRegrowthRate = grassRegrowthRateSpringFall;
                break;
            case 2: // Winter
                currentRegrowthRate = grassRegrowthRateWinter;
                break;
            case 3: // Spring
                currentRegrowthRate = grassRegrowthRateSpringFall;
                break;
            }

            // Only place random grass if the regrowth rate is greater than 0
            if (currentRegrowthRate > 0.0) {
                int regrowthAmount = static_cast<int>(grassPopulation * currentRegrowthRate);
                placeRandomGrass(grid, regrowthAmount);

                // Recalculate counts
                remainingGrassCount += regrowthAmount;
            }

            // Update season every 6 steps
            if ((steps + 1) % 6 == 0) {
                currentSeason = (currentSeason + 1) % 4;
            }

            // Call countAnimals to update the counts
            countAnimals(grid, herbivoreCount, predatorCount, youngHerbivoreCount, youngPredatorCount, oldHerbivoreCount, oldPredatorCount);

            // Обновление температуры
            updateTemperature(currentTemperature, steps, currentSeason);

            ++steps;
        }
    }

    return 0;
}
