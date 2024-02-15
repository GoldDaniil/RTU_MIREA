import numpy as np

def task_1_3_1():
    matrix = [[0] * 8 for _ in range (8)]
    for i in range(8):
        for j in range(8):
            if (i + j) % 2 == 0:
                matrix[i][j] = 1
    for row in matrix:
        print(row)

def task_1_3_2():

    matrix = np.arange(5) + np.arange(5)[:, np.newaxis]
    print(matrix)

def task_1_3_3():

    array = np.random.rand(3, 3, 3)
    print(array)

def task_1_3_4():

    rows, cols = 5, 5
    matrix = np.zeros((rows, cols))
    matrix[0, :] = 1
    matrix[-1, :] = 1
    matrix[:, 0] = 1
    matrix[:, -1] = 1

    print(matrix)

