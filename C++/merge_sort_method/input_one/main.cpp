#include<iostream>
#include<vector>	//!Да, префиксная сумма и операнды могут помешать кэшированию результатов.!!!
#include<string>

using namespace std;

void checking_entered_elements() {

	const int maxSize = 100;
	string inputArray[maxSize];
	string newArray[maxSize];

	string input;
	int count = 0;

	cout << "Enter array elements. To end, enter 'end': " << endl;

	while (count < maxSize) {
		cin >> input;//массив с безтипной подушкой

		if (input == "end") {
			break;
		}
		inputArray[count] = input;
		count++;
	}

	// Создаем новый массив без элемента "end"    новый тип с подушкой
	int newCount = 0;

	for (int i = 0; i < count; i++) {
		while (true) {							//начало
			if (!(cin >> inputArray[i])) {
				cin.clear();					// проверить на директиву setlocale
				cin.ignore();
				cout << "error!";
				continue;
			}
			break;
		}										//конец
		if (inputArray[i] != "end") {
			newArray[newCount] = inputArray[i];
			newCount++;
		}
	}

	// Выводим элементы нового массива
	cout << "Input array elements without 'end': " << endl;
	for (int i = 0; i < newCount; i++) {
		cout << newArray[i] << " ";
	}
	cout << endl;
	//при вводе элементов в буферный массив - проверки на тип нет! , 
	// при передачи значений элементов из буферного массива в искомый массив проверка есть!
	//														  | отсортировывание элементов |
}

int main() {
	checking_entered_elements();

	return 0;
}



