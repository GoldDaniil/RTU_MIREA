#include <iostream>
#include <vector>
#include <cstdlib> 

using namespace std;

struct Animal {
    int age;
    // другие параметры координаты символы изображения
};

struct Environment {
    int screen_width;
    int screen_height;
    int initial_grass;
    double grass_regrowth_rate;
    double natural_disaster_probability;
    // здесь другие параметры окружающей среды
};

void initializeHerbivorePopulation(Animal herbivores[], int initialPopulation) {
    // инициализации травоядных

}

void initializePredatorPopulation(Animal predators[], int initialPopulation) {
    // инициализации хищников

}

int main() {
    // инициализация параметров окружающей среды
    Environment environment;
    environment.screen_width = 800;
    environment.screen_height = 600;
    environment.initial_grass = 1000;
    environment.grass_regrowth_rate = 0.02;
    environment.natural_disaster_probability = 0.05;

    int initial_herbivore_population, initial_predator_population;
    cout << "enter the initial number of herbivores: ";
    cin >> initial_herbivore_population;
    cout << "enter the initial number of predators: ";
    cin >> initial_predator_population;

    // инициализация популяции травоядных и хищников
    Animal herbivores[initial_herbivore_population];
    initializeHerbivorePopulation(herbivores, initial_herbivore_population);

    Animal predators[initial_predator_population];
    initializePredatorPopulation(predators, initial_predator_population);


    return 0;
}
