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
const char predator_symbol_young = 'p';
const char predator_symbol_old = 'P';
const char herbivore_symbol_young = 'h';
const char herbivore_symbol_old = 'H';
const char grass_symbol = '#';
const char river_symbol = '~';
const int screen_width = 200;
const int screen_height = 30;
int predator_population = 1200;
int herbivore_population = 1200;
int grass_population = 4000;
const double grass_regrowth_rate_summer = 0.031;
const double grass_regrowth_rate_springfall = 0.0155;
const double grass_regrowth_rate_winter = 0.0;
const double death_probability_per_step = 0.1;
double current_temperature = 20.0; // Начальная температура
double tsunami_probability = 0.3;
const int young_herbivore_hunger_threshold = 3; // Сколько шагов молодое травоядное животное может пройти без еды
const int young_predator_hunger_threshold = 3; // Сколько шагов молодой хищник может пройти без еды
const int old_herbivore_hunger_threshold = 6; // Сколько шагов старое травоядное животное может пройти без еды
const int old_predator_hunger_threshold = 6; // Сколько шагов старый хищник может пройти без еды
const int predator_starvation_threshold = 4; // Number of steps a predator can go without successfully hunting

struct Animal {
    char symbol;
    int age;
    int steps_without_eating;
};

int natural_death_predator_count = 0;
int predator_count = 0;

void initializeGrid(Animal grid[][screen_width]) {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            grid[i][j].symbol = ' ';
            grid[i][j].age = 0;
            grid[i][j].steps_without_eating = 0;
        }
    }
}

void placeRandomRivers(Animal grid[][screen_width], int riverCount) {
    for (int i = 0; i < riverCount; ++i) {
        int riverSize = rand() % 4 + 6; // Random river size between 2x2 and 5x5

        int riverX = rand() % (screen_height - riverSize);
        int riverY = rand() % (screen_width - riverSize);

        for (int x = riverX; x < riverX + riverSize; ++x) {
            for (int y = riverY; y < riverY + riverSize; ++y) {
                grid[x][y].symbol = river_symbol;
            }
        }
    }
}

void printGrid(const Animal grid[][screen_width], int herbivore_count, int predator_count,
    int young_herbivore_count, int young_predator_count, int old_herbivore_count, int old_predator_count,
    int dead_herbivore_count, int remaining_grass_count, int current_step, int current_season,
    int natural_death_predator_count, double current_temperature, int& old_age_death_count) {

    cout << "Herbivores: " << max(0, herbivore_count)
        << " | Predators: " << max(0, predator_count)
        << " | Young Herbivores (< 10 years): " << young_herbivore_count
        << " | Young Predators (< 10 years): " << young_predator_count
        << " | Old Herbivores (>= 10 years): " << old_herbivore_count
        << " | Old Predators (>= 10 years): " << old_predator_count
        << " | Dead Herbivores: " << dead_herbivore_count
        << " | Natural Deaths (Predators): " << natural_death_predator_count
        << " | Old Age Deaths: " << old_age_death_count
        << " | Remaining Grass: " << remaining_grass_count
        << " | Step: " << current_step + 1
        << " | Current Temperature: " << current_temperature << "^C"
        << " | Season: ";

    switch (current_season) {
    case 0:
        cout << "Summer";
        break;
    case 1:
        cout << "Autumn";
        break;
    case 2:
        cout << "Winter";
        break;
    case 3:
        cout << "Spring";
        break;
    default:
        cout << "+";
        break;
    }

    cout << endl << endl;

    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == grass_symbol) {
                if (current_season == 1) {
                    cout << "\033[1;33m" << grid[i][j].symbol << "\033[0m"; // Set color to orange for grass in autumn
                }
                // Check if it's winter and color the grass white
                else if (current_season == 2) {
                    cout << "\033[1;37m" << grid[i][j].symbol << "\033[0m"; // Set color to white for grass in winter
                }
                else {
                    cout << "\033[1;32m" << grid[i][j].symbol << "\033[0m"; // Set color to green for grass
                }
            }
            else if (grid[i][j].symbol == river_symbol) {
                cout << "\033[1;34m" << grid[i][j].symbol << "\033[0m"; // Set color to blue for rivers
            }
            else if (grid[i][j].symbol == herbivore_symbol_young) {
                cout << "\033[1;31m" << grid[i][j].symbol << "\033[0m"; // Set color to red for young herbivores
            }
            else if (grid[i][j].symbol == predator_symbol_young) {
                cout << "\033[1;31m" << grid[i][j].symbol << "\033[0m"; // Set color to red for young predators
            }
            else {
                cout << grid[i][j].symbol;
            }
        }
        cout << endl;
    }
}

