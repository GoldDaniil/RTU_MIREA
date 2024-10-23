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
    vector<int> collisionCount;//массив для хранения колва коллизий

    int hash1(int key) {//начальный иднекс
        return key % size;
    }

    int hash2(int key) {//вычисляем сдвиг
        return 1 + (key % (size - 1));
    }

    //увеличение размера таблицы и пересчет хешей
    void rehash() {
        int oldSize = size;
        size *= 2;//увеличиваем размер таблицы в 2 раза
        vector<Abonement*> oldTable = table;

        vector<int> oldCollisions = collisionCount;//сохраняем старый массив коллизий

        table.clear();
        table.resize(size, nullptr);
        collisionCount.clear();
        collisionCount.resize(size, 0);
        count = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != nullptr && oldTable[i]->number != DELETED) {
                insert(*oldTable[i]);//перезаполняем таблицу
            }
        }
    }

public:
    //констурктор
    HashTable(int initialSize) : size(initialSize), count(0) {
        table.resize(size, nullptr);
        collisionCount.resize(size, 0);//иИнициализируем массив коллизий
    }

    //вставка нового абонемента в таблицу
    void insert(const Abonement& abonement) {
        if (count >= size / 2) {
            rehash();//если таблица заполнена более чем на 50% - увеличиваем размер
        }

        int index = hash1(abonement.number);
        int step = hash2(abonement.number);//вычисляем сдвиг
        bool collided = false;

        //пробирование пока место не найдем
        while (table[index] != nullptr && table[index]->number != DELETED) {
            collided = true;
            collisionCount[index]++; //увеличиваем количество коллизий для текущего индекса
            index = (index + step) % size;
        }

        if (table[index] == nullptr || table[index]->number == DELETED) {
            table[index] = new Abonement(abonement);
            count++;
            if (collided) {
                collisionCount[index]++;//фиксируем коллизию на конечной позиции
            }
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
                    << ", address: " << table[i]->address
                    << ", collisions: " << collisionCount[i] << endl;//колво коллизий для ячейки
            }
        }
    }

    void displayCollisions() {
        cout << "\ncollision information:\n";
        for (int i = 0; i < size; i++) {
            if (collisionCount[i] > 0) {
                cout << "index " << i << ": " << collisionCount[i] << " collisions\n";
            }
        }
    }

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
        cout << "\n1 - insert abonement\n2 - search abonement\n3 - remove abonement";
        cout << "\n4 - display all abonements\n5 - display collision info\n6 - exit\n";
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
                cout << "abonement found: " << result->number << ", name: " << result->name 
                    << ", address: " << result->address << endl;
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
        else if (choice == 5) {
            table.displayCollisions(); 
        }
    } while (choice != 6);
}

int main() {
    HashTable table(11);
    autoFill(table);    
    menu(table);         
    return 0;
}
