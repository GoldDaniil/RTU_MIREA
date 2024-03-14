//Using snake_case! Using camelCase for class!
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;

void test_stroka() {
    for (size_t i = 0; i < test_array_str.length(); ++i) {
        if (!isdigit(test_array_str[i])) {
            test_array_str.erase(i, 1);
            --i;  //уменьшаем индекс чтобы избежать пропуски символов
        }
    }
    
    cout << "sorting test_string " << test_array_str << endl;
    
    stringstream(test_array_str) >> test_array;
}

void test_zero() {
    int test_array;
    string test_array_str;
    
    if (cin >> test_array_str) {
        //cerr << "return 1\n";
        
        for (size_t i = 0; i < test_array_str.length(); ++i) {
            if (!isdigit(test_array_str[i])) {
                test_array_str.erase(i, 1);
                --i;  //уменьшаем индекс чтобы избежать пропуски символов
            }
        }

        //sort(test_array_str.begin(), test_array_str.end());
        cout << "sorting test_string " << test_array_str << endl;

        stringstream(test_array_str) >> test_array;
        //выходим
    }


    //для выхода
    else if (test_array_str == "exit") { 
        cout << "return 0\n"; 
        return;
    } 
    //для хуйни
    else { 
        try {

            cout << "sdasd\n";


        }
        catch (const exception& err) {
            cerr << "return 0" << err.what();
        }
    }


    /*switch (test_array) {
    case 1:
        break;

    default:
        break;
    }*/
}                             

//class void_vector {
//public:
//    clock_t zero_user = clock();
//
//    void zero_recurrent(int arr_set) {
//        cerr << arr_set << " \n";
//        
//        try {
//            if (arr_set == 0) {
//                return;
//            }
//            switch (arr_set) {
//            case 1:
//                cout << arr_set - 1 << endl;
//                break;
//            case 2:
//                cout << arr_set - 2 << endl;
//                break;
//            case 3:
//                cout << arr_set - 3 << endl;
//                break;
//            case 4:
//                cout << arr_set - 4 << endl;
//                break;
//            default:
//                cerr << arr_set << endl;
//                break;
//            }
//        }
//        catch (const exception& err) {
//            cout << "return 1" << err.what();
//        }
//    }
//
//    clock_t one_user = clock();
//    double spent_time = (double)(zero_user - one_user) / CLOCKS_PER_SEC;
//    
////private:
////    const int return_function = 0, const return_claster = 0;
////    int** local_array = new int*[return_function];
////    for (int k = 0; k < arr_set; k++) {
////        local_array[k] = new int[return_claster];
////    }
//};

int main() {
    //two_dimensional_array();

    ///////////////////////////////////////////
    test_zero();
    //test_one();


    //тест//
    return 0;
}
