#include <iostream>
#include <algorithm>

using namespace std;

void print_permutation(int permutation[], int size) {
    for (int i = 0; i < size; i++) {
        cout << permutation[i] << " ";
    }
    cout << endl;
}

void generate_permutation(int permutation[], int n, int i, int& count) {
    if (i == n) {
        count++;
        return;
    }

    for (int j = i; j < n; j++) {
        swap(permutation[i], permutation[j]);

        generate_permutation(permutation, n, i + 1, count);

        swap(permutation[i], permutation[j]);
    }
}

int main() {
    int n;
    while (true) {
        cout << "Enter the number of balls: ";
        if (!(cin >> n)) {
            cin.clear();
            cin.ignore();
            cout << "Error\n";
            continue;
        }
        break;
    }

    int* balls = new int[n];
    for (int i = 0; i < n; i++) {
        balls[i] = i + 1;
    }

    int count = 0;

    generate_permutation(balls, n, 0, count);

    cout << "\nTotal number of permutations with at least one match: " << count << endl;

    delete[] balls;
    
    return 0;
}
