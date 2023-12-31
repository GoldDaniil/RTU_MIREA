#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void return_abc_max() {
    int base_cost, spinner_cost, max_spinner_cost;
    while (true) {
        cout << "enter base_cost, spinner_cost, max_spinner_cost: ";
        if (!(cin >> base_cost) || !(cin >> spinner_cost) || !(cin >> max_spinner_cost)) {
            cin.clear();
            cin.ignore();
            cerr << "error!\n";
            continue;
        }
        break;
    }

    if (base_cost <= max_spinner_cost) {
        cout << (max_spinner_cost - base_cost) / spinner_cost;
    }
    else {
        cout << "error!" << endl;
    }
}

void return_abc_max_two() {
    int total_cost;
    if ((cin >> total_cost) && (total_cost != '.' && total_cost != ',')) {
        int num_of_3, num_of_4;
        num_of_4 = total_cost % 3;
        num_of_3 = (total_cost - 4 * num_of_4) / 3;
        if (num_of_3 >= 0) {
            cout << num_of_3 << endl << num_of_4;
        }
        else {
            cout << 0 << endl << 0;
        }
    }
    else {
        cout << "error!\n";
    }
}

void return_abc_max_tree() {
    int row_count, col_count;
    if ((cin >> row_count && cin >> col_count) && (col_count != '.' && col_count != ',' && row_count != '.' && row_count != ',')) {
        cout << row_count * (row_count + 1) / 2 * col_count * (col_count + 1) / 2;
    }
    else {
        cout << "error!\n";
    }
}

class VoidFour {
public:
    static const int MaxArraySize = 100;
    static int counterArray[MaxArraySize];

    int getIndex(int value) {
        if (value <= 36) {
            return (value - 1) / 4;
        }
        else {
            return 8 - (value - 37) / 2;
        }
    }

    void main_task() {
        int arraySize;
        int maxSequence = 0;
        int currentSequence = 0;
        if ((cin >> arraySize) && (-1 < arraySize && arraySize < 55) && (arraySize != '.' && arraySize != ',')) {
            for (int i = 1; i <= arraySize; i++) {
                int element;
                if (cin >> element) {
                    this->counterArray[this->getIndex(element)] += 1;
                }
            }
            for (int i = 0; i < 9; i++) {
                if (this->counterArray[i] == 6) {
                    currentSequence += 1;
                    maxSequence = max(maxSequence, currentSequence);
                }
                else {
                    currentSequence = 0;
                }
            }
            cout << maxSequence;
        }
        else {
            cout << "error!\n";
        }
    }
};

int VoidFour::counterArray[VoidFour::MaxArraySize] = { 0 };

void task_five() {
    int n, k;

    cout << "enter : ";
    if (cin >> n >> k && k >= 1 && k <= n) {
        while (k >= 1) {
            n = (n - k % 2) / 2;
            k /= 2;
        }

        int left_seats = (n - 1) / 2;
        int right_seats = n / 2;

        cout << left_seats << endl;
        cout << right_seats << endl;
    }
    else {
        cout << "error! ";
    }
}

void launcher() {
    while (true) {
        cout << "launcher tasks:\n";

        int taskNumber;
        string taskNumberStr;

        while (true) {
            cout << "if you want to exit the program, enter 'exit'\nEnter task number: ";
            cin >> taskNumberStr;

            if (taskNumberStr == "exit") {
                cout << "okay(\n";
                return;
            }

            bool hasNonDigit = false;

            for (char digit : taskNumberStr) {
                if (!isdigit(digit)) {
                    hasNonDigit = true;
                    break;
                }
            }

            if (hasNonDigit) {
                cerr << "error!\n";
                cin.clear();
                cin.ignore();
            }
            else {
                stringstream(taskNumberStr) >> taskNumber;
                break;
            }
        }

        switch (taskNumber) {
        case 1:
            cout << endl;
            return_abc_max();
            cout << endl;
            break;
        case 2:
            cout << endl;
            return_abc_max_two();
            cout << endl;
            break;
        case 3:
            cout << endl;
            return_abc_max_tree();
            cout << endl;
            break;
        case 4:
            cout << endl;
            VoidFour LocalSubject;
            LocalSubject.main_task();
            cout << endl;
            break;
        case 5:
            cout << endl;
            task_five();
            cout << endl;
            break;
        default:
            cout << "error!\n";
            break;
        }
    }
}

int main() {
    launcher();
    return 0;
}
