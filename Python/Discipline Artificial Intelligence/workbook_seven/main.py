import numpy as np

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
    print('hello world MLPClassified')

def task_1_3():
    print('hello world MLPRegressor')

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
