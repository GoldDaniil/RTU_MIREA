def qZ_1(x, y):
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
            arrZ = [qZ_func(x, Y[i]) for i, x in enumerate(X)]
            X, Y, Z = evoStep(X, Y, arrZ)
            X, Y = exchangeScheme(X, Y, sorting(Z))
            results.append([X, Y, qSumZ(arrZ), arrZ])
        return X, Y, results

    results = evoSteps(newX, newY)

    for i in range(len(results[2])):
        print(f'max_{i + 1}_step: {results[2][i][2]}')
    qualityArrZ = []
    for i in range(len(results[2])):
        qualityArrZ += results[2][i][3]
    print(f'max Z:{max(qualityArrZ)}')

# первый вариант
def task_1_1_1_one():


# второй вариант
def task_1_1_2_one():


# третий вариант
def task_1_1_3_one():


# четвертый вариант
def task_1_1_4_one():


# пятый вариант
def task_1_1_5_one():


# шестой вариант
def task_1_1_6_one():


# седьмой вариант
def task_1_1_7_one():


# восьмой вариант
def task_1_1_8_one():

# девятый вариант
def task_1_1_9_one():
    newX = [-1, 0, 2, 3]
    newY = [0, -1, -2, 1]
    common_task(qZ_1, newX, newY)

# десятый вариант
def task_1_1_10_one():
    newX = [-1, 0, 2, 3]
    newY = [0, 1, -2, 2]
    common_task(qZ_2, newX, newY)

# Вызываем нужные функции для каждой задачи

task_1_1_1_one()
task_1_1_2_one()
task_1_1_3_one()
task_1_1_4_one()
task_1_1_5_one()
task_1_1_6_one()
task_1_1_7_one()
task_1_1_8_one()
task_1_1_9_one()
task_1_1_10_one()
