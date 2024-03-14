 #include<iostream>
 #include<math.h>
 #include<cmath>
 #include<stdio.h>

 using namespace std;

 int main () {
     int i;
     ///Task "Cone"
     double visota, bolshoy_radius, radius, V, S, dlina_obrazueshey;
     ///Task "Branching"
     double arbitrary_a, argument_x, arbitrary_w, e;
     ///Task "Function"
     double arbitrary_b, arbitrary_y, arbitrary_x, function_z;
     ///Task "Order"
     double number_N;
     ///The Tabulation task
     double function_x, function_y;

     /////////////////////////////////////////////
     ///Task "Cone"
     while (true) {
         cout << "vvedite visotu : " << endl;
         if (!(cin >> visota)) {
             cin.ignore();
             cin.clear();
             cout << "Error, you entered a non-numeric value!" << endl;
             continue;
         }
         break;
     }
     while (true) {
         cout << "vvedite bolshoy_radius : " << endl;
         if (!(cin >> bolshoy_radius)) {
             cin.ignore();
             cin.clear();
             cout << "Error, you entered a non-numeric value!" << endl;
             continue;
         }
         break;
     }
     while (true) {
         cout << "vvedite radius : " << endl;
         if (!(cin >> radius)) {
             cin.ignore();
             cin.clear();
             cout << "Error, you entered a non-numeric value!" << endl;
             continue;
         }
         break;
     }

     if ((radius > 1 and radius != 0) and (visota > 1 and visota != 0) and (bolshoy_radius > 1 and bolshoy_radius != 0)) {
         dlina_obrazueshey = sqrt(pow(visota, 2) + pow((bolshoy_radius-radius), 2));
     } else {
         cout << "the root value must be greater than 0 and 1" << endl;
     }

     if (visota != 0) {
         V = (1/(3 * 3.14159265359 * visota)) * (pow(bolshoy_radius, 2) + bolshoy_radius * radius + (pow(radius, 2)));
         cout << V << endl;
         S = 3.14159265359*(pow(bolshoy_radius, 2) + (bolshoy_radius + radius)*dlina_obrazueshey + (pow(radius, 2)));
         cout << S << endl << endl;
     } else {
         cout << "delit na nol nelyza! nelyza nayti V" << endl;
         S = 3.14159265359*(pow(bolshoy_radius, 2) + (bolshoy_radius + radius)*dlina_obrazueshey + (pow(radius, 2)));
         cout << S << endl << endl;
     }
 /////////////////////////////////////////////
 ///    Task "Branching"
 ///    double arbitrary_a, argument_x, arbitrary_w, e;
     while (true) {
         cout << "enter arbitrary_a : " << endl;
         if(!(cin >> arbitrary_a)) {
             cin.clear();
             cin.ignore();
             continue;
         }
         break;
     }
     while (true) {
         cout << "enter argument_x : " << endl;
         if(!(cin >> argument_x)) {
             cin.clear();
             cin.ignore();
             continue;
         }
         break;
     }

     if ((abs(argument_x) < 1) and (argument_x >= 0)) {
         arbitrary_w = arbitrary_a * log(arbitrary_x);
         cout << arbitrary_w << endl;
     } else if ((abs(argument_x) >= 1) and (argument_x >= 0)) {
         arbitrary_w = sqrt(arbitrary_a - pow(arbitrary_x, 2));
         cout << "arbitrary_w : " << arbitrary_w << endl << endl;
     }

 /////////////////////////////////////////////
 ///Task "Function"
     while (true) {
         cout << "enter arbitrary_b: " << endl;
         if (!(cin >> arbitrary_b)) {
             cin.clear();
             cin.ignore();
             cout << "Error, you entered a non-numeric value!" << endl;
             continue;
         }
         break;
     }
     while (true) {
         cout << "enter arbitrary_y: " << endl;
         if (!(cin >> arbitrary_y)) {
             cin.clear();
             cin.ignore();
             cout << "Error, you entered a non-numeric value!" << endl;
             continue;
         }
         break;
     }
     while (true) {
         cout << "enter arbitrary_x: " << endl;
         if (!(cin >> arbitrary_x)) {
             cin.clear();
             cin.ignore();
             cout << "Error, you entered a non-numeric value!" << endl;
             continue;
         }
         break;
     }
     if ((arbitrary_b - arbitrary_x) >= 0 and ((arbitrary_b - arbitrary_y) > 0)) {
         function_z = log(arbitrary_b - arbitrary_y) * sqrt(arbitrary_b - arbitrary_x);
         cout << function_z << endl << endl;
     } else {
         cout << "function z cannot be calculated " << endl;
     }

     /////////////////////////////////////////////
     ///Task "Order"

     while (true) {
         cout << "enter number_N : " << endl;
         if (!(cin >> number_N) and (number_N <= 0)){
             cin.clear();
             cin.ignore();
             continue;
         }
         break;
     }
     for (int i = number_N ; i < number_N + 10; i++ ) {
         cout << i << endl;
     }
     /////////////////////////////////////////////
     ///The Tabulation task

     for (i = -4; i <= 4; i += 0.5) {
         if (i == 1) {
             cout << "error, for x = 1 the denominator will be 0! " << endl;
         } else {
             cout << "";
             function_y = (pow(i, 2) - 2 * i + 2) / (i - 1);
             cout << function_y << endl << endl;
         }
     }
    return 0;
 }
