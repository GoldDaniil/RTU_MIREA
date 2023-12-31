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

double current_temperature = 20.0; // не вводим
const double grass_regrowth_rate_summer = 0.031; // не вводим
const double grass_regrowth_rate_springfall = 0.0155; // не вводим 
const double grass_regrowth_rate_winter = 0.0; // не вводим

const char mountain_symbol = '^';
int mountain_population = 100; // количество гор

int herbivore_population;    // вводим
int age_predators_herbivores; // вводим
int grass_population;         // вводим
int reproductive_animals_min, reproductive_animals_max; // вводим
int probability_reproduce;   // вводим
double tsunami_probability; // вводим

int screen_width; // вводим
int screen_height; // вводим

char predator_symbol_young; // вводим
char predator_symbol_old;   // вводим
char herbivore_symbol_young; // вводим
char herbivore_symbol_old;   // вводим
char grass_symbol;          // вводим
char river_symbol;          // вводим

int predator_population;            // вводим
double death_probability_per_step;   // вводим
int young_herbivore_hunger_threshold; // вводим
int young_predator_hunger_threshold;  // вводим
int old_herbivore_hunger_threshold;   // вводим
int old_predator_hunger_threshold;    // вводим
int predator_starvation_threshold;   // вводим

struct Animal {
    char symbol;
    int age;
    int steps_without_eating;
};

int natural_death_predator_count = 0;
int predator_count = 0;

void placeRandomMountains(Animal**& grid, int mountain_count) {
    int count = 0;
    while (count < mountain_count) {
        int x = rand() % screen_height;
        int y = rand() % screen_width;

        if (grid[x][y].symbol == ' ') {
            grid[x][y].symbol = mountain_symbol;
            ++count;
        }
    }
}

void initializeGrid(Animal**& grid, int rows, int cols) {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            grid[i][j].symbol = ' ';
            grid[i][j].age = 0;
            grid[i][j].steps_without_eating = 0;
        }
    }

    // случайное место горы
    placeRandomMountains(grid, mountain_population);
}

void placeRandomRivers(Animal**& grid, int river_count) {
    for (int i = 0; i < river_count; ++i) {
        int river_size = rand() % 4 + 6; // случайный размер реки от 2х2 до 5х5

        int riverX = rand() % (screen_height - river_size);
        int riverY = rand() % (screen_width - river_size);

        for (int x = riverX; x < riverX + river_size; ++x) {
            for (int y = riverY; y < riverY + river_size; ++y) {
                grid[x][y].symbol = river_symbol;
            }
        }
    }
}

void printGrid(Animal**& grid, int herbivore_count, int predator_count,
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
                    cout << "\033[1;33m" << grid[i][j].symbol << "\033[0m"; // оранжевый цвет для травы осенью
                }
                // если сейчас зима - трава = белый цвет
                else if (current_season == 2) {
                    cout << "\033[1;37m" << grid[i][j].symbol << "\033[0m"; // белый цвет для травы осенью
                }
                else {
                    cout << "\033[1;32m" << grid[i][j].symbol << "\033[0m"; // зеленый цвет для травы
                }
            }
            else if (grid[i][j].symbol == river_symbol) {
                cout << "\033[1;34m" << grid[i][j].symbol << "\033[0m"; // голубой цвет для реки
            }
            else if (grid[i][j].symbol == herbivore_symbol_young) {
                cout << "\033[1;31m" << grid[i][j].symbol << "\033[0m"; // красный цвет для новорожденных особей травоядных
            }
            else if (grid[i][j].symbol == predator_symbol_young) {
                cout << "\033[1;31m" << grid[i][j].symbol << "\033[0m"; // красный цвет для новорожденных особей хищников
            }
            else if (grid[i][j].symbol == mountain_symbol) {
                cout << "\033[1;37m" << grid[i][j].symbol << "\033[0m"; // белый цвет для гор
            }
            else {
                cout << grid[i][j].symbol;
            }
        }
        cout << endl;
    }
}

