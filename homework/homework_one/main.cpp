#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

int main () {
    double visota, bolshoy_radius, radius, dlina_obrazueshey, V, S;
    while (true) {
        cout << "vvedite visotu : " << endl;

        if (!(cin >> visota)) {
            cin.ignore();
            cin.clear();
            cout << "Oshibka, vi vveli nechislovoe znachenie!" << endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "vvedite bolshoy_radius : " << endl;

        if (!(cin >> bolshoy_radius)) {
            cin.ignore();
            cin.clear();
            cout << "Oshibka, vi vveli nechislovoe znachenie!" << endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "vvedite radius : " << endl;

        if (!(cin >> radius)) {
            cin.ignore();
            cin.clear();
            cout << "Oshibka, vi vveli nechislovoe znachenie!" << endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "vvedite dlina_obrazueshey : " << endl;

        if (!(cin >> dlina_obrazueshey)) {
            cin.ignore();
            cin.clear();
            cout << "Oshibka, vi vveli nechislovoe znachenie!" << endl;
            continue;
        }
        break;
    }
    if (visota != 0) {
        V = (1/(3 * 3.14159265359 * visota)) * (pow(bolshoy_radius, 2) + bolshoy_radius * radius + (pow(radius, 2)));
        cout << V << endl;
        S = 3.14159265359*(pow(bolshoy_radius, 2) + (bolshoy_radius + radius)*dlina_obrazueshey + (pow(radius, 2)));
        cout << S << endl;
    } else {
        cout << "delit na nol nelyza! nelyza nayti V" << endl;
        S = 3.14159265359*(pow(bolshoy_radius, 2) + (bolshoy_radius + radius)*dlina_obrazueshey + (pow(radius, 2)));
        cout << S << endl;
    }

    return 0;
}