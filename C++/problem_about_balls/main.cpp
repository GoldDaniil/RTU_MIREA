#include <iostream>
#include <algorithm>

using namespace std;

void print_permutation(int permutation[], int size) {
    for (int i = 0; i < size; i++) {
        cout << permutation[i] << " ";
    }
    cout << endl;
}

bool is_valid_permutation(int permutation[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        if (permutation[i] == 1 && permutation[i + 1] == 2) {
            return true;
        }
    }
    return false;
}

void generate_permutation(int permutation[], int n, int i, int& count) {
    if (i == n) {
        if (is_valid_permutation(permutation, n)) {
            print_permutation(permutation, n);
            count++;
        }
        return;
    }

    for (int j = i; j < n; j++) {
        swap(permutation[i], permutation[j]);
        generate_permutation(permutation, n, i + 1, count);
        swap(permutation[i], permutation[j]);
    }
}

int main() {
    while (true) {
        int n;
        while (true) {
            cout << "enter the number of balls: ";
            if (!(cin >> n)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "error\n";
                continue;
            }
            break;
        }

        if (n <= 0) {
            cout << "Number of balls should be positive.\n";
            continue;
        }

        int* balls = new int[n];
        for (int i = 0; i < n; i++) {
            balls[i] = i + 1;
        }

        int count = 0;

        generate_permutation(balls, n, 0, count);

        cout << "\ntotal number of valid permutations: " << count << endl;
        delete[] balls;
    }

    return 0;
}