void countAnimals(Animal**& grid, int& herbivore_count, int& predator_count,
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

void placeRandomAnimals(Animal**& grid, char young_symbol, char old_symbol, int total_population) {
    for (int i = 0; i < total_population; ++i) {
        int x = rand() % screen_height;
        int y = rand() % screen_width;
        int age = rand() % 20 + 1; // устанавливаем возраст случайным образом от 1 до 20 лет

        if (age <= 10) {
            grid[x][y].symbol = young_symbol;   // если до 10 лет - молодая особь
        }
        else {
            grid[x][y].symbol = old_symbol; // если после 10 лет - взрослая особь
        }

        grid[x][y].age = age;
    }
}

void placeRandomGrass(Animal**& grid, int population) {
    for (int i = 0; i < population; ++i) {
        int x = rand() % screen_height;
        int y = rand() % screen_width;
        grid[x][y].symbol = grass_symbol;
        grid[x][y].age = 0; // возраст травы не имеет значения - установлен в 0
    }
}

void moveRandomly(Animal**& grid, char animal_symbol) {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == animal_symbol) {
                grid[i][j].symbol = ' ';

                // движение в случайном направлении
                int direction = rand() % 4;
                int newI = i;
                int newJ = j;

                switch (direction) {
                case 0: // двигаться вверх
                    if ((i > 0) && (grid[i - 1][j].symbol != river_symbol) && (grid[i - 1][j].symbol != mountain_symbol)) {
                        newI = i - 1;
                    }
                    break;
                case 1: // двигаться вниз
                    if ((i < screen_height - 1) && (grid[i + 1][j].symbol != river_symbol) && (grid[i + 1][j].symbol != mountain_symbol)) {
                        newI = i + 1;
                    }
                    break;
                case 2: // двигаться влево
                    if ((j > 0) && (grid[i][j - 1].symbol != river_symbol) && (grid[i][j - 1].symbol != mountain_symbol)) {
                        newJ = j - 1;
                    }
                    break;
                case 3: // двигаться направо
                    if ((j < screen_width - 1) && (grid[i][j + 1].symbol != river_symbol) && (grid[i][j + 1].symbol != mountain_symbol)) {
                        newJ = j + 1;
                    }
                    break;
                }

                // если новая позиция = трава = отменяем изменения
                if (grid[newI][newJ].symbol == grass_symbol) {
                    grid[newI][newJ].steps_without_eating = 0;
                }

                grid[newI][newJ].symbol = animal_symbol; // обновляем позицию
                grid[newI][newJ].age = grid[i][j].age + 1; // увеличиваем возраст
            }
        }
    }
}

void eatGrass(Animal**& grid, int x, int y, int& remaining_grass_count) {
    if (grid[x][y].symbol == grass_symbol && grid[x][y].symbol != mountain_symbol) {
        grid[x][y].symbol = ' '; // очищаем блок травы
        --remaining_grass_count;
    }
}

void updateTemperature(double& current_temperature, int steps, int current_season) {
    int random_temperature_change = 0;

    switch (current_season) {
    case 0: // лето
        random_temperature_change = (steps / 3) % 2 == 0 ? rand() % 13 + 18 : -(rand() % 13 + 1);
        break;

    case 1: // осень
        random_temperature_change = (steps / 3) % 2 == 0 ? min(rand() % 11, 10) : -(rand() % 14 + 4);

        // проверка = что при изменении температуры температура не поднимается выше 10 градусов 
        if (current_temperature + random_temperature_change > 10) {
            random_temperature_change = max(-10.0, 10.0 - current_temperature);
        }
        break;
    case 2: // зима
        random_temperature_change = (steps / 3) % 2 == 0 ? max(-(rand() % 21 + 10), -30) : min(rand() % 26 - 25, -10);
        break;
    case 3: // весна
        random_temperature_change = (steps / 3) % 2 == 0 ? min(rand() % 11 + 5, 15) : max(-(rand() % 11 + 5), -10);

        // проверка = что при изменении температуры температура не поднимается выше 20 градусов 
        if (current_temperature + random_temperature_change > 20) {
            random_temperature_change = max(-10.0, 20.0 - current_temperature);
        }
        break;
    }

    // обновляем темпу
    current_temperature += random_temperature_change;

    // проверяем что температура остается в разумных пределах (например = от -10 до 30 градусов)
    current_temperature = max(-10.0, min(30.0, current_temperature));
}

bool isAdjacent(int x1, int y1, int x2, int y2, Animal**& grid) {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1 && grid[x2][y2].symbol != mountain_symbol;
}

void herbivoreEatGrass(Animal**& grid, int herbivoreX, int herbivoreY, int& remaining_grass_count) {
    for (int i = max(0, herbivoreX - 1); i < min(screen_height, herbivoreX + 2); ++i) {
        for (int j = max(0, herbivoreY - 1); j < min(screen_width, herbivoreY + 2); ++j) {
            if (grid[i][j].symbol == grass_symbol && (i != herbivoreX || j != herbivoreY) && grid[i][j].symbol != river_symbol && grid[i][j].symbol != mountain_symbol) {
                eatGrass(grid, i, j, remaining_grass_count);
            }
        }
    }
}

