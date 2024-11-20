#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

int calculate_distance(const string& word1, const string& word2) {
    int distance = 0;
    int min_length = min(word1.size(), word2.size());

    for (int i = 0; i < min_length; ++i) {//считаем позиции - в которых символы различаются
        distance += (word1[i] != word2[i]) ? 1 : 0;
        //добавляем 1 к distance -если символы в позиции i различаются - и 0 — если одинаковы
    }

    distance += abs((int)word1.size() - (int)word2.size());//добавляем разницу в длине- если слова разной длины

    return distance;
}

void find_closest_words(const string& sentence) {
    vector<string> words;
    string word = "";

    for (char ch : sentence) {//проходим по предложению и разбиваем на слова - игнорируя запятые
        if (ch == ' ' || ch == ',') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else {
            word += ch;
        }
    }
    if (!word.empty()) {//добавляем последнее слово - если оно не пустое
        words.push_back(word);
    }

    int min_distance = numeric_limits<int>::max();
    pair<string, string> closestPair;


    for (size_t i = 0; i < words.size(); ++i) {//линейный поиск - перебираем все пары слов
        for (size_t j = i + 1; j < words.size(); ++j) {
            int distance = calculate_distance(words[i], words[j]);
            if (distance < min_distance) {
                min_distance = distance;
                closestPair = { words[i], words[j] };
            }
        }
    }

    cout << "couple words with minimum distance: " << closestPair.first
        << " and " << closestPair.second << " (distance: " << min_distance << ")\n";
}

class BoyerMoreGoodSuffix {
public:
    vector<int> z_function(const string& s) {//функция для вычисления Z-функции
        int line_length_n = s.length();//длина строки
        vector<int> z(line_length_n, 0);//инициализируем массив z нулями
        int left_index_border = 0, right_index_border = 0;//границы строки

        for (int i = 1; i < line_length_n; ++i) {//проходим по строке начиная с индекса 1
            if (i <= right_index_border) {
                z[i] = min(right_index_border - i + 1, z[i - left_index_border]);
            }
            while (i + z[i] < line_length_n && s[z[i]] == s[i + z[i]]) {//расширяем совпадение
                z[i]++;//увелич длин совпадения
            }
            if (i + z[i] - 1 > right_index_border) {//если новое совпадение расширяет область
                left_index_border = i;
                right_index_border = i + z[i] - 1;
            }
        }

        return z;
    }

    vector<int> build_good_suffix_table(const string& pattern) {
        int length_template_substring_m = pattern.length();//длина шаблона
        string reversed_pattern = pattern;//строка-реверс шаблона
        reverse(reversed_pattern.begin(), reversed_pattern.end());

        string concatenation_string = pattern + "$" + reversed_pattern;//объединяем шаблон с его реверсией через разделитель
        vector<int> z = z_function(concatenation_string);

        vector<int> good_suffix(length_template_substring_m + 1, length_template_substring_m);
        for (int j = 0; j < length_template_substring_m; ++j) {//проходим по всем индексам шаблона
            good_suffix[j] = length_template_substring_m - z[length_template_substring_m + 1 + j];//заполняем таблицу сдвигами
            //по совпавшим суффиксам
        }
        return good_suffix;
    }

    void search(const string& text, const string& pattern) {
        auto start = chrono::high_resolution_clock::now();

        int line_length_n = text.length();//длина текста
        int length_template_substring_m = pattern.length();//длина шаблона

        vector<int> good_suffix = build_good_suffix_table(pattern);

        int s = 0;//начальное смещение для шаблона
        int iterations = 0;

        while (s <= line_length_n - length_template_substring_m) {//в пределах строки
            int j = length_template_substring_m - 1;//с конца шаблона

            //начинаем сравнение с конца шаблона
            while (j >= 0 && pattern[j] == text[s + j]) {//если совпад
                --j;
            }

            if (j < 0) {//шаблон совпал
                cout << "\npattern found at position: " << s << endl;
                s += good_suffix[0]; // сдвиг шаблон = знач табл суффиксов
            }
            else {//нет
                s += good_suffix[j + 1];//сдвиг = тбл хор суфф
            }
            ++iterations;
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "\niterations: " << iterations << endl;
        cout << "\ntime taken: " << duration.count() << " sec\n";
    }
};

class BoyerMoreBadSuffix {
public:
    BoyerMoreBadSuffix(const string& pattern) {
        this->pattern = pattern;
        this->m_pattern_length = pattern.length();
        create_bad_suffix_table();
    }

