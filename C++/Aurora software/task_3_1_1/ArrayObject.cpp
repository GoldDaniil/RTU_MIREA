#include "ArrayObject.h"
#include <iostream>
#include <vector>

using namespace std;

ArrayObject::ArrayObject(int size) {
	array.resize(size, size);
}

void ArrayObject::set_second_object(const ArrayObject& second_object) {
	array = second_object.array;
}

void ArrayObject::print_array() const {
		for(int i = 0; i < array.size(); ++i) {
			cout << array[i];
			if(i != array.size() - 1) {
				cout << " ";
			}
		}
		cout << endl;
}
