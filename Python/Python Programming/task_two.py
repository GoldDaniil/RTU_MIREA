import pycodestyle
import random
import string
from itertools import groupby

def launcher():
    while True:
        print("\nвыберите номер блока или 'exit' для завершения:")
        print(" 1 - блок 1")
        print(" 2 - блок 2")
        print(" 3 - блок 3")
        block = input("номер блока: ").strip()
        if block.lower() == "exit":
            print("пока")
            break
        elif block in ['1', '2', '3']:
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
    print("Преобразование строк в числа:", list(map(int, s)))

def block_third_second(s):
    print("Количество уникальных элементов:", len(set(s)))

def block_third_third(s):
    print("Обратная последовательность:", s[::-1])

def block_third_fourth(s, x):
    print("Индексы x в s:", [i for i, val in enumerate(s) if val == x])

def block_third_fifth(s):
    print("Сумма элементов с четными индексами:", sum(s[::2]))

def block_third_sixth(s):
    print("Строка максимальной длины:", max(s, key=len))

def block_third_seventh(n):
    print("Число является харшад-числом:", n % sum(map(int, str(n))) == 0)

def block_third_eighth(size):
    print("Случайная строка:", ''.join(random.choices(string.ascii_letters, k=size)))

def block_third_ninth(text):
    print("RLE-сжатие:", [(char, len(list(group))) for char, group in groupby(text)])

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

def main():
    launcher()

if __name__ == '__main__':
    main()
