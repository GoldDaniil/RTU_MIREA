//last versiont on this charge set_UP
//localized namespace and used method

#include "ArrayObject.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main() {
	int input_one, input_two;
	cin >> input_one >> input_two;
	
	if(input_one <= 4 || input_two <= 4) {
		cerr << (input_one <= 4 ? input_one : input_two) << "error";
		return 0;
	}

	ArrayObject first_object(input_one);
	ArrayObject second_object(input_two);
	
	first_object.print_array();
	second_object.print_array();
	
	return 0;
}
