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
    angle_degrees = 45
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
            root = str(tree[0])
            graph.node(root, label=root, shape='oval')
            if len(tree[1]) > 0:
                left_child = str(tree[1][0])
                graph.node(left_child, label=left_child, shape='oval') #метка узла - идентификатор 
                graph.edge(root, left_child)
                create_tree_graph(tree[1], graph)
            if len(tree[2]) > 0:
                right_child = str(tree[2][0])
                graph.node(right_child, label=right_child, shape='oval')
                graph.edge(root, right_child)
                create_tree_graph(tree[2], graph)
        return graph

    tree_graph = create_tree_graph(tree)

    tree_graph.render('tree')
    tree_graph.view()

# def task_1_2():
#     T = [["d", "e"], ["f"]]
#     print(T)
#     print(T[0])
#     print(T[1])

def task_1_3():
    class Tree:
        def __init__(self, data):
            self.left = None
            self.right = None
            self.data = data

        def insert(self, data):
            if data < self.data:
                if self.left is None:
                    self.left = Tree(data)
                else:
                    self.left.insert(data)
            elif data > self.data:
                if self.right is None:
                    self.right = Tree(data)
                else:
                    self.right.insert(data)

        def print_tree(self, dot, parent_node=None):
            dot.node(str(self.data))
            if parent_node is not None:
                dot.edge(str(parent_node.data), str(self.data))
            if self.left:
                self.left.print_tree(dot, self)
            if self.right:
                self.right.print_tree(dot, self)

    root = Tree(5)

    root.insert(3)
    root.insert(7)
    root.insert(2)
    root.insert(4)
    root.insert(6)
    root.insert(8)

    dot = Digraph()

    root.print_tree(dot)

    dot.render('binary_tree_corrected', format='png', view=True)


def task_1_3_1():
    X = np.array([[-1, -1], [-2, -1], [-3, -2], [1, 1], [2, 1], [3, 2]])
    target = [0, 0, 0, 1, 1, 1]

    clf = DecisionTreeClassifier()
    clf.fit(X, target)

    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.01),
                         np.arange(y_min, y_max, 0.01))

    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)

    plt.contourf(xx, yy, Z, alpha=0.8)
    plt.scatter(X[:, 0], X[:, 1], c=target, cmap=plt.cm.coolwarm)
    plt.xlabel('Feature 1')
    plt.ylabel('Feature 2')
    plt.title('Decision Tree Classifier')
    plt.show()

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
