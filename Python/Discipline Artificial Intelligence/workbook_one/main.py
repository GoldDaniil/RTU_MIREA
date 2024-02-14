def task_1_3():
    x = 5 >= 2
    A = {1, 3, 7, 8}
    B = {2, 4, 5, 10, 'apple'}
    C = A & B
    df = 'Антоновна Антонина', 34, 'ж'
    z = 'type'
    D = [1, 'title', 2, 'content']

    print(x, '|', type(x), '\n', A, '|', type(A), '\n', B, '|', type(B), '\n', C, '|', type(C), '\n', df, '|', type(df), '\n', z, '|', type(z), '\n', D, '|', type(D))

def task_2_3():
    x = int(input("\nenter x: "))

    if x < -5:
        print('(-infinity, -5)')
    elif -5 <= x <= 5:
        print('[-5, 5]')
    else:
        print('(5, +infinity)')

def task_3_3_1():
    x = int(input('enter x = '))
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
    for num in range(106, 5, 25):
        print(num)

def task_3_3_5():
    x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    even_indices_slice = x[2:9:2]  # 2 - начальный индекс, 9 - конечный индекс (не включая), 2 - шаг
    even_indices_slice.reverse()
    x[2:9:2] = even_indices_slice  # заменяем часть списка перевернутым срезом

    print(x)

def task_4_3_1():
    import math as m
    import numpy as np
    import matplotlib.pyplot as plt

    np.random.seed(42)  # Чтобы результат был воспроизводимым
    data = np.random.rand(100)

    # Рассчитываем среднее значение
    mean_value = np.mean(data)

    # Рассчитываем медиану
    median_value = np.median(data)

    print("Среднее значение:", mean_value)
    print("Медиана:", median_value)

    # Строим точечную диаграмму рассеяния
    plt.figure(figsize=(8, 6))
    plt.scatter(range(len(data)), data, color='blue', alpha=0.5)
    plt.axhline(y=mean_value, color='r', linestyle='-', label='Среднее значение')
    plt.axhline(y=median_value, color='g', linestyle='--', label='Медиана')
    plt.xlabel('Индекс')
    plt.ylabel('Значение')
    plt.title('Точечная диаграмма рассеяния')
    plt.legend()
    plt.grid(True)
    plt.show()

def task_4_3_2():
    import numpy as np
    import matplotlib.pyplot as plt
    import math

    # Функция
    def my_function(x):
        return (math.sqrt(1 + math.exp(math.sqrt(x)) + math.cos(x**2)) /
                abs(1 - math.sin(x)**3)) + math.log(abs(2*x))

    # Создаем массив x от 1 до 10
    x = np.linspace(1, 10, 10)

    # Вычисляем значения функции для массива x
    y = np.array([my_function(val) for val in x])

    # Выделение среза первой половины массива
    x_slice = x[:5]
    y_slice = y[:5]

    # Построение графика для основного массива (линейный)
    plt.figure(figsize=(10, 5))
    plt.plot(x, y, label='основной массив', color='blue')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('график функции')
    plt.grid(True)
    plt.legend()
    plt.show()

    # Построение графика для среза (точечный)
    plt.figure(figsize=(10, 5))
    plt.scatter(x_slice, y_slice, label='Срез', color='red')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('график среза первой половины массива')
    plt.grid(True)
    plt.legend()
    plt.show()

def task_4_3_3():
    from scipy.integrate import simps
    from numpy import trapz


def task_4_3_4():
    print("  ")

def task_4_3_5():
    print("  ")


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
