#include<iostream>
#include<vector>	
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
		cin >> input;

		if (input == "end") {
			break;
		}
		inputArray[count] = input;
		count++;
	}

	
	int newCount = 0;

	for (int i = 0; i < count; i++) {
		while (true) {							
			if (!(cin >> inputArray[i])) {
				cin.clear();					
				cin.ignore();
				cout << "error!";
				continue;
			}
			break;
		}										
		if (inputArray[i] != "end") {
			newArray[newCount] = inputArray[i];
			newCount++;
		}
	}

	cout << "Input array elements without 'end': " << endl;
	for (int i = 0; i < newCount; i++) {
		cout << newArray[i] << " ";
	}
	cout << endl;
														
}

int main() {
	checking_entered_elements();

	return 0;
}



