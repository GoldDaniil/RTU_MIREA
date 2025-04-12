import pycodestyle
import random
import string
from itertools import groupby
import struct
import argparse
import sys
import re
def launcher():
    while True:
        print("\nвыберите номер блока или 'exit' для завершения:")
        print(" 1 - блок 1")
        print(" 2 - блок 2")
        print(" 3 - блок 3")
        print(" 4 - блок 4")
        print(" 5 - блок 5")
        print(" 6 - блок 6")
        print(" 8 - блок 8")

        block = input("номер блока: ").strip()
        if block.lower() == "exit":
            print("пока")
            break
        elif block in ['1', '2', '3', '4', '5', '6', '8']:
            tasks_menu(block)
        else:
            print("неверный номер блока - введите еще раз")

def block_first_first():
    try:
        code = '''
        	print("ошибка E101")
        '''
        print(code)
        print("ошибка E101")
    except Exception as e:
        print("E101 error caught:", e)

def block_first_second():
    try:
        code = '''
       print("ошибка E111")
        '''
        print(code)
        print("ошибка E111")
    except Exception as e:
        print("E111 error caught:", e)

def block_first_third():
    try:
        code = '''
        if True:
print("ошибка E112")
        '''
        print(code)
        print("ошибка E112")
    except Exception as e:
        print("E112 error caught:", e)

def block_first_fourth():
    try:
        code = '''
        value = [
        1, 2,
        3, 4]
        '''
        print(code)
        print("ошибка E121")
    except Exception as e:
        print("E121 error caught:", e)

def block_first_fifth():
    try:
        code = '''
        result = 1 +\
        2
        '''
        print(code)
        print("ошибка E122")
    except Exception as e:
        print("E122 error caught:", e)

def block_first_sixth():
    try:
        code = '''
        my_list = [
            1, 2,
        3, 4
        ]
        '''
        print(code)
        print("ошибка E123")
    except Exception as e:
        print("E123 error caught:", e)

def block_first_seventh():
    try:
        code = '''
        my_dict = {
            "key1": "value1",
            "key2": "value2",
            }
        '''
        print(code)
        print("ошибка E124")
    except Exception as e:
        print("E124 error caught:", e)

def block_first_eighth():
    try:
        code = '''
        if (True or
            False):
            print("ошибка E125")
        '''
        print(code)
        print("ошибка E125")
    except Exception as e:
        print("E125 error caught:", e)

def block_second_first():
    try:
        '''
        [0xfor _ in 'abc']
        '''
        print("ошибка - некореектный синтаксис генератора списка")
    except Exception as e:
        print("err caught:", e)

def block_second_second():
    try:
        '''
        a = 1
        b = 1
        c = 300000
        d = 300000
        print(a is b, c is d)

        a, b = 'py', 'py'
        c = ''.join(['p', 'y'])
        print(a is b, a == c, a is c)
        '''
        print("разные диапазоны кэширования объектов в питоне вызывают такие результаты")
    except Exception as e:
        print("err caught:", e)

def block_second_third():
    try:
        '''
        i = 0
        'much code wow'[i::5]
        '''
        print("оптимизированный код сокращает количество символов до 19 - используя срез строки")
    except Exception as e:
        print("err caught:", e)

def block_second_fourth():
    try:
        '''
        lst = ['a', 'b', 'c']
        lst += 'd'
        print(lst)

        lst = lst + 'd'
        print(lst)

        lst += 42
        print(lst)
        '''
        print("ошибка происходит из за попытки сложения списка и строки - а также списка и числа")
    except Exception as e:
        print("err caught:", e)

def block_third_first(s):
    print("преобразование строк в числа:", list(map(int, s)))

def block_third_second(s):
    print("колво уник элементов:", len(set(s)))

def block_third_third(s):
    print("обрат послед:", s[::-1])

def block_third_fourth(s, x):
    print("индексы x в s:", [i for i, val in enumerate(s) if val == x])

