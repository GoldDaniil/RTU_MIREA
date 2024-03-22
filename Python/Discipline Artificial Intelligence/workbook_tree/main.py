import matplotlib.pyplot as plt
import numpy as np
from numpy import *
from mpl_toolkits.mplot3d import Axes3D

def check_variable_int_float(variable):
    while True:
        try:
            variable = float(variable)
            return variable
        except ValueError:
            print("error/ required type - integer/float \n")
            variable = input("try entering again: ")

def task_1_3_1():
    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")

    ax.scatter(1, 1, 1)
    ax.scatter(2, 2, 2)
    ax.scatter(4, 3, 5)
    ax.scatter(3, 2, 1)

    x = np.array([1, 1, 1])
    y = np.array([2, 2, 2])
    c = np.array([4, 3, 5])
    v = np.array([3, 2, 1])

    print(np.linalg.norm(x-y))
    print(np.linalg.norm(y-c) ** 2)
    print(np.linalg.norm(c - v, ord=np.inf))
    print(np.linalg.norm(v - x, ord=1))
    plt.show()

def task_1_3_2():
    x = array([arange(5)] * 5)
    print(x)

def task_2_3_1():


def task_3_3_2():



def main():
    while True:
        print("\nselect a task to open:")
        print("1 = task 1.3.1")
        print("2 = task 1.3.2")
        print("3 = task 2.3.1")
        print("4 = task 3.3.2")
        print("no task - if you want to exit, enter 'exit'\n\n")

        choice = input("enter your choice: ")

        if choice == '1':
            task_1_3_1()
        elif choice == '2':
            task_1_3_2()
        elif choice == '3':
            task_2_3_1()
        elif choice == '4':
            task_3_3_2()
        elif choice == 'exit':
            print("oh, okay:(")
            break
        else:
            print("invalid choice. please enter a valid option")

if __name__ == "__main__":
    main()
  