void predatorEatHerbivore(Animal**& grid, int predatorX, int predatorY, int herbivoreX,
    int herbivoreY, int& dead_herbivore_count, int& predator_count) {
    if (isAdjacent(predatorX, predatorY, herbivoreX, herbivoreY, grid) && grid[herbivoreX][herbivoreY].symbol != mountain_symbol) {
        // проверка на возраст хищника и травоядного животного
        bool is_young_predator = (grid[predatorX][predatorY].symbol == predator_symbol_young);
        bool is_young_herbivore = (grid[herbivoreX][herbivoreY].symbol == herbivore_symbol_young);

        if ((is_young_predator && is_young_herbivore) || (!is_young_predator && !is_young_herbivore)) {
            // хищник и травоядное животное имеют одинаковую возрастную группу - хищник ест травоядное животное
            grid[herbivoreX][herbivoreY].symbol = ' '; // мертвое травоядное - очищаем herbivore
            ++dead_herbivore_count;
            grid[predatorX][predatorY].steps_without_eating = 0; // сбрасываем счетчик голода
        }
        else {
            // хищники и травоядные животные принадлежат к разным возрастным группам - хищник ест травоядное животное
            if (grid[predatorX][predatorY].steps_without_eating >= 4) {
                // хищник умирает - если не наелся
                --predator_count; // умирает
                grid[predatorX][predatorY].symbol = ' '; // очищаем доску экран
                grid[predatorX][predatorY].steps_without_eating = 0; // сбрасываем счетчик голода
            }
            else {
                // хищник сьедает травоядное животное и сбрасывает счетчик голода
                grid[predatorX][predatorY].symbol = ' '; // очищаем доску экран
                grid[predatorX][predatorY].steps_without_eating = 0; // сбрасываем счетчик голода
            }
        }
    }
}

