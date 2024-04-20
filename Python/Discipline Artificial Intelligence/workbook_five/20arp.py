#готово
import math
from graphviz import Digraph
import matplotlib.pyplot as plt
import numpy as np
from sklearn.tree import DecisionTreeClassifier
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
import ssl
import urllib.request
import requests
from io import StringIO

def check_variable_int_float(variable):
    while True:
        try:
            variable = float(variable)
            if variable < 0:
                raise ValueError("error!\n")
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
def task_1_1():
    class Trigonometry:
        @staticmethod
        def cosine(angle):
            return math.cos(angle)

        @staticmethod
        def sine(angle):
            return math.sin(angle)

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
    angle_degrees = check_variable_int_float(input("Enter angle in degrees: "))
    angle_radians = Trigonometry.degress_to_radians(angle_degrees)

    print("Cosine: ", Trigonometry.cosine(angle_radians))
    print("Sine: ", Trigonometry.sine(angle_radians))
    print("Tangent: ", Trigonometry.tangent(angle_radians))
    print("Arcsine: ", Trigonometry.arcsine(0.7071067811865476))
    print("Arccosine: ", Trigonometry.arccosine(0.7071067811865476))
    print("Arctangent: ", Trigonometry.arctangent(1))

def task_1_2():
    tree = ['A', ['B', ['D', [], []], ['E', [], []]], ['C', ['F', [], []], []]]

    def create_tree_graph(tree, graph=None):
        if graph is None:
            graph = Digraph(format='png')
        if len(tree) > 0:
            root = str(tree[0]) #узел
            graph.node(root, label=root, shape='oval')
            if len(tree[1]) > 0:
                left_child = str(tree[1][0])
                graph.node(left_child, label=left_child, shape='oval') #метка узла - идентификатор 
                graph.edge(root, left_child) #нач уз - конечный
                create_tree_graph(tree[1], graph)
            if len(tree[2]) > 0:
                right_child = str(tree[2][0])
                graph.node(right_child, label=right_child, shape='oval')
                graph.edge(root, right_child)
                create_tree_graph(tree[2], graph)
        return graph

    tree_graph = create_tree_graph(tree) #результат вызова функции

    tree_graph.render('tree')
    tree_graph.view()

def task_1_3():
    class Tree:
        def __init__(self, data):#конструктор
            self.left = None
            self.right = None #поддерево
            self.data = data 

        def insert(self, data):
            if data < self.data:
                if self.left is None:
                    self.left = Tree(data) #создание нового объекта (data)
                else:
                    self.left.insert(data) #вставка в левое поддерево текущего узла
            elif data > self.data:
                if self.right is None:
                    self.right = Tree(data)
                else:
                    self.right.insert(data)

        def print_tree(self, dot, parent_node=None):
            dot.node(str(self.data)) #создание узла с меткой равной значению текущего узла
            if parent_node is not None: #существует ли родительский узел
                dot.edge(str(parent_node.data), str(self.data)) #создание ребра
            if self.left:
                self.left.print_tree(dot, self)
            if self.right:
                self.right.print_tree(dot, self)

    root = Tree(5) # корневой узел = 5

    root.insert(1) # добавление новых узлов со значениями
    root.insert(10)
    root.insert(2)
    root.insert(4)
    root.insert(60)
    root.insert(8)

    dot = Digraph() # создание объекта 

    root.print_tree(dot) # печать

    dot.render('binary_tree_corrected', format='png', view=True) # открытие для просмотра

# def task_1_3_1():
#     X = np.array([[-1, -1], [-2, -1], [-3, -2], [1, 1], [2, 1], [3, 2]]) # создание набора данных Х
#     target = [0, 0, 0, 1, 1, 1] # и метки клссов target
#
#     clf = DecisionTreeClassifier() # создание объекта классификатора
#     clf.fit(X, target)  # обучение на наборе данных Х с метками target
#
#     manCheck = [] # создаем пустой список для хранения введеных пользователем щнач
#
#     for i in range(2):
#         value = input(f"Введите значение {i + 1}: ")  # Запрашиваем ввод числа,  что пользователь будет вводить числа с плавающей точкой
#         manCheck.append(value)  # добавление введеного знач в список manCheck
#         value = check_variable_int_float(value)
#         manCheck.append(value)
#
#     manCheck = np.array(manCheck).reshape(1, -1)  # преобразование списка в массив numpy
#     prediction = clf.predict(manCheck)  # пркдскаываем класс для введеных пользователем значений
#
#     if prediction == 0:
#         print("класс 0")
#     else:
#         print("класс 1")
#
#     x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1  #
#     y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1  #
#     xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.01), #
#                          np.arange(y_min, y_max, 0.01)) #
#
#     Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
#     Z = Z.reshape(xx.shape)
#     plt.contourf(xx, yy, Z, alpha=0.8)
#     plt.scatter(X[:, 0], X[:, 1], c=target, cmap=plt.cm.coolwarm)
#     plt.xlabel('Feature 1')
#     plt.ylabel('Feature 2')
#     plt.title('Decision Tree Classifier')
#     plt.show()

