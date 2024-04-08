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
def main():
    while True:
        choice = input("\nselect a task to open: \n \n1 = task () \n2 = task ()\n3 = task () \n(no task - if you want to exit, enter 'exit'): ")

        menu = {
            #'1': task_1_1,
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
