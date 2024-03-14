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
        for(int num : array) {
            cout << num << " ";
        }
        cout << endl; //проверить на
    }     // возможность утечки памяти
};

int main()
{
    int input;
    cin >> input;
    
    if(input <= 4) {
        cout << input << "?";
        return 0;
    }
    
    ArrayObject first_object(input);
    
    cin >> input;
    
    if(input <= 4) {
        cout << input << "?";
        return 0;
    }
    
    ArrayObject second_object(input);
    
    first_object.set_second_object(second_object);
    
    first_object.print_array();
    second_object.print_array();
    
    return 0;
}