def block_third_fifth(s):
    print("sum элементов с 2 индексами:", sum(s[::2]))

def block_third_sixth(s):
    print("строка макс длины:", max(s, key=len))

def block_third_seventh(n):
    print("число является харшад числом:", n % sum(map(int, str(n))) == 0)

def block_third_eighth(size):
    print("рандом строка:", ''.join(random.choices(string.ascii_letters, k=size)))

def block_third_ninth(text):
    print("RLE-сжатие:", [(char, len(list(group))) for char, group in groupby(text)])

def block_fourth_first():
    try:
        '''
        generate_groups = lambda: [f"{x}{y}" for x in "АБВГДЕ" for y in range(1, 6)]
        '''
        print("generate_groups:", [f"{x}{y}" for x in "АБВГДЕ" for y in range(1, 6)])
    except Exception as e:
        print("4.1 err caught:", e)


def decrypt_tea(data, key):
    v0, v1 = data
    sum = 0xC6EF3720
    delta = 0x9E3779B9
    k0, k1, k2, k3 = key
    for _ in range(32):
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3)
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1)
        sum -= delta
    return v0, v1

def block_fourth_second():
    try:
        encrypted_data = [0xE3238557, 0x6204A1F8]
        key = [0, 4, 5, 1]
        decrypted = decrypt_tea(encrypted_data, key)
        print("decrypt_tea:", decrypted)
    except Exception as e:
        print("4.2 err caught:", e)


def block_fifth_first():
    def ham_dist(x, y):
        return bin(x ^ y).count('1')

    print("5.1")

    print(ham_dist(0b10, 0b11))#1

    print(ham_dist(0b1100, 0b0011))#4


#5.2
def block_fifth_second():
    def encode_val(k, m, n):
        return int(''.join([bin(n)[2:].zfill(k)] * m), 2)#двочиное представление - + нули до l k

    def decode_val(k, m, n):
        bin_n = bin(n)[2:]#2-представ - игнор 0b

        bin_n = bin_n.zfill(len(bin_n) + (k - len(bin_n) % k) % k)#add 0 , чтобы д % k

        blocks = [bin_n[i:i + k] for i in range(0, len(bin_n), k)]#строку на блоки по к

        decoded = int(''.join(blocks), 2)#возврат

        return decoded

    def ham_dist(x, y):
        return bin(x ^ y).count('1')

    encoded = encode_val(4, 3, 0b1011)
    print(f"coded значение: {bin(encoded)}")

    decoded = decode_val(4, 3, 0b111000111111)
    print(f"decoded значение: {bin(decoded)}")

    print(ham_dist(encode_val(4, 3, 0b1001), encode_val(4, 3, 0b1000)))

    decoded = decode_val(4, 3, 0b110010110111)#декод с коррекцией
    print(f"excep значение: {bin(decoded)}")

def block_fifth_third():
    def levenshtein_distance(s1, s2):
        len_s1, len_s2 = len(s1), len(s2)
        dp = [[0] * (len_s2 + 1) for _ in range(len_s1 + 1)]

        for i in range(len_s1 + 1):
            dp[i][0] = i
        for j in range(len_s2 + 1):
            dp[0][j] = j

        for i in range(1, len_s1 + 1):
            for j in range(1, len_s2 + 1):
                cost = 0 if s1[i - 1] == s2[j - 1] else 1
                dp[i][j] = min(
                    dp[i - 1][j] + 1,#del
                    dp[i][j - 1] + 1,#add
                    dp[i - 1][j - 1] + cost#rep
                )

        return dp[len_s1][len_s2]

    print(levenshtein_distance('столб', 'слон'))

