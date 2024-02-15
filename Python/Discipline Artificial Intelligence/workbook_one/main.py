#написать функцию с параметрами для проверки введенных данных - вводится переменная - закидываю ее в параметры ф-ции
#прописать исключения - не отваливалось

def check_variable_type(variable, expected_type):
    try:
        expected_type(variable)
        return True
    except ValueError:
        return False

def check_variables(variables):
    for var_name, expected_type in variables.items():
        while True:
            user_input = input(f"enter {var_name}: ")
            if check_variable_type(user_input, expected_type):
                variables[var_name] = expected_type(user_input)
                break
            else:
                print(f"error {expected_type.__name__}")

#------------------------------------------------------------------

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
    #x = int(input("\nenter x: "))
    #expected_type = int
    #test_x = input_variable(expected_type, "Enter x: ")

    variables = {
        'x': int,
    }
    # проверка переменных
    check_variables(variables)
    # проверка проверки
    print("Variables:", variables)

    # алгоритм - х1йня - подумать еще раз над проверкой

    if x < -5:
        print('(-infinity, -5)')
    elif -5 <= x <= 5:
        print('[-5, 5]')
    else:
        print('(5, +infinity)')

def task_3_3_1():
    x = int(input('enter x = '))         #написать функцию с параметрами - проверка на введеные данные

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
    import numpy as np
    import matplotlib.pyplot as plt
    import math

    # функция
    def my_function(x):
        return (math.sqrt(1 + math.exp(math.sqrt(x)) + math.cos(x**2)) /
                abs(1 - math.sin(x)**3)) + math.log(abs(2*x))

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
    #from scipy.integrate import simps
    from numpy import trapz

def task_4_3_4():
    print("  ")

def task_4_3_5():
    import math

    def add(x, y):
        return x + y
    
    def substruct(x, y):
        return x - y

    def multiply(x, y):
        return x * y

    def divide(x, y):
        if y == 0:
            return "error\n"
        else :
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

    choice = input("enter transaction number (1/ 2/ 3/ 4/ 5/ 6/ 7/ 8): ")
        #написать функцию с параметрами - проверка на введеные данные


    if choice in ('1', '2', '3', '4', '8'):
        num1 = float(input("enter first number: "))
                #написать функцию с параметрами - проверка на введеные данные

        num2 = float(input("enter second number: "))
        #написать функцию с параметрами - проверка на введеные данные

        if choice == '1':
            print("result:", add(num1, num2))
        elif choice == '2':
            print("result: ", subtract(num1, num2))
        elif choice == '3':
            print("result: ", multiply(num1, num2))
        elif choice == '4':
            print("result: ", divide(num1, num2))
        elif choice == '8':
            print("result: ", power(num1, num2))
    else:
        num = float(input("enter number "))
                #написать функцию с параметрами - проверка на введеные данные

        if choice == '5':
            print("result: ", exponential(num, num))
        elif choice == '6':
            print("result: ", sine(num, num))
        elif choice == '7':
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
        #написать функцию с параметрами - проверка на введеные данные

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
