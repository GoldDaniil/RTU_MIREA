#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>

using namespace std;

struct Node {//узел дерева шеннона-фано
    char symbol;
    double symbol_frequency;
    string character_code;
};

bool compare_frequency(Node tree_nodes_a, Node tree_nodes_b) {//сравниваем частот для сортировоки
    return tree_nodes_a.symbol_frequency > tree_nodes_b.symbol_frequency;
}

void generate_codes(vector<Node>& symbol_nodes, int start, int end, string character_code) {//рекурс функ - построение кодов
    if (start == end) {
        symbol_nodes[start].character_code = character_code;
        return;
    }
    
    double sum_symbol_frequency_left = 0, sum_symbol_frequency_right = 0;
    int left_froup_end_index  = start;

    for (int i = start; i <= end; ++i) sum_symbol_frequency_right += symbol_nodes[i].symbol_frequency;

    for (int i = start; i <= end; ++i) {
        sum_symbol_frequency_left += symbol_nodes[i].symbol_frequency;
        sum_symbol_frequency_right -= symbol_nodes[i].symbol_frequency;

        if (sum_symbol_frequency_left >= sum_symbol_frequency_right) {
            left_froup_end_index  = i;
            break;
        }
    }

    generate_codes(symbol_nodes, start, left_froup_end_index , character_code + "0");
    generate_codes(symbol_nodes, left_froup_end_index  + 1, end, character_code + "1");
}

int main() {
    setlocale(LC_ALL, ""); 

    //string input = "Эни-бени_рити-Фати._Дорба,_дорба_сентибрати._Дэл._Дэл._Кошка._Дэл._Фати!";
    //э = q ; Э = Q ; ш = s;  
    
    string input = "Qni-beni riti-Fati. Dorba, dorba centibrati. Dql. Dql. Koska. Dql. Fati!";

    map<char, double> frequency_map;//частота симв
    for (char c : input) {
        frequency_map[c]++;
    }

    vector<Node> symbol_nodes;
    for (auto pair : frequency_map) {
        symbol_nodes.push_back({ pair.first, pair.second / input.size(), "" });
    }

    sort(symbol_nodes.begin(), symbol_nodes.end(), compare_frequency);

    generate_codes(symbol_nodes, 0, symbol_nodes.size() - 1, "");//строим дерево

    map<char, string> codes;
    for (auto node : symbol_nodes) {
        codes[node.symbol] = node.character_code;
        cout << node.symbol << " -> " << node.character_code << endl;
    }

    string encoded = "";//кодирование
    for (char c : input) {
        encoded += codes[c];
    }

    cout << "encoded text: " << encoded << endl;

    return 0;
}
