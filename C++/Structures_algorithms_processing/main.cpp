#include <iostream>
#include <string> 
#include <vector>    
#include <unordered_map> 
#include <algorithm>

using namespace std;

vector<int> boyer_moore_turbo_search(const string& text, const string& pattern) {
    int n = text.size();//длина текста
    int m = pattern.size();//длина подстроки(шаблона)
    vector<int> result;//вектор для хранения позиций вхождений подстроки

    if (m == 0 || n < m) {
        return result;
    }

    unordered_map<char, int> bad_char_shift;

    for (int i = 0; i < m - 1; ++i) {
        bad_char_shift[pattern[i]] = m - i - 1;
    }

    int s = 0;//смещение текстовой строки
    int shift = m;//на сколько сдвиг после каждого цикла


    while (s <= n - m) {//пока в пределах строки
        int j = m - 1;//с конца шаблона 

        while (j >= 0 && pattern[j] == text[s + j]) {//пока символы совпадают
            --j;//к левому переход
        }

        if (j < 0) {
            result.push_back(s);//нашли вхождение
            s += shift;
        }
        else {
            int bad_сhar_shift_val = bad_char_shift.count(text[s + j]) ? bad_char_shift[text[s + j]] : m;
            shift = max(1, bad_сhar_shift_val - (m - 1 - j));
            s += shift;//сдвиг вправо на shift
        }
    }

    return result;
}

unordered_map<char, int> build_bad_char_table(const string& pattern) {//эвристика плохого символа

    unordered_map<char, int> bad_char_shift;
    int m = pattern.size();

    for (int i = 0; i < m - 1; ++i) {
        bad_char_shift[pattern[i]] = m - i - 1;
    }

    return bad_char_shift;
}

vector<int> build_good_suffix_table(const string& pattern) {//эвристика хорошего суффикса
    int m = pattern.size();
    vector<int> good_suffix_shift(m + 1, m);
    int last_prefix_pos = m;

    for (int i = m; i > 0; --i) {
        if (pattern.compare(0, m - i, pattern, i, m - i) == 0) {
            last_prefix_pos = i;
        }
        good_suffix_shift[m - i] = last_prefix_pos + m - i;
    }

    for (int i = 0; i < m - 1; ++i) {
        int suffix_len = i + 1;
        if (pattern.compare(m - suffix_len, suffix_len, pattern, 0, suffix_len) == 0) {
            good_suffix_shift[suffix_len] = m - suffix_len;
        }
    }

    return good_suffix_shift;
}

int turbo_shift(const string& text, const string& pattern, int s, int j) {//турбо-сдвиг
    int shift = 1;
    if (j < pattern.size() - 1 && pattern[j] != text[s + j]) {
        shift = 1;
    }
    return shift;
}

vector<int> boyer_moore_turbo_search(const string& text, const string& pattern, int& total_shifts) {//основная функция поиска с использованием каждой эвристики
    int n = text.size();
    int m = pattern.size();
    vector<int> result;
    total_shifts = 0;//счетчик общего числа сдвигов

    if (m == 0 || n < m) {
        return result;
    }

    auto bad_char_shift = build_bad_char_table(pattern);
    auto good_suffix_shift = build_good_suffix_table(pattern);

    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j]) {
            --j;
        }

        if (j < 0) {
            result.push_back(s);
            s += good_suffix_shift[0];
            total_shifts++;
        }
        else {
            int bad_char_shift_val = bad_char_shift.count(text[s + j]) ? bad_char_shift[text[s + j]] : m;
            int good_suffix_shift_val = (j < m - 1) ? good_suffix_shift[j + 1] : m;
            int shift = max({ 1, bad_char_shift_val - (m - 1 - j), good_suffix_shift_val, turbo_shift(text, pattern, s, j) });
            s += shift;
            total_shifts++;
        }
    }
    return result;
}

int main() {
    string text, pattern;

    cout << "enter text: ";
    getline(cin, text);

    cout << "enter pattern: ";
    getline(cin, pattern);

    int shifts_bad_char = 0, shifts_good_suffix = 0, shifts_turbo_shift = 0;

    vector<int> occurrences_bad_char = boyer_moore_turbo_search(text, pattern, shifts_bad_char);

    vector<int> occurrences_good_suffix = boyer_moore_turbo_search(text, pattern, shifts_good_suffix);

    vector<int> occurrences_turbo_shift = boyer_moore_turbo_search(text, pattern, shifts_turbo_shift);

    cout << "results bad: ";
    for (int pos : occurrences_bad_char) {
        cout << pos << " ";
    }
    cout << "\ntotal shifts (bad): " << shifts_bad_char << endl;

    cout << "results good suffix: ";
    for (int pos : occurrences_good_suffix) {
        cout << pos << " ";
    }
    cout << "\ntotal shifts (good): " << shifts_good_suffix << endl;

    cout << "results turbu shift: ";
    for (int pos : occurrences_turbo_shift) {
        cout << pos << " ";
    }
    cout << "\ntotal shifts (trbbo): " << shifts_turbo_shift << endl;

    int min_shifts = min({ shifts_bad_char, shifts_good_suffix, shifts_turbo_shift });
    cout << "\nbest : ";
    if (min_shifts == shifts_bad_char) {
        cout << "bad chara ";
    }
    else if (min_shifts == shifts_good_suffix) {
        cout << "good suffix";
    }
    else {
        cout << "turbo shift";
    }
    cout << " with " << min_shifts << " shifts\n";

    return 0;
}
