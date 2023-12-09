#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int screenWidth = 180;
const int screenHeight = 22;
const int numHerbivores = 70;
const int numPredators = 40;
const int movementRange = 1;

void initializePopulation(int population[][2], int size) {
    for (int i = 0; i < size; ++i) {
        population[i][0] = rand() % screenWidth;
        population[i][1] = rand() % screenHeight;

        // Рандомно определите направление по вертикали (вверх/вниз)
        int direction = rand() % 2 == 0 ? 1 : -1;
        population[i][1] += direction * (screenHeight / 2);
        population[i][1] = (population[i][1] + screenHeight) % screenHeight;
    }
}

void printPopulation(const int population[][2], int size, char symbol) {
    char screen[screenHeight][screenWidth];
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            screen[i][j] = ' ';
        }
    }

    for (int i = 0; i < size; ++i) {
        int x = population[i][0];
        int y = population[i][1];
        screen[y][x] = symbol;
    }

    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            std::cout << screen[i][j];
        }
        std::cout << std::endl;
    }
}

void movePopulation(int population[][2], int size) {
    for (int i = 0; i < size; ++i) {
        int deltaX = rand() % (2 * movementRange + 1) - movementRange;
        int deltaY = rand() % (2 * movementRange + 1) - movementRange;

        population[i][0] = (population[i][0] + deltaX + screenWidth) % screenWidth;
        population[i][1] = (population[i][1] + deltaY + screenHeight) % screenHeight;
    }
}

void simulateInteraction(int herbivores[][2], int predators[][2]) {
    for (int i = 0; i < numHerbivores; ++i) {
        for (int j = 0; j < numPredators; ++j) {
            int distanceX = abs(herbivores[i][0] - predators[j][0]);
            int distanceY = abs(herbivores[i][1] - predators[j][1]);

            if (distanceX <= 1 && distanceY <= 1) {
                // Herbivore eaten by predator
                herbivores[i][0] = -1;
                herbivores[i][1] = -1;
            }
        }
    }
}

void simulateEnvironmentalEvents(int herbivores[][2], int predators[][2], double probability) {
    for (int i = 0; i < numHerbivores; ++i) {
        if (rand() % 100 < probability) {
            herbivores[i][0] = -1;
            herbivores[i][1] = -1;
        }
    }

    for (int i = 0; i < numPredators; ++i) {
        if (rand() % 100 < probability) {
            predators[i][0] = -1;
            predators[i][1] = -1;
        }
    }
}

int main() {
    cout << "time\n";

    srand(static_cast<unsigned>(time(0)));

    int herbivores[numHerbivores][2];
    int predators[numPredators][2];

    initializePopulation(herbivores, numHerbivores);
    initializePopulation(predators, numPredators);

    for (int i = 0; i < 100; ++i) {
        //system("clear");  // For Linux/Mac
        system("cls");  // For Windows

        simulateInteraction(herbivores, predators);
        printPopulation(herbivores, numHerbivores, '0');
        printPopulation(predators, numPredators, '1');

        movePopulation(herbivores, numHerbivores);
        movePopulation(predators, numPredators);

        // Simulate environmental events with a probability of 70% to 100%
        double environmentalEventProbability = 70 + rand() % 31;
        simulateEnvironmentalEvents(herbivores, predators, environmentalEventProbability);

        std::cout << "Press Enter to continue...";
        std::cin.ignore();
    }

    return 0;
}
