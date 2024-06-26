import numpy as np # доработать 1 номер
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPRegressor, MLPClassifier
from sklearn.metrics import mean_squared_error, r2_score, accuracy_score
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import requests
from io import StringIO
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.preprocessing import LabelEncoder, StandardScaler

class Neuron:
    def __init__(self, weights, bias):
        self.weights = weights
        self.bias = bias

    def feedforward(self, inputs):
        total = np.dot(self.weights, inputs) + self.bias
        return self.sigmoid(total)

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

class NeuralNetwork1:
    def __init__(self):
        weights = np.array([0.5, 0.5, 0.5])
        bias = 0
        self.h1 = Neuron(weights, bias)
        self.h2 = Neuron(weights, bias)
        self.o1 = Neuron(weights, bias)

    def feedforward(self, x):
        x = np.concatenate([x, [1]])
        out_h1 = self.h1.feedforward(x)
        out_h2 = self.h2.feedforward(x)
        out_o1 = self.o1.feedforward(np.array([out_h1, out_h2]))
        return out_o1

class NeuralNetwork2:
    def __init__(self):
        weights = np.array([1, 0])
        bias = 1
        self.h1 = Neuron(weights, bias)
        self.h2 = Neuron(weights, bias)
        self.o1 = Neuron(weights, bias)
        self.o2 = Neuron(weights, bias)

    def feedforward(self, x):
        x = np.concatenate([x, [1]])
        out_h1 = self.h1.feedforward(x)
        out_h2 = self.h2.feedforward(x)
        out_o1 = self.o1.feedforward(np.array([out_h1, out_h2]))
        out_o2 = self.o2.feedforward(np.array([out_h1, out_h2]))
        return out_o1, out_o2

def task_1_1():
    network1 = NeuralNetwork1()
    x = np.array([2, 3])
    print(network1.feedforward(x))  # ч

    network2 = NeuralNetwork2()
    x = np.array([2, 3])
    print(network2.feedforward(x))  # ч


class ActivationFunctions:
    @staticmethod
    def sigmoid(x):
        return 1 / (1 + np.exp(-x))

    @staticmethod
    def tanh(x):
        return np.tanh(x)

    @staticmethod
    def relu(x):
        return np.maximum(0, x)

class NeuralNetwork:
    # слои нейронной сети, self - параметр; конструктор; тип функции активации
    def __init__(self, input_size, hidden_size, output_size, activation_function):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size
        self.activation_function = activation_function

        self.weights_input_hidden = np.random.rand(input_size, hidden_size)
        self.weights_hidden_output = np.random.rand(hidden_size, output_size)
        self.bias = np.zeros((1, hidden_size))

    def feedforward(self, x):
        hidden_layer_input = np.dot(x, self.weights_input_hidden) + self.bias

        if self.activation_function == 'sigmoid':
            hidden_layer_output = ActivationFunctions.sigmoid(hidden_layer_input)
        elif self.activation_function == 'tanh':
            hidden_layer_output = ActivationFunctions.tanh(hidden_layer_input)
        elif self.activation_function == 'relu':
            hidden_layer_output = ActivationFunctions.relu(hidden_layer_input)
        else:
            raise ValueError("error")

        output = np.dot(hidden_layer_output, self.weights_hidden_output)

        return output

def task_1_2():
    nn_sigmoid = NeuralNetwork(input_size=2, hidden_size=2, output_size=2, activation_function='sigmoid')

    nn_tanh = NeuralNetwork(input_size=2, hidden_size=2, output_size=2, activation_function='tanh')

    nn_relu = NeuralNetwork(input_size=2, hidden_size=2, output_size=2, activation_function='relu')

    x = np.array([[0.5, 0.7]])

    output_sigmoid = nn_sigmoid.feedforward(x)
    output_tanh = nn_tanh.feedforward(x)
    output_relu = nn_relu.feedforward(x)

    print("output using sigmoid activation function:", output_sigmoid)
    print("output using tanh activation function:", output_tanh)
    print("output using ReLU activation function:", output_relu)

def task_1_3():
    url = "https://gist.githubusercontent.com/netj/8836201/raw/6f9306ad21398ea43cba4f7d537619d0e07d5ae3/iris.csv"
    response = requests.get(url)
    data = pd.read_csv(StringIO(response.text))

    X = data.iloc[:, :-1].values
    y = data.iloc[:, -1].values

    le = LabelEncoder()
    y = le.fit_transform(y)

    scaler = StandardScaler()
    X = scaler.fit_transform(X)

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    classifier = MLPClassifier(hidden_layer_sizes=(100,), activation='relu', solver='adam', max_iter=1000,
                               random_state=42)
    classifier.fit(X_train, y_train)

    y_pred = classifier.predict(X_test)

    print("Confusion Matrix:")
    print(confusion_matrix(y_test, y_pred))
    print("\nClassification Report:")
    print(classification_report(y_test, y_pred))

def task_1_4():
    url = "https://raw.githubusercontent.com/AnnaShestova/salary-years-simple-linear-regression/master/Salary_Data.csv"
    response = requests.get(url)
    data = pd.read_csv(StringIO(response.text))
    X_reg = data.iloc[:, :-1].values
    y_reg = data.iloc[:, 1].values

    X_train_reg, X_test_reg, y_train_reg, y_test_reg = train_test_split(X_reg, y_reg, test_size=0.2, random_state=42)

    regressor = MLPRegressor(hidden_layer_sizes=(100,), activation='relu', solver='adam', max_iter=1000,
                             random_state=42)
    regressor.fit(X_train_reg, y_train_reg)

    y_pred_reg = regressor.predict(X_test_reg)

    mse_reg = mean_squared_error(y_test_reg, y_pred_reg)
    r2_reg = r2_score(y_test_reg, y_pred_reg)

    plt.scatter(X_test_reg, y_test_reg, color='black')
    plt.plot(X_test_reg, y_pred_reg, color='blue', linewidth=3)
    plt.xlabel('опыт работы (лет)')
    plt.ylabel('заработная плата ($)')
    plt.title('зависимость заработной платы от опыта работы (регрессия)')
    plt.show()

    iris = load_iris()
    X_cls = iris.data
    y_cls = iris.target

    scaler = StandardScaler()
    X_scaled_cls = scaler.fit_transform(X_cls)

    X_train_cls, X_test_cls, y_train_cls, y_test_cls = train_test_split(X_scaled_cls, y_cls, test_size=0.2,
                                                                        random_state=42)

    classifier = MLPClassifier(hidden_layer_sizes=(100,), activation='relu', solver='adam', max_iter=1000,
                               random_state=42)
    classifier.fit(X_train_cls, y_train_cls)

    y_pred_cls = classifier.predict(X_test_cls)

    accuracy_cls = accuracy_score(y_test_cls, y_pred_cls)

    print("regression Mean Squared Error:", mse_reg)
    print("regression R^2 Score:", r2_reg)

    print("classification Accuracy:", accuracy_cls)

def main():
    while True:
        choice = input(
            "\nselect a task to open: \n \n1 = task() \n2 = task() \n3 = task() class MLPClassified \n4 = task() class MLPRegressor \n(no task - if you want to exit, enter 'exit'): ")

        menu = {
            '1': task_1_1,
            '2': task_1_2,
            '3': task_1_3,
            '4': task_1_4,
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
