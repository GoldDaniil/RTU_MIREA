#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

void setConsoleColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    cout << "\033[38;5;" << color << "m";
#endif
}

int main() {
    for (int i = 0; i < 256; ++i) {
        setConsoleColor(i);
        cout << "happy new year! color : " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    setConsoleColor(7); 

    return 0;
}
