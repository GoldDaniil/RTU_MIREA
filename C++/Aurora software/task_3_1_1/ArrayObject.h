#ifndef __ARRAYOBJECT__H
#define __ARRAYOBJECT__H

#include <vector>

using namespace std;

class ArrayObject {
private:
	vector<int> array;

public:
	ArrayObject(int size);
	void set_second_object(const ArrayObject& second_object);
	void print_array() const;
};

#endif
