import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return x * (1 - x)

class Perceptron:
    def __init__(self, N):
        self.w = [0] * N

    def calc(self, x):
        res = 0
        for i in range(len(self.w)):
            res += self.w[i] * x[i]
        return res

    def sign(self, x):
        if self.calc(x) > 0:
            return 1
        else:
            return -1

    def learn(self, la, x, y):
        if y * self.calc(x) <= 0:
            for i in range(len(self.w)):
                self.w[i] += la * y * x[i]

    def learning(self, la, T):
        for n in range(100):
            for t in T:
                self.learn(la, t[0], t[1])

class NeuralNetwork1:
    def __init__(self):
        self.input_size = 3
        self.hidden_size = 3
        self.output_size = 1
        self.weights_input_hidden = np.array([[0.5, 0.5, 0.5],
                                              [0.5, 0.5, 0.5],
                                              [0.5, 0.5, 0.5]])
        self.weights_hidden_output = np.random.rand(self.hidden_size, self.output_size)
        self.bias = 0

    def feedforward(self, x):
        self.hidden_layer_input = np.dot(x, self.weights_input_hidden) + self.bias
        self.hidden_layer_output = sigmoid(self.hidden_layer_input)
        self.output = sigmoid(np.dot(self.hidden_layer_output, self.weights_hidden_output))
        return self.output


class NeuralNetwork2:
    def __init__(self):
        self.input_size = 2
        self.hidden_size = 2
        self.output_size = 2
        self.weights_input_hidden = np.array([[1, 0],
                                              [1, 0]])
        self.weights_hidden_output = np.random.rand(self.hidden_size, self.output_size)
        self.bias = 1

    def feedforward(self, x):
        self.hidden_layer_input = np.dot(x, self.weights_input_hidden) + self.bias
        self.hidden_layer_output = sigmoid(self.hidden_layer_input)
        self.output = sigmoid(np.dot(self.hidden_layer_output, self.weights_hidden_output))
        return self.output

if __name__ == "__main__":
    perceptron = Perceptron(2)
    la = 0.1  
    T = [[[2, 1], 1],
         [[3, 2], 1],
         [[4, 1], 1],
         [[1, 2], -1],
         [[2, 3], -1],
         [[5, 7], -1]]
    perceptron.learning(la, T)

    nn1 = NeuralNetwork1()
    x_nn1 = np.array([[1, 0, 1]])
    output_nn1 = nn1.feedforward(x_nn1)
    print("Neural Network 1 output:", output_nn1)

    nn2 = NeuralNetwork2()
    x_nn2 = np.array([[1, 0]])
    output_nn2 = nn2.feedforward(x_nn2)
    print("Neural Network 2 output:", output_nn2)
