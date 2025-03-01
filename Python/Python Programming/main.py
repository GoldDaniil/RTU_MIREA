import math
import tkinter as tk

def launcher():
    while True:
        print("\nвыберите номер блока или 'exit' для заверщения:")
        print(" 1 - блок 1")
        print(" 2 - блок 2")
        print(" 3 - блок 3")
        print(" 4 - блок 4")
        print(" 5 - блок 5")
        block = input("номер блока: ").strip()
        if block.lower() == "exit":
            print("пока")
            break
        elif block in ['1', '2', '3', '4', '5']:
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
    d = c - (x - c)
    return d
''')

def block_third_fourth():
    print('''\
def naive_mul(x, y):
    result = 0
    for i in range(y):
        result = result + x
    return result

if __name__ == '__main__':
    for _ in range(10):
        a = random.randint(1, 100)
        b = random.randint(1, 100)
        assert naive_mul(a, b) == a * b"
    print("all tests passed")
''')

def block_third_fifth():
    print('''\
def fast_mul(x, y):
    result = 0
    shift = 0
    while y > 0:
        if y & 1:
            result += x << shift
        y >>= 1
        shift += 1
    return result
assert fast_mul(15, 10) == 15 * 10
    ''')

def block_third_six():
    print('''\
    result = 1
    while n > 0:
        if n & 1:
            result *= x
        x *= x
        n >>= 1
    return result
