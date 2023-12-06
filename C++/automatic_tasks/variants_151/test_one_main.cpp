#include <iostream>
#include <cstdlib>
#include <cmath>        //последняя версия
#include <vector>

//07.12.23 - задаю логику выбора статистики по необходимости
// предоставление возможности выбора пользователя


using namespace std;

const int MAX_ANIMALS = 1000; // максимальное количество животных
const int max_new_generation = 1000; // для репродукции

struct Animal {
    int age;
    int hunger;
    int reproductive_age_min;
    int reproductive_age_max;
    int max_age;
    double reproduction_rate;

    int x, y; // координаты на экране 
};

struct Environment {
    int screen_width;
    int screen_height;
    int initial_grass;
    double grass_regrowth_rate;
    double natural_disaster_probability;
    int herbivore_food_needed;
    int grass_food_needed;
    double grass_recovery_rate;
    double herbivore_food_recovery;
};

const int max_age = 20; //максимальный возрастной уровень
const int max_hunger = 5; //уровень голода для гибели
const int reproduction_age = 3; //возраст для репродукции
const int max_population_size = 1000; // максимальную численность населения

double calculate_distance(const Animal& animal1, const Animal& animal2) {
    return sqrt(pow(animal1.x - animal2.x, 2) + pow(animal1.y - animal2.y, 2));
}


void death_by_starvation(vector<Animal>& population) {
    population.erase(remove_if(population.begin(), population.end(), [](const Animal& animal) {
        return animal.hunger > max_hunger;
        }), population.end());
}


void reproduce(vector<Animal>& population) {
    vector<Animal> newGeneration;

    for (const auto& parent : population) {
        if (parent.age >= reproduction_age) {
            // логика рождения нового потомства
            Animal child;
            child.age = 0; // рождение
            child.hunger = 0; // начальный уровень голода
            newGeneration.push_back(child);
        }
    }

    // добавляем новых потомков в основную популяцию
    population.insert(population.end(), newGeneration.begin(), newGeneration.end());
}



void display_population_size(const vector<Animal>& herbivores, const vector<Animal>& predators) {
    cout << "Herbivores: " << herbivores.size() << ", Predators: " << predators.size() << endl;
}



void display_interaction(const Animal& herbivore, const Animal& predator) {
    cout << "display_interaction!" << endl;
}



void visualizeInteraction(const vector<Animal>& herbivores, const vector<Animal>& predators) {
    //код визуализации
}



void display_total_population(const vector<Animal>& herbivores, const vector<Animal>& predators) {
    cout << "Total number of herbivores: " << herbivores.size() << endl;
    cout << "Total number of predators: " << predators.size() << endl;
}


//передвижение травоядных и хишинков
void simulate_one_time_step(vector<Animal>& herbivores, vector<Animal>& predators, Environment& environment, int time_step, int total_simulation_steps) { 
    for (auto& herbivore : herbivores) {
        herbivore.x += rand() % 3 - 1; // случайное число от -1 до 1
        herbivore.y += rand() % 3 - 1;
    }

    for (auto& predator : predators) {
        predator.x += rand() % 3 - 1;
        predator.y += rand() % 3 - 1;
    }

    // старение особей
    for (auto& herbivore : herbivores) {
        herbivore.age++;
        herbivore.hunger++; // увеличиваем уровень голода
    }

    for (auto& predator : predators) {
        predator.age++;
        predator.hunger++;
    }

    // проверка взаимодействия хищников и травоядных
    for (const auto& herbivore : herbivores) {
        for (const auto& predator : predators) {
            double distance = calculate_distance(herbivore, predator);
            if (distance < 1.0) {
                display_interaction(herbivore, predator);
                // логика съедения травоядного хищником
            }
        }
    }

    // восстановление травы
    environment.initial_grass += static_cast<int>(environment.initial_grass * environment.grass_regrowth_rate);

    // логика гибели от голода
    death_by_starvation(herbivores);
    death_by_starvation(predators);

    // логика репродукции
    reproduce(herbivores);
    reproduce(predators);

    // визуализация взаимодействия (по желанию)
    visualizeInteraction(herbivores, predators);

    // вывод информации о текущем состоянии

    cout << "Number of herbivores: " << herbivores.size() << ", Predators: " << predators.size() << endl;
    cout << "Time step: " << time_step << "/" << total_simulation_steps << endl;
    display_population_size(herbivores, predators);
    cout << "Amount of grass: " << environment.initial_grass << endl;
    cout << "---------------------------" << endl;
}



void initialize_herbivore_population(Animal herbivores[], int initial_population, int max_age, int reproductive_age_min, int reproductive_age_max, double reproduction_rate) {
    for (int i = 0; i < initial_population; ++i) {
        herbivores[i].age = rand() % (max_age + 1);
        herbivores[i].hunger = 0; // начальное значение голода
        herbivores[i].reproductive_age_min = reproductive_age_min;
        herbivores[i].reproductive_age_max = reproductive_age_max;
        herbivores[i].max_age = max_age;
        herbivores[i].reproduction_rate = reproduction_rate;
    }
}

