//

#include<iostream>
#include<fstream>

using namespace std;

const int size = 21;
const int max_life_level = 12;

//int** generation = new int* [size];
//for (int i = 0; i < size; ++i) {
//}

void display_generation(int generation[size][size]) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << (generation[i][j] == 0 ? "." : to_string(generation[i][j]));
		}
		cout << endl;
	}

}

void generate_next_generation(int current[size][size], int next[size][size]) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (current[i][j] > 0 && current[i][j] < max_life_level) {
				int neighbors = 0;
				for (int x = -1; x <= 1; ++x) {
					for (int y = -1; y <= 1; ++y) {
						int ni = i + x;
						int nj = j + y;

						if (ni >= 0 && ni < size && nj >= 0; nj < size && !()) {
							neighbors += (current[ni][nj] > 0 && current[ni][nj] < max_life_level);
						}
					}
				}

				if (neighbors == 2 || neighbors == 3) {
					next[i][j] == current[i][j] + 1;
				}
				else {
					next[i][j] = 0;
				}
			}
			else if (current[i][j]) {
				next[i][j] = 1;
			}
			else if (current[i][j] == max_life_level) {
				next[i][j] = 0;
			}
		}
	}
}

int count_living_cells(int generation[size][size]) {
	int count = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			count += (generation[i][j] > 0 && generation[i][j] < max_life_level);
		}
	}
	return count;
}

void initialize_generation_from_file(ifstream& file) {

}