def block_fifth_fourth():
    def levenshtein_operations(s1, s2):
        len_s1, len_s2 = len(s1), len(s2)
        dp = [[0] * (len_s2 + 1) for _ in range(len_s1 + 1)]

        for i in range(len_s1 + 1):
            dp[i][0] = i
        for j in range(len_s2 + 1):
            dp[0][j] = j

        for i in range(1, len_s1 + 1):
            for j in range(1, len_s2 + 1):
                cost = 0 if s1[i - 1] == s2[j - 1] else 1
                dp[i][j] = min(
                    dp[i - 1][j] + 1,#del
                    dp[i][j - 1] + 1,#add
                    dp[i - 1][j - 1] + cost#rep
                )

        i, j = len_s1, len_s2#восстанов пути
        operations = []

        while i > 0 or j > 0:
            if i > 0 and dp[i][j] == dp[i - 1][j] + 1:
                operations.append('удаление')
                i -= 1
            elif j > 0 and dp[i][j] == dp[i][j - 1] + 1:
                operations.append('вставка')
                j -= 1
            elif i > 0 and j > 0 and dp[i][j] == dp[i - 1][j - 1] + 1:
                operations.append('замена')
                i -= 1
                j -= 1
            else:
                i -= 1
                j -= 1

        operations.reverse()
        return operations

    print(levenshtein_operations('столб', 'слон'))

def block_fifth_five():
    def levenshtein_distance(s1, s2):
        dp = [[0] * (len(s2) + 1) for _ in range(len(s1) + 1)]
        for i in range(len(s1) + 1):
            dp[i][0] = i
        for j in range(len(s2) + 1):
            dp[0][j] = j
        for i in range(1, len(s1) + 1):
            for j in range(1, len(s2) + 1):
                cost = 0 if s1[i - 1] == s2[j - 1] else 1
                dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost)
        return dp[-1][-1]

    def lev_dist_gen(s1, s2):
        operations = []
        i, j = len(s1), len(s2)
        dp = [[0] * (j + 1) for _ in range(i + 1)]
        for x in range(i + 1):
            dp[x][0] = x
        for y in range(j + 1):
            dp[0][y] = y

        for x in range(1, i + 1):
            for y in range(1, j + 1):
                cost = 0 if s1[x - 1] == s2[y - 1] else 1
                dp[x][y] = min(
                    dp[x - 1][y] + 1,
                    dp[x][y - 1] + 1,
                    dp[x - 1][y - 1] + cost
                )

        x, y = i, j
        while x > 0 or y > 0:
            if x > 0 and dp[x][y] == dp[x - 1][y] + 1:
                operations.append(f"del x[{x - 1}]")
                x -= 1
            elif y > 0 and dp[x][y] == dp[x][y - 1] + 1:
                operations.append(f"x.insert({x}, y[{y - 1}])")
                y -= 1
            elif x > 0 and y > 0:
                if s1[x - 1] != s2[y - 1]:
                    operations.append(f"x[{x - 1}] = y[{y - 1}]")
                x -= 1
                y -= 1

        return '\n'.join(reversed(operations))

    print(lev_dist_gen('достаток', 'остаточный'))

    s1 = ''.join(random.choices(string.ascii_lowercase, k=10))
    s2 = ''.join(random.choices(string.ascii_lowercase, k=10))
    print(f"s1: {s1}, s2: {s2}")
    print(lev_dist_gen(s1, s2))

