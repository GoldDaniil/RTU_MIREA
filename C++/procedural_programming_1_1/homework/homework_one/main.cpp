#include<iostream>
#include <cmath>

using namespace std;

int main() {
    string my_name = "Daniil";
    cout << my_name << endl;
    /////////////////////////

    double num1, num2;

    cout << "enter the first number: ";
    cin >> num1;

    cout << "enter the second number: ";
    cin >> num2;

    cout << "sum: " << num1 + num2 << endl;
    cout << "difference: " << num1 - num2 << endl;
    cout << "product: " << num1 * num2 << endl;

    if (num2 != 0) {
        cout << "quotient: " << num1 / num2 << endl;
    }
    else {
        cout << "division by zero is not possible\n";
    }
    /////////////////////////

    double b, c;

    cout << "enter the value of b: ";
    cin >> b;

    cout << "enter the value of c: ";
    cin >> c;

    if (b != 0) {
        double x = -c / b;
        cout << "solution: x = " << x << endl;
    }
    else {
        cout << "invalid equation. 'b' cannot be zero\n";
    }

    /////////////////////////

    double aa, bb, cc;

    while (true) {
        cout << "Enter the value of a: ";
        if (!(cin >> aa)) {
            cin.clear();
            cin.ignore();
            cout << "error\n";
            continue;
        } break;
    }

    while (true) {
        cout << "Enter the value of b: ";
        if (!(cin >> bb)) {
            cin.clear();
            cin.ignore();
            cout << "error\n";
            continue;
        } break;
    }

    while (true) {
        cout << "Enter the value of c: ";
        if (!(cin >> cc)) {
            cin.clear();
            cin.ignore();
            cout << "error\n";
            continue;
        } break;
    }

    double discriminant = bb * bb - 4 * aa * c;

    if (discriminant > 0) {
        double root1 = (-bb + sqrt(discriminant)) / (2 * aa);
        double root2 = (-bb - sqrt(discriminant)) / (2 * aa);
        cout << "two real and distinct roots: x1 = " << root1 << ", x2 = " << root2 << endl;
    }
    else if (discriminant == 0) {
        double root = -bb / (2 * aa);
        cout << "one real root: x = " << root << endl;
    }
    else {
        double realPart = -bb / (2 * aa);
        double imaginaryPart = sqrt(-discriminant) / (2 * aa);
        cout << "two complex roots: x1 = " << realPart << " + " << imaginaryPart << "i, x2 = " << realPart << " - " << imaginaryPart << "i\n";
    }

    return 0;
}
