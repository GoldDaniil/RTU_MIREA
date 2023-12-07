#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include<windows.h>
#include <thread>
#include <chrono>
#include<time.h>

using namespace std;

const int MAX_ANIMALS = 1000;
const int max_new_generation = 500;


struct Animal {
    int age;
    int reproductive_age_min;
    int reproductive_age_max;
    int max_age;
    double reproduction_rate;
    int x, y;
    int hunger;
    bool isAlive;
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

double calculate_distance(const Animal& animal1, const Animal& animal2) {
    return sqrt(pow(animal1.x - animal2.x, 2) + pow(animal1.y - animal2.y, 2));
}


void deathByStarvation(Animal population[], int& populationSize) {
    int newSize = 0;

    for (int i = 0; i < populationSize; ++i) {
        if (population[i].hunger <= max_hunger) {
            population[newSize++] = population[i];
        }
    }

    populationSize = newSize;
}

void reproduce(Animal population[], int& populationSize) {
    Animal newGeneration[max_new_generation];
    int newGenerationSize = 0;

    for (int i = 0; i < populationSize; ++i) {
        const auto& parent = population[i];

        if (parent.age >= reproduction_age) {
            // логика рождения нового потомства
            Animal child;
            child.age = 0; // рождение 
            child.hunger = 0; // начальный уровень 

            newGeneration[newGenerationSize++] = child;
        }
    }

    // Добавляем новых потомков в основную популяцию
    for (int i = 0; i < newGenerationSize; ++i) {
        population[populationSize++] = newGeneration[i];
    }
}


// Function to print an animal based on its state
void printAnimal(const Animal& animal) {
    if (!animal.isAlive) {
        // Print red "xo" for dead herbivore
        cout << "\033[1;31m" << "xo" << "\033[0m";
    }
    else {
        if (animal.hunger > 5) {
            // Print red "xl" for dead predator
            cout << "\033[1;31m" << "xl" << "\033[0m";
        }
        else {
            // Print "0" for herbivore and "1" for predator
            cout << (animal.reproduction_rate < 0.5 ? "0" : "1");
        }
    }
}

void printSimulationState(Animal herbivores[], int herbivoreCount, Animal predators[], int predatorCount, Environment& environment) {
    // Print the simulation state (grid of animals)
    for (int i = 0; i < environment.screen_height; ++i) {
        for (int j = 0; j < environment.screen_width; ++j) {
            bool foundAnimal = false;

            // Check for herbivores at (i, j)
            for (int h = 0; h < herbivoreCount; ++h) {
                if (herbivores[h].x == j && herbivores[h].y == i) {
                    printAnimal(herbivores[h]);
                    foundAnimal = true;
                    break;
                }
            }

            // Check for predators at (i, j)
            for (int p = 0; p < predatorCount; ++p) {
                if (predators[p].x == j && predators[p].y == i) {
                    printAnimal(predators[p]);
                    foundAnimal = true;
                    break;
                }
            }

            // If no animal found, print grass or empty space
            if (!foundAnimal) {
                cout << ".";
            }
        }
        cout << endl;
    }
    cout << "---------------------\n";
}

void simulate_one_time_step(Animal herbivores[], int& herbivoreCount, Animal predators[], int& predatorCount, Environment& environment) {

    //передвижение травоядных и хишинков
    for (int i = 0; i < herbivoreCount; ++i) {
        herbivores[i].x += rand() % 3 - 1; // случайное число от -1 до 1
        herbivores[i].y += rand() % 3 - 1;
    }
    for (int i = 0; i < predatorCount; ++i) {
        predators[i].x += rand() % 3 - 1;
        predators[i].y += rand() % 3 - 1;
    }

    //логика старения
    for (int i = 0; i < herbivoreCount; ++i) {
        herbivores[i].age++;
    }
    for (int i = 0; i < predatorCount; ++i) {
        predators[i].age++;
    }


    // провера репродуктивного возраста - 
    // вариант 1: просто удаляем особей старше максимального возраста - написано 
    // вариант 2: удаляем после конкретной возраста(гугл) - не написано
    herbivoreCount = remove_if(herbivores, herbivores + herbivoreCount, [](const Animal& herbivore) {
        return herbivore.age > max_age;
        }) - herbivores;

    predatorCount = remove_if(predators, predators + predatorCount, [](const Animal& predator) {
        return predator.age > max_age;
        }) - predators;

    // проверка взаимодействия хищников и травоядных
    for (int i = 0; i < herbivoreCount; ++i) {
        for (int j = 0; j < predatorCount; ++j) {
            double distance = calculate_distance(herbivores[i], predators[j]);
            if (distance < 1.0) {
                // особь сьедена хищником
                cout << "\nThe predator ate the herbivore!\n";
                // дополнительная взаимодействия - разработать
            }
        }
    }

    // восстановление травы
    environment.initial_grass += static_cast<int>(environment.initial_grass * environment.grass_regrowth_rate);


    deathByStarvation(herbivores, herbivoreCount);
    deathByStarvation(predators, predatorCount);

    // Логика репродукции
    reproduce(herbivores, herbivoreCount);
    reproduce(predators, predatorCount);

    printSimulationState(herbivores, herbivoreCount, predators, predatorCount, environment);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Sleep for 500 milliseconds (adjust as needed)


}

void initialize_herbivore_population(Animal herbivores[], int initial_population, int max_age, int reproductive_age_min, int reproductive_age_max, double reproduction_rate) {
    for (int i = 0; i < initial_population; ++i) {
        herbivores[i].age = rand() % (max_age + 1);
        herbivores[i].reproductive_age_min = reproductive_age_min;
        herbivores[i].reproductive_age_max = reproductive_age_max;
        herbivores[i].max_age = max_age;
        herbivores[i].reproduction_rate = reproduction_rate;
        herbivores[i].isAlive = true; // Initialize the isAlive flag
    }
}

void initialize_predator_population(Animal predators[], int initial_population, int max_age, int reproductive_age_min, int reproductive_age_max, double reproduction_rate) {
    for (int i = 0; i < initial_population; ++i) {
        predators[i].age = rand() % (max_age + 1);
        predators[i].reproductive_age_min = reproductive_age_min;
        predators[i].reproductive_age_max = reproductive_age_max;
        predators[i].max_age = max_age;
        predators[i].reproduction_rate = reproduction_rate;
        predators[i].isAlive = true; // Initialize the isAlive flag
    }
}


int main() {
    using namespace std;

    // Инициализация параметров окружающей среды
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

    // Ввод данных о популяции травоядных и хищников
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

    // инициализация популяции травоядных и хищников
    Animal herbivores[MAX_ANIMALS];
    initialize_herbivore_population(herbivores, initial_herbivore_population, max_herbivore_age, reproductive_age_min_herbivore, reproductive_age_max_herbivore, reproduction_rate_herbivore);

    Animal predators[MAX_ANIMALS];
    initialize_predator_population(predators, initial_predator_population, max_predator_age, reproductive_age_min_predator, reproductive_age_max_predator, reproduction_rate_predator);

    while (true) {
        // Simulate one time step
        simulate_one_time_step(herbivores, initial_herbivore_population, predators, initial_predator_population, environment);

        // Add exit condition if needed
        // For example, exit the loop after a certain number of iterations
        static int iteration = 0;
        if (++iteration >= 100) {
            break;
        }
    }

    return 0;
}