void countAnimals(const Animal grid[][screen_width], int& herbivore_count, int& predator_count,
    int& young_herbivore_count, int& young_predator_count, int& old_herbivore_count, int& old_predator_count) {
    herbivore_count = 0;
    predator_count = 0;
    young_herbivore_count = 0;
    young_predator_count = 0;
    old_herbivore_count = 0;
    old_predator_count = 0;

    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == herbivore_symbol_young) {
                ++herbivore_count;
                ++young_herbivore_count;
            }
            else if (grid[i][j].symbol == herbivore_symbol_old) {
                ++herbivore_count;
                ++old_herbivore_count;
            }
            else if (grid[i][j].symbol == predator_symbol_young) {
                ++predator_count;
                ++young_predator_count;
            }
            else if (grid[i][j].symbol == predator_symbol_old) {
                ++predator_count;
                ++old_predator_count;
            }
        }
    }
}

void placeRandomAnimals(Animal grid[][screen_width], char young_symbol, char old_symbol, int total_population) {
    for (int i = 0; i < total_population; ++i) {
        int x = rand() % screen_height;
        int y = rand() % screen_width;
        int age = rand() % 20 + 1; // Set age randomly between 1 and 20

        if (age <= 10) {
            grid[x][y].symbol = young_symbol;
        }
        else {
            grid[x][y].symbol = old_symbol;
        }

        grid[x][y].age = age;
    }
}

void placeRandomGrass(Animal grid[][screen_width], int population) {
    for (int i = 0; i < population; ++i) {
        int x = rand() % screen_height;
        int y = rand() % screen_width;
        grid[x][y].symbol = grass_symbol;
        grid[x][y].age = 0; // Grass age is irrelevant, set to 0
    }
}

void moveRandomly(Animal grid[][screen_width], char animal_symbol) {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == animal_symbol) {
                grid[i][j].symbol = ' '; // Clear current position

                // Move in a random direction
                int direction = rand() % 4;
                int newI = i;
                int newJ = j;

                switch (direction) {
                case 0: // Move up
                    if ((i > 0) && (grid[i - 1][j].symbol != river_symbol)) {
                        newI = i - 1;
                    }
                    break;
                case 1: // Move down
                    if ((i < screen_height - 1) && (grid[i + 1][j].symbol != river_symbol)) {
                        newI = i + 1;
                    }
                    break;
                case 2: // Move left
                    if ((j > 0) && (grid[i][j - 1].symbol != river_symbol)) {
                        newJ = j - 1;
                    }
                    break;
                case 3: // Move right
                    if ((j < screen_width - 1) && (grid[i][j + 1].symbol != river_symbol)) {
                        newJ = j + 1;
                    }
                    break;
                }

                // Check if the new position is grass, and if so, revert the changes
                if (grid[newI][newJ].symbol == grass_symbol) {
                    grid[newI][newJ].steps_without_eating = 0;
                }

                grid[newI][newJ].symbol = animal_symbol; // Update position
                grid[newI][newJ].age = grid[i][j].age + 1; // Increment age
            }
        }
    }
}

void eatGrass(Animal grid[][screen_width], int x, int y, int& remaining_grass_count) {
    grid[x][y].symbol = ' '; // Clear grass
    --remaining_grass_count;
}

