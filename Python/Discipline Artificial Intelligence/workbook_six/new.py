#готово
import networkx as nx
import matplotlib.pyplot as plt
from math import e

def qZ_1(x, y): # вычисление значения функции 𝑞𝑍1 для заданных значений x и y
    return (x - 3 * y + 1) / (3 * x ** 2 + 3 * y ** 2 + 1)

def qZ_2(x, y):
    return (x - 2 * y - 3) / (x ** 2 + 3 * y ** 2 + 1)

def qZ_3(x, y):
    return (x - 3 * y - 2) / (x ** 2 + y ** 2 + 1)

def qZ_4(x, y):
    return (x + 3 * y) / (3 * x ** 2 + y ** 2 + 1)

def qZ_5(x, y):
    return (x - 3 * y + 1) / (3 * x ** 2 + y ** 2 + 1)

def qZ_6(x, y):
    return (x + 3 * y) / (x ** 2 + y ** 2 + 1)

def qZ_7(x, y):
    return (x + 3 * y - 3) / (3 * x ** 2 + y ** 2 + 1)

def qZ_8(x, y):
    return (x - 3 * y - 3) / (x ** 2 + 2 * y ** 2 + 1)

def qZ_9(x, y):
    return (x - 2 * y) / (x ** 2 + y ** 2 + 1)

def qZ_10(x, y):
    return (x - 3 * y) / (2 * x ** 2 + 2 * y ** 2 + 1)

def common_task(qZ_func, newX, newY):
    def qSumZ(Z):
        return sum(Z) #возврат суммы всех элементов списка Z

    def exchangeScheme(oldX, oldY, sortedId): #список старых значений, индексов, отсортированных по убыванию
        X = [0 for i in range(4)]
        Y = [0 for i in range(4)] #создание новых списков

        X[2] = oldX[sortedId[2]]
        X[3] = oldX[sortedId[2]]

        X[0] = oldX[sortedId[0]]
        X[1] = oldX[sortedId[1]]

        Y[0] = oldY[sortedId[2]]
        Y[1] = oldY[sortedId[2]]

        Y[2] = oldY[sortedId[0]]

        Y[3] = oldY[sortedId[1]] #переупорядочивание значений переменных х и у на основе отсортированных индексов sortedId

        return X, Y

    def sorting(Z):
        sortedId = sorted(range(len(Z)), key=lambda k: Z[k])
        return sortedId

    def evoStep(X, Y, Z):
        _, minId = min((value, id) for (id, value) in enumerate(Z))

        X = X[:] # создание копии списков
        Y = Y[:]
        Z = Z[:]
        X.pop(minId)
        Y.pop(minId) # удаление элементов с минимальным значением функции
        Z.pop(minId)
        return X, Y, Z

    def evoSteps(X, Y, stepsNum=4): # вычисление значения Z для каждой комбинации значений x и y
        results = []
        for i in range(4):
            arrZ = [qZ_func(x, Y[i]) for i, x in enumerate(X)]

            X, Y, Z = evoStep(X, Y, arrZ)
            X, Y = exchangeScheme(X, Y, sorting(Z))
            results.append([X, Y, qSumZ(arrZ), arrZ]) # создание списка результатов
        return X, Y, results

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []    # отслеживание изменения функции qZ и нахождение ее максимального значения
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

# первый вариант
def task_1_1_1_one():
    newX = [-2, -1, 0, -1]
    newY = [-2, -1, 0, -1]
    common_task(qZ_1, newX, newY)

# второй вариант
def task_1_1_2_one():
    newX = [-4, -2, 0, 2]
    newY = [-1, 1, 0, -2]
    common_task(qZ_2, newX, newY)

# третий вариант
def task_1_1_3_one():
    newX = [-1, 0, 2, 3]
    newY = [-2, 1, 0, -1]
    common_task(qZ_3, newX, newY)

# четвертый вариант
def task_1_1_4_one():
    newX = [-1, 0, 2, 4]
    newY = [-2, 1, -1, 0]
    common_task(qZ_4, newX, newY)

# пятый вариант
def task_1_1_5_one():
    newX = [-2, -1, 0, 2]
    newY = [-2, 0, -1, 1]
    common_task(qZ_5, newX, newY)