assert fast_pow(5, 3) == pow(5, 3)
    ''')

#------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------

def block_third_seven_bits(x, y, bits):
    x &= (2 ** bits - 1)
    y &= (2 ** bits - 1)
    return x * y

def block_third_seven_l16(x, y):
    xLow = x & 0x00FF
    xHigh = (x & 0xFF00) >> 8
    yLow = y & 0x00FF
    yHigh = (y & 0xFF00) >> 8

    xLow_yLow = block_third_seven_bits(xLow, yLow, 8)
    xHigh_yLow = block_third_seven_bits(xHigh, yLow, 8)
    xLow_yHigh = block_third_seven_bits(xLow, yHigh, 8)
    xHigh_yHigh = block_third_seven_bits(xHigh, yHigh, 8)

    return ((xHigh_yHigh) << 16) + ((xHigh_yLow + xLow_yHigh) << 8) + (xLow_yLow)
assert block_third_seven_l16(65025, 63100) == 65025 * 63100

#------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------

def block_third_eight(x, y):
    x0 = x & 0xFF
    x1 = (x >> 8) & 0xFF

    y0 = y & 0xFF
    y1 = (y >> 8) & 0xFF

    z0 = x0 * y0
    z1 = x1 * y1
    z2 = (x1 + x0) * (y1 + y0) - z1 - z0

    result = (z1 << 16) + (z2 << 8) + z0
    return result

assert block_third_eight(65025, 63100) == 65025 * 63100

#------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------

#3.9
def fast_mul_gen(var):

    def fast_mul(x, y):
        print("-" * 30)
        result = 0
        sums = 0
        print('f(x) =', result, '\ny = ', y)
        sums += 1
        shift = 0
        while x:
            if x % 2 != 0:
                print(f'f(x) = {result} + {y}')
                result += y << shift
                sums += 1
            print('y = y + ', y)
            x >>= 1
            shift += 1
            sums += 1
        print('f(x) =', result, '\nsummaries made:', sums)
        return result

    def task12(x):
        return fast_mul(x, 12)
    def task16(x):
        return fast_mul(x, 16)
    def task15(x):
        return fast_mul(x, 15)

    print(task12(var))
    print(task16(var))
    print(task15(var))

fast_mul_gen(2)



#------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------

def block_third_ten(var):

    def fast_pow(x, y):
        print("-" * 30)
        result = 1
        oper = 0
        print('f(x) =', result, '\ny = ', y)
        oper += 1
        while y > 0:
            if y & 1:
                print(f'f(x) = {result} + {y}')
                result *= x
                oper += 1
            print('y = y + ', y)
            oper += 1
            x *= x
            y >>= 1
        print('f(x) =', result, '\nOperations made:', oper)
        return result

    def task1(x):
        return fast_pow(x, 2)
    def task2(x):
        return fast_pow(x, 4)
    def task3(x):
        return fast_pow(x, 8)

    print(task1(var))
    print(task2(var))
    print(task3(var))


#--- 4 Пиксельные шейдеры----------------------------------------------------------------------------------------------------------------------------------------
#def block_four_one():

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

def block_four_two(shader, width, height):
    image = bytearray((0, 0, 0) * width * height)
    for y in range(height):
        for x in range(width):
            pos = (width * y + x) * 3
            color = shader(x / width, y / height)
            normalized = [max(min(int(c * 255), 255), 0) for c in color]
            image[pos:pos + 3] = normalized
    header = bytes(f'P6\n{width} {height}\n255\n', 'ascii')
    return header + image

def start(shader):
    root = tk.Tk()
    root.title("asdas")
    img = tk.PhotoImage(data=block_four_two(shader, 256, 256)).zoom(2, 2)
    label = tk.Label(root, image=img)
    label.pack()
    root.mainloop()

def shader_41(x, y):
    return 0.0, 0.0, 0.0

def test_42(x, y):
    cx, cy = 0.5, 0.5
    radius = 0.4
# ------------------------------------------------------------------------------

    dx = x - cx  # будем делать арасст от центрва
    dy = y - cy
    r = math.sqrt(dx * dx + dy * dy)

    mask = (1 - math.tanh((r - radius) * 20)) / 2
    # https://github.com/Harry24k/adversarial-attacks-pytorch/blob/master/torchattacks/attacks/cw.py

    t = (y - (cy - radius)) / (2 * radius)  # первый параметр: от 0 (верх) до 1 (низ)

    # градиент
    if t < 0.5:
        f = t / 0.5  # f
        r_col = 0.5 + f * (1.0 - 0.5)
        g_col = 1.0  # f
        b_col = 0.5 + f * (0.0 - 0.5)
    else:
        f = (t - 0.5) / 0.5  # от центра к низу
        r_col = 1.0
        g_col = 1.0 + f * (0.0 - 1.0)
        b_col = 0.0  # f

    bgBLACK = 0.05

    red = bgBLACK + mask * (r_col - bgBLACK)
    green = bgBLACK + mask * (g_col - bgBLACK)
    blue = bgBLACK + mask * (b_col - bgBLACK)
    return red, green, blue

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

def create_canvas(width, height):
    root = tk.Tk()
    root.title("sdflsdkl")
    canvas = tk.Canvas(root, width=width, height=height, bg="black")
    canvas.pack()
    return root, canvas

def draw_pacman(canvas, x, y, size):
    mouth_angle = 70#size
    start_angle = 35#right
    extent_angle = 360 - mouth_angle#часть дуги

    canvas.create_arc(x, y, x + size, y + size, start=start_angle,
                      extent=extent_angle, fill="yellow", outline="yellow")

    eye_radius = size * 0.05#size глаза относительно диаметра
    eye_x = x + size * 0.65
    eye_y = y + size * 0.25
    canvas.create_oval(eye_x - eye_radius, eye_y - eye_radius,
                       eye_x + eye_radius, eye_y + eye_radius,
                       fill="black", outline="black")

def block_four_three():
    canvas_size = 400
    root, canvas = create_canvas(canvas_size, canvas_size)

    pacman_size = canvas_size * 0.8
    pacman_x = (canvas_size - pacman_size) / 2
    pacman_y = (canvas_size - pacman_size) / 2

    draw_pacman(canvas, pacman_x, pacman_y, pacman_size)
    root.mainloop()

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

def noise(x, y):
    n = x + y * 57#сворач х и у в одно

    n = (n << 13) ^ n#бит операция - перемеш бит (хеш-функция)
    n = n * (n * n * 60493 + 19990303) + 1376312589

    n = n & 0x7fffffff#привет сиаод - 31 бит + убираем знак

    return n / float(0x7fffffff)#ток 0..1

def block_four_four():
    width, height = 400, 400

    root = tk.Tk()
    root.title("gfdgd")

    canvas = tk.Canvas(root, width=width, height=height, bg="white", highlightthickness=0)
    canvas.pack()

    for y in range(height):
        for x in range(width):
            val = noise(x, y)#знач
            gray = int(val * 255)#серый от 0
            color = f"#{gray:02x}{gray:02x}{gray:02x}"#RRGGBB
            canvas.create_rectangle(x, y, x + 1, y + 1, outline=color, fill=color)

    root.mainloop()

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

def block_four_five() :
    width, height = 256, 256
    scale = 16.0

    root = tk.Tk()
    root.title("asdasdsad")

    canvas = tk.Canvas(root, width=width, height=height, bg="white", highlightthickness=0)
    canvas.pack()

    for y in range(height):
        for x in range(width):
            px = x / scale
            py = y / scale

            val = val_noise(px, py)

            gray = int(val * 255)
            color = f"#{gray:02x}{gray:02x}{gray:02x}"

            canvas.create_rectangle(x, y, x + 1, y + 1, outline=color, fill=color)

    root.mainloop()

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

def fade(t):
    return 3 * (t**2) - 2 * (t**3)

def val_noise(px, py):
    x0 = math.floor(px)#округление вниз
    y0 = math.floor(py)
    x1 = x0 + 1
    y1 = y0 + 1

    dx = px - x0#float
    dy = py - y0

    v00 = noise(x0, y0)#noise squard
    v10 = noise(x1, y0)
    v01 = noise(x0, y1)
    v11 = noise(x1, y1)

    u = fade(dx)
    v = fade(dy)

    # Интерполяция по x
    ix0 = v00 + u * (v10 - v00)#интер х
    ix1 = v01 + u * (v11 - v01)

    return ix0 + v * (ix1 - ix0)#y

def fractal_noise(px, py, octaves=5, persistence=0.5, lacunarity=2.0):
    total = 0.0
    amplitude = 1.0
    frequency = 1.0
    max_value = 0.0#нужно чтобы нормировать результат в диапазон [0..1]

    for _ in range(octaves):
        total += val_noise(px * frequency, py * frequency) * amplitude#текущ частота

        max_value += amplitude
        amplitude *= persistence
        frequency *= lacunarity

    return total / max_value

def blend_colors(c1, c2, t):
    r = int(c1[0] + (c2[0] - c1[0]) * t)#интерпол с1 / с2
    g = int(c1[1] + (c2[1] - c1[1]) * t)
    b = int(c1[2] + (c2[2] - c1[2]) * t)
    return (r, g, b)

def block_four_six():
    width, height = 512, 512

    octaves = 5#фрактал шум
    persistence = 0.5
    lacunarity = 2.0

    scale = 0.01#масггтаб по осям

    sky_color = (70, 130, 180)
    cloud_color = (255, 255, 255)

    root = tk.Tk()
    root.title("Fractal Clouds (fBm)")

    canvas = tk.Canvas(root, width=width, height=height, bg="white", highlightthickness=0)
    canvas.pack()

    for y in range(height):
        for x in range(width):
            val = fractal_noise(x * scale, y * scale, octaves, persistence, lacunarity)#фрактал шум

            #val = val**1.3

            r, g, b = blend_colors(sky_color, cloud_color, val)

            color_hex = f"#{r:02x}{g:02x}{b:02x}"#RRGGBB

            canvas.create_rectangle(x, y, x + 1, y + 1, outline=color_hex, fill=color_hex)#1x1

    root.mainloop()
# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

# def block_four_seven():


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
        elif block == '4':
            print('1')
            print('2')
            print('3')
            print('4')
            print('5')
            print('6')
            print('7')

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
            elif task == '5': block_third_fifth()
            elif task == '6': block_third_six()
            elif task == '7': block_third_fourth()
            elif task == '8': block_third_eight()
            elif task == '9': block_third_fourth()
            elif task == '10':block_third_ten(2)
            print("error - try again")
        elif block == '4':
            #if task == '1': block_four_one()
            if task == '2': start(test_42)
            elif task == '3': block_four_three()
            elif task == '4': block_four_four()
            elif task == '5': block_four_five()
            elif task == '6': block_four_six()
            #elif task == '7': block_four_seven()

def main():
    launcher()

if __name__ == '__main__':
    main()