def task_1_3_1():
    X = np.array([[-1, -1], [-2, -1], [-3, -2], [1, 1], [2, 1], [3, 2]])  # создание набора данных Х
    target = [0, 0, 0, 1, 1, 1]  # и метки клссов target

    clf = DecisionTreeClassifier()  # создание объекта классификатора
    clf.fit(X, target)  # обучение на наборе данных Х с метками target

    manCheck = [] # создаем пустой список для хранения введеных пользователем щнач

    # Запрашиваем у пользователя ввод двух значений
    for i in range(2):
        while True:
            value = input(f"Введите значение {i+1}: ")
            try:
                value = float(value)
                if value < 0:
                    raise ValueError("error")
                manCheck.append(value)
                break
            except ValueError:
                print("error.")

    manCheck = np.array(manCheck).reshape(1, -1)
    prediction = clf.predict(manCheck)

    if prediction == 0:
        print("класс 0")
    else:
        print("класс 1")

    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1  #
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1  #
    xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.01),  #
                         np.arange(y_min, y_max, 0.01))  #

    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)

    plt.contourf(xx, yy, Z, alpha=0.8)
    plt.scatter(X[:, 0], X[:, 1], c=target, cmap=plt.cm.coolwarm)
    plt.xlabel('Feature 1')
    plt.ylabel('Feature 2')
    plt.title('Decision Tree Classifier')
    plt.show()

    num_points = Z.size
    print(f"Количество точек, используемых для построения графика: {num_points}")

def task_1_4_1():
    ssl._create_default_https_context = ssl._create_unverified_context

    url = "https://raw.githubusercontent.com/likarajo/petrol_consumption/master/data/petrol_consumption.csv"

    data = pd.read_csv(url)

    X = data.drop('Petrol_Consumption', axis=1)
    y = data['Petrol_Consumption']

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    model = LinearRegression()
    model.fit(X_train, y_train)

    y_pred = model.predict(X_test)

    mse = mean_squared_error(y_test, y_pred)
    r2 = r2_score(y_test, y_pred)
    print(f'Среднеквадратичная ошибка (MSE): {mse:.2f}')
    print(f'Коэффициент детерминации (R^2): {r2:.2f}')

    plt.scatter(y_test, y_pred)
    plt.xlabel("реал знач")
    plt.ylabel("предсказ знач")
    plt.title("график реал vs предссказс знач")
    plt.show()
# def task_1_4_1():
#     ssl._create_default_https_context = ssl._create_unverified_context
#
#     url = "https://raw.githubusercontent.com/likarajo/petrol_consumption/master/data/petrol_consumption.csv"
#
#     data = pd.read_csv(url)
#
#     X = data.drop('Petrol_Consumption', axis=1)
#     y = data['Petrol_Consumption']
#
#     X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
#
#     model = LinearRegression()
#     model.fit(X_train, y_train)
#
#     y_pred = model.predict(X_test)
#
#     mse = mean_squared_error(y_test, y_pred)
#     r2 = r2_score(y_test, y_pred)
#     print(f'Среднеквадратичная ошибка (MSE): {mse:.2f}')
#     print(f'Коэффициент детерминации (R^2): {r2:.2f}')

def main():
    while True:
        choice = input("\nselect a task to open: \n \n1 = task 1.1() \n2 = task 1.2()\n3 = task 1.3()\n4 = task 1.3.1()\n5 = task 1.4.1() \n(no task - if you want to exit, enter 'exit'): ")

        menu = {
            '1': task_1_1,
            '2': task_1_2,
            '3': task_1_3,
            '4': task_1_3_1,
            '5': task_1_4_1,
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
