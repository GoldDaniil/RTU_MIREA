import numpy as np
import matplotlib.pyplot as plt
import scipy as sp

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

def task_1_1_3():
    # Создаем фиктивные данные
    x = np.array([-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6])
    y = np.array([-53, -26, -9, 0, 1, 0, 9, 26, 53, 88, 129])

    # Построение экстраполяции полиномами первой, второй и третьей степени
    m = np.vstack((x ** 3, x ** 2, x, np.ones(11))).T
    s1 = np.linalg.lstsq(m[:, :2], y, rcond=None)[0]  # Полином первой степени
    s2 = np.linalg.lstsq(m[:, :3], y, rcond=None)[0]  # Полином второй степени

    # Новые точки для экстраполяции
    x_prec = np.linspace(-5, 7, 101)

    # Построение графика
    plt.plot(x, y, 'D', label='Исходные данные')
    plt.plot(x_prec, s1[0] * x_prec + s1[1], '-', lw=3, label='Полином 1-й степени')
    plt.plot(x_prec, s2[0] * x_prec ** 2 + s2[1] * x_prec + s2[2], '-', lw=3, label='Полином 2-й степени')
    plt.grid()
    plt.legend()
    plt.savefig('полиномы_1_и_2_степени.png')
    plt.show()

class TaskOneFive:
    @staticmethod
    def fun_one():
        # Определение своей функции
        def f(x, b0, b1):
            return b0 + b1 * x ** 2  # Пример квадратичной функции

        # Задание своих данных
        xdata = np.linspace(0, 5, 50)  # Создаем свои данные x
        b0, b1 = 1.5, 2.5  # Пример коэффициентов для функции
        y = f(xdata, b0, b1)  # Вычисляем значения функции без шума
        ydata = y + 0.2 * np.random.randn(len(xdata))  # Добавляем шум

        # Аппроксимация
        beta_opt, beta_cov = sp.optimize.curve_fit(f, xdata, ydata)

        # Вывод результатов
        print("Оптимальные коэффициенты:", beta_opt)
        lin_dev = sum(beta_cov[0])  # Линейное отклонение
        print("Линейное отклонение:", lin_dev)
        residuals = ydata - f(xdata, *beta_opt)  # Остатки
        fres = sum(residuals ** 2)  # Квадратичное отклонение
        print("Квадратичное отклонение:", fres)

        # Визуализация
        fig, ax = plt.subplots()
        ax.scatter(xdata, ydata)
        ax.plot(xdata, y, 'r--', lw=2, label='Исходная функция')
        ax.plot(xdata, f(xdata, *beta_opt), 'b', lw=2, label='Аппроксимация')
        ax.set_xlim(0, 5)
        ax.set_xlabel(r"$x$", fontsize=18)
        ax.set_ylabel(r"$f(x, \beta)$", fontsize=18)
        ax.legend()
        plt.show()
    @staticmethod
    def fun_two():
        def f(x, b0, b1, b2):
            return b0 + b1 * x + b2 * x ** 2  # Пример квадратичной функции

        # Задание своих данных
        xdata = np.linspace(0, 5, 50)  # Создаем свои данные x
        beta = (0.25, 0.75, 0.5)  # Пример коэффициентов для функции
        y = f(xdata, *beta)  # Вычисляем значения функции без шума
        ydata = y + 0.05 * np.random.randn(len(xdata))  # Добавляем шум

        # Аппроксимация
        beta_opt, beta_cov = sp.optimize.curve_fit(f, xdata, ydata)

        # Вывод результатов
        print("Оптимальные коэффициенты:", beta_opt)
        lin_dev = sum(beta_cov[0])  # Линейное отклонение
        print("Линейное отклонение:", lin_dev)
        residuals = ydata - f(xdata, *beta_opt)  # Остатки
        fres = sum(residuals ** 2)  # Квадратичное отклонение
        print("Квадратичное отклонение:", fres)

        # Визуализация
        fig, ax = plt.subplots()
        ax.scatter(xdata, ydata)
        ax.plot(xdata, y, 'r', lw=2, label='Исходная функция')
        ax.plot(xdata, f(xdata, *beta_opt), 'b', lw=2, label='Аппроксимация')
        ax.set_xlim(0, 5)
        ax.set_xlabel(r"$x$", fontsize=18)
        ax.set_ylabel(r"$f(x, \beta)$", fontsize=18)
        ax.legend()
        plt.show()
    @staticmethod
    def fun_three():
        def f(x, b0, b1):
            return b0 + b1 * np.log(x)  # Функция с логарифмом

        # Задание своих данных
        xdata = np.linspace(1, 5, 50)  # Создаем свои данные x
        beta = (1, 2)  # Пример коэффициентов для функции
        y = f(xdata, *beta)  # Вычисляем значения функции без шума
        ydata = y + 0.05 * np.random.randn(len(xdata))  # Добавляем шум

        # Аппроксимация
        beta_opt, beta_cov = sp.optimize.curve_fit(f, xdata, ydata)

        # Вывод результатов
        print("Оптимальные коэффициенты:", beta_opt)
        lin_dev = sum(beta_cov[0])  # Линейное отклонение
        print("Линейное отклонение:", lin_dev)
        residuals = ydata - f(xdata, *beta_opt)  # Остатки
        fres = sum(residuals ** 2)  # Квадратичное отклонение
        print("Квадратичное отклонение:", fres)

        # Визуализация
        fig, ax = plt.subplots()
        ax.scatter(xdata, ydata)
        ax.plot(xdata, y, 'r', lw=2, label='Исходная функция')
        ax.plot(xdata, f(xdata, *beta_opt), 'b', lw=2, label='Аппроксимация')
        ax.set_xlim(0, 5)
        ax.set_xlabel(r"$x$", fontsize=18)
        ax.set_ylabel(r"$f(x, \beta)$", fontsize=18)
        ax.legend()
        plt.show()
    @staticmethod
    def fun_four():
        def f(x, b0, b1):
            return b0 * x ** b1  # Пример степенной функции

        # Задание своих данных
        xdata = np.linspace(1, 5, 50)  # Создаем свои данные x
        beta = (1, 2)  # Пример коэффициентов для функции
        y = f(xdata, *beta)  # Вычисляем значения функции без шума
        ydata = y + 0.05 * np.random.randn(len(xdata))  # Добавляем шум

        # Аппроксимация
        beta_opt, beta_cov = sp.optimize.curve_fit(f, xdata, ydata)

        # Вывод результатов
        print("Оптимальные коэффициенты:", beta_opt)
        lin_dev = sum(beta_cov[0])  # Линейное отклонение
        print("Линейное отклонение:", lin_dev)
        residuals = ydata - f(xdata, *beta_opt)  # Остатки
        fres = sum(residuals ** 2)  # Квадратичное отклонение
        print("Квадратичное отклонение:", fres)

        # Визуализация
        fig, ax = plt.subplots()
        ax.scatter(xdata, ydata)
        ax.plot(xdata, y, 'r', lw=2, label='Исходная функция')
        ax.plot(xdata, f(xdata, *beta_opt), 'b', lw=2, label='Аппроксимация')
        ax.set_xlim(0, 5)
        ax.set_xlabel(r"$x$", fontsize=18)
        ax.set_ylabel(r"$f(x, \beta)$", fontsize=18)
        ax.legend()
        plt.show()

def main() :
    while True:
        print("\nselect a task to open:")
        print("1 = task 1.1.3")
        print("2 = task 1.1.5")
        print("3 = task 1.2.1")
        print("4 = task 1.3.2")
        print("5 = task 1.3.3")
        print("no task - if you want to exit, enter 'exit'\n\n")

        choice = input("enter your choice: ")

        if choice == '1':
            task_1_1_3()
        elif choice == '2':
            TaskOneFive.fun_one()
            TaskOneFive.fun_two()
            TaskOneFive.fun_three()
            TaskOneFive.fun_four()

        #elif choice == '3':
        #    task_1_2_1()
        #elif choice == '4':
        #    task_1_3_2()
        #elif choice == '5':
        #    task_1_3_3()
        elif choice == 'exit':
            print("oh, okay:(")
            break
        else:
            print("invalid choice. please enter a valid option")

    if __name__ == "__main__":
        main()
