#include<iostream>
#include<stdio.h>
#include<cmath>

using namespace std;

int main() {
    float i;
    /////////////////////////////
    ///task ""///1

    ///task "number sign"///2
    double variable_x, variable_result;
    ///task ""///3

    ///task ""///4

    ///task ""///5
    /////////////////////////////

    /////////////////////////////
    ///task "number sign"///2
    while (true) {
        cout << "enter variable x : " << endl;
        if (!(cin >> variable_x)) {
            cin.clear();
            cin.ignore();
            cout << "error!" << endl;
            continue;
        }
        break;
    }
    if (variable_x > 0) {
        cout << 1 << endl << endl;
    } else if (variable_x < 0) {
        cout << -1 << endl << endl;
    } else if (variable_x == 0) {
        cout << 0 << endl << endl;
    }
    return 0;
}
