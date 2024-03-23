import matplotlib.pyplot as plt
import numpy as np
from numpy import *
from mpl_toolkits.mplot3d import Axes3D
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.neighbors import KNeighborsClassifier

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
    iris = sns.load_dataset('iris')

    # Split data into training and testing sets
    X_train, X_test, y_train, y_test = train_test_split(
        iris.iloc[:, :-1],
        iris.iloc[:, -1],
        test_size=0.15,
        random_state=42  # Added for reproducibility
    )

    # Function to initialize and train KNN model
    def init_model(k, X_train, y_train, X_test):
        model = KNeighborsClassifier(n_neighbors=k)
        model.fit(X_train, y_train)
        y_pred = model.predict(X_test)
        return y_pred

    # Function to plot the data points and misclassified points
    def graph(y_test, X_test, y_pred):
        plt.figure(figsize=(10, 7))
        sns.scatterplot(x='petal_width', y='petal_length', data=iris, hue='species', s=70)
        plt.xlabel("Длина лепестка, см")
        plt.ylabel("Ширина лепестка, см")
        plt.legend(loc=2)
        plt.grid()

        for i in range(len(y_test)):
            if np.array(y_test)[i] != y_pred[i]:
                plt.scatter(X_test.iloc[i, 3], X_test.iloc[i, 2], color='red', s=150)

    # Function to calculate accuracy and print it
    def calculate_accuracy(y_pred, y_test):
        accuracy = accuracy_score(y_pred, y_test)
        print(f'Accuracy: {accuracy:.3}')

    # Get user input for k
    k = int(input('Введите значение k (1, 5, или 10): '))

    # Initialize and train the model
    y_pred = init_model(k, X_train, y_train, X_test)

    # Calculate and print accuracy
    calculate_accuracy(y_pred, y_test)

    # Plot the graph
    graph(y_test, X_test, y_pred)
    plt.show()

def task_3_3_2():
    from sklearn.feature_extraction import DictVectorizer

    x = [{"Двуногое": 2, },
         {"без перьев": 3}]
    dictVectorizer = DictVectorizer(sparse=False)
    y = dictVectorizer.fit_transform(x)
    print(y)


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
