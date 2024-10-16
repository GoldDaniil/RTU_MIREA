#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <Windows.h>
#include <limits>
#include <chrono>

using namespace std;

HANDLE back_col = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(back_col, 0x0a); green
//SetConsoleTextAttribute(back_col, 0x07); default
//SetConsoleTextAttribute(back_col, 0x0C); red

class task_one {
public:
    struct infile_record_structure {
        int policy_number;
        string name_company;
        string owner_company_name;
    };



    //генерация случайных записей
    vector<infile_record_structure> generate_records(int count) {
        vector<infile_record_structure> records;
        srand(time(0));  //инициализация генератора случайных чисел

        for (int i = 0; i < count; ++i) {
            infile_record_structure record;

            //генерация случайного номера полиса    
            record.policy_number = rand() % 1000000;

            //названия компании и владельца
            record.name_company = "company_" + to_string(i + 1);
            record.owner_company_name = "owner_" + to_string(i + 1);

            records.push_back(record);
        }

        //сортировка записей по номеру полиса (policy_number)
        sort(records.begin(), records.end(), [](const infile_record_structure& a, const infile_record_structure& b) {
            return a.policy_number < b.policy_number;
            });

        return records;
    }

    //запись текстового файла
    void write_to_text_file(const vector<infile_record_structure>& records, const string& filename) {
        ofstream outfile(filename);

        if (!outfile.is_open()) {
            cerr << "error opening file for writing" << endl;
            return;
        }

        for (const auto& record : records) {
            outfile << record.policy_number << " " << record.name_company << " " << record.owner_company_name << endl;
        }

        outfile.close();
    }

    //запись в двоичный файл
    void write_to_binary_file(const vector<infile_record_structure>& records, const string& filename) {
        ofstream outfile(filename, ios::binary);

        if (!outfile.is_open()) {
            cerr << "error opening binary file for writing" << endl;
            return;
        }

        for (const auto& record : records) {
            outfile.write((char*)&record.policy_number, sizeof(record.policy_number));
            outfile.write(record.name_company.c_str(), record.name_company.size());
            outfile.put('\0');  //завершающий символ для строк
            outfile.write(record.owner_company_name.c_str(), record.owner_company_name.size());
            outfile.put('\0');
        }

        outfile.close();
    }
};

class task_two {
public:
    struct infile_record_structure {
        int policy_number;
        string name_company;
        string owner_company_name;
    };

public:
    //линейный поиск по ключу в бинарном файле
    infile_record_structure linear_search_in_binary_file(const string& filename, int key) {
        ifstream infile(filename, ios::binary);
        infile_record_structure record;

        if (!infile.is_open()) {
            cerr << "error opening binary file for reading" << endl;
            return record;
        }

        while (infile.read((char*)&record.policy_number, sizeof(record.policy_number))) {
            getline(infile, record.name_company, '\0');  //чтение строки до нуля
            getline(infile, record.owner_company_name, '\0');

            if (record.policy_number == key) {
                return record;//если нашли запись - возвращаем ее
            }
        }

        cerr << "record with key " << key << " not found!" << endl;
        return record;
    }
};


class task_three {
public:
    struct IndexEntry {
        int policy_number;
        streampos file_offset;
    };

    //функция создания таблицы ключ-смещение из бинарного файла
    vector<IndexEntry> create_index_table(const string& filename) {
        vector<IndexEntry> index_table;
        ifstream infile(filename, ios::binary);
        task_one::infile_record_structure record;

        if (!infile.is_open()) {
            cerr << "error opening binary file for reading" << endl;
            return index_table;
        }

        while (!infile.eof()) {
            //получаем смещение текущей записи
            streampos current_offset = infile.tellg();

            //чтение policy_number
            infile.read((char*)&record.policy_number, sizeof(record.policy_number));

            if (infile.eof()) break;

            //пропускаем строки (компанию и владельца)
            infile.ignore((numeric_limits<streamsize>::max)(), '\0');
            infile.ignore((numeric_limits<streamsize>::max)(), '\0');

            //добавляем запись в таблицу
            index_table.push_back({ record.policy_number, current_offset });
        }

        infile.close();

        //сортировка таблицы индексов по policy_number
        sort(index_table.begin(), index_table.end(), [](const IndexEntry& a, const IndexEntry& b) {
            return a.policy_number < b.policy_number;
            });

        return index_table;
    }

