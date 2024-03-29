#готово
import math
import math as m
import numpy as np
import matplotlib.pyplot as plt

def check_variable_int_float(variable):
    # функция - которая проверяет - является ли переменная целым или числом
    # с плавающей точкой(дробным числом)и предоставляет пользователю возможность
    # вводить значение переменной до тех пор - пока не будет введен верный тип
    while True:
        try:
            variable = float(variable)  # преобразуем введенное значение в число
            return variable  # возвращаем значение - если успешно преобразовалось
        except ValueError:
            print("error/ required type - integer/float \n")
            variable = input("try entering again: ")  # запрашиваем ввод снова

def check_variable_str(variable):
    while True:
        try:
            variable = str(variable)
            return variable
        except ValueError:
            print("error. required type - string \n")
            variable = input("try entering again: ")

# ------------------------------------------------------------------

def task_1_3():
    x = 5 >= 2
    A = {1, 3, 7, 8}
    B = {2, 4, 5, 10, 'apple'}
    C = A & B
    df = 'Антоновна Антонина', 34, 'ж'
    z = 'type'
    D = [1, 'title', 2, 'content']

    print(x, '|', type(x), '\n', A, '|', type(A), '\n', B, '|', type(B), '\n', C, '|', type(C), '\n', df, '|', type(df),
          '\n', z, '|', type(z), '\n', D, '|', type(D))


def task_2_3():
    variable = input("enter x: ")
    x = check_variable_int_float(variable)

    if x < -5:
        print('(-infinity, -5)')
    elif -5 <= x <= 5:
        print('[-5, 5]')
    else:
        print('(5, +infinity)')


def task_3_3_1():
    variable = input("enter x: ")
    x = check_variable_int_float(variable)

    while x >= 1:
        print(x)
        x -= 3


def task_3_3_2():
    features = [
        "Возраст",
        "Пол",
        "Рост",
        "Вес",
        "Группа крови",
        "Этническая принадлежность",
        "Образование",
        "Профессия",
        "Семейное положение",
        "Доход"
    ]

    for feature in features:
        print(feature)


def task_3_3_3():
    numbers = list(range(2, 16))
    print(numbers)


def task_3_3_4():
    for i in range(105, 5, -25):
        print(i)


def task_3_3_5():
    x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    even_indices_slice = x[2:9:2]  # 2 - начальный индекс, 9 - конечный индекс (не включая), 2 - шаг
    even_indices_slice.reverse()
    x[2:9:2] = even_indices_slice  # заменяем часть списка перевернутым срезом
    print(x)


def task_4_3_1():
    np.random.seed(42)  # чтобы результат был воспроизводимым
    data = np.random.rand(100)

    # рассчитываем среднее значение
    mean_value = np.mean(data)

    # рассчитываем медиану
    median_value = np.median(data)

    print("среднее значение:", mean_value)
    print("медиана:", median_value)

    # строим точечную диаграмму рассеяния
    plt.figure(figsize=(8, 6))
    plt.scatter(range(len(data)), data, color='blue', alpha=0.5)
    plt.axhline(y=mean_value, color='r', linestyle='-', label='среднее значение')
    plt.axhline(y=median_value, color='g', linestyle='--', label='медиана')
    plt.xlabel('индекс')
    plt.ylabel('значение')
    plt.title('точечная диаграмма рассеяния')
    plt.legend()
    plt.grid(True)
    plt.show()


def task_4_3_2():
    # функция
    def my_function(x):
        return (math.sqrt(1 + math.exp(math.sqrt(x)) + math.cos(x ** 2)) /
                abs(1 - math.sin(x) ** 3)) + math.log(abs(2 * x))

    # создаем массив x от 1 до 10
    x = np.linspace(1, 10, 10)

    # вычисляем значения функции для массива x
    y = np.array([my_function(val) for val in x])

    # выделение среза первой половины массива
    x_slice = x[:5]
    y_slice = y[:5]

    # построение графика для основного массива (линейный)
    plt.figure(figsize=(10, 5))
    plt.plot(x, y, label='основной массив', color='blue')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('график функции')
    plt.grid(True)
    plt.legend()
    plt.show()

    # построение графика для среза (точечный)
    plt.figure(figsize=(10, 5))
    plt.scatter(x_slice, y_slice, label='Срез', color='red')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('график среза первой половины массива')
    plt.grid(True)
    plt.legend()
    plt.show()


