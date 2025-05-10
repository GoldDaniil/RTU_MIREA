// Финальный вариант

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<string>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

const char predator_symbol_young = 'p';
const char predator_symbol_old = 'P';
const char herbivore_symbol_young = 'h';
const char herbivore_symbol_old = 'H';
const char grass_symbol = '#';
const char river_symbol = '~';
const char mountain_symbol = '^';
int mountain_population = 100; // количество гор
const int screen_width = 200;
const int screen_height = 30;
int predator_population = 1800;
int herbivore_population = 1200;
int grass_population = 4000; // количество травы
const double grass_regrowth_rate_summer = 0.031; // вероятность восстанавливаемости травы летом 
const double grass_regrowth_rate_springfall = 0.0155; // вероятность восстанавливаемости травы осенью и весной 
const double grass_regrowth_rate_winter = 0.0; // вероятность восстанавливаемости травы зимой 
const double death_probability_per_step = 0.1;
double current_temperature = 20.0; // начальная температура
double tsunami_probability = 0.3; // вероятность цунами
const int young_herbivore_hunger_threshold = 3; // сколько шагов молодое травоядное животное может пройти без еды
const int young_predator_hunger_threshold = 3; // сколько шагов молодой хищник может пройти без еды
const int old_herbivore_hunger_threshold = 6; // сколько шагов старое травоядное животное может пройти без еды
const int old_predator_hunger_threshold = 6; // сколько шагов старый хищник может пройти без еды
const int predator_starvation_threshold = 4; // сколько шагов хищник может пройти без еды

struct Animal {
    char symbol;
    int age;
    int steps_without_eating;
};

struct Poacher {
    int x;
    int y;
    bool active; // активен ли браконьер в этом сезоне
};

const int max_poachers = 100;
Poacher poachers[max_poachers];

const char poacher_symbol = 'B';

void spawnPoachers(Poacher poachers[], Animal grid[][screen_width], std::string season) {
    int poacherCount = 0;
    for (int i = 0; i < max_poachers; ++i) {
        poachers[i].active = false;
    }

    if (season == "spring" || season == "summer") {
        poacherCount = rand() % (max_poachers / 2 + 1) + (max_poachers / 2); // от 5 до 10

        for (int i = 0; i < poacherCount; ++i) {
            while (true) {
                int x = rand() % screen_height;
                int y = rand() % screen_width;

                if (grid[x][y].symbol == ' ') {
                    poachers[i] = { x, y, true };
                    grid[x][y].symbol = 'P'; // символ браконьера
                    break;
                }
            }
        }
    }
}

#include <algorithm> // Для std::min и std::max

void movePoachers(Poacher poachers[], int count, Animal grid[][screen_width],
    int& herbivore_count, int& predator_count) {
    for (int i = 0; i < count; ++i) {
        if (!poachers[i].active) continue;

        // Удаляем старый символ
        grid[poachers[i].x][poachers[i].y].symbol = ' ';

        // Случайное перемещение
        int dx = (rand() % 3) - 1; // -1, 0, 1
        int dy = (rand() % 3) - 1;
        int newX = std::min(std::max(poachers[i].x + dx, 0), screen_height - 1);
        int newY = std::min(std::max(poachers[i].y + dy, 0), screen_width - 1);

        poachers[i].x = newX;
        poachers[i].y = newY;

        // Убиваем животных рядом
        for (int x = std::max(0, newX - 1); x <= std::min(screen_height - 1, newX + 1); ++x) {
            for (int y = std::max(0, newY - 1); y <= std::min(screen_width - 1, newY + 1); ++y) {
                char sym = grid[x][y].symbol;
                if (sym == herbivore_symbol_young || sym == herbivore_symbol_old) {
                    grid[x][y].symbol = ' ';
                    --herbivore_count;
                }
                else if (sym == predator_symbol_young || sym == predator_symbol_old) {
                    grid[x][y].symbol = ' ';
                    --predator_count;
                }
            }
        }

        // Отображаем браконьера
        grid[newX][newY].symbol = poacher_symbol;
    }
}

