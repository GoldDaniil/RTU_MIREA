//main.cpp
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "Triangle.h"

using namespace std;

//функция - которая проверяет - является ли переменная целым или числом 
//с плавающей точкой(дробным числом) и предоставляет юзеру возможность 
//вводить значения переменной до тех пор - пока не будет введен верный 
//тип
float check_variable_int_float(string variable) {
	float result;
	
	while(true) { //запрашиваем ввод до тех пор - пока не будет введен верное значение
		try {
			result = stof(variable); //преобразуем введеное значение в число типа float
			return result; //возврат значения - если преобразование прошло успешно
		} catch(const exception& err) {
			cout << "eerror/ required type - integer/float \ntry entering again: ";
			getline(cin, variable); //запрашиваем ввод снова
		}
	}
}

int main() {
	string temporary_variable;
	int side_one, side_two, side_three;
	
	cout << "enter second side value: ";
	getline(cin, temporary_variable);
	float float_input = check_variable_int_float(temporary_variable);
	side_one = float_input;
	
	cout << "enter second side value: ";
	getline(cin, temporary_variable);
	float_input = check_variable_int_float(temporary_variable);
	side_two = float_input;
	
	cout << "enter second side value: ";
	getline(cin, temporary_variable);
	float_input = check_variable_int_float(temporary_variable);
	side_three = float_input;
	
	Triangle triangle(side_one, side_two, side_three);
	
	cout << "Triangle perimeter: P = " << triangle.get_perimeter() << endl;
	cout << "Triangle square: S = " << triangle.get_area() << endl;
	
	return 0;
}

//Triangle.cpp
#include "Triangle.h"
#include <cmath>

Triangle::Triangle(int first_side_value, int second_side_value, int third_side_value) :
	side_one(first_side_value), side_two(second_side_value), side_three(third_side_value) {}

int Triangle::get_perimeter() {
	return side_one + side_two + side_three;
}

double Triangle::get_area() {
	double semi_perimeter = (side_one + side_two + side_three) / 2.0;
	double square_triangle = semi_perimeter * (semi_perimeter - side_one) * (semi_perimeter - side_two) * (semi_perimeter - side_three);
	return sqrt(square_triangle);
}

//Triangle.h
#ifndef __TRIANGLE__H
#define __TRIANGLE__H

class Triangle {
private:
	int side_one, side_two, side_three;
		
public:
	Triangle(int first_side_value, int second_side_value, int third_side_value);
	
	int get_perimeter();
	double get_area();
};

#endif
