import math 
import math as np

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

#-----------------------------------------------------------------------

def task_1_1():
    class Trigonometry:
        @staticmethod
        def cosine(angle):
            return math.cos(angle)
        
        @staticmethod
        def sine(angle):
            return math.sine(angle)
        
        @staticmethod
        def tangent(angle):
            return math.tan(angle)
        
        @staticmethod
        def arcsine(value):
            return math.asin(value)
        
        @staticmethod
        def arccosine(value):
            return math.acos(value)
        
        @staticmethod
        def arctangent(value):
            return math.atan(value)
        
        @staticmethod
        def degress_to_radians(degress):
            return math.radians(degress)

    # пример
    angle_degrees = 45
    angle_radians = Trigonometry.degress_to_radians(angle_degrees)

    print("Cosine: ", Trigonometry.cosine(angle_radians))
    print("Sine: ", Trigonometry.sine(angle_radians))
    print("Tangent: ", Trigonometry.tangent(angle_radians))
    print("Arcsine: ", Trigonometry.arcsine(0.7071067811865476))
    print("Arccosine: ", Trigonometry.arccosine(7071067811865476))
    print("Arctangent: ", Trigonometry.arctangent(1))


def main():
    while True:
        print("\nselect a task to open:")
        print("1 = task 1.1\n2 = task 1.2   ")

        choice = input("enter your choice: ")

        if choice == '1':
                task_1_1()
        if choice == '2':
                task_1_2()
        if choice == 'exit':
            print("oh, okay:(")
            break
        else:
            print("invalid choice. please enter a valid option")


if __name__ == "__main__":
    main()