# шестой вариант
def task_1_1_6_one():
    newX = [-5, -3, -2, -1]
    newY = [-1, -2, 0, 1]
    common_task(qZ_6, newX, newY)

# седьмой вариант
def task_1_1_7_one():
    newX = [-5, -3, -2, 0]
    newY = [-1, -2, 0, 1]
    common_task(qZ_7, newX, newY)

# восьмой вариант
def task_1_1_8_one():
    newX = [-5, -3, -2, -1]
    newY = [-1, -2, 0, 1]
    common_task(qZ_8, newX, newY)

# девятый вариант
def task_1_1_9_one():
    newX = [-1, 0, 2, 3]
    newY = [0, -1, -2, 1]
    common_task(qZ_9, newX, newY)

# десятый вариант
def task_1_1_10_one():
    newX = [-1, 0, 2, 3]
    newY = [0, 1, -2, 2]
    common_task(qZ_10, newX, newY)

# вызываем нужные функции для каждой задачи
def launcher_1_1_1():
    while True:
        choice = input(
            "\nselect task option: \n1 = first option \n2 = second option \n3 = third option \n4 = fourth option \n5 = fifth option \n6 = sixth option \n7 = seventh option \n8 = eighth option  \n9 = ninth option \n10 = tenth option \n(no option - if you want to exit, enter 'exit'):")

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

# -----------------------------------------------------------------------------------------------

def probability(delta, T):
    return 100 * e ** (-delta / T)

def reductTemp(prevT):
    nextT = 0.5 * prevT
    return nextT

def edgeLength(i, j, distances, roundTrip=True):
    if roundTrip:
        return max([(item[2] if (item[0] == i and item[1] == j) or (item[1] == i and item[0] == j) else -1)
                    for item in distances])
    else:
        return max([(item[2] if (item[0] == i and item[1] == j) else -1) for item in distances])

def routeLength(V, distances):
    edges = []
    for i in range(len(V) - 1):
        edges.append(edgeLength(V[i], V[i + 1], distances))
    return sum(edges)

def routeOneReplacement(arrV, Z, replacementByName=True):
    decrement = 1 if replacementByName else 0
    arrV[Z[0] - decrement], arrV[Z[1] - decrement] = arrV[Z[1] - decrement], arrV[Z[0] - decrement]
    return arrV

def routeReplacement(V, Z):
    for z in Z:
        V = routeOneReplacement(V, z)
    return V

def chooseRoute(distances, V, z, T, P):
    sumLength = routeLength(V, distances)
    arrSum = [sumLength]

    for i in range(len(z)):
        newV = routeOneReplacement(V[:], z[i])
        newS = routeLength(newV, distances)
        arrSum.append(newS)
        deltas = newS - sumLength

        if deltas > 0:
            p = probability(deltas, T)
            if p > P[i]:
                V = newV
                sumLength = newS
            else:
                V = newV
                sumLength = newS

            T = reductTemp(T)

    return V, arrSum

def drawRouteGraph(distances, bestRoute):
    newDistances = []
    for i in range(len(bestRoute) - 1):
        for distance in distances:
            if (distance[0] == bestRoute[i] and distance[1] == bestRoute[i + 1]) or (distance[1] == bestRoute[i] and distance[0] == bestRoute[i + 1]):
                newDistances.append(distance)

    graph = nx.Graph()
    graph.add_weighted_edges_from(newDistances)
    pos = nx.kamada_kawai_layout(graph)
    nx.draw(graph, pos, with_labels=True, node_color='#fb7258', node_size=2000)
    labels = nx.get_edge_attributes(graph, 'weight')
    nx.draw_networkx_edge_labels(graph, pos, edge_labels=labels)
    plt.show()