def task_4_3_3():
    from scipy.integrate import simps  ### scipy.integrate ???
    from numpy import trapz
    import matplotlib.pyplot as plt

    # определяем функцию
    def f(x):
        return np.abs(np.cos(x * np.exp(np.cos(x) + np.log(x + 1))))

    # задаем интервал и шаг
    a = 0
    b = 10
    h = 1

    # вычисляем значения функции
    x = np.arange(a, b + h, h)
    y = f(x)

    # вычисляем площадь под кривой
    S = trapz(y, x)

    # строим график
    plt.plot(x, y, color="blue")
    plt.fill_between(x, y, 0, color="gray")

    # фформляем график
    plt.xlabel("x")
    plt.ylabel("|cos(x * e^(cos(x) + ln(x + 1)))|")
    plt.grid()

    # показываем график
    plt.show()

    # выводим площадь
    print("Площадь:", S)


def task_4_3_4():
    import yfinance as yf
    import matplotlib.pyplot as plt
    import numpy as np

    a = yf.download('AAPL', '2021-01-01', '2021-12-31')
    b = yf.download('MSFT', '2021-01-01', '2021-12-31')
    d = yf.download('GOOG', '2021-01-01', '2021-12-31')

    plt.grid(True)
    plt.plot(a, color='g')
    plt.plot(b, color='b')
    plt.plot(d, color='r')
    plt.show()


def task_4_3_5():
    import math

    def add(x, y):
        return x + y

    def subtract(x, y):
        return x - y

    def multiply(x, y):
        return x * y

    def divide(x, y):
        if y == 0:
            return "error\n"
        else:
            return x / y

    def exponential(x, y):
        return math.exp(x + y)

    def sine(x, y):
        return math.sin(x + y)

    def cosine(x, y):
        return math.cos(x + y)

    def power(x, y):
        return x ** y

    print("select operation:")
    print("1. addition +")
    print("2. subtraction -")
    print("3. multiplication *")
    print("4. division /")
    print("5. exponential function (e**(x+y))")
    print("6. sine (sin(x + y))")
    print("7. cosine (cos(x + y))")
    print("8. exponentiation (x**y)")

    def check_variable_int_float(var):
        try:
            return int(var)
        except ValueError:
            try:
                return float(var)
            except ValueError:
                return None

    variable = input("enter transaction number (1/ 2/ 3/ 4/ 5/ 6/ 7/ 8): ")
    choice = check_variable_int_float(variable)

    if choice in (1, 2, 3, 4, 8):
        num1 = input("enter first number: ")
        num1 = check_variable_int_float(num1)
        num2 = input("enter second number: ")
        num2 = check_variable_int_float(num2)

        if choice == 1:
            print("result:", add(num1, num2))
        elif choice == 2:
            print("result: ", subtract(num1, num2))
        elif choice == 3:
            print("result: ", multiply(num1, num2))
        elif choice == 4:
            print("result: ", divide(num1, num2))
        elif choice == 8:
            print("result: ", power(num1, num2))
    else:
        num = input("enter number: ")
        num = check_variable_int_float(num)

        if choice == 5:
            print("result: ", exponential(num, num))
        elif choice == 6:
            print("result: ", sine(num, num))
        elif choice == 7:
            print("result: ", cosine(num, num))




def main():
    while True:
        print("\nselect a task to open:")
        print("1 = task 1.3")
        print("2 = task 2.3")
        print("3 = task 3.3.1")
        print("4 = task 3.3.2")
        print("5 = task 3.3.3")
        print("6 = task 3.3.4")
        print("7 = task 3.3.5")
        print("8 = task 4.3.1")
        print("9 = task 4.3.2")
        print("10 = task 4.3.3")
        print("11 = task 4.3.4")
        print("12 = task 4.3.5")
        print("no task - if you want to exit, enter 'exit'\n\n")

        choice = input("enter your choice: ")

        if choice == '1':
            task_1_3()
        elif choice == '2':
            task_2_3()
        elif choice == '3':
            task_3_3_1()
        elif choice == '4':
            task_3_3_2()
        elif choice == '5':
            task_3_3_3()
        elif choice == '6':
            task_3_3_4()
        elif choice == '7':
            task_3_3_5()
        elif choice == '8':
            task_4_3_1()
        elif choice == '9':
            task_4_3_2()
        elif choice == '10':
            task_4_3_3()
        elif choice == '11':
            task_4_3_4()
        elif choice == '12':
            task_4_3_5()

        elif choice == 'exit':
            print("oh, okay:(")
            break
        else:
            print("invalid choice. please enter a valid option")


if __name__ == "__main__":
    main()
