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

def task_1_1_5():


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
            task_1_1_5()
        elif choice == '3':
            task_1_2_1()
        elif choice == '4':
            task_1_3_2()
        elif choice == '5':
            task_1_3_3()
        elif choice == 'exit':
            print("oh, okay:(")
            break
        else:
            print("invalid choice. please enter a valid option")

    if __name__ == "__main__":
        main()
