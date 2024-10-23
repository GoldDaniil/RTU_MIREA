#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int DELETED = -1;//маркер для удаления

//cтруктура - хранения данных читательского абонемента
struct Abonement {
    int number;        
    string name;        
    string address;
};

//класс для работы с хеш-таблицей (открытая адресация - двойное хеширование)
class HashTable {
private:
    vector<Abonement*> table;//хеш-таблица
    int size;
    int count;

    int hash1(int key) {
        return key % size;
    }

    int hash2(int key) {
        return 1 + (key % (size - 1));
    }

    //увеличение размера таблицы и пересчет хешей
    void rehash() {
        int oldSize = size;
        size *= 2;//увеличиваем размер таблицы в 2 раза
        vector<Abonement*> oldTable = table;

        table.clear();
        table.resize(size, nullptr);
        count = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != nullptr) {
                insert(*oldTable[i]);//перезаполняем таблицу
            }
        }
    }

public:
    //констурктор
    HashTable(int initialSize) : size(initialSize), count(0) {
        table.resize(size, nullptr);
    }

    //вставка нового абонемента в таблицу
    void insert(const Abonement& abonement) {
        if (count >= size / 2) {
            rehash();//если таблица заполнена более чем на 50% - увеличиваем размер
        }

        int index = hash1(abonement.number);
        int step = hash2(abonement.number);

        while (table[index] != nullptr && table[index]->number != DELETED) {//пробирование пока место не найдем
            index = (index + step) % size;
        }

        if (table[index] == nullptr || table[index]->number == DELETED) {
            table[index] = new Abonement(abonement);
            count++;
        }
    }

    //поиск абонемента по номеру
    Abonement* search(int number) {
        int index = hash1(number);
        int step = hash2(number);

        while (table[index] != nullptr) {
            if (table[index]->number == number) {
                return table[index];
            }
            index = (index + step) % size;
        }
        return nullptr;//если не найден
    }

    //удаление абонемента по номеру
    void remove(int number) {
        int index = hash1(number);
        int step = hash2(number);

        while (table[index] != nullptr) {
            if (table[index]->number == number) {
                table[index]->number = DELETED;//ставим маркер удаления
                cout << "abonement marked as deleted\n";
                return;
            }
            index = (index + step) % size;
        }
        cout << "abonement not found\n";
    }

    //вывод всех абонементов
    void display() {
        for (int i = 0; i < size; i++) {
            if (table[i] != nullptr && table[i]->number != DELETED) {
                cout << "abonement: " << table[i]->number
                    << ", name: " << table[i]->name
                    << ", address: " << table[i]->address << endl;
            }
        }
    }

    //деструктор
    ~HashTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
    }
};

void autoFill(HashTable& table) {
    Abonement abonements[] = {
        {11111, "name a first", "city A"},
        {22222, "name b second", "city B"},
        {33333, "name c three", "city C"},
        {44444, "name d four", "city D"},
        {55555, "name e five", "city E"}
    };

    for (const auto& abonement : abonements) {
        table.insert(abonement);
    }
}

void menu(HashTable& table) {
    int choice;
    do {
        cout << "\n1 - insert abonement\n2 - search abonement\n3 - remove abonement\n4 - display all abonements\n5 - exit\n";
        cout << "choose number: ";
        cin >> choice;

        if (choice == 1) {
            Abonement abonement;
            cout << "enter abonement number: ";
            cin >> abonement.number;
            cout << "enter name: ";
            cin.ignore();
            getline(cin, abonement.name);
            cout << "enter address: ";
            getline(cin, abonement.address);
            table.insert(abonement);
        }
        else if (choice == 2) {
            int number;
            cout << "enter abonement number to search: ";
            cin >> number;
            Abonement* result = table.search(number);
            if (result) {
                cout << "abonement found: " << result->number << ", name: " << result->name << ", address: " << result->address << endl;
            }
            else {
                cout << "abonement not found.\n";   
            }
        }
        else if (choice == 3) {
            int number;
            cout << "enter abonement number to remove: ";
            cin >> number;
            table.remove(number);
        }
        else if (choice == 4) {
            table.display();
        }
    } while (choice != 5);
}

int main() {
    HashTable table(11);
    autoFill(table);    
    menu(table);         
    return 0;
}
