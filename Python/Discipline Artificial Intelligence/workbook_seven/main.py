import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPRegressor, MLPClassifier
from sklearn.metrics import mean_squared_error, r2_score, accuracy_score
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt

# все кроме последнего задания
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

def task_1_1():
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

def task_1_2():
    print('hello MLPClassified')

def task_1_3():
    url = "https://raw.githubusercontent.com/AnnaShestova/salary-years-simple-linear-regression/master/Salary_Data.csv"
    data = pd.read_csv(url)
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
            "\nselect a task to open: \n \n1 = task () \n2 = task() class MLPClassified \n3 = task() class MLPRegressor \n(no task - if you want to exit, enter 'exit'): ")

        menu = {
            '1': task_1_1,
            '2': task_1_2,
            '3': task_1_3,
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