# первый вариант
def task_1_2_1_one():
    distances = [(1, 2, 26), (1, 3, 42), (1, 4, 44), (1, 5, 31), (1, 6, 24), (2, 3, 20), (2, 4, 34), (2, 5, 40),
                 (2, 6, 15), (3, 4, 23), (3, 5, 43), (3, 6, 20), (4, 5, 27), (4, 6, 22), (5, 6, 26)]

    V = [1, 2, 3, 4, 5, 6, 1]
    z = [(3, 4), (4, 6), (5, 6), (6, 2)]
    P = [90, 45, 43, 31]
    T = 100

    bestRoute, arrLength = chooseRoute(distances, V, z, T, P)

    print(f'лучший выбранный маршрут: {bestRoute}')
    print(f'длина лучшего выбранного маршрута: {routeLength(bestRoute, distances)}')
    print(f'длины всех рассмотренных маршрутов: {arrLength}')

    drawRouteGraph(distances, bestRoute)

# второй вариант
def task_1_2_2_one():
    distances = [(1, 2, 25), (1, 3, 41), (1, 4, 38), (1, 5, 27), (1, 6, 20), (2, 3, 21), (2, 4, 34), (2, 5, 39),
                 (2, 6, 17), (3, 4, 24), (3, 5, 40), (3, 6, 22), (4, 5, 21), (4, 6, 21), (5, 6, 22)]

    V = [1, 3, 5, 4, 6, 2, 1]
    z = [(3, 4), (4, 6), (5, 6), (2, 4)]
    P = [41, 60, 85, 60]
    T = 100

    bestRoute, arrLength = chooseRoute(distances, V, z, T, P)

    print(f'лучший выбранный маршрут: {bestRoute}')
    print(f'длина лучшего выбранного маршрута: {routeLength(bestRoute, distances)}')
    print(f'длины всех рассмотренных маршрутов: {arrLength}')

    drawRouteGraph(distances, bestRoute)

# третий вариант
def task_1_2_3_one():
    distances = [(1, 2, 23), (1, 3, 42), (1, 4, 40), (1, 5, 25), (1, 6, 22), (2, 3, 20), (2, 4, 30), (2, 5, 34),
                 (2, 6, 13), (3, 4, 22), (3, 5, 41), (3, 6, 21), (4, 5, 26), (4, 6, 19), (5, 6, 22)]
    V = [1, 3, 4, 5, 6, 2, 1]
    z = [(4, 5), (5, 6), (2, 4), (6, 2)]
    P = [78, 24, 63, 17]
    T = 100

    bestRoute, arrLength = chooseRoute(distances, V, z, T, P)

    print(f'лучший выбранный маршрут: {bestRoute}')
    print(f'длина лучшего выбранного маршрута: {routeLength(bestRoute, distances)}')
    print(f'длины всех рассмотренных маршрутов: {arrLength}')

    drawRouteGraph(distances, bestRoute)

# четвертый вариант
def task_1_2_4_one():
    distances = [(1, 2, 17), (1, 3, 39), (1, 4, 32), (1, 5, 28), (1, 6, 18), (2, 3, 24), (2, 4, 28), (2, 5, 35),
                 (2, 6, 13), (3, 4, 25), (3, 5, 43), (3, 6, 23), (4, 5, 20), (4, 6, 16), (5, 6, 24)]
    V = [1, 5, 2, 6, 3, 4, 1]
    z = [(3, 4), (4, 5), (5, 2), (6, 2)]
    P = [78, 79, 25, 82]
    T = 100

    bestRoute, arrLength = chooseRoute(distances, V, z, T, P)

    print(f'лучший выбранный маршрут: {bestRoute}')
    print(f'длина лучшего выбранного маршрута: {routeLength(bestRoute, distances)}')
    print(f'длины всех рассмотренных маршрутов: {arrLength}')

    drawRouteGraph(distances, bestRoute)

# пятый вариант
def task_1_2_5_one():
    distances = [(1, 2, 18), (1, 3, 41), (1, 4, 36), (1, 5, 29), (1, 6, 19), (2, 3, 27), (2, 4, 31), (2, 5, 37),
                 (2, 6, 15), (3, 4, 19), (3, 5, 42), (3, 6, 23), (4, 5, 24), (4, 6, 17), (5, 6, 24)]
    V = [1, 3, 4, 5, 6, 2, 1]
    z = [(2, 4), (3, 4), (4, 6), (5, 6)]
    P = [63, 49, 45, 53]
    T = 100

    bestRoute, arrLength = chooseRoute(distances, V, z, T, P)

    print(f'лучший выбранный маршрут: {bestRoute}')
    print(f'длина лучшего выбранного маршрута: {routeLength(bestRoute, distances)}')
    print(f'длины всех рассмотренных маршрутов: {arrLength}')

    drawRouteGraph(distances, bestRoute)

