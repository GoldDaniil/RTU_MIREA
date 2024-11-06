#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

constexpr double PI = 3.141592653589793;

void cone_task();
void branching_task();
void function_task();
void order_task();
void tabulation_task();
void clear_input();
double get_positive_double(const string& prompt);

int main() {
    int choice;

    while (true) {
        cout << "\n=== task launcher ===\n";
        cout << "1 - task 'cone'\n";
        cout << "2 - task 'branching'\n";
        cout << "3 - task 'function'\n";
        cout << "4 - task 'order'\n";
        cout << "5 - task 'tabulation'\n";
        cout << "0 - exit\n";
        cout << "choose a task to execute: ";

        if (!(cin >> choice) || choice < 0 || choice > 5) {
            cout << "enter a number between 0 and 5\n";
            clear_input();
            continue;
        }

        switch (choice) {
        case 1: cone_task(); break;
        case 2: branching_task(); break;
        case 3: function_task(); break;
        case 4: order_task(); break;
        case 5: tabulation_task(); break;
        case 0: cout << "\nwhy?!\n"; return 0;
        }
    }
}

void cone_task() {
    cout << "\n--- task: cone ---\n";

    double height = get_positive_double("enter height: ");
    double big_radius = get_positive_double("enter big radius: ");
    double radius = get_positive_double("enter small radius: ");

    double slantHeight = sqrt(pow(height, 2) + pow(big_radius - radius, 2));
    double volume = (PI * height / 3) * (pow(big_radius, 2) + big_radius * radius + pow(radius, 2));
    double surfaceArea = PI * (pow(big_radius, 2) + (big_radius + radius) * slantHeight + pow(radius, 2));

    cout << "volume: " << volume << "\nsurface area: " << surfaceArea << "\n\n";
}

void branching_task() {
    cout << "\n--- task: branching ---\n";

    double a = get_positive_double("enter arbitrary a: ");
    double x = get_positive_double("enter argument x: ");
    double w;

    if (abs(x) < 1 && x >= 0) {
        w = a * log(x);
    }
    else if (abs(x) >= 1 && x >= 0) {
        w = sqrt(a - pow(x, 2));
    }
    else {
        cout << "x is out of range for calculations\n";
        return;
    }

    cout << "result (w): " << w << "\n\n";
}

void function_task() {
    cout << "\n--- task: function ---\n";

    double b = get_positive_double("enter arbitrary b: ");
    double y = get_positive_double("enter arbitrary y: ");
    double x = get_positive_double("enter arbitrary x: ");
    double z;

    if ((b - x) >= 0 && (b - y) > 0) {
        z = log(b - y) * sqrt(b - x);
        cout << "result (z): " << z << "\n\n";
    }
    else {
        cout << "cannot compute z due to invalid input values\n";
    }
}

void order_task() {
    cout << "\n--- task: order ---\n";

    int N;
    cout << "enter number N (positive integer): ";
    while (!(cin >> N) || N <= 0) {
        cout << "enter a positive integer\n";
        clear_input();
    }

    cout << "sequence starting from " << N << ":\n";
    for (int i = N; i < N + 10; ++i) {
        cout << i << " ";
    }
    cout << "\n\n";
}

void tabulation_task() {
    cout << "\n--- task: tabulation ---\n";

    for (double x = -4; x <= 4; x += 0.5) {
        if (x == 1) {
            cout << "x = " << x << ":error (denominator is zero)\n";
        }
        else {
            double y = (pow(x, 2) - 2 * x + 2) / (x - 1);
            cout << "x = " << x << ", y = " << y << "\n";
        }
    }
    cout << "\n";
}

double get_positive_double(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) return value;

        cout << "error\n";
        clear_input();
    }
}

void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