void initialize_predator_population(Animal predators[], int initial_population, int max_age, int reproductive_age_min, int reproductive_age_max, double reproduction_rate) {
    for (int i = 0; i < initial_population; ++i) {
        predators[i].age = rand() % (max_age + 1);
        predators[i].hunger = 0; // начальное значение голода
        predators[i].reproductive_age_min = reproductive_age_min;
        predators[i].reproductive_age_max = reproductive_age_max;
        predators[i].max_age = max_age;
        predators[i].reproduction_rate = reproduction_rate;
    }
}






int count_dead_herbivores(const vector<Animal>& herbivores) {
    return count_if(herbivores.begin(), herbivores.end(), [](const Animal& herbivore) {
        return herbivore.age >= herbivore.max_age; // предполагаем что умирают от старости
    });
}


int count_dead_predators(const std::vector<Animal>& predators) {
    return count_if(predators.begin(), predators.end(), [](const Animal& predator) {
        return predator.age >= predator.max_age; // предполагаем что умирают от старости
        });
}


void display_statistics_andexit(const vector<Animal>& herbivores, const vector<Animal>& predators, int herbivores_died, int predators_died) {
    display_total_population(herbivores, predators);

    cout << "herbivores died: " << herbivores_died << endl;
    cout << "predators died: " << predators_died << endl;
    
    // подумать над выводом другой статистики

    // предоставление возможности выбора пользователя
    char choice;
    cout << "do u want to run another simulation? (yes/no): ";
    cin >> choice;

    if (choice == 'no' || choice == 'No' || choice == 'NO' || choice == 'nO') {
        cout << "exiting the program.Goodbye!\n";
        exit(0);
    }

}


int main() {
    using namespace std;

    // инициализация параметров окружающей среды
    Environment environment;
    cout << "Enter environmental parameters:\n";
    cout << "screen width: ";
    cin >> environment.screen_width;
    cout << "screen height: ";
    cin >> environment.screen_height;
    cout << "initial grass quantity: ";
    cin >> environment.initial_grass;
    cout << "grass regrowth rate: ";
    cin >> environment.grass_regrowth_rate;
    cout << "probability of natural disasters: ";
    cin >> environment.natural_disaster_probability;
    cout << "number of herbivores needed for predator's food: ";
    cin >> environment.herbivore_food_needed;
    cout << "amount of grass needed for herbivore's food: ";
    cin >> environment.grass_food_needed;
    cout << "percentage of grass recovery: ";
    cin >> environment.grass_recovery_rate;
    cout << "amount of herbivore food recovered per year: ";
    cin >> environment.herbivore_food_recovery;

    // ввод данных о популяции травоядных и хищников
    int initial_herbivore_population, initial_predator_population;
    int max_herbivore_age, max_predator_age;
    int reproductive_age_min_herbivore, reproductive_age_max_herbivore, reproductive_age_min_predator, reproductive_age_max_predator;
    double reproduction_rate_herbivore, reproduction_rate_predator;

    //цвет
    cout << "Enter herbivore information:\n";
    //цвет
    cout << "initial quantity: ";
    cin >> initial_herbivore_population;
    cout << "maximum age: ";
    cin >> max_herbivore_age;
    cout << "minimum age for reproduction: ";
    cin >> reproductive_age_min_herbivore;
    cout << "maximum breeding age: ";
    cin >> reproductive_age_max_herbivore;
    cout << "reproduction level: ";
    cin >> reproduction_rate_herbivore;

    //цвет
    cout << "Enter predator data:\n";
    //цвет
    cout << "initial quantity: ";
    cin >> initial_predator_population;
    cout << "maximum age: ";
    cin >> max_predator_age;
    cout << "minimum age for reproduction: ";
    cin >> reproductive_age_min_predator;
    cout << "maximum breeding age: ";
    cin >> reproductive_age_max_predator;
    cout << "reproduction level: ";
    cin >> reproduction_rate_predator;

    vector<Animal> herbivores;
    vector<Animal> predators;

    for (int i = 0; i < initial_herbivore_population; ++i) {
        Animal herbivore;
        herbivore.age = rand() % (max_herbivore_age - 1) + 1;
        herbivore.hunger = rand() % 3;
        herbivore.x = rand() % environment.screen_width;
        herbivore.y = rand() % environment.screen_height;
        herbivores.push_back(herbivore);
    }

    for (int i = 0; i < initial_predator_population; ++i) {
        Animal predator;
        predator.age = rand() % (max_predator_age - 1) + 1;
        predator.hunger = rand() % 3;
        predator.x = rand() % environment.screen_width;
        predator.y = rand() % environment.screen_height;
        predators.push_back(predator);
    }

    int totalSimulationSteps = 10;
    int herbivores_died = 0; // счетчик умерших травоядных
    int predators_died = 0; // счетчик умерших хищников



    // Основной цикл моделирования
    for (int time_step = 0; time_step < total_simulation_steps; ++time_step) {
        simulate_one_time_step(herbivores, predators, environment, time_step, total_simulation_steps);

        // Обновление счетчиков умерших травоядных и хищников
        herbivores_died += count_dead_herbivores(herbivores);
        predators_died += count_dead_predators(predators);
    }

    display_statistics_andexit(herbivores, predators, herbivores_died, predators_died);

    return 0;
}