    void search(const string& text) { //поиск подстроки в строке
        auto start_time = chrono::high_resolution_clock::now();
        int n_line_length = text.length();
        int i = 0; //индекс в тексте
        int count = 0; //счетчик итераций

        while (i <= n_line_length - m_pattern_length) {
            int j = m_pattern_length - 1; //индекс в шаблоне
            while (j >= 0 && pattern[j] == text[i + j]) {
                j--;
            }

            if (j < 0) { //совпадение найдено
                cout << "\npattern found at position: " << i << endl;
                i += good_suffix[0];//cдвиг по хорошему суффиксу
            }
            else {
                int bad_char_shift = max(1, j - last_occurence[text[i + j]]); //вычисление сдвигов для плохого символа и
               //хорошего суффикса
                int good_suffix_shift = good_suffix[j + 1];

                i += max(bad_char_shift, good_suffix_shift); //сдвиг
            }
            count++;
        }

        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end_time - start_time;

        cout << "\niterations: " << count << endl;
        cout << "time taken: " << duration.count() << " sec\n";
    }

private:
    string pattern;
    int m_pattern_length;
    vector<int> good_suffix;
    unordered_map<char, int> last_occurence;

    void create_bad_suffix_table() {
        for (int i = 0; i < m_pattern_length; i++) { //заполняем таблицу последних вхождений каждого символа
            last_occurence[pattern[i]] = i;
        }

        good_suffix = vector<int>(m_pattern_length + 1, m_pattern_length); //создание таблицы хороших суффиксов
        for (int i = m_pattern_length - 2; i >= 0; i--) {
            int j = i;
            while (j >= 0 && pattern[j] == pattern[m_pattern_length - 1 - (i - j)]) { //поиск наибольшего суффикса шаблона
                j--;
            }
            good_suffix[i] = max(1, m_pattern_length - (i - j));
        }
    }
};

class BoyerMoreTurboShift {
public:
    BoyerMoreTurboShift(const string& pattern) {
        this->pattern = pattern;
        this->m_pattern_length = pattern.length();
        create_bad_suffix_table();
        create_good_suffix_table();
    }

    void search(const string& text) {
        auto start_time = chrono::high_resolution_clock::now();
        int n_line_length = text.length();
        int i = 0;//индекс в тексте
        int count = 0;//счетчик итераций
        bool turbo_shift_used = false;

        while (i <= n_line_length - m_pattern_length) {
            int j = m_pattern_length - 1;//индекс в шаблоне
            while (j >= 0 && pattern[j] == text[i + j]) {
                j--;
            }

            if (j < 0) { 
                cout << "\npattern found position: " << i << endl;

                //применяем турбосдвиг
                if (turbo_shift_used) {
                    i += m_pattern_length;//применяем турбосдвиг
                    cout << "turbo shift applied from index " << i - m_pattern_length << " to " << i << endl;
                }
                else {
                    turbo_shift_used = true;//после первого совпадения применяем турбосдвиг
                    i += m_pattern_length;//стандартный сдвиг
                }
            }
            else {
                int bad_char_shift = max(1, j - last_occurence[text[i + j]]);
                int good_suffix_shift = good_suffix[j + 1];

                int shift = max(bad_char_shift, good_suffix_shift);
                i += shift;//jбычный сдвиг
            }
            count++;
        }

        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end_time - start_time;

        cout << "\niterations: " << count << endl;
        cout << "time taken: " << duration.count() << " sec\n";
    }

private:
    string pattern;
    int m_pattern_length;
    vector<int> good_suffix;
    unordered_map<char, int> last_occurence;

    void create_bad_suffix_table() {
        for (int i = 0; i < m_pattern_length; i++) {
            last_occurence[pattern[i]] = i;
        }
    }

    void create_good_suffix_table() {
        good_suffix = vector<int>(m_pattern_length + 1, m_pattern_length);//создание таблицы хороших суффиксов
        for (int i = m_pattern_length - 2; i >= 0; i--) {
            int j = i;
            while (j >= 0 && pattern[j] == pattern[m_pattern_length - 1 - (i - j)]) {//поиск наибольшего суффикса шаблона
                j--;
            }
            good_suffix[i] = max(1, m_pattern_length - (i - j));
        }
    }
};

int main() {
    string text;
    string pattern;

    //первое задание - распечатать те пары слов, расстояние между которыми наименьшее
    //string sentence = "ajdfkdfjk, kdasd a skdlksl ,  asdd dskdlk";
    //find_closest_words(sentence);

    //выбрать алгоритм бойера-мура:
    
    cout << "enter the text: ";
    cin >> text;

    cout << "enter the pattern: ";
    cin >> pattern;

    //алгоритм бойера-мура с эвристикой хорошего суффикса
    //BoyerMoreGoodSuffix object;
    //object.search(text, pattern);

    //алгоритм бойера-мура с эвристикой плохого суффикса
    //BoyerMoreBadSuffix object(pattern);
    //object.search(text);

    //эвристика бойера-мура с турбосдвигом
    //BoyerMoreTurboShift turboShiftObject(pattern);
    //turboShiftObject.search(text);
    return 0;
}