void poachersKillNearbyAnimals(Poacher poachers[], Animal grid[][screen_width]) {
    const char animals[] = { herbivore_symbol_young, herbivore_symbol_old,
                            predator_symbol_young, predator_symbol_old };

    for (int i = 0; i < max_poachers; ++i) {
        if (!poachers[i].active) continue;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int x = poachers[i].x + dx;
                int y = poachers[i].y + dy;

                if (x >= 0 && x < screen_height && y >= 0 && y < screen_width) {
                    for (char animal : animals) {
                        if (grid[x][y].symbol == animal) {
                            grid[x][y].symbol = ' ';
                            break;
                        }
                    }
                }
            }
        }
    }
}

int natural_death_predator_count = 0;
int predator_count = 0;

void placeRandomMountains(Animal grid[][screen_width], int mountainCount) {
    int count = 0;
    while (count < mountainCount) {
        int x = rand() % screen_height;
        int y = rand() % screen_width;

        if (grid[x][y].symbol == ' ') {
            grid[x][y].symbol = mountain_symbol;
            ++count;
        }
    }
}

void initializeGrid(Animal grid[][screen_width]) {
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

void placeRandomRivers(Animal grid[][screen_width], int riverCount) {
    for (int i = 0; i < riverCount; ++i) {
        int riverSize = rand() % 4 + 6; // случайный размер реки от 2х2 до 5х5

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
        << " | Poacher: " << poachers
        << " | Max poacher: " << max_poachers
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

void placeRandomGrass(Animal grid[][screen_width], int population) {
    for (int i = 0; i < population; ++i) {
        int x = rand() % screen_height;
        int y = rand() % screen_width;
        grid[x][y].symbol = grass_symbol;
        grid[x][y].age = 0; // возраст травы не имеет значения - установлен в 0
    }
}

void moveRandomly(Animal grid[][screen_width], char animal_symbol) {
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

void eatGrass(Animal grid[][screen_width], int x, int y, int& remaining_grass_count) {
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

bool isAdjacent(int x1, int y1, int x2, int y2, const Animal grid[][screen_width]) {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1 && grid[x2][y2].symbol != mountain_symbol;
}

void herbivoreEatGrass(Animal grid[][screen_width], int herbivoreX, int herbivoreY, int& remaining_grass_count) {
    for (int i = max(0, herbivoreX - 1); i < min(screen_height, herbivoreX + 2); ++i) {
        for (int j = max(0, herbivoreY - 1); j < min(screen_width, herbivoreY + 2); ++j) {
            if (grid[i][j].symbol == grass_symbol && (i != herbivoreX || j != herbivoreY) && grid[i][j].symbol != river_symbol && grid[i][j].symbol != mountain_symbol) {
                eatGrass(grid, i, j, remaining_grass_count);
            }
        }
    }
}

void predatorEatHerbivore(Animal grid[][screen_width], int predatorX, int predatorY, int herbivoreX,
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

void ageAnimals(Animal grid[][screen_width], int& herbivore_count, int& predator_count, int& dead_herbivore_count,
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
    // проверка - принадлежат ли два животного к одному типу и находятся ли они рядом
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

void checkStarvation(Animal grid[][screen_width], int& herbivore_count, int& predator_count, int& dead_herbivore_count,
    int& natural_death_predator_count) {
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

void checkStarvationHerbivores(Animal grid[][screen_width], int& herbivore_count, int& dead_herbivore_count,
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

void placeRandomPoachers(Poacher poachers[], int count, Animal grid[][screen_width]) {
    for (int i = 0; i < count; ++i) {
        int x, y;
        do {
            x = rand() % screen_height;
            y = rand() % screen_width;
        } while (grid[x][y].symbol != ' '); // свободная ячейка

        poachers[i] = { x, y, true };
        grid[x][y].symbol = poacher_symbol;
    }
}


int main() {
    srand(static_cast<unsigned>(time(0)));

    Animal grid[screen_height][screen_width];
    initializeGrid(grid);

    // размещение животных - травы и рек
    placeRandomAnimals(grid, predator_symbol_young, predator_symbol_old, predator_population);
    placeRandomAnimals(grid, herbivore_symbol_young, herbivore_symbol_old, herbivore_population);
    placeRandomGrass(grid, grass_population);
    placeRandomRivers(grid, 5); // количество рек

    int herbivore_count = 0;
    int young_herbivore_count = 0;
    int young_predator_count = 0;
    int old_herbivore_count = 0;
    int old_predator_count = 0;
    int dead_herbivore_count = 0;
    int remaining_grass_count = grass_population;
    int steps = 0;
    int current_season = 0;
    double current_regrowth_rate = 0.0;
    int old_age_death_count = 0;


    bool is_tsunami = false;
    bool game_ended = false;
    string user_input;  // переменная для хранения пользовательских данных

    int poacher_count = rand() % max_poachers;
    placeRandomPoachers(poachers, poacher_count, grid);


    while (steps < 576 && !game_ended) {
        system(CLEAR_SCREEN);

        if (rand() % 100 < tsunami_probability) {     // вероятность цунами
            is_tsunami = true;
        }

        if (is_tsunami) {
            cout << "\033[1;34m";
            for (int i = 0; i < screen_height; ++i) {
                for (int j = 0; j < screen_width; ++j) {
                    cout << (grid[i][j].symbol == ' ' ? ' ' : grid[i][j].symbol);
                }
                cout << endl;
            }
            cout << "\033[0m";

            // удялаем всех живых животных из сетки
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
            // вывод информации о симуляции - счетчик
            printGrid(grid, herbivore_count, predator_count, young_herbivore_count, young_predator_count, old_herbivore_count,
                old_predator_count, dead_herbivore_count, remaining_grass_count, steps, current_season,
                natural_death_predator_count, current_temperature, old_age_death_count);

            cout << "\nEnter 'exit'/'EXIT' to exit the game. Or press Enter move animals... ";
            getline(cin, user_input);

            if (user_input == "exit" or user_input == "EXIT") {
                cout << "\nokay. goodbye :( \n";
                break;
            }

            // движение животных и размножение
            moveRandomly(grid, predator_symbol_young);
            moveRandomly(grid, predator_symbol_old);
            moveRandomly(grid, herbivore_symbol_young);
            moveRandomly(grid, herbivore_symbol_old);

            // рождение детей
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

            // проверка на голод перед тем - как животные поедят
            checkStarvation(grid, herbivore_count, predator_count, dead_herbivore_count, natural_death_predator_count);

            // травоядные едят траву после шагов
            for (int i = 0; i < screen_height; ++i) {
                for (int j = 0; j < screen_width; ++j) {
                    if (grid[i][j].symbol == herbivore_symbol_young || grid[i][j].symbol == herbivore_symbol_old) {
                        herbivoreEatGrass(grid, i, j, remaining_grass_count);
                    }
                }
            }

            // хищники едят травоядных
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
            
            movePoachers(poachers, max_poachers, grid, herbivore_count, predator_count);


            // увеличение возраста на 1 - животных кажждые 24 шага 
            ageAnimals(grid, herbivore_count, predator_count, dead_herbivore_count, steps, old_age_death_count);

            // счет молодых особей
            countYoungAnimals(grid, young_herbivore_count, young_predator_count);

            // проверка травоядных на предмет голодания
            checkStarvationHerbivores(grid, herbivore_count, dead_herbivore_count, remaining_grass_count);

            // расчет отрастание травы на основе текущего сезона
            double current_regrowth_rate = 0.0;

            switch (current_season) {
            case 0: // лето
                current_regrowth_rate = grass_regrowth_rate_summer;
                break;
            case 1: // осень
                current_regrowth_rate = grass_regrowth_rate_springfall;
                break;
            case 2: // зима
                current_regrowth_rate = grass_regrowth_rate_winter;
                break;
            case 3: // весна
                current_regrowth_rate = grass_regrowth_rate_springfall;
                break;
            }

            // случайная траву только в том случае - если скорость отрастания превышает 0
            if (current_regrowth_rate > 0.0) {
                int regrowth_amount = static_cast<int>(grass_population * current_regrowth_rate);
                placeRandomGrass(grid, regrowth_amount);

                // пересчет отсчета
                remaining_grass_count += regrowth_amount;
            }

            // обновления сезона каждые 6 шагов
            if ((steps + 1) % 6 == 0) {
                current_season = (current_season + 1) % 4;
            }

            // вызов countAnimals для обновления подсчета
            countAnimals(grid, herbivore_count, predator_count, young_herbivore_count, young_predator_count, old_herbivore_count, old_predator_count);

            // обновление температуры
            updateTemperature(current_temperature, steps, current_season);

            ++steps;
        }
    }

    return 0;
}
