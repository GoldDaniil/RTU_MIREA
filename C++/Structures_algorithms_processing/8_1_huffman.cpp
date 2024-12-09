#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct huffman_node {//узел дерева хаффмана
    char symbol;
    double symbol_frequency;
    huffman_node* left_child;
    huffman_node* right_child;
};

struct compare {//компаратор для приоритетной очереди
    bool operator()(huffman_node* tree_nodes_a, huffman_node* tree_nodes_b) {
        return tree_nodes_a->symbol_frequency > tree_nodes_b->symbol_frequency;
    }
};

void generate_huffman_codes(huffman_node* node, string current_code, map<char, string>& huffman_codes) {
    if (!node) return;
    //рекурсивная функция для генерации кодов символов

    if (!node->left_child && !node->right_child) {//если узел листовой - добавляем символ и его код
        huffman_codes[node->symbol] = current_code;
    }

    generate_huffman_codes(node->left_child, current_code + "0", huffman_codes);//рекурсивно вызываем для левого и правого поддерева
    generate_huffman_codes(node->right_child, current_code + "1", huffman_codes);
}

void delete_huffman_tree(huffman_node* node) {//рекурсивное удаление дерева
    if (!node) return;
    delete_huffman_tree(node->left_child);
    delete_huffman_tree(node->right_child);
    delete node;
}

int main() {
    string input_text = "Gold Daniil Vladimirovich";

    map<char, double> frequency_map;
    for (char c : input_text) {
        frequency_map[c]++;
    }

    priority_queue<huffman_node*, vector<huffman_node*>, compare> priority_queue_huffman_nodes;//создание приоритетной очереди
    for (auto pair : frequency_map) {
        huffman_node* new_huffman_node = new huffman_node{ pair.first, pair.second, nullptr, nullptr };
        priority_queue_huffman_nodes.push(new_huffman_node);
    }

    while (priority_queue_huffman_nodes.size() > 1) {//построение дерева хаффмана
        huffman_node* left_child = priority_queue_huffman_nodes.top(); priority_queue_huffman_nodes.pop();
        huffman_node* right_child = priority_queue_huffman_nodes.top(); priority_queue_huffman_nodes.pop();

        huffman_node* merged = new huffman_node{ '\0', left_child->symbol_frequency + right_child->symbol_frequency,
            left_child, right_child };
        priority_queue_huffman_nodes.push(merged);
    }

    huffman_node* root = priority_queue_huffman_nodes.top();//корень дерева хаффмана
    map<char, string> huffman_codes;//генерация кодов символов
    generate_huffman_codes(root, "", huffman_codes);

    cout << "symbols codes:\n";//отображение кодов символов
    for (auto pair : huffman_codes) {
        cout << pair.first << " -> " << pair.second << endl;
    }

    string encoded_text = "";
    for (char c : input_text) {
        encoded_text += huffman_codes[c];
    }
    cout << "\nencoded text: " << encoded_text << endl;

    //сжатый текст
    int original_size_bits = input_text.size() * 8;//исходный размер в битах (по 8 бит на символ)
    int compressed_size_bits = encoded_text.size();//сжатый размер в битах

    //коэффициенты сжатия
    double compression_ratio_ascii = (double)original_size_bits / compressed_size_bits;
    double average_code_length = 0.0;
    double variance = 0.0;

    for (auto pair : huffman_codes) {//расчет средней длины кода и дисперсии
        int code_length = pair.second.size();
        average_code_length += code_length * (pair.second.size() / (double)input_text.size());
    }

    for (auto pair : huffman_codes) {//вычисление дисперсии длины кодов
        int code_length = pair.second.size();
        variance += (code_length - average_code_length) * (code_length - average_code_length) *
            (pair.second.size() / (double)input_text.size());
    }

    //коэффициент сжатия относительно равномерного кода
    int uniform_code_size = (int)ceil(log2(frequency_map.size())) * input_text.size();//равномерный код
    double compression_ratio_uniform = (double)original_size_bits / uniform_code_size;

    cout << "\ncompressed size in bits: " << compressed_size_bits << endl;
    cout << "compression ratio (ASCII): " << compression_ratio_ascii << endl;
    cout << "compression ratio (uniform code): " << compression_ratio_uniform << endl;
    cout << "average code length: " << average_code_length << " bits\n";
    cout << "variance code length: " << variance << endl;

    string decoded_text = "";//декодирование текста
    huffman_node* current_node = root;
    for (char bit : encoded_text) {
        if (bit == '0') {
            current_node = current_node->left_child;
        }
        else {
            current_node = current_node->right_child;
        }

        if (!current_node->left_child && !current_node->right_child) {
            decoded_text += current_node->symbol;
            current_node = root;
        }
    }

    cout << "\ndecoded text: " << decoded_text << endl;

    delete_huffman_tree(root);

    return 0;
}
