import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier, MLPRegressor
from sklearn.metrics import confusion_matrix

iris_data = pd.read_csv("https://gist.githubusercontent.com/netj/8836201/raw/6f9306ad21398ea43cba4f7d537619d0e07d5ae3/iris.csv")
X_iris = iris_data.drop('species', axis=1)
Y_iris = iris_data['species']

salary_data = pd.read_csv("https://raw.githubusercontent.com/AnnaShestova/salary-years-simple-linear-regression/master/Salary_Data.csv")
X_salary = salary_data[['YearsExperience']]
Y_salary = salary_data['Salary']

X_train_iris, X_test_iris, Y_train_iris, Y_test_iris = train_test_split(X_iris, Y_iris, train_size=0.8, random_state=123)
X_train_salary, X_test_salary, Y_train_salary, Y_test_salary = train_test_split(X_salary, Y_salary, train_size=0.8, random_state=123)


# MLPClassifier
mlp_classifier = MLPClassifier(random_state=123)
mlp_classifier.fit(X_train_iris, Y_train_iris)

# MLPRegressor
mlp_regressor = MLPRegressor(random_state=123)
mlp_regressor.fit(X_train_salary, Y_train_salary)


print("MLPClassifier Attributes Analysis:")
print("Loss:", mlp_classifier.loss_)
print("Number of Coefficients:", len(mlp_classifier.coefs_))
print("Number of Intercepts:", len(mlp_classifier.intercepts_))
print("Number of Iterations for Which Estimator Ran:", mlp_classifier.n_iter_)
print("Name of Output Layer Activation Function:", mlp_classifier.out_activation_)

print("MLPClassifier Test Accuracy:", mlp_classifier.score(X_test_iris, Y_test_iris))
print("MLPClassifier Training Accuracy:", mlp_classifier.score(X_train_iris, Y_train_iris))

def plot_confusion_matrix(Y_test, Y_preds):
    conf_mat = confusion_matrix(Y_test, Y_preds)
    fig = plt.figure(figsize=(6, 6))
    plt.matshow(conf_mat, cmap=plt.cm.Blues, fignum=1)
    plt.yticks(range(3), iris_data['species'].unique())
    plt.xticks(range(3), iris_data['species'].unique())
    plt.colorbar()
    for i in range(3):
        for j in range(3):
            plt.text(i - 0.2, j + 0.1, str(conf_mat[j, i]), color='tab:red')
    plt.xlabel("Predicted")
    plt.ylabel("Actual")
    plt.title("Confusion Matrix for MLPClassifier")
    plt.show()

plot_confusion_matrix(Y_test_iris, mlp_classifier.predict(X_test_iris))

print("\nMLPRegressor Attributes Analysis:")
print("Loss:", mlp_regressor.loss_)
print("Number of Coefficients:", len(mlp_regressor.coefs_))
print("Number of Intercepts:", len(mlp_regressor.intercepts_))
print("Number of Iterations for Which Estimator Ran:", mlp_regressor.n_iter_)
print("Name of Output Layer Activation Function:", mlp_regressor.out_activation_)

print("MLPRegressor Test Score:", mlp_regressor.score(X_test_salary, Y_test_salary))
print("MLPRegressor Training Score:", mlp_regressor.score(X_train_salary, Y_train_salary))

print("Predictions:", mlp_regressor.predict(X_test_salary))
