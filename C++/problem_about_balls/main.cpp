// The plot of the problem is about balls. One ball is taken out of the urn with 10 numbered balls.
// Calculate the total number of situations when the number of at least one removed ball coincides
// with the sequence number of the "taking out" action, for example, when ball No. 3 is taken out
// by the 3rd in order.
// Сюжет задачи про шарики. Из урны с 10 пронумерованными шариками вынимают по одному шарику. 
// Подсчитать общее количество ситуаций, когда номер хотя бы одного вынутого шарика совпадает 
// с порядковым номером действия "вынимания", например, когда шарик № 3 будет вынут 3-им по порядку.

#include<iostream>
#include<string>
#include<algorithm>
#include<cstdlib>

using namespace std;

const int number_balls = 10;  // количество шариков
int* arr = new int[number_balls]; // выделяем память под массив шариков
int count_situations = 0; // количество ситуаций

void generate_permutations(int selected_count) { 
	if (selected_count == number_balls) {   // вывод очередной перестановки	
		// проверяем, совпадает ли номер вынутого шарика с порядковым номером действия
		for (int i = 0; i < number_balls; ++i) {
			cout << arr[i] << " ";
			if (arr[i] == i + 1) {
				count_situations++;
			}
		} 
		cerr << endl;
		exit(0);
		//return; 
	} 
	else {
		for (int j = selected_count; j < number_balls; ++j) {		// запускаем процесс обмена
			swap(arr[selected_count], arr[j]);
			generate_permutations(selected_count + 1); // рекурсивный вызов функции
			swap(arr[selected_count], arr[j]); // восстанавливаем порядок для следующей итерации
			//sum_numbers++;	
			//sum_numbers--;
		}
	}
}

int main() {
	// иницилизируем массив шариков
	for (int k = 0; k < number_balls; ++k) {
		arr[k] = k + 1;
	}

	generate_permutations(3);
	cout << "total situations: " << count_situations << endl;

	delete[] arr;

	return 0;
}
