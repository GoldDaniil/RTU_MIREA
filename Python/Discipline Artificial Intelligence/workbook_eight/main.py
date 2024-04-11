import matplotlib.pyplot as plt
import numpy as np
from sklearn.cluster import KMeans
from sklearn import datasets

def task_1_1_2():
    X = np.array([[5, 3],
                  [10, 15],
                  [15, 12],
                  [24, 10],
                  [30, 45],
                  [85, 70],
                  [71, 80],
                  [60, 78],
                  [55, 52],
                  [80, 91]])

    k_values = range(1, 6)  # Попробуем от 1 до 5 кластеров

    titles = [f'k={k}' for k in k_values]

    fig, axes = plt.subplots(1, len(k_values), figsize=(15, 4))

    for k, title, ax in zip(k_values, titles, axes):
        kmeans = KMeans(n_clusters=k, random_state=0)
        clusters = kmeans.fit_predict(X)
        ax.scatter(X[:, 0], X[:, 1], c=clusters, cmap='viridis', s=50, edgecolors='k')
        ax.set_title(title)
        ax.set_xlabel('feature 1')
        ax.set_ylabel('feature 2')
        ax.scatter(kmeans.cluster_centers_[:, 0], kmeans.cluster_centers_[:, 1], c='red', s=200, marker='X')
    plt.tight_layout()
    plt.show()

def task_1_1_3():
    iris = datasets.load_iris()
    X = iris.data

    k_values = range(1, 6)

    fig, axes = plt.subplots(1, len(k_values), figsize=(15, 4))

    for k, ax in zip(k_values, axes):
        kmeans = KMeans(n_clusters=k, random_state=0)
        clusters = kmeans.fit_predict(X)
        ax.scatter(X[:, 0], X[:, 1], c=clusters, cmap='viridis', s=50, edgecolors='k')
        ax.set_title(f'k={k}')
        ax.set_xlabel('Sepal length')
        ax.set_ylabel('Sepal width')
        ax.scatter(kmeans.cluster_centers_[:, 0], kmeans.cluster_centers_[:, 1], c='red', s=200, marker='X')
    plt.tight_layout()
    plt.show()

def main():
    while True:
        choice = input(
            "\nselect task: \n1 = first task \n2 = second task \n3 = third task \n4 = fourth task \n(no option - if you want to exit, enter 'exit'): ")

        menu = {
            '1': task_1_1_2,
            '2': task_1_1_3,
            #'3': task_1_1_4,
            #'4': task_1_1_4,
            'exit': lambda: print("\n\nmain menu!")
        }

        if choice in menu:
            menu[choice]()
            if choice == 'exit':
                return
        else:
            print("invalid choice. please enter a valid option")

if __name__ == "__main__":
    main()