void updateTemperature(double& current_temperature, int steps, int current_season) {
    int random_temperature_change = 0;

    switch (current_season) {
    case 0: // Summer
        random_temperature_change = (steps / 3) % 2 == 0 ? rand() % 13 + 18 : -(rand() % 13 + 1);
        break;

    case 1: // Autumn
        random_temperature_change = (steps / 3) % 2 == 0 ? min(rand() % 11, 10) : -(rand() % 14 + 4);

        // Ensure the temperature change doesn't make the temperature go above 10 degrees Celsius
        if (current_temperature + random_temperature_change > 10) {
            random_temperature_change = max(-10.0, 10.0 - current_temperature);
        }
        break;
    case 2: // Winter
        random_temperature_change = (steps / 3) % 2 == 0 ? max(-(rand() % 21 + 10), -30) : min(rand() % 26 - 25, -10);
        break;
    case 3: // Spring
        random_temperature_change = (steps / 3) % 2 == 0 ? min(rand() % 11 + 5, 15) : max(-(rand() % 11 + 5), -10);

        // Ensure the temperature change doesn't make the temperature go above 20 degrees Celsius
        if (current_temperature + random_temperature_change > 20) {
            random_temperature_change = max(-10.0, 20.0 - current_temperature);
        }
        break;
    }

    // Update the temperature
    current_temperature += random_temperature_change;

    // Ensure the temperature stays within a reasonable range (e.g., -10 to 30 degrees Celsius)
    current_temperature = max(-10.0, min(30.0, current_temperature));
}

bool isAdjacent(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1;
}

void herbivoreEatGrass(Animal grid[][screen_width], int herbivoreX, int herbivoreY, int& remaining_grass_count) {
    for (int i = max(0, herbivoreX - 1); i < min(screen_height, herbivoreX + 2); ++i) {
        for (int j = max(0, herbivoreY - 1); j < min(screen_width, herbivoreY + 2); ++j) {
            if (grid[i][j].symbol == grass_symbol && (i != herbivoreX || j != herbivoreY) && grid[i][j].symbol != river_symbol) {
                eatGrass(grid, i, j, remaining_grass_count);
            }
        }
    }
}

void predatorEatHerbivore(Animal grid[][screen_width], int predatorX, int predatorY, int herbivoreX,
    int herbivoreY, int& dead_herbivore_count, int& predator_count) {
    if (isAdjacent(predatorX, predatorY, herbivoreX, herbivoreY)) {
        // Check the age of the predator and herbivore
        bool is_young_predator = (grid[predatorX][predatorY].symbol == predator_symbol_young);
        bool is_young_herbivore = (grid[herbivoreX][herbivoreY].symbol == herbivore_symbol_young);

        if ((is_young_predator && is_young_herbivore) || (!is_young_predator && !is_young_herbivore)) {
            // Predator and herbivore have the same age group, predator eats herbivore
            grid[herbivoreX][herbivoreY].symbol = ' '; // Clear herbivore
            ++dead_herbivore_count;
            grid[predatorX][predatorY].steps_without_eating = 0; // Reset hunger counter
        }
        else {
            // Predator and herbivore have different age groups
            if (grid[predatorX][predatorY].steps_without_eating >= 2) {
                // Predator dies if not enough prey
                --predator_count;  // Use the parameter passed from the main function
                grid[predatorX][predatorY].symbol = ' '; // Clear predator
                grid[predatorX][predatorY].steps_without_eating = 0; // Reset hunger counter
            }
            else {
                // Predator eats herbivore and resets hunger counter
                grid[predatorX][predatorY].symbol = ' '; // Clear predator
                grid[predatorX][predatorY].steps_without_eating = 0; // Reset hunger counter
            }
        }
    }
}

void ageAnimals(Animal grid[][screen_width], int& herbivore_count, int& predator_count, int& dead_herbivore_count,
    int& current_step, int& old_age_death_count) {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == predator_symbol_young || grid[i][j].symbol == herbivore_symbol_young) {
                // Increment age and hunger counters every 24 steps (1 year)
                if ((current_step + 1) % 24 == 0) {
                    grid[i][j].age += 2;  // Увеличьте возраст на 2 вместо 1
                    grid[i][j].steps_without_eating += 1;

                    if (grid[i][j].age >= 480) {
                        // Если хищник достиг возраста 20, он не обязательно должен умереть, уменьшим вероятность
                        if (rand() % 100 < 10) {  // Уменьшим вероятность смерти
                            --predator_count;
                            grid[i][j].symbol = ' ';
                            grid[i][j].age = 0;
                            ++old_age_death_count;
                        }
                    }

                    else if (grid[i][j].age >= 350) {  // Увеличьте возраст на 20
                        // Если хищник достиг возраста 10, он становится старым
                        if (grid[i][j].symbol == predator_symbol_young) {
                            grid[i][j].symbol = predator_symbol_old;
                        }
                        else {
                            grid[i][j].symbol = herbivore_symbol_old;
                        }
                    }
                }
            }
        }
    }
}

