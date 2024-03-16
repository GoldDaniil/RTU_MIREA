//last versiont on this charge set_UP
//localized namespace and used method

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

class ArrayObject {
private:
    vector<int> array;

public:
    ArrayObject(int size) {
        array.resize(size, size);
    }

    void set_second_object(const ArrayObject& second_object) {
        array = second_object.array;
    }

    void print_array() const {
        for(int i = 0; i < array.size(); ++i) {
            cout << array[i];
            if (i != array.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    int input1, input2;
    cin >> input1 >> input2;

    if(input1 <= 4 || input2 <= 4) {
        cout << (input1 <= 4 ? input1 : input2) << "error";
        return 0;
    }

    ArrayObject first_object(input1);
    ArrayObject second_object(input2);

    first_object.print_array();
    second_object.print_array();

    return 0;
}