# шестой вариант
def task_1_2_6_one():
    distances = [(1, 2, 22), (1, 3, 43), (1, 4, 39), (1, 5, 28), (1, 6, 20), (2, 3, 26), (2, 4, 33), (2, 5, 36),
                 (2, 6, 17), (3, 4, 22), (3, 5, 40), (3, 6, 24), (4, 5, 22), (4, 6, 19), (5, 6, 20)]
    V = [1, 3, 4, 5, 6, 2, 1]
    z = [(2, 4), (4, 6), (3, 5), (5, 2)]
    P = [51, 23, 29, 31]
    T = 100

    bestRoute, arrLength = chooseRoute(distances, V, z, T, P)

    print(f'лучший выбранный маршрут: {bestRoute}')
    print(f'длина лучшего выбранного маршрута: {routeLength(bestRoute, distances)}')
    print(f'длины всех рассмотренных маршрутов: {arrLength}')

    drawRouteGraph(distances, bestRoute)

# седьмой вариант
def task_1_2_7_one():
    distances = [(1, 2, 24), (1, 3, 41), (1, 4, 36), (1, 5, 22), (1, 6, 19), (2, 3, 21), (2, 4, 33), (2, 5, 33),
                 (2, 6, 14), (3, 4, 27), (3, 5, 39), (3, 6, 23), (4, 5, 20), (4, 6, 20), (5, 6, 19)]
    V = [1, 3, 4, 5, 6, 2, 1]
    z = [(3, 4), (4, 6), (5, 2), (6, 2)]
    P = [33, 82, 51, 76]
    T = 100

    bestRoute, arrLength = chooseRoute(distances, V, z, T, P)

    print(f'лучший выбранный маршрут: {bestRoute}')
    print(f'длина лучшего выбранного маршрута: {routeLength(bestRoute, distances)}')
    print(f'длины всех рассмотренных маршрутов: {arrLength}')

    drawRouteGraph(distances, bestRoute)

# восьмой вариант
def task_1_2_8_one():
    distances = [(1, 2, 19), (1, 3, 39), (1, 4, 35), (1, 5, 26), (1, 6, 18), (2, 3, 26), (2, 4, 33), (2, 5, 37),
                 (2, 6, 14), (3, 4, 22), (3, 5, 41), (3, 6, 21), (4, 5, 22), (4, 6, 19), (5, 6, 24)]
    V = [1, 4, 2, 3, 5, 6, 1]
    z = [(5, 2), (4, 5), (2, 3), (3, 4)]
    P = [88, 54, 24, 64]
    T = 100

    bestRoute, arrLength = chooseRoute(distances, V, z, T, P)

    print(f'лучший выбранный маршрут: {bestRoute}')
    print(f'длина лучшего выбранного маршрута: {routeLength(bestRoute, distances)}')
    print(f'длины всех рассмотренных маршрутов: {arrLength}')

    drawRouteGraph(distances, bestRoute)

def launcher_1_2_1():
    while True:
        choice = input(
            "\nselect task option: \n1 = first option \n2 = second option \n3 = third option \n4 = fourth option \n5 = fifth option \n6 = sixth option \n7 = seventh option \n8 = eighth option \n(no option - if you want to exit, enter 'exit'):")

        menu = {
            '1': task_1_2_1_one,
            '2': task_1_2_2_one,
            '3': task_1_2_3_one,
            '4': task_1_2_4_one,
            '5': task_1_2_5_one,
            '6': task_1_2_6_one,
            '7': task_1_2_7_one,
            '8': task_1_2_8_one,
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
        choice = input(
            "\nselect a task to open: \n \n1 = task () \n2 = task () \n(no task - if you want to exit, enter 'exit'): ")

        menu = {
            '1': launcher_1_1_1,
            '2': launcher_1_2_1,
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
