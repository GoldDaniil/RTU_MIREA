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

# 2 номер доработать = проверить 5 номер

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
    # Определение структуры дерева в виде списка из списков
    tree = ['A', ['B', ['D', [], []], ['E', [], []]], ['C', ['F', [], []], []]]

    # Функция для создания графа из списка списков
    def create_tree_graph(tree, graph=None):
        if graph is None:
            graph = Digraph(format='png')
        if len(tree) > 0:
            root = str(tree[0])
            graph.node(root, label=root, shape='oval')
            if len(tree[1]) > 0:
                left_child = str(tree[1][0])
                graph.node(left_child, label=left_child, shape='oval')
                graph.edge(root, left_child)
                create_tree_graph(tree[1], graph)
            if len(tree[2]) > 0:
                right_child = str(tree[2][0])
                graph.node(right_child, label=right_child, shape='oval')
                graph.edge(root, right_child)
                create_tree_graph(tree[2], graph)
        return graph

    # Создание графа дерева
    tree_graph = create_tree_graph(tree)

    # Вывод графа на экран
    tree_graph.render('tree')
    tree_graph.view()

def task_1_3():
    class Tree:
        def __init__(self, data):
            self.left = None
            self.right = None
            self.data = data

        def insert(self, value):
            """Метод для вставки нового элемента в бинарное дерево поиска."""
            if value < self.data:
                if self.left is None:
                    self.left = Tree(value)
                else:
                    self.left.insert(value)
            elif value > self.data:
                if self.right is None:
                    self.right = Tree(value)
                else:
                    self.right.insert(value)

        def print_tree(self, x=0, y=0, x_parent=None, y_parent=None):
            """Метод для визуализации дерева."""
            if self.left:
                plt.plot([x, x_parent], [y - 1, y], 'k-')
                self.left.print_tree(x - 2, y - 1, x, y)
            if self.right:
                plt.plot([x, x_parent], [y - 1, y], 'k-')
                self.right.print_tree(x + 2, y - 1, x, y)
            plt.text(x, y, str(self.data), fontsize=12, ha='center', va='center',
                     bbox=dict(facecolor='white', edgecolor='black', boxstyle='circle'))

    # Пример использования класса Tree
    if __name__ == "__main__":
        # Создаем корень дерева
        root = Tree(10)

        # Вставляем новые элементы
        root.insert(5)
        root.insert(15)
        root.insert(3)
        root.insert(8)
        root.insert(12)
        root.insert(20)

        # Выводим дерево
        plt.figure(figsize=(8, 8))
        root.print_tree()
        plt.xlim(-10, 10)
        plt.ylim(-10, 0)
        plt.gca().invert_yaxis()
        plt.axis('off')
        plt.show()

def task_1_3_1():
    X = np.array([[-1, -1], [-2, -1], [-3, -2], [1, 1], [2, 1], [3, 2]])
    target = [0, 0, 0, 1, 1, 1]

    # Создание и обучение модели дерева принятия решений
    clf = DecisionTreeClassifier()
    clf.fit(X, target)

    # Визуализация решающей поверхности
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

    # URL для загрузки данных
    url = "https://raw.githubusercontent.com/likarajo/petrol_consumption/master/data/petrol_consumption.csv"

    # Загрузка данных
    data = pd.read_csv(url)

    # Подготовка данных
    X = data.drop('Petrol_Consumption', axis=1)
    y = data['Petrol_Consumption']

    # Разделение данных на обучающий и тестовый наборы
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    # Создание и обучение модели регрессии
    model = LinearRegression()
    model.fit(X_train, y_train)

    # Прогнозирование на тестовом наборе
    y_pred = model.predict(X_test)

    # Оценка точности модели
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
