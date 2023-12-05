#include <iostream>
#include <cstdlib>
#include <cmath>        //последняя версия
#include <vector>

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
//void death_by_starvation(Animal population[], int& population_size) {
//    int new_population_size = 0;
//
//    for (int i = 0; i < population_size; ++i) {
//        if (population[i].hunger <= max_hunger) {
//            population[new_population_size++] = population[i];
//        }
//    }
//
//    population_size = new_population_size;
//}

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
//вариант с массивом
//void reproduce(Animal population[], int& population_size) {
//    Animal new_generation[max_population_size];
//    int new_population_size = 0;
//
//    for (int i = 0; i < population_size; ++i) {
//        if (population[i].age >= reproduction_age) {
//            //            // логика рождения нового потомства
//            Animal child;
//            child.age = 0;     // рождение
//            child.hunger = 0;  // начальный уровень
//
//            new_generation[new_population_size++] = child;
//        }
//    }
//
//    copy(new_generation, new_generation + new_population_size, population + population_size);
//    population_size += new_population_size;
//}


void display_population_size(const vector<Animal>& herbivores, const vector<Animal>& predators) {
    cout << "Herbivores: " << herbivores.size() << ", Predators: " << predators.size() << endl;
}
// вариант с массивом
//void display_population_size(int herbivores_count, int predators_count) {
//    cout << "Herbivores: " << herbivores_count << ", Predators: " << predators_count << endl;
//}


void display_interaction(const Animal& herbivore, const Animal& predator) {
    cout << "display_interaction!" << endl;
}
// вариант с массивом
//void display_interaction(const Animal& herbivore, const Animal& predator) {
//    cout << "Herbivore encountered a predator!" << endl;
//}


void visualizeInteraction(const vector<Animal>& herbivores, const vector<Animal>& predators) {
    //код визуализации
}
// вариант с массивом
//void visualize_interaction(const Animal herbivores[], int herbivores_count, const Animal predators[], int predators_count) {
//    //код визуализации
//}


void display_total_population(const vector<Animal>& herbivores, const vector<Animal>& predators) {
    cout << "Total number of herbivores: " << herbivores.size() << endl;
    cout << "Total number of predators: " << predators.size() << endl;
}

//начало основной цикл моделирования//
//const int max_populations_size = 1000;


void simulateOneTimeStep(vector<Animal>& herbivores, vector<Animal>& predators, Environment& environment, int time_step) {
    //передвижение травоядных и хишинков
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

    cout << "Number of herbivores: " << herbivores.size() << ", Predators: " << predators.size() << std::endl;
    cout << "Time step: " << time_step << endl;
    display_population_size(herbivores, predators);
    cout << "Amount of grass: " << environment.initial_grass << endl;
    cout << "---------------------------" << endl;

}

//вариант с массивом
//void simulate_one_time_step(Animal herbivores[], int& herbivore_count, Animal predators[], int& predator_count, Environment& environment) {
//
//    //передвижение травоядных и хишинков
//    for (int i = 0; i < herbivore_count; ++i) {
//        herbivores[i].x += rand() % 3 - 1; // случайное число от -1 до 1
//        herbivores[i].y += rand() % 3 - 1;
//    }
//    for (int i = 0; i < predator_count; ++i) {
//        predators[i].x += rand() % 3 - 1;
//        predators[i].y += rand() % 3 - 1;
//    }
//
//    //логика старения
//    for (int i = 0; i < herbivore_count; ++i) {
//        herbivores[i].age++;
//    }
//    for (int i = 0; i < predator_count; ++i) {
//        predators[i].age++;
//    }
//
//
//    // провера репродуктивного возраста - 
//    // вариант 1: просто удаляем особей старше максимального возраста - написано 
//    // вариант 2: удаляем после конкретной возраста(гугл) - не написано
//    herbivore_count = remove_if(herbivores, herbivores + herbivore_count, [](const Animal& herbivore) {
//        return herbivore.age > max_age;
//        }) - herbivores;
//
//    predator_count = remove_if(predators, predators + predator_count, [](const Animal& predator) {
//        return predator.age > max_age;
//        }) - predators;
//
//    // проверка взаимодействия хищников и травоядных
//    for (int i = 0; i < herbivore_count; ++i) {
//        for (int j = 0; j < predator_count; ++j) {
//            double distance = calculate_distance(herbivores[i], predators[j]);
//            if (distance < 1.0) {
//                // особь сьедена хищником
//                cout << "\nThe predator ate the herbivore!\n";
//                // дополнительная взаимодействия - разработать
//            }
//        }
//    }
//
//    // восстановление травы
//    environment.initial_grass += static_cast<int>(environment.initial_grass * environment.grass_regrowth_rate);
//
//
//    // гибель от голода
//    death_by_starvation(herbivores, herbivore_count);
//    death_by_starvation(predators, predator_count);
//
//
//    // репродукция
//    reproduce(herbivores, herbivore_count);
//    reproduce(predators, predator_count);
//
//    // взаимодействие хищников и травоядных
//    for (int i = 0; i < herbivore_count; ++i) {
//        for (int j = 0; j < predator_count; ++j) {
//            double distance = calculate_distance(herbivores[i], predators[j]);
//            if (distance < 1.0) {
//                // травоядное животное съедено хищником
//                display_interaction(herbivores[i], predators[j]);
//            }
//        }
//    }
//
//    visualize_interaction(herbivores, herbivore_count, predators, predator_count);
//
//
//}
//конец  Основной цикл моделирования


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

    // Основной цикл моделирования
    for (int time_step = 0; time_step < totalSimulationSteps; ++time_step) {
        simulateOneTimeStep(herbivores, predators, environment);
    }

    display_total_population(herbivores, predators);

    return 0;

    //// инициализация популяции травоядных и хищников
    //Animal herbivores[MAX_ANIMALS];
    //initialize_herbivore_population(herbivores, initial_herbivore_population, max_herbivore_age, reproductive_age_min_herbivore, reproductive_age_max_herbivore, reproduction_rate_herbivore);

    //Animal predators[MAX_ANIMALS];
    //initialize_predator_population(predators, initial_predator_population, max_predator_age, reproductive_age_min_predator, reproductive_age_max_predator, reproduction_rate_predator);

    //initial_herbivore_population = min(initial_herbivore_population, MAX_ANIMALS);
    //initial_predator_population = min(initial_predator_population, MAX_ANIMALS);

    //int herbivore_count = initial_herbivore_population;
    //int predator_count = initial_predator_population;

    //int simulation_duration = 100;

    //for (int time_step = 0; time_step < simulation_duration; ++time_step) {
    //    simulate_one_time_step(herbivores, herbivore_count, predators, predator_count, environment);


    //    //Отображение размера популяции на каждом временном шаге
    //    display_population_size(herbivore_count, predator_count);
    //}

    //// Вывод общего поголовья

    //display_total_population(herbivores, predators);

    //return 0;
}
