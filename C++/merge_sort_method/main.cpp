//merge sort method
//the code uses the style, snake_case naming notation

#include<iostream>;
#include<stdio.h>;

using namespace std;

void merge(int arr[], int left, int right, int middle);
void merge_sort(int arr[], int left, int right);

void input_and_verification() { //функция для ввода и проверки элементов массива
    int n;
    while (true) {
        cout << "enter the number of elements: ";
        if (!(cin >> n)) {
            cin.clear(); //очищаем буфер ввода
            cin.ignore(); //игнорируем введенные данные
            cout << "error! You need to enter the data type integer! " << endl;
            continue; //повторяем цикл
        }
        break; //прерываем цикл
    }
    const int X = n; //задаем константу X - равную введенному значению n
    int* integer_array = new int[X]; //создаем массив целых чисел размером X

    cout << "enter array elements: " << endl;
    for (int i = 0; i < X; i++) { //цикл для ввода элементов массива
        while (true) {
            if (!(cin >> integer_array[i])) {
                cin.clear();
                cin.ignore();
                cout << "error! You need to enter the data type integer! " << endl;
                continue;
            }
            break;
        }
    }
    cout << "\n";

    cout << "array elements: " << endl;
    for (int i = 0; i < X; i++) { //цикл для вывода элементов массива
        cout << integer_array[i] << " "; //вывод элементов массива на экран
    }
    cout << endl;
    int amount_elements = X; //задаем переменную amount_elements, равную X
    cout << "number of elements in the array: " << amount_elements << endl << endl; //выводим количество элементов массива

    merge_sort(integer_array, 0, amount_elements - 1); //вызов функцию сортировки слиянием

    cout << "Sorted array: " << endl;
    for (int i = 0; i < X; i++) { //цикл для вывода отсортированных элементов массива
        cout << integer_array[i] << " "; //вывод отсортированных элементов массива
    }
    cout << endl << "\n";
}

void merge(int arr[], int left, int right, int middle) { //функция для слияния двух подмассивов arr[left, middle] и arr[middle+1, right]
    int left_sizes_subarrays = (middle - left + 1); //размер подмассива left_sizes_subarrays
    int right_sizes_subarrays = (right - middle); //размер подмассива right_sizes_subarrays

    //cоздание временных подмассивов
    int* Left_subarray = new int[left_sizes_subarrays];
    int* Right_subarray = new int[right_sizes_subarrays];

    //копирование данных во временные подмассивы Left_subarray[] и Right_subarray[]
    for (int i = 0; i < left_sizes_subarrays; i++) {
        Left_subarray[i] = arr[left + i];
    }
    for (int j = 0; j < right_sizes_subarrays; j++) {
        Right_subarray[j] = arr[middle + 1 + j];
    }

    //ю.объединение временные подмассивы обратно в arr[left...right]
    int i = 0; //индекс первого подмассива Left_subarray
    int j = 0; //индекс второго подмассива Right_subarray
    int k = left; //индекс объединенного подмассива

    while (i < left_sizes_subarrays && j < right_sizes_subarrays) {
        if (Left_subarray[i] <= Right_subarray[j]) { //если элемент в Left_subarray[i] меньше или равен элементу в Right_subarray[j] то
            arr[k] = Left_subarray[i]; //                   присваиваем значение из левого подмассива в общий массив
            i++; //увеличиваем индекс Left_subarray[i]
        }
        else {
            arr[k] = Right_subarray[j];
            j++; //увеличиваем индекс Right_subarray[j]
        }
        k++; //увеличиваем индекс общего массива
    }

    //если остались элементы то копируем их в Left_subarray[]
    while (i < left_sizes_subarrays) {
        arr[k] = Left_subarray[i];
        i++; //увеличиваем индекс Left_subarray[i]
        k++; //увеличиваем индекс общего массива
    }

    //если остались элементы то копируем их в Right_subarray[]
    while (j < right_sizes_subarrays) {
        arr[k] = Right_subarray[j];
        j++; //увеличиваем индекс Right_subarray[j]
        k++;
    }
}

void merge_sort(int arr[], int left, int right) { //функция сортировки слиянием
    if (left >= right) { //если левая граница больше или равна правой то выходим
        return;
    }

    int middleIndex = left + (right - left) / 2; //находим середину
    merge_sort(arr, left, middleIndex); //сортируем левую половину
    merge_sort(arr, middleIndex + 1, right); //сортируем правую половину
    merge(arr, left, right, middleIndex); //соединяем - сливаем две отсортированные половины
}

int main() { //главная функция программы
    input_and_verification(); //вызываем функцию для ввода и проверки данных
    return 0;
}
