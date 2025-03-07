import pycodestyle
import random
import string
from itertools import groupby
import struct
def launcher():
    while True:
        print("\nвыберите номер блока или 'exit' для завершения:")
        print(" 1 - блок 1")
        print(" 2 - блок 2")
        print(" 3 - блок 3")
        print(" 4 - блок 4")

        block = input("номер блока: ").strip()
        if block.lower() == "exit":
            print("пока")
            break
        elif block in ['1', '2', '3', '4']:
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

def main():
    launcher()

if __name__ == '__main__':
    main()
