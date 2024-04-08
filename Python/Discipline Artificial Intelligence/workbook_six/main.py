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

def task_1_1_1_one():
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

    newX = [-2, -1, 0, -1]
    newY = [-2, -1, 0, -1]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def task_1_1_2_one():
    def qZ(x, y):
        return (x - 2 * y - 3) / (x ** 2 + 3 * y ** 2 + 1)

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

    newX = [-4, -2, 0, 2]
    newY = [-1, 1, 0, -2]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def task_1_1_3_one():
    def qZ(x, y):
        return (x - 3 * y - 2) / (x ** 2 + y ** 2 + 1)

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

    newX = [-1, 0, 2, 3]
    newY = [-2, 1, 0, -1]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def task_1_1_4_one():
    def qZ(x, y):
        return (x + 3 * y) / (3 * x ** 2 + y ** 2 + 1)

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

    newX = [-1, 0, 2, 4]
    newY = [-2, 1, -1, 0]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def task_1_1_5_one():
    def qZ(x, y):
        return (x - 3 * y + 1) / (3 * x ** 2 + y ** 2 + 1)

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

    newX = [-2, -1, 0, 2]
    newY = [-2, 0, -1, 1]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def task_1_1_6_one():
    def qZ(x, y):
        return (x + 3 * y) / (x ** 2 + y ** 2 + 1)

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

    newX = [-5, -3, -2, -1]
    newY = [-1, -2, 0, 1]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def task_1_1_7_one():
    def qZ(x, y):
        return (x + 3 * y - 3) / (3 * x ** 2 + y ** 2 + 1)

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

    newX = [-5, -3, -2, 0]
    newY = [-1, -2, 0, 1]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def task_1_1_8_one():
    def qZ(x, y):
        return (x - 3 * y - 3) / (x ** 2 + 2 * y ** 2 + 1)

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

    newX = [-5, -3, -2, -1]
    newY = [-1, -2, 0, 1]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def task_1_1_9_one():
    def qZ(x, y):
        return (x - 2 * y) / (x ** 2 + y ** 2 + 1)

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

    newX = [-1, 0, 2, 3]
    newY = [0, -1, -2, 1]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def task_1_1_10_one():
    def qZ(x, y):
        return (x - 3 * y) / (2 * x ** 2 + 2 * y ** 2 + 1)

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

    newX = [-1, 0, 2, 3]
    newY = [0, 1, -2, 2]

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

def launcher_1_1_1():
    while True:
        choice = input("\nselect task option: \n1 = first option \n2 = second option \n3 = third option \n4 = fourth option \n5 = fifth option \n6 = sixth option \n7 = seventh option \n8 = eighth option  \n9 = ninth option \n10 = tenth option \n(no option - if you want to exit, enter 'exit'):")

        menu = {
            '1': task_1_1_1_one,
            '2': task_1_1_2_one,
            '3': task_1_1_3_one,
            '4': task_1_1_4_one,
            '5': task_1_1_5_one,
            '6': task_1_1_6_one,
            '7': task_1_1_7_one,
            '8': task_1_1_8_one,
            '9': task_1_1_9_one,
            '10': task_1_1_10_one,

            'exit': lambda: print("\n\nmain menu!")
        }

        if choice in menu:
            menu[choice]()
            if choice == 'exit':
                return
        else:
            print("invalid choice. please enter a valid option")

def main():
    while True:
        choice = input("\nselect a task to open: \n \n1 = task () \n2 = task ()\n3 = task () \n(no task - if you want to exit, enter 'exit'): ")

        menu = {
            '1': launcher_1_1_1,
            #'2': второй лаунчер,
            #'3': третий лаунчер(по надобности),
            'exit': lambda: print("oh, okay:(")
        }

        if choice in menu:
            menu[choice]()
            if choice == 'exit':
                return
        else:
            print("invalid choice. please enter a valid option")


if __name__ == "__main__":
    main()
