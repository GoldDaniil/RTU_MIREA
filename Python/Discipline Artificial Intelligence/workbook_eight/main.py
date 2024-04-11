import matplotlib.pyplot as plt
import numpy as np
from sklearn.cluster import KMeans
from sklearn import datasets

X = np.array([[5,3],
              [10,15],
              [15,12],
              [24,10],
              [30,45],
              [85,70],
              [71,80],
              [60,78],
              [55,52],
              [80,91]])

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
