// The plot of the problem is about balls. One ball is taken out of the urn with 10 numbered balls.
// Calculate the total number of situations when the number of at least one removed ball coincides
// with the sequence number of the "taking out" action, for example, when ball No. 3 is taken out
// by the 3rd in order.
// Сюжет задачи про шарики. Из урны с 10 пронумерованными шариками вынимают по одному шарику. 
// Подсчитать общее количество ситуаций, когда номер хотя бы одного вынутого шарика совпадает 
// с порядковым номером действия "вынимания", например, когда шарик № 3 будет вынут 3-им по порядку.

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void print_permutation(int permutation[], int size) {
    for (int i = 0; i < size; i++) {
        cout << permutation[i] << " ";
    }
    cout << endl;
}

void generate_permutation(int permutation[], int n, int i, int& count, vector<int*>& valid_permutations) {
    if (i == n) {
        bool has_match = false;
        for (int j = 0; j < n; j++) {
            if (permutation[j] == j + 1) {
                has_match = true;
                break;
            }
        }

        if (has_match) {
            count++;
            int* valid_permutation = new int[n];
            copy(permutation, permutation + n, valid_permutation);
            valid_permutations.push_back(valid_permutation);
        }

        return;
    }

    for (int j = i; j < n; j++) {
        swap(permutation[i], permutation[j]);

        generate_permutation(permutation, n, i + 1, count, valid_permutations);

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
                cin.ignore();
                cout << "\nerror!\n";
                continue;
            }
            break;
        }

        int* balls = new int[n];
        for (int i = 0; i < n; i++) {
            balls[i] = i + 1;
        }

        int count_matches = 0;
        vector<int*> valid_permutations;

        generate_permutation(balls, n, 0, count_matches, valid_permutations);

        cout << "\npermutations with at least one match:\n";
        for (int i = 0; i < valid_permutations.size(); i++) {
            print_permutation(valid_permutations[i], n);
        }
        cout << "\ntotal number of permutations with at least one match: " << count_matches << endl << endl;

        cout << "\nall permutations:\n";
        do {
            print_permutation(balls, n);
        } while (next_permutation(balls, balls + n));

        int total_permutations = 1;
        for (int i = 1; i <= n; i++) {
            total_permutations *= i;
        }

        cout << "\ntotal permutations: " << total_permutations << endl;

        for (int i = 0; i < valid_permutations.size(); i++) {
            delete[] valid_permutations[i];
        }

        delete[] balls;
    }
    

    return 0;
}