    //функция для предвычисления чисел Фибоначчи
    vector<int> generate_fibonacci(int n) {
        vector<int> fib(n + 2, 0); // создаем массив для хранения чисел Фибоначчи
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i <= n; ++i) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
        return fib;
    }

    //поиск по ключу в таблице индексов с использованием поиска Фибоначчи
    streampos fibonacci_search_in_index_table(const vector<IndexEntry>& index_table, int key) {
        int n = index_table.size();

        //генерация всех чисел Фибоначчи до размера массива
        vector<int> fib = generate_fibonacci(n);

        //инициализация индексов
        int fibM2 = 0;     // (m-2)
        int fibM1 = 1;     // (m-1)
        int fibM = fibM2 + fibM1; // m-е число Фибоначчи

        //найдем наибольшее число Фибоначчи - меньшее или равное n
        while (fibM < n) {
            fibM2 = fibM1;
            fibM1 = fibM;
            fibM = fibM1 + fibM2;
        }

        //инициализация оффсета
        int offset = -1;

        //пока больше одного элемента
        while (fibM > 1) {
            int i = min(offset + fibM2, n - 1);

            if (index_table[i].policy_number < key) {
                fibM = fibM1;
                fibM1 = fibM2;
                fibM2 = fibM - fibM1;
                offset = i;
            }
            else if (index_table[i].policy_number > key) {
                fibM = fibM2;
                fibM1 = fibM1 - fibM2;
                fibM2 = fibM - fibM1;
            }
            else {
                return index_table[i].file_offset;
            }
        }

        //проверяем последний элемент
        if (fibM1 && index_table[offset + 1].policy_number == key) {
            return index_table[offset + 1].file_offset;
        }

        cerr << "record with key " << key << " not found in the index table!" << endl;
        return -1;
    }

    //чтение записи по смещению из бинарного файла
    task_one::infile_record_structure read_record_by_offset(const string& filename, streampos offset) {
        ifstream infile(filename, ios::binary);
        task_one::infile_record_structure record;

        if (!infile.is_open()) {
            cerr << "error opening binary file for reading!" << endl;
            return record;
        }

        //переходим к нужному смещению
        infile.seekg(offset);

        //читаем запись
        infile.read((char*)&record.policy_number, sizeof(record.policy_number));
        getline(infile, record.name_company, '\0');
        getline(infile, record.owner_company_name, '\0');

        infile.close();
        return record;
    }
};


int main() {
    int user_choice;

    while (true) {
        SetConsoleTextAttribute(back_col, 0x0a);
        cout << "\nselect task:" << endl;
        cout << "1 - first task" << endl;
        cout << "2 - second task" << endl;
        cout << "3 - third task" << endl;
        cout << "4 - exit" << endl;
        cout << "enter u choice: ";
        SetConsoleTextAttribute(back_col, 0x07);
        cin >> user_choice;

        switch (user_choice) {
        case 1: {
            task_one object;
            int num_records;

            SetConsoleTextAttribute(back_col, 0x0a);
            cout << "enter the number of records to generate: ";
            SetConsoleTextAttribute(back_col, 0x07);
            cin >> num_records;

            //генерация записей
            vector<task_one::infile_record_structure> records = object.generate_records(num_records);

            //запись в текстовый файл
            object.write_to_text_file(records, "records.txt");
            cout << "text file 'records.txt' created" << endl;

            //запись в двоичный файл
            object.write_to_binary_file(records, "records.bin");
            cout << "binary file 'records.bin' created" << endl;
            break;
        }
        case 2: {
            auto start = std::chrono::high_resolution_clock::now();

            task_two object;
            int key;

            SetConsoleTextAttribute(back_col, 0x0a);
            cout << "enter the key (policy number) to search: ";
            SetConsoleTextAttribute(back_col, 0x07);
            cin >> key;

            task_two::infile_record_structure result = object.linear_search_in_binary_file("records.bin", key);

            if (result.policy_number != 0) {  //eсли нашли запись
                cout << "record found: policy number: " << result.policy_number
                    << ", company: " << result.name_company
                    << ", owner: " << result.owner_company_name << endl;
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "time: " << duration.count() << " seconds\n";
            }
            break;


        }
        case 3: {
            auto start = std::chrono::high_resolution_clock::now();

            task_three object;

            //создание таблицы ключ-смещение
            vector<task_three::IndexEntry> index_table = object.create_index_table("records.bin");
            cout << "index table created" << endl;

            //поиск записи по ключу
            int key;
            SetConsoleTextAttribute(back_col, 0x0a);
            cout << "enter the key (policy number) to search in index table: ";
            SetConsoleTextAttribute(back_col, 0x07);
            cin >> key;

            streampos offset = object.fibonacci_search_in_index_table(index_table, key);

            //чтение записи по смещению
            if (offset != -1) {
                task_one::infile_record_structure result = object.read_record_by_offset("records.bin", offset);
                cout << "record found: policy number: " << result.policy_number
                    << ", company: " << result.name_company
                    << ", owner: " << result.owner_company_name << endl;
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "time: " << duration.count() << " seconds\n";
            }
            break;
        }
        case 4:
            cout << "oh...okay:(" << endl;
            return 0;
        default:
            cout << "error!" << endl;
        }
    }
    return 0;
}