def block_fifth_six():
    def spell(word, dictionary):
        if word in dictionary:
            return word

        def candidates(dist):
            return [w for w in dictionary if levenshtein_distance(word, w) == dist]

        def best_candidate(candidates):
            return max(candidates, key=lambda w: dictionary[w], default=word)

        for dist in [1, 2]:
            found = candidates(dist)
            if found:
                return best_candidate(found)

        return word

    def levenshtein_distance(s1, s2):
        dp = [[0] * (len(s2) + 1) for _ in range(len(s1) + 1)]
        for i in range(len(s1) + 1):
            dp[i][0] = i
        for j in range(len(s2) + 1):
            dp[0][j] = j
        for i in range(1, len(s1) + 1):
            for j in range(1, len(s2) + 1):
                cost = 0 if s1[i - 1] == s2[j - 1] else 1
                dp[i][j] = min(
                    dp[i - 1][j] + 1,
                    dp[i][j - 1] + 1,
                    dp[i - 1][j - 1] + cost
                )
        return dp[-1][-1]

    dictionary = {'по-моему': 10, 'я': 100, 'написал': 90, 'всё': 80, 'правильно': 70}
    sentence = 'помоему я напесал усё правильна'.split()
    corrected = ' '.join(spell(word, dictionary) for word in sentence)
    print(corrected)

def block_fifth_seventh():
    similar_letters = {'a': 'а', 'e': 'е', 'o': 'о', 'p': 'р', 'c': 'с', 'x': 'х'}

    def modified_lev_dist(s1, s2):
        len_s1, len_s2 = len(s1), len(s2)
        dp = [[0] * (len_s2 + 1) for _ in range(len_s1 + 1)]

        for i in range(len_s1 + 1):
            dp[i][0] = i
        for j in range(len_s2 + 1):
            dp[0][j] = j

        for i in range(1, len_s1 + 1):
            for j in range(1, len_s2 + 1):
                cost = 0 if s1[i - 1] == s2[j - 1] or similar_letters.get(s1[i - 1]) == s2[j - 1] else 1
                dp[i][j] = min(
                    dp[i - 1][j] + 1,
                    dp[i][j - 1] + 1,
                    dp[i - 1][j - 1] + cost
                )
                if i > 1 and j > 1 and s1[i - 1] == s2[j - 2] and s1[i - 2] == s2[j - 1]:
                    dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + 1)
        return dp[len_s1][len_s2]

    def advanced_spell(word, dictionary):
        if word in dictionary:
            return word

        candidates = [(w, freq) for w, freq in dictionary.items() if modified_lev_dist(word, w) <= 2]
        if candidates:
            return max(candidates, key=lambda x: x[1])[0]
        return word

    dictionary = {'по-моему': 100, 'я': 200, 'написал': 150, 'всё': 300, 'правильно': 250}
    text = 'pomoymu ya napisal vsyo pravilno'
    words = text.split()
    corrected = [advanced_spell(word, dictionary) for word in words]
    print(' '.join(corrected))

def block_six_first():
    table = [
        ["Коллеги,", "парадигма цифровой экономики", "открывает новые возможности для", "дальнейшего углубления"],
        ["В то же время,", "контекст цифровой трансформации", "выдвигает новые требования",
         "бюджетного финансирования"],
        ["Однако,", "диджитализация бизнес-процессов", "несёт в себе риски", "синергетического эффекта"],
        ["Тем не менее,", "прагматичный подход к цифровым платформам", "расширяет горизонты",
         "компрометации конфиденциальных"]
    ]

    def generate_report(table, num_paragraphs=3):
        paragraphs = []
        for _ in range(num_paragraphs):
            sentences = []
            rows = random.sample(table, len(table))
            for row in rows:
                sentence = f"{row[0]} {row[1]} {row[2]} {row[3]}."
                sentences.append(sentence)
            paragraph = " ".join(sentences)
            paragraphs.append(paragraph)

        report = "Уважаемые коллеги, вашему вниманию представляется доклад по вопросам цифровой экономики.\n\n"
        report += "\n\n".join(paragraphs)
        return report

    #генерация доклада
    report_text = generate_report(table)
    print(report_text)


