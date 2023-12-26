//2)Создать файл, содержащий сведения в библиотеке о книгах: ФИО автора, название, год издания. Данные
//вводить с клавиатуры. В этом файле: найти название книги, автор и год издания которой вводятся
//вручную; определить имеется ли книга, в названии которой есть слово «С++». Если «да», то сообщить
//автора и год издания:

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // создаем и открываем файл для записи
    ofstream library_file("library.txt");

    try {
        if (!library_file.is_open()) {
            cout << "error\n";
            return 1;
        }
    }
    catch (const exception& err) {
        cerr << " " << err.what() << " ";
    }

    // вводим информацию о книгах с клавиатуры
    for (int i = 0; i < 3; ++i) {
        string author, title;
        int year;

        cout << "enter name_1" << i + 1 << ": ";
        getline(cin, author);

        cout << "enter name_2" << i + 1 << ": ";
        getline(cin, title);

        cout << "" << i + 1 << ": ";
        while (true) {
            if (!(cin >> year)) {
                cin.clear();
                cin.ignore();
                cout << "error\n";
                continue;
            }
            cin.ignore();
            break;
        }

        // записываем информацию в файл
        library_file << author << "|" << title << "|" << year << "\n";
    }


    // закрываем файл
    library_file.close();

    // открываем файл для чтения
    ifstream read_file("library.txt");

    try {
        if (!read_file.is_open()) {
            cerr << "error" << endl;
            return 1;
        }
    }
    catch (const exception& err) {
        cerr << " " << err.what() << " \n";
    }

    // поиск книги по названию автору и году издания
    string search_title, search_author;
    int search_year;

    cout << "enter name_1 for search: ";
    getline(cin, search_title);

    cout << "enter name_2 for search: ";
    getline(cin, search_author);

    cout << "enter year for search: ";
    cin >> search_year;

    string line;
    bool found = false;

    // поиск в файле
    while (getline(read_file, line)) {
        size_t pos = line.find("|");
        string author = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find("|");
        string title = line.substr(0, pos);
        line.erase(0, pos + 1);

        int year = stoi(line);

        // cравниваем введенные данные с данными в файле
        if (title == search_title and author == search_author and year == search_year) {
            found = true;
            cout << "book find: " << title << " (author: " << author << ", year: " << year << ")\n";
            break;
        }
    }

    if (!found) {
        cout << "book not find.\n";
    }

    // закрываем файл
    read_file.close();

    return 0;
}
