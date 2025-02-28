def launcher():
    while True:
        print("\nвыберите номер блока или 'exit' для заверщения:")
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
    print("\ncпособы записи числа 42:\n")
    lit1 = 42#dec
    lit2 = 0b101010#b стр 2
    lit3 = 0B101010#b пр
    lit4 = 0o52#o 8
    lit5 = 0o5_2#o + разделитель
    lit6 = 0x2A#A- прописи
    lit7 = 0x2_A#A с разделителем 16
    lit8 = 0x2a#a строчные 16
    lit9 = 4_2#десятичн с разделителем
    lit10 = 42.0
    lit12 = 4_2.0
    lit13 = 42e0#float со степенью 0
    lit14 = (42)
    lit15 = 42 + 0j

    literals = [
        lit1, lit2, lit3, lit4, lit5, lit6, lit7, lit8,
        lit9, lit10, lit12, lit13, lit14, lit15
    ]

    for i, lit in enumerate(literals, start=1):
        if isinstance(lit, complex):
            res = (lit == 42)
            print(f"{i:2d}. {lit!r:>10}  ->  {res} (тип: {type(lit).__name__})")
        else:
            print(f"{i:2d}. {lit!r:>10}  ->  {lit == 42}")

def block_first_second():
    import sys
    print("\nв питоне:")
    print("целые числа (int) имеют произвольную точность – ограничены только памятью\n числа с плавающей точкой (float) основаны на стандарте IEEE-754 (64-битное представление)\nмаксимальное значение float: {sys.float_info.max:e}")

def block_first_third():
    print("\nответ:")
    print("функция divmod(a, b) возвращает одновременно частное и остаток от деления")
    a, b = 17, 5
    print(f"divmod({a}, {b}) -> {divmod(a, b)}")

def block_first_fourth():
    code_snippet = '''\
a = 10
while a != 0:
    a -= 0.1
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("число 0.1 не может быть представлено точно в двоичном формате - что приводит к накоплению погрешностей\n"
          "условие (a != 0) может никогда не выполниться - и цикл зациклится")

def block_first_fifth():
    code_snippet = '''\
z = 1
z <<= 40
2 ** z.
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("после сдвига битов z становится очень большим и вычисление 2 ** z \nпытается возвести 2 в большую степень что приводит к зависанию или долгому вычислению")

def block_first_sixth():
    code_snippet = '''\
i = 0
while i < 10:
    print(i)
    ++i
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("в питон оператор ++ не увеличивает значение переменной\n выражение ++i просто интерпретируется как +(+i) и i не изменяется\nчто приводит к бесконечному циклу\n правильно использовать i += 1")

def block_first_seventh():
    code_snippet = "(True * 2 + False) * -True"
    print('\nисходный код:')
    print(code_snippet)
    print("в питон булевы значения являются подклассами int - где True = 1 - а False = 0 \nтаким образом выражение становится:")
    print("(1 * 2 + 0) * -1, что равно -2")

def block_first_eighth():
    code_snippet = '''\
x = 5
print(1 < x < 10) #True
x = 5
print(1 < (x < 10)) #False
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("в выражении 1 < x < 10 Python интерпретирует это как две проверки: 1 < x и x < 10\nи возвращает True - если обе истины \nесли же обернуть (x < 10) в скобки - сначала вычислится x < 10 - что даст True\nа затем сравнение 1 < True (где True эквивалентно 1) даст False - так как 1 < 1 ложно")

#=== 2. Сообщения об ошибках------------------------------------------------------------------------------------------------------------------------------------------

def block_second_first():
    code_snippet = '''\
def func()
    print("Missing colon in function definition")
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("SyntaxError: invalid syntax — пропущен двоеточие после определения функции")

def block_second_second():
    code_snippet = '''\
42 = x
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("SyntaxError: cannot assign to literal — попытка присвоить значение литералу - что недопустимо")

def block_second_third():
    code_snippet = '''\
print(undeclared_variable)
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("NameError: name 'undeclared_variable' is not defined — переменная не была объявлена до использования")

def block_second_fourth():
    code_snippet = '''\
s = "This string never ends...
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("SyntaxError: unterminated string literal — строковый литерал не завершён (пропущена закрывающая кавычка)")

def block_second_fifth():
    code_snippet = '''\
result = "string" - 5
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("TypeError: unsupported operand type(s) for -: 'str' and 'int' — нельзя вычитать число из строки")

def block_second_sixth():
    code_snippet = '''\
if True:
print("No indentation")
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("IndentationError: expected an indented block — после конструкции if требуется отступ для вложенного блока кода")

def block_second_seventh():
    code_snippet = '''\
def func():
    print("Hello")
  print("Mismatch indentation")
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("IndentationError: unindent does not match any outer indentation level — уровень отступов не совпадает с ожидаемым")

def block_second_eighth():
    code_snippet = '''\
import math
result = math.sqrt(-1)
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("ValueError: math domain error — попытка извлечь квадратный корень из отрицательного числа")

def block_second_ninth():
    code_snippet = '''\
import math
result = math.exp(1000)
'''
    print('\nисходный код:')
    print(code_snippet.rstrip())
    print("OverflowError: math range error — результат вычисления выходит за пределы представимых значений")


#--- 3. Арифметика ----------------------------------------------------------------------------------------------------------------------------------------
def block_third_first():
    print('''\
def multiply_by_12(x):
    a = x + x     #2x   1 сл
    b = a + x     #3x   2 сл
    c = b + b     #6x   3 сл
    result = c + c#12x  4 сл
    return result
''')

def block_third_second():
    print('''\
def multiply_by_16(x):
    a = x + x     #2x   1 сл
    b = a + a     #4x   2 сл
    c = b + b     #8x   3 сл
    result = c + c#16x  4 сл
    return result
''')

def block_third_third():
    print('''\
def multiply_by_15(x):
    a = x + x  #2x
    b = a + a  #4x
    c = b + b  #8x
    result = c + c - (a - x)#(c+c)=16x, (a - x)= (2x-x)=x, 16x - x = 15x
    return result
''')

def block_third_fourth():
    print('''\
def naive_mul(x, y):
    result = 0
    for i in range(y):
        result = result + x
    return result

if __name__ == '__main__':
    import random
    for _ in range(10):
        a = random.randint(1, 100)
        b = random.randint(1, 100)
        assert naive_mul(a, b) == a * b, f"Test failed for a={a}, b={b}"
    print("All tests passed.")
''')

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
            print("1 - SyntaxError")
            print("2 - SyntaxError")
            print("3 - NameError")
            print("4 - SyntaxError")
            print("5 - TypeError")
            print("6 - IndentationError")
            print("7 - IndentationError")
            print("8 - ValueError")
            print("9 - OverflowError")
        elif block == '3':
            print("1")
            print("2")
            print("3")
            print("4")
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
            elif task == '8':
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
            elif task == '5':
                block_second_fifth()
            elif task == '6':
                block_second_sixth()
            elif task == '7':
                block_second_seventh()
            elif task == '8':
                block_second_eighth()
            elif task == '9':
                block_second_ninth()
            else:
                print("error - try again")
        elif block == '3':
            if task == '1': block_third_first()
            elif task == '2': block_third_second()
            elif task == '3': block_third_third()
            elif task == '4': block_third_fourth()
            print("error - try again")
def main():
    launcher()

if __name__ == '__main__':
    main()
