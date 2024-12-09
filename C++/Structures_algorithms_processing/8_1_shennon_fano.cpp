#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <cmath>

//using namespace std;

struct Node {//узел дерева шеннона-фано
    char symbol;
    double symbol_frequency;
    std::string character_code;
};

bool compare_frequency(Node tree_nodes_a, Node tree_nodes_b) {//сравниваем частот для сортировоки
    return tree_nodes_a.symbol_frequency > tree_nodes_b.symbol_frequency;
}

void generate_codes(std::vector<Node>& symbol_nodes, int start, int end, std::string character_code) {//рекурс функ - построение кодов
    if (start == end) {
        symbol_nodes[start].character_code = character_code;
        return;
    }

    double sum_symbol_frequency_left = 0, sum_symbol_frequency_right = 0;
    int left_froup_end_index = start;

    for (int i = start; i <= end; ++i) sum_symbol_frequency_right += symbol_nodes[i].symbol_frequency;

    for (int i = start; i <= end; ++i) {
        sum_symbol_frequency_left += symbol_nodes[i].symbol_frequency;
        sum_symbol_frequency_right -= symbol_nodes[i].symbol_frequency;

        if (sum_symbol_frequency_left >= sum_symbol_frequency_right) {
            left_froup_end_index = i;
            break;
        }
    }

    generate_codes(symbol_nodes, start, left_froup_end_index, character_code + "0");
    generate_codes(symbol_nodes, left_froup_end_index + 1, end, character_code + "1");
}

int main() {
    setlocale(LC_ALL, "");

    //string input = "Эни-бени_рити-Фати._Дорба,_дорба_сентибрати._Дэл._Дэл._Кошка._Дэл._Фати!";
    //э = q ; Э = Q ; ш = s;  

    std::string input = "Qni-beni riti-Fati. Dorba, dorba centibrati. Dql. Dql. Koska. Dql. Fati!";

    std::map<char, double> frequency_map;//частота симв
    for (char c : input) {
        frequency_map[c]++;
    }

    std::vector<Node> symbol_nodes;
    for (auto pair : frequency_map) {
        symbol_nodes.push_back({ pair.first, pair.second / input.size(), "" });
    }

    sort(symbol_nodes.begin(), symbol_nodes.end(), compare_frequency);

    generate_codes(symbol_nodes, 0, symbol_nodes.size() - 1, "");//строим дерево

    std::map<char, std::string> codes;
    for (auto node : symbol_nodes) {
        codes[node.symbol] = node.character_code;
        std::cout << node.symbol << " -> " << node.character_code << std::endl;
    }

    std::string encoded = "";//кодирование
    for (char c : input) {
        encoded += codes[c];
    }

    std::cout << "encoded text: " << encoded << std::endl;

    //cжатый текст
    int original_size_bits = input.size() * 8;//исходный размер в битах
    int compressed_size_bits = encoded.size();//сжатый размер в битах

    double compression_ratio = (double)compressed_size_bits / original_size_bits * 100;//процент сжатия

    std::string decoded = "";//декодирование
    std::string temp = "";
    for (char bit : encoded) {
        temp += bit;
        for (auto node : symbol_nodes) {
            if (node.character_code == temp) {
                decoded += node.symbol;
                temp = "";
                break;
            }
        }
    }

    double average_code_length = 0.0;//вычисление средней длины кода
    for (auto node : symbol_nodes) {
        average_code_length += node.character_code.length() * node.symbol_frequency;
    }

    double variance = 0.0;//вычисление дисперсии длины кода
    for (auto node : symbol_nodes) {
        double length_diff = node.character_code.length() - average_code_length;
        variance += pow(length_diff, 2) * node.symbol_frequency;
    }

    std::cout << "\ncompressed text in bits: " << compressed_size_bits << std::endl;
    std::cout << "compression ratio: " << compression_ratio << "%\n";
    std::cout << "\ndecoded text: " << decoded << std::endl;
    std::cout << "\naverage code length: " << average_code_length << std::endl;
    std::cout << "code length variance: " << variance << std::endl;

    return 0;
}
