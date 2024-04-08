import math
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def check_variable_int_float(variable):
    while True:
        try:
            variable = float(variable)
            return variable
        except ValueError:
            print("error/ required type - integer/float \n")
            variable = input("try entering again: ")

def check_variable_str(variable):
    while True:
        try:
            variable = str(variable)
            return variable
        except ValueError:
            print("error. required type - string \n")
            variable = input("try entering again: ")

# -----------------------------------------------------------------------

# def local_data_set:
#     def qZ(x, y):
#         return (x - 3 * y + 1) / (3 * x ** 2 + 3 * y ** 2 + 1)
#     def qSumZ(Z):
#         return sum(Z)
#
#     def exchangeScheme(oldX, oldY, sortedId):
#         X = [0 for i in range(4)]
#         Y = [0 for i in range(4)]
#
#         X[2] = oldX[sortedId[2]]
#         X[3] = oldX[sortedId[2]]
#
#         X[0] = oldX[sortedId[0]]
#
#         X[1] = oldX[sortedId[1]]
#
#         Y[0] = oldY[sortedId[2]]
#         Y[1] = oldY[sortedId[2]]
#
#         Y[2] = oldY[sortedId[0]]
#
#         Y[3] = oldY[sortedId[1]]
#
#         return X, Y
#
#     def sorting(Z):
#         sortedId = sorted(range(len(Z)), key =lambda k: Z[k])
#
#         return sortedId
#
#
#     def evoStep(X, Y, Z):
#         _, minId = min((value, id) for (id, value) in enumerate(Z))
#
#         X = X[:]
#         Y = Y[:]
#         Z = Z[:]
#         X.pop(minId)
#         Y.pop(minId)
#         Z.pop(minId)
#         return X, Y, Z
#
#     def evoSteps(X, Y, stepsNum=4):
#         results = []
#         for i in range(4):
#             arrZ = [qZ(x, Y[i]) for i, x in enumerate(X)]
#             X, Y, Z = evoStep(X, Y, arrZ)
#             X, Y = exchangeScheme(X, Y, sorting(Z))
#             results.append([X, Y, qSumZ(arrZ), arrZ])
#             return X, Y, results
#
#     # Теперь, когда мы подготовились к решению задачи, написав все
#     # необходимые функции для реализации генетического алгоритма (оценки
#     # качества хромосом, сортировки потомков и эволюционных шагов), решим
#     # задачу в числах. Пусть даны следующие массивы хромосом X и Y:
#
#     # объявление массивов хромосом
#     X = [-2, -1, 0, 1]
#     Y = [-2, -1, 0, 1]
#
#     # Реализация алгоритма
#     results = evoSteps(X, Y)
#
#     for i in range(len(results[2])):
#         print(f'max_{i + 1}_step: {results[2][i][2]}')
#     qualityArrZ = []
#     for i in range(len(results[2])): qualityArrZ += results[2][i][3]
#     print(f'max Z:{max(qualityArrZ)}')

# построить ~Деструктор &конструктор с динимаческим выделением памяти 
# отдельный класс : &_, 1:

def local_data_set():
    def qZ(x, y):
        return (x - 3 * y + 1) / (3 * x ** 2 + 3 * y ** 2 + 1)

    def qSumZ(Z):
        return sum(Z)

    def exchangeScheme(oldX, oldY, sortedId):
        X = [0 for i in range(4)]
        Y = [0 for i in range(4)]

        X[2] = oldX[sortedId[2]]
        X[3] = oldX[sortedId[2]]

        X[0] = oldX[sortedId[0]]

        X[1] = oldX[sortedId[1]]

        Y[0] = oldY[sortedId[2]]
        Y[1] = oldY[sortedId[2]]

        Y[2] = oldY[sortedId[0]]

        Y[3] = oldY[sortedId[1]]

        return X, Y

    def sorting(Z):
        sortedId = sorted(range(len(Z)), key=lambda k: Z[k])

        return sortedId

    def evoStep(X, Y, Z):
        _, minId = min((value, id) for (id, value) in enumerate(Z))

        X = X[:]
        Y = Y[:]
        Z = Z[:]
        X.pop(minId)
        Y.pop(minId)
        Z.pop(minId)
        return X, Y, Z

    def evoSteps(X, Y, stepsNum=4):
        results = []
        for i in range(4):
            arrZ = [qZ(x, Y[i]) for i, x in enumerate(X)]
            X, Y, Z = evoStep(X, Y, arrZ)
            X, Y = exchangeScheme(X, Y, sorting(Z))
            results.append([X, Y, qSumZ(arrZ), arrZ])
        return X, Y, results

    # Новые значения x, y
    newX = [-2, -1, 0, -1]
    newY = [-2, -1, 0, -1]

    # Реализация алгоритма с новыми значениями
    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def main():
    while True:
        choice = input("\nselect a task to open: \n \n1 = task () \n2 = task ()\n3 = task () \n(no task - if you want to exit, enter 'exit'): ")

        menu = {
            '1': local_data_set,
            #'2': task_1_2,
            #'3': task_1_3,
            'exit': lambda: print("oh, okay:(")
        }

        if choice in menu:
            menu[choice]()
            if choice == 'exit':
                break
        else:
            print("invalid choice. please enter a valid option")


if __name__ == "__main__":
    main()