def block_six_second(text):
    sentences = text.replace("\n", " ").split(". ")
    table = []

    for sentence in sentences:
        sentence = sentence.strip()
        if not sentence:
            continue

        words = sentence.split()

        while len(words) < 4:
            words.append("")

        part_length = max(1, len(words) // 4)
        row = []

        for i in range(0, len(words), part_length):
            part = " ".join(words[i:i + part_length])
            row.append(part)

        if len(row) > 4:
            row = row[:4]

        while len(row) < 4:
            row.append("")

        table.append(row)

    return table

def block_six_third():
    def generate_name():
        first_names = [
            "даниил", "вадик", "ярик", "сеня", "Николай", "леха", "тоха",
            "амир", "илья", "игорт", "семен", "иван", "ваня", "даня"
        ]
        middle_initial = random.choice("АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЭЮЯ")

        syllables_start = ["Фу", "Фе", "Шо", "Та", "Му", "Чер", "На", "Ку", "Гу", "Се", "Ба", "Гид", "Са"]
        syllables_end = ["ций", "чли", "дяк", "сяк", "дич", "ев", "бян", "арий", "янц", "мидяк", "ко", "ин", "ский"]

        last_name = random.choice(syllables_start) + random.choice(syllables_end)
        return f"{random.choice(first_names)} {middle_initial}. {last_name}"

    for _ in range(10):
        print(generate_name())

def block_six_fourth():
    import random
    from collections import defaultdict

    def build_model(text, prefix_len):
        model = defaultdict(lambda: defaultdict(int))
        for i in range(len(text) - prefix_len):
            prefix = text[i:i + prefix_len]
            next_char = text[i + prefix_len]
            model[prefix][next_char] += 1
        return model

    def generate_text(model, prefix_len, length, start=None):
        if start is None:
            start = random.choice(list(model.keys()))
        result = start

        current_prefix = start
        for _ in range(length - prefix_len):
            if current_prefix not in model:
                break
            next_chars = list(model[current_prefix].keys())
            weights = list(model[current_prefix].values())
            next_char = random.choices(next_chars, weights=weights)[0]
            result += next_char
            current_prefix = result[-prefix_len:]
        return result

    text = "на дворе трава, на траве дрова"
    prefix_len = 2

    model = build_model(text, prefix_len)
    generated = generate_text(model, prefix_len, 100)
    print(generated)


def block_eighth_first():
    import os
    import argparse

    def list_dir(path, all=False, long=False):
        try:
            entries = os.listdir(path)
            if not all:
                entries = [e for e in entries if not e.startswith('.')]
            if long:
                for entry in entries:
                    full_path = os.path.join(path, entry)
                    stats = os.stat(full_path)
                    print(f'{stats.st_mode} {stats.st_size} {entry}')
            else:
                for entry in entries:
                    print(entry)
        except Exception as e:
            print(f"error: {e}")

    parser = argparse.ArgumentParser(description='аналог коаманды ls')
    parser.add_argument('path', nargs='?', default='.', help='путь к директории')
    parser.add_argument('-a', '--all', action='store_true', help='покащать все файлы - включая скрытые')
    parser.add_argument('-l', '--long', action='store_true', help='показать подробную инфу')
    args = parser.parse_args()

    list_dir(args.path, args.all, args.long)

def block_eighth_second():
    import os

    def build_tree(path, prefix=''):
        entries = os.listdir(path)
        for entry in entries:
            full_path = os.path.join(path, entry)
            if os.path.isdir(full_path):
                print(f'{prefix}"{entry}" [shape=folder];')
                build_tree(full_path, prefix + '    ')
            else:
                print(f'{prefix}"{entry}" [shape=file];')

    start_path = input('введи путь: ').strip()
    print('digraph G {')
    build_tree(start_path)
    print('}')

def block_eighth_third():


    def convert_quotes(text):
        result = []
        inside_code = False
        quote_open = True
        for line in text.splitlines():
            if line.strip().startswith('```'):
                inside_code = not inside_code
                result.append(line)
                continue
            if not inside_code:
                line = re.sub(r'"(.*?)"', lambda m: f'«{m.group(1)}»', line)
            result.append(line)
        return '\n'.join(result)

    parser = argparse.ArgumentParser(description='преобразование кавычек в кавычки-елочки')
    parser.add_argument('file', nargs='?', help='example.md')
    args = parser.parse_args()

    if args.file:
        with open(args.file, 'r', encoding='utf-8') as f:
            content = f.read()
    else:
        content = sys.stdin.read()

    print(convert_quotes(content))

def tasks_menu(block):
    while True:
        print(f"\nвыберите задание из блока {block} или 'exit' для возврата к выбору блока:")
        if block == '1':
            print("1")
            print("2")
            print("3")
            print("4")
            print("5")
            print("6")
            print("7")
            print("8")
        elif block == '2':
            print("1")
            print("2")
            print("3")
            print("4")
        if block == '3':
            print("1")
            print("2")
            print("3")
            print("4")
            print("5")
            print("6")
            print("7")
            print("8")
            print("9")
        if block == '4':
            print("1")
            print("2")
        if block == '5':
            print("1")
            print("2")
            print("3")
            print("4")
            print("5")
            print("6")
            print("7")
        if block == '6':
            print("1")
            print("2")
            print("3")
            print("4")
        if block == '8':
            print("1")
            print("2")
            print("3")

        task = input("номер задания: ").strip()

        if task.lower() == "exit":
            break

        if block == '1':
            if task == '1':
                block_first_first()
            elif task == '2':
                block_first_second()
            elif task == '3':
                block_first_third()
            elif task == '4':
                block_first_fourth()
            elif task == '5':
                block_first_fifth()
            elif task == '6':
                block_first_sixth()
            elif task == '7':
                block_first_seventh()
                block_first_eighth()
            else:
                print("error - try again")
        elif block == '2':
            if task == '1':
                block_second_first()
            elif task == '2':
                block_second_second()
            elif task == '3':
                block_second_third()
            elif task == '4':
                block_second_fourth()
            else:
                print("error - try again")
        elif block == '3':
            if task == '1':
                block_third_first(["1", "2", "3"])
            elif task == '2':
                block_third_second([1, 2, 2, 3, 4])
            elif task == '3':
                block_third_third([1, 2, 3, 4])
            elif task == '4':
                block_third_fourth([1, 2, 3, 1, 2, 3], 2)
            elif task == '5':
                block_third_fifth([1, 2, 3, 4, 5])
            elif task == '6':
                block_third_sixth(["short", "longer", "longest"])
            elif task == '7':
                block_third_seventh(18)
            elif task == '8':
                block_third_eighth(10)
            elif task == '9':
                block_third_ninth("ABBCCCDEF")
            else:
                print("error - try again")
        elif block == '4':
            if task == '1':
                block_fourth_first()
            elif task == '2':
                block_fourth_second()
            else:
                print("error - try again")
        elif block == '5':
            if task == '1':
                block_fifth_first()
            elif task == '2':
                block_fifth_second()
            elif task == '3':
                block_fifth_third()
            elif task == '4':
                block_fifth_fourth()
            elif task == '5':
                block_fifth_five()
            elif task == '6':
                block_fifth_six()
            elif task == '7':
                block_fifth_seventh()
            else:
                print("error - try again")
        elif block == '6':
            if task == '1':
                block_six_first()
            elif task == '2':
                text = input("введите текст для преобразования:\n")
                table = block_six_second(text)
                print("\nполученная таблица:")
                for row in table:
                    print(row)
            elif task == '3':
                block_six_third()
            elif task == '4':
                block_six_fourth()
        #else:
        #    print("error - try again")
            #if task == '1': block_six_first()
            #if task == '2': block_six_second()
            #if task == '3': block_six_second()
        if block == '8':
            if task == '1':
                block_eighth_first()
            elif task == '2':
                block_eighth_second()
            elif task == '3':
                block_eighth_third()
            else:
                print("error - try again")

def main():
    launcher()

if __name__ == '__main__':
    main()