void countYoungAnimals(const Animal grid[][screen_width], int& young_herbivore_count, int& young_predator_count) {
    young_herbivore_count = 0;
    young_predator_count = 0;

    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == herbivore_symbol_young && grid[i][j].age < 10) {
                ++young_herbivore_count;
            }
            else if (grid[i][j].symbol == predator_symbol_young && grid[i][j].age < 10) {
                ++young_predator_count;
            }
        }
    }
}

void reproduce(Animal grid[][screen_width], int x1, int y1, int x2, int y2, char young_symbol, char old_symbol,
    int& herbivore_count, int& predator_count) {
    // Check if the two animals are of the same type and are adjacent
    if ((grid[x1][y1].symbol == grid[x2][y2].symbol) && isAdjacent(x1, y1, x2, y2)) {
        // Check if the reproduction probability is met (1% chance)
        if (rand() % 100 < 0.0005) {
            for (int i = max(0, x1 - 1); i < min(screen_height, x1 + 2); ++i) {
                for (int j = max(0, y1 - 1); j < min(screen_width, y1 + 2); ++j) {
                    if (grid[i][j].symbol == ' ') {
                        // Reproduction successful, create a new offspring
                        if (grid[x1][y1].symbol == predator_symbol_young || grid[x1][y1].symbol == herbivore_symbol_young) {
                            // Limit the number of offspring created to 1
                            grid[i][j].symbol = (grid[x1][y1].age <= 10) ? young_symbol : old_symbol;
                            grid[i][j].age = 0;
                            grid[i][j].steps_without_eating = 0;

                            // Update counts based on the offspring type
                            if (grid[i][j].symbol == young_symbol) {
                                if (grid[i][j].symbol == herbivore_symbol_young) {
                                    ++herbivore_count;
                                }
                                else {
                                    ++predator_count;
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

void checkStarvation(Animal grid[][screen_width], int& herbivore_count, int& predator_count, int& dead_herbivore_count,
    int& natural_death_predator_count) {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == predator_symbol_young || grid[i][j].symbol == predator_symbol_old) {
                int hunger_threshold = (grid[i][j].symbol == predator_symbol_young) ? young_predator_hunger_threshold : old_predator_hunger_threshold;
                int starvation_counter = (grid[i][j].symbol == predator_symbol_young) ? predator_starvation_threshold : predator_starvation_threshold * 2;

                if (grid[i][j].steps_without_eating >= hunger_threshold) {
                    // Predator died of starvation
                    --predator_count;
                    ++natural_death_predator_count;  // Increment the new counter
                    grid[i][j].symbol = ' ';
                    grid[i][j].steps_without_eating = 0;
                }
                else if (grid[i][j].steps_without_eating >= starvation_counter) {
                    // Predator died of starvation without successful predation
                    --predator_count;
                    grid[i][j].symbol = ' ';
                    grid[i][j].steps_without_eating = 0;
                }
                else {
                    // Check if the predator has successfully hunted in the last month
                    bool has_hunted = false;

                    for (int k = 0; k < screen_height; ++k) {
                        for (int l = 0; l < screen_width; ++l) {
                            if (grid[k][l].symbol == herbivore_symbol_young || grid[k][l].symbol == herbivore_symbol_old) {
                                if (isAdjacent(i, j, k, l)) {
                                    // Predator successfully hunted a herbivore
                                    has_hunted = true;
                                    grid[i][j].steps_without_eating = 0; // Reset hunger counter
                                    break;
                                }
                            }
                        }
                        if (has_hunted) {
                            break;
                        }
                    }

                    // If the predator hasn't hunted, increase the starvation counter
                    if (!has_hunted) {
                        grid[i][j].steps_without_eating++;
                    }
                }
            }
        }
    }
}

void checkStarvationHerbivores(Animal grid[][screen_width], int& herbivore_count, int& dead_herbivore_count,
    int& remaining_grass_count) {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == herbivore_symbol_young || grid[i][j].symbol == herbivore_symbol_old) {
                int hunger_threshold = (grid[i][j].symbol == herbivore_symbol_young) ? young_herbivore_hunger_threshold : old_herbivore_hunger_threshold;

                if (grid[i][j].steps_without_eating >= hunger_threshold) {
                    // Herbivore died of starvation
                    --herbivore_count;
                    ++dead_herbivore_count;
                    grid[i][j].symbol = ' ';
                    grid[i][j].steps_without_eating = 0;
                }
                else {
                    // Check if the herbivore has successfully eaten grass in the last month
                    bool has_eaten = false;

                    for (int k = max(0, i - 1); k < min(screen_height, i + 2); ++k) {
                        for (int l = max(0, j - 1); l < min(screen_width, j + 2); ++l) {
                            if (grid[k][l].symbol == grass_symbol && (k != i || l != j)) {
                                // Herbivore successfully ate grass
                                has_eaten = true;
                                grid[i][j].steps_without_eating = 0; // Reset hunger counter
                                eatGrass(grid, k, l, remaining_grass_count);
                                break;
                            }
                        }
                        if (has_eaten) {
                            break;
                        }
                    }

                    // If the herbivore hasn't eaten, increase the starvation counter
                    if (!has_eaten) {
                        grid[i][j].steps_without_eating++;
                    }
                }
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    Animal grid[screen_height][screen_width];
    initializeGrid(grid);

    // Place animals, grass, and rivers
    placeRandomAnimals(grid, predator_symbol_young, predator_symbol_old, predator_population);
    placeRandomAnimals(grid, herbivore_symbol_young, herbivore_symbol_old, herbivore_population);
    placeRandomGrass(grid, grass_population);
    placeRandomRivers(grid, 5); // Adjust the river count as needed

    int herbivore_count = 0;
    int young_herbivore_count = 0;
    int young_predator_count = 0;
    int old_herbivore_count = 0;
    int old_predator_count = 0;
    int dead_herbivore_count = 0;
    int remaining_grass_count = grass_population;
    int steps = 0;
    int current_season = 0;
    double current_regrowth_rate = 0.0; // Default to no regrowth
    int old_age_death_count = 0;

    bool is_tsunami = false;
    bool game_ended = false;
    string user_input;  // Variable to store user input

    while (steps < 576 && !game_ended) {
        system(CLEAR_SCREEN);

        if (rand() % 100 < tsunami_probability) {     // вероятность цунами
            is_tsunami = true;
        }

        if (is_tsunami) {
            // Set the terminal color to blue
            cout << "\033[1;34m";

            // Color empty cells (cells with no animals) with blue
            for (int i = 0; i < screen_height; ++i) {
                for (int j = 0; j < screen_width; ++j) {
                    if (grid[i][j].symbol == ' ') {
                        cout << ' ';
                    }
                    else {
                        cout << grid[i][j].symbol;
                    }
                }
                cout << endl;
            }

            // Reset the terminal color
            cout << "\033[0m";

            // Remove all living animals from the grid
            for (int i = 0; i < screen_height; ++i) {
                for (int j = 0; j < screen_width; ++j) {
                    if (grid[i][j].symbol == predator_symbol_young || grid[i][j].symbol == predator_symbol_old ||
                        grid[i][j].symbol == herbivore_symbol_young || grid[i][j].symbol == herbivore_symbol_old) {
                        grid[i][j].symbol = ' ';
                    }
                }
            }

            game_ended = true;
        }
        else {
            // Вывод информации о симуляции
            printGrid(grid, herbivore_count, predator_count, young_herbivore_count, young_predator_count, old_herbivore_count,
                old_predator_count, dead_herbivore_count, remaining_grass_count, steps, current_season,
                natural_death_predator_count, current_temperature, old_age_death_count);


            cout << "\nEnter 'exit'/'EXIT' to exit the game. Or press Enter move animals... ";
            getline(cin, user_input);

            if (user_input == "exit" or user_input == "EXIT") {
                cout << "\nokay. goodbye :( \n";
                break;
            }

            // Движение животных и размножение
            moveRandomly(grid, predator_symbol_young);
            moveRandomly(grid, predator_symbol_old);
            moveRandomly(grid, herbivore_symbol_young);
            moveRandomly(grid, herbivore_symbol_old);

            // Reproduce animals
            for (int i = 0; i < screen_height; ++i) {
                for (int j = 0; j < screen_width; ++j) {
                    if (grid[i][j].symbol == predator_symbol_young || grid[i][j].symbol == predator_symbol_old) {
                        for (int k = 0; k < screen_height; ++k) {
                            for (int l = 0; l < screen_width; ++l) {
                                if (grid[k][l].symbol == predator_symbol_young || grid[k][l].symbol == predator_symbol_old) {
                                    reproduce(grid, i, j, k, l, predator_symbol_young, predator_symbol_old, herbivore_count, predator_count);
                                }
                            }
                        }
                    }
                    else if (grid[i][j].symbol == herbivore_symbol_young || grid[i][j].symbol == herbivore_symbol_old) {
                        for (int k = 0; k < screen_height; ++k) {
                            for (int l = 0; l < screen_width; ++l) {
                                if (grid[k][l].symbol == herbivore_symbol_young || grid[k][l].symbol == herbivore_symbol_old) {
                                    reproduce(grid, i, j, k, l, herbivore_symbol_young, herbivore_symbol_old, herbivore_count, predator_count);
                                }
                            }
                        }
                    }
                }
            }

            // Проверка на голод перед тем, как животные поедят
            checkStarvation(grid, herbivore_count, predator_count, dead_herbivore_count, natural_death_predator_count);

            // Herbivores eat grass after moving
            for (int i = 0; i < screen_height; ++i) {
                for (int j = 0; j < screen_width; ++j) {
                    if (grid[i][j].symbol == herbivore_symbol_young || grid[i][j].symbol == herbivore_symbol_old) {
                        herbivoreEatGrass(grid, i, j, remaining_grass_count);
                    }
                }
            }

            // Predators eat herbivores
            for (int i = 0; i < screen_height; ++i) {
                for (int j = 0; j < screen_width; ++j) {
                    if (grid[i][j].symbol == predator_symbol_young || grid[i][j].symbol == predator_symbol_old) {
                        for (int k = 0; k < screen_height; ++k) {
                            for (int l = 0; l < screen_width; ++l) {
                                if (grid[k][l].symbol == herbivore_symbol_young || grid[k][l].symbol == herbivore_symbol_old) {
                                    predatorEatHerbivore(grid, i, j, k, l, dead_herbivore_count, predator_count);
                                }
                            }
                        }
                    }
                }
            }

            // Age animals every 24 steps
            ageAnimals(grid, herbivore_count, predator_count, dead_herbivore_count, steps, old_age_death_count);

            // Count young animals
            countYoungAnimals(grid, young_herbivore_count, young_predator_count);

            // Check herbivores for starvation
            checkStarvationHerbivores(grid, herbivore_count, dead_herbivore_count, remaining_grass_count);

            // Calculate regrowth of grass based on the current season
            double current_regrowth_rate = 0.0; // Default to no regrowth

            switch (current_season) {
            case 0: // Summer
                current_regrowth_rate = grass_regrowth_rate_summer;
                break;
            case 1: // Autumn
                current_regrowth_rate = grass_regrowth_rate_springfall;
                break;
            case 2: // Winter
                current_regrowth_rate = grass_regrowth_rate_winter;
                break;
            case 3: // Spring
                current_regrowth_rate = grass_regrowth_rate_springfall;
                break;
            }

            // Only place random grass if the regrowth rate is greater than 0
            if (current_regrowth_rate > 0.0) {
                int regrowth_amount = static_cast<int>(grass_population * current_regrowth_rate);
                placeRandomGrass(grid, regrowth_amount);

                // Recalculate counts
                remaining_grass_count += regrowth_amount;
            }

            // Update season every 6 steps
            if ((steps + 1) % 6 == 0) {
                current_season = (current_season + 1) % 4;
            }

            // Call countAnimals to update the counts
            countAnimals(grid, herbivore_count, predator_count, young_herbivore_count, young_predator_count, old_herbivore_count, old_predator_count);

            // Обновление температуры
            updateTemperature(current_temperature, steps, current_season);

            ++steps;
        }
    }

    return 0;
}
