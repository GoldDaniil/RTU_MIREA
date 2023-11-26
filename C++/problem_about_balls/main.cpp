// The plot of the problem is about balls. One ball is taken out of the urn with 10 numbered balls.
// Calculate the total number of situations when the number of at least one removed ball coincides
// with the sequence number of the "taking out" action, for example, when ball No. 3 is taken out
// by the 3rd in order.
// Сюжет задачи про шарики. Из урны с 10 пронумерованными шариками вынимают по одному шарику. 
// Подсчитать общее количество ситуаций, когда номер хотя бы одного вынутого шарика совпадает 
// с порядковым номером действия "вынимания", например, когда шарик № 3 будет вынут 3-им по порядку.

#include<iostream>

using namespace std;

void print_permutation(int permutation[], int size) {
	for (int i = 0; i < size; i++) {
		cout << permutation[i] << " ";
	}
	cout << endl;
}

void generate_permutation(int permutation[], int m, int n, int i) {
	if (i == n) {
		print_permutation(permutation, n);
		return;
	}

	if (i == m) {
		print_permutation(permutation, n);
	}
	else {
		for (int j = i; j < n; j++) {
			swap(permutation[i], permutation[j]);
			generate_permutation(permutation, m, n, i + 1);
			swap(permutation[i], permutation[j]);
		}
	}
}

int main() {
	int n;
	while (true) {
		cout << "enter the number of balls: ";
		if (!(cin >> n)) {
			cin.clear();
			cin.ignore();
			cout << "error\n";
			continue;
		}
		break;
	}

	int* balls = new int[n];
	for (int i = 0; i < n; i++) {
		balls[i] = i + 1;
	}

	int count = 0;

	generate_permutation(balls, n, n, 1);

	cout << "kolvo : " << count << endl;

	delete[] balls;

	return 0;
}