void ageAnimals(Animal**& grid, int& herbivore_count, int& predator_count, int& dead_herbivore_count,
    int& current_step, int& old_age_death_count) {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == predator_symbol_young || grid[i][j].symbol == herbivore_symbol_young) {
                // увеличиваем счетчик возраста и голода каждые 24 шага (1 год)
                if ((current_step + 1) % 24 == 0) {
                    grid[i][j].age += 2;  // увеличиваем возраст на 2
                    grid[i][j].steps_without_eating += 1;

                    if (grid[i][j].age >= 480) {
                        // если хищник достиг возраста 20 = он обязательно должен умереть
                        if (rand() % 100 < 10) {  // вероятность смерти
                            --predator_count;
                            grid[i][j].symbol = ' ';
                            grid[i][j].age = 0;
                            ++old_age_death_count;
                        }
                    }

                    else if (grid[i][j].age >= 350) {
                        // если хищник достиг возраста 10 = он становится старым
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

void countYoungAnimals(Animal**& grid, int& young_herbivore_count, int& young_predator_count) {
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

void reproduce(Animal**& grid, int x1, int y1, int x2, int y2, char young_symbol, char old_symbol,
    int& herbivore_count, int& predator_count) {

    if ((grid[x1][y1].symbol == grid[x2][y2].symbol) && isAdjacent(x1, y1, x2, y2, grid)) {
        if (rand() % 100 < 0.0005) {
            for (int i = max(0, x1 - 1); i < min(screen_height, x1 + 2); ++i) {
                for (int j = max(0, y1 - 1); j < min(screen_width, y1 + 2); ++j) {
                    if (grid[i][j].symbol == ' ') {
                        if (grid[x1][y1].symbol == predator_symbol_young || grid[x1][y1].symbol == herbivore_symbol_young) {
                            grid[i][j].symbol = (grid[x1][y1].age <= 10) ? young_symbol : old_symbol;
                            grid[i][j].age = 0;
                            grid[i][j].steps_without_eating = 0;

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

void checkStarvation(Animal**& grid, int& herbivore_count, int& predator_count, int& dead_herbivore_count, int& natural_death_predator_count) {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == predator_symbol_young || grid[i][j].symbol == predator_symbol_old) {
                int hunger_threshold = (grid[i][j].symbol == predator_symbol_young) ? young_predator_hunger_threshold : old_predator_hunger_threshold;
                int starvation_counter = (grid[i][j].symbol == predator_symbol_young) ? predator_starvation_threshold : predator_starvation_threshold * 2;

                if (grid[i][j].steps_without_eating >= hunger_threshold) {
                    // хищник умирает от голода
                    --predator_count;
                    ++natural_death_predator_count;  // увеличиваем счетчик
                    grid[i][j].symbol = ' ';
                    grid[i][j].steps_without_eating = 0;
                }
                else if (grid[i][j].steps_without_eating >= starvation_counter) {
                    // хищник умер от голода  -  не сьел нужное колво
                    --predator_count;
                    grid[i][j].symbol = ' ';
                    grid[i][j].steps_without_eating = 0;
                }
                else {
                    // проверка успешно ли охотился хищник за последний месяц
                    bool has_hunted = false;

                    for (int k = 0; k < screen_height; ++k) {
                        for (int l = 0; l < screen_width; ++l) {
                            if (grid[k][l].symbol == herbivore_symbol_young || grid[k][l].symbol == herbivore_symbol_old) {
                                if (isAdjacent(i, j, k, l, grid)) {
                                    // хищник успешно охотился на травоядное животное
                                    has_hunted = true;
                                    grid[i][j].steps_without_eating = 0; // сбрасываем счетчик голода
                                    break;
                                }
                            }
                        }
                        if (has_hunted) {
                            break;
                        }
                    }

                    // если хищник не охотился - увеличиваем счетчик голодания
                    if (!has_hunted) {
                        grid[i][j].steps_without_eating++;
                    }
                }
            }
        }
    }
}

void checkStarvationHerbivores(Animal**& grid, int& herbivore_count, int& dead_herbivore_count,
    int& remaining_grass_count) {

    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            if (grid[i][j].symbol == herbivore_symbol_young || grid[i][j].symbol == herbivore_symbol_old) {
                int hunger_threshold = (grid[i][j].symbol == herbivore_symbol_young) ? young_herbivore_hunger_threshold : old_herbivore_hunger_threshold;

                if (grid[i][j].steps_without_eating >= hunger_threshold) {
                    // травоядное умирает от голода
                    --herbivore_count;
                    ++dead_herbivore_count;
                    grid[i][j].symbol = ' ';
                    grid[i][j].steps_without_eating = 0;
                }
                else {
                    // проверка успешно ли ел хищник за последний месяц
                    bool has_eaten = false;

                    for (int k = max(0, i - 1); k < min(screen_height, i + 2); ++k) {
                        for (int l = max(0, j - 1); l < min(screen_width, j + 2); ++l) {
                            if (grid[k][l].symbol == grass_symbol && (k != i || l != j)) {
                                // травоядный успешно сьедает траву - не голодает временно
                                has_eaten = true;
                                grid[i][j].steps_without_eating = 0; // сбрасываем счетчик голода
                                eatGrass(grid, k, l, remaining_grass_count);
                                break;
                            }
                        }
                        if (has_eaten) {
                            break;
                        }
                    }

                    // если травоядное не поело - увеличиваем счетчик голодания
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

    string user_input;
    cout << "start the game with default values and parameters? (yes/no): ";
    getline(cin, user_input);

    if (user_input == "no" || user_input == "NO" || user_input == "nO" || user_input == "No") {
        cout << "\nenter custom settings: \n";

        //cout << "\nenter the number of predators: ";
        //cin >> predator_population;

        cout << "\nenter the screen width: ";
        cin >> screen_width;

        cout << "\nenter the screen height: ";
        cin >> screen_height;

        cout << "\nenter the symbol for a young predator: ";
        cin >> predator_symbol_young;

        cout << "\nenter the symbol for an old predator: ";
        cin >> predator_symbol_old;

        cin >> herbivore_symbol_young;

    }
    else if (user_input == "yes" || user_input == "YES" || user_input == "Yes" || user_input == "yeS") {
        char predator_symbol_young = 'p';
        char predator_symbol_old = 'P';
        char herbivore_symbol_young = 'h';
        char herbivore_symbol_old = 'H';
        char grass_symbol = '#';
        char river_symbol = '~';
        int screen_width = 200;
        int screen_height = 30;
        int predator_population = 1200;
        int herbivore_population = 1200;
        int grass_population = 4000;
        double grass_regrowth_rate_summer = 0.031;
        double grass_regrowth_rate_springfall = 0.0155;
        double grass_regrowth_rate_winter = 0.0;
        double death_probability_per_step = 0.1;
        double current_temperature = 20.0; // Начальная температура
        double tsunami_probability = 0.3;
        int young_herbivore_hunger_threshold = 3; // Сколько шагов молодое травоядное животное может пройти без еды
        int young_predator_hunger_threshold = 3; // Сколько шагов молодой хищник может пройти без еды
        int old_herbivore_hunger_threshold = 6; // Сколько шагов старое травоядное животное может пройти без еды
        int old_predator_hunger_threshold = 6; // Сколько шагов старый хищник может пройти без еды
        int predator_starvation_threshold = 4; // Number of steps a predator can go without successfully hunting
    }

    Animal** grid;
    initializeGrid(grid, screen_height, screen_width);

    placeRandomAnimals(grid, predator_symbol_young, predator_symbol_old, predator_population);
    placeRandomAnimals(grid, herbivore_symbol_young, herbivore_symbol_old, herbivore_population);
    placeRandomGrass(grid, grass_population);
    placeRandomRivers(grid, 5);

    int herbivore_count = 0;
    int young_herbivore_count = 0;
    int young_predator_count = 0;
    int old_herbivore_count = 0;
    int old_predator_count = 0;
    int dead_herbivore_count = 0;
    int remaining_grass_count = grass_population;
    int steps = 0;
    int current_season = 0;
    double currentRegrowthRate = 0.0;
    int old_age_death_count = 0;

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

            cout << "\033[0m";

            for (int i = 0; i < screen_height; ++i) {
                for (int j = 0; j < screen_width; ++j) {
                    if (grid[i][j].symbol == predator_symbol_young || grid[i][j].symbol == predator_symbol_old ||
                        grid[i][j].symbol == herbivore_symbol_young || grid[i][j].symbol == herbivore_symbol_old) {
                        grid[i][j].symbol = ' ';
                    }
                }
            }

            gameEnded = true;
        }
        else {

            printGrid(grid, herbivore_count, predator_count, young_herbivore_count, young_predator_count, old_herbivore_count,
                old_predator_count, dead_herbivore_count, remaining_grass_count, steps, current_season,
                natural_death_predator_count, current_temperature, old_age_death_count);


            cout << "\nEnter 'exit'/'EXIT' to exit the game. Or press Enter move animals... ";
            getline(cin, userInput);

            if (userInput == "exit" or userInput == "EXIT") {
                cout << "\nokay. goodbye :( \n";
                break;
            }

            // Движение животных и размножение
            moveRandomly(grid, predator_symbol_young);
            moveRandomly(grid, predator_symbol_old);
            moveRandomly(grid, herbivore_symbol_young);
            moveRandomly(grid, herbivore_symbol_old);

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

            for (int i = 0; i < screen_height; ++i) {
                for (int j = 0; j < screen_width; ++j) {
                    if (grid[i][j].symbol == herbivore_symbol_young || grid[i][j].symbol == herbivore_symbol_old) {
                        herbivoreEatGrass(grid, i, j, remaining_grass_count);
                    }
                }
            }

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

            ageAnimals(grid, herbivore_count, predator_count, dead_herbivore_count, steps, old_age_death_count);

            countYoungAnimals(grid, young_herbivore_count, young_predator_count);

            checkStarvationHerbivores(grid, herbivore_count, dead_herbivore_count, remaining_grass_count);

            double currentRegrowthRate = 0.0;

            switch (current_season) {
            case 0:
                currentRegrowthRate = grass_regrowth_rate_summer;
                break;
            case 1:
                currentRegrowthRate = grass_regrowth_rate_springfall;
                break;
            case 2:
                currentRegrowthRate = grass_regrowth_rate_winter;
                break;
            case 3:
                currentRegrowthRate = grass_regrowth_rate_springfall;
                break;
            }

            if (currentRegrowthRate > 0.0) {
                int regrowthAmount = static_cast<int>(grass_population * currentRegrowthRate);
                placeRandomGrass(grid, regrowthAmount);

                remaining_grass_count += regrowthAmount;
            }

            if ((steps + 1) % 6 == 0) {
                current_season = (current_season + 1) % 4;
            }

            countAnimals(grid, herbivore_count, predator_count, young_herbivore_count, young_predator_count, old_herbivore_count, old_predator_count);

            updateTemperature(current_temperature, steps, current_season);

            ++steps;
        }
    }

    return 0;
}
