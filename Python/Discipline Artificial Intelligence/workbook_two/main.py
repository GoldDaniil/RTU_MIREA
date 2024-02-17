import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler, StandardScaler

def check_variable_int_float(variable):
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

def task_1_3_5():
    arr = np.array([3, 1, 5, 2, 4])

    arr_sorted = np.sort(arr)[::-1]

    print("исходный массив:", arr)
    print("массив - отсортированный по убыванию:", arr_sorted)

def task_1_3_6():
    matrix = np.array([[1, 2, 3],
                   [4, 5, 6],
                   [7, 8, 9]])

    print("форма матрицы:", matrix.shape)
    print("pазмер матрицы:", matrix.size)
    print("pазмерность матрицы:", matrix.ndim)


def task_3_3_2():
    url = "https://raw.githubusercontent.com/akmand/datasets/master/iris.csv"
    iris_df = pd.read_csv(url)

    print("первые несколько строк данных:")
    print(iris_df.head())

    min_max_scaler = MinMaxScaler()
    iris_df['sepal_length_cm_normalized'] = min_max_scaler.fit_transform(iris_df[['sepal_length_cm']])

    standard_scaler = StandardScaler()
    iris_df['sepal_width_cm_scaled'] = standard_scaler.fit_transform(iris_df[['sepal_width_cm']])

    print("\nнормализованные данные:")
    print(iris_df[['sepal_length_cm_normalized', 'sepal_width_cm_scaled']].head())


def main():
    while True:
        print("\nselect a task to open:")
        print("1 = task 1.3.1")
        print("2 = task 1.3.2")
        print("3 = task 1.3.3")
        print("4 = task 1.3.4")
        print("5 = task 1.3.5")
        print("6 = task 1.3.6")
        print("7 = task 2.3.1")
        print("8 = task 2.3.2")
        print("9 = task 2.3.3")
        print("10 = task 3.3.2")
        print("no task - if you want to exit, enter 'exit'\n\n")

        choice = input("enter your choice: ")

        if choice == '1':
            task_1_3_1()
        elif choice == '2':
            task_1_3_2()
        elif choice == '3':
            task_1_3_3()
        elif choice == '4':
            task_1_3_4()
        elif choice == '5':
            task_1_3_5()
        elif choice == '6':
            task_1_3_6()

        elif choice == '7':
            task_2_3_1()
        elif choice == '8':
            task_2_3_2()
        elif choice == '9':
            task_2_3_3()
        elif choice == '10':
            task_3_3_2()
        elif choice == 'exit':
            print("oh, okay:(")
            break
        else:
            print("invalid choice. please enter a valid option")

if __name__ == "__main__":
    main()
    
