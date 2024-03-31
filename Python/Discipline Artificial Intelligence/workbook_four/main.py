import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score

# ОШИБКА В 6 И 7 НОМЕРЕ

def check_variable_int_float(variable):
    # функция - которая проверяет - является ли переменная целым или числом
    # с плавающей точкой(дробным числом)и предоставляет пользователю возможность
    # вводить значение переменной до тех пор - пока не будет введен верный тип
    while True:
        try:
            variable = float(variable)  # преобразуем введенное значение в число
            return variable  # возвращаем значение - если успешно преобразовалось
        except ValueError:
            print("error/ required type - integer/float \n")
            variable = input("try entering again: ")  # запрашиваем ввод снова

def check_variable_str(variable):
    while True:
        try:
            variable = str(variable)
            return variable
        except ValueError:
            print("error. required type - string \n")
            variable = input("try entering again: ")

def task_1_1_3():
    # Создаем фиктивные данные
    x = np.array([-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6])
    y = np.array([-53, -26, -9, 0, 1, 0, 9, 26, 53, 88, 129])

    # Построение экстраполяции полиномами первой, второй и третьей степени
    m = np.vstack((x ** 3, x ** 2, x, np.ones(11))).T
    s1 = np.linalg.lstsq(m[:, :2], y, rcond=None)[0]  # Полином первой степени
    s2 = np.linalg.lstsq(m[:, :3], y, rcond=None)[0]  # Полином второй степени

    # Новые точки для экстраполяции
    x_prec = np.linspace(-5, 7, 101)

    # Построение графика
    plt.plot(x, y, 'D', label='Исходные данные')
    plt.plot(x_prec, s1[0] * x_prec + s1[1], '-', lw=3, label='Полином 1-й степени')
    plt.plot(x_prec, s2[0] * x_prec ** 2 + s2[1] * x_prec + s2[2], '-', lw=3, label='Полином 2-й степени')
    plt.grid()
    plt.legend()
    plt.savefig('полиномы_1_и_2_степени.png')
    plt.show()

def task_five_fun_one():
    # Определение своей функции
    def f(x, b0, b1):
        return b0 + b1 * x ** 2  # Пример квадратичной функции

    # Задание своих данных
    xdata = np.linspace(0, 5, 50)  # Создаем свои данные x
    b0, b1 = 1.5, 2.5  # Пример коэффициентов для функции
    y = f(xdata, b0, b1)  # Вычисляем значения функции без шума
    ydata = y + 0.2 * np.random.randn(len(xdata))  # Добавляем шум

    # Аппроксимация
    beta_opt, beta_cov = sp.optimize.curve_fit(f, xdata, ydata)

        # Вывод результатов
    print("Оптимальные коэффициенты:", beta_opt)
    lin_dev = sum(beta_cov[0])  # Линейное отклонение
    print("Линейное отклонение:", lin_dev)
    residuals = ydata - f(xdata, *beta_opt)  # Остатки
    fres = sum(residuals ** 2)  # Квадратичное отклонение
    print("Квадратичное отклонение:", fres)

    # Визуализация
    fig, ax = plt.subplots()
    ax.scatter(xdata, ydata)
    ax.plot(xdata, y, 'r--', lw=2, label='Исходная функция')
    ax.plot(xdata, f(xdata, *beta_opt), 'b', lw=2, label='Аппроксимация')
    ax.set_xlim(0, 5)
    ax.set_xlabel(r"$x$", fontsize=18)
    ax.set_ylabel(r"$f(x, \beta)$", fontsize=18)
    ax.legend()
    plt.show()

def task_five_fun_two():
    def f(x, b0, b1, b2):
        return b0 + b1 * x + b2 * x ** 2  # Пример квадратичной функции

    # Задание своих данных
    xdata = np.linspace(0, 5, 50)  # Создаем свои данные x
    beta = (0.25, 0.75, 0.5)  # Пример коэффициентов для функции
    y = f(xdata, *beta)  # Вычисляем значения функции без шума
    ydata = y + 0.05 * np.random.randn(len(xdata))  # Добавляем шум

    # Аппроксимация
    beta_opt, beta_cov = sp.optimize.curve_fit(f, xdata, ydata)

    # Вывод результатов
    print("Оптимальные коэффициенты:", beta_opt)
    lin_dev = sum(beta_cov[0])  # Линейное отклонение
    print("Линейное отклонение:", lin_dev)
    residuals = ydata - f(xdata, *beta_opt)  # Остатки
    fres = sum(residuals ** 2)  # Квадратичное отклонение
    print("Квадратичное отклонение:", fres)

    # Визуализация
    fig, ax = plt.subplots()
    ax.scatter(xdata, ydata)
    ax.plot(xdata, y, 'r', lw=2, label='Исходная функция')
    ax.plot(xdata, f(xdata, *beta_opt), 'b', lw=2, label='Аппроксимация')
    ax.set_xlim(0, 5)
    ax.set_xlabel(r"$x$", fontsize=18)
    ax.set_ylabel(r"$f(x, \beta)$", fontsize=18)
    ax.legend()
    plt.show()

def task_five_fun_three():
    def f(x, b0, b1):
        return b0 + b1 * np.log(x)  # Функция с логарифмом

    # Задание своих данных
    xdata = np.linspace(1, 5, 50)  # Создаем свои данные x
    beta = (1, 2)  # Пример коэффициентов для функции
    y = f(xdata, *beta)  # Вычисляем значения функции без шума
    ydata = y + 0.05 * np.random.randn(len(xdata))  # Добавляем шум

    # Аппроксимация
    beta_opt, beta_cov = sp.optimize.curve_fit(f, xdata, ydata)

    # Вывод результатов
    print("Оптимальные коэффициенты:", beta_opt)
    lin_dev = sum(beta_cov[0])  # Линейное отклонение
    print("Линейное отклонение:", lin_dev)
    residuals = ydata - f(xdata, *beta_opt)  # Остатки
    fres = sum(residuals ** 2)  # Квадратичное отклонение
    print("Квадратичное отклонение:", fres)

    # Визуализация
    fig, ax = plt.subplots()
    ax.scatter(xdata, ydata)
    ax.plot(xdata, y, 'r', lw=2, label='Исходная функция')
    ax.plot(xdata, f(xdata, *beta_opt), 'b', lw=2, label='Аппроксимация')
    ax.set_xlim(0, 5)
    ax.set_xlabel(r"$x$", fontsize=18)
    ax.set_ylabel(r"$f(x, \beta)$", fontsize=18)
    ax.legend()
    plt.show()

def task_five_fun_four():
    def f(x, b0, b1):
        return b0 * x ** b1  # Пример степенной функции

    # Задание своих данных
    xdata = np.linspace(1, 5, 50)  # Создаем свои данные x
    beta = (1, 2)  # Пример коэффициентов для функции
    y = f(xdata, *beta)  # Вычисляем значения функции без шума
    ydata = y + 0.05 * np.random.randn(len(xdata))  # Добавляем шум

    # Аппроксимация
    beta_opt, beta_cov = sp.optimize.curve_fit(f, xdata, ydata)

    # Вывод результатов
    print("Оптимальные коэффициенты:", beta_opt)
    lin_dev = sum(beta_cov[0])  # Линейное отклонение
    print("Линейное отклонение:", lin_dev)
    residuals = ydata - f(xdata, *beta_opt)  # Остатки
    fres = sum(residuals ** 2)  # Квадратичное отклонение
    print("Квадратичное отклонение:", fres)

    # Визуализация
    fig, ax = plt.subplots()
    ax.scatter(xdata, ydata)
    ax.plot(xdata, y, 'r', lw=2, label='Исходная функция')
    ax.plot(xdata, f(xdata, *beta_opt), 'b', lw=2, label='Аппроксимация')
    ax.set_xlim(0, 5)
    ax.set_xlabel(r"$x$", fontsize=18)
    ax.set_ylabel(r"$f(x, \beta)$", fontsize=18)
    ax.legend()
    plt.show()

def task_1_2_1():
    url = "https://raw.githubusercontent.com/AnnaShestova/salary-years-simple-linear-regression/master/Salary_Data.csv"
    data = pd.read_csv(url)

    years_experience = data['YearsExperience'].values.reshape(-1, 1)  # Reshaping to 2D array for sklearn
    salary = data['Salary'].values

    model = LinearRegression()
    model.fit(years_experience, salary)

    intercept = model.intercept_
    slope = model.coef_[0]
    print("Intercept:", intercept)
    print("Slope:", slope)

    plt.scatter(years_experience, salary, color='blue', label='Data')
    plt.plot(years_experience, model.predict(years_experience), color='red', label='Linear Regression')
    plt.xlabel('Years of Experience')
    plt.ylabel('Salary')
    plt.title('Linear Regression: Salary vs. Years of Experience')
    plt.legend()
    plt.show()

    years_exp_new = np.array([[10], [15], [20]])
    predictions = model.predict(years_exp_new)
    for i, exp in enumerate(years_exp_new):
        print(f"Predicted salary for {exp} years of experience: {predictions[i]}")

def task_1_3_2():
    url = "https://raw.githubusercontent.com/aniruddhachoudhury/Red-Wine-Quality/master/winequality-red.csv"
    data = pd.read_csv(url)

    # Предварительный анализ данных
    print(data.head())  # Первые строки данных
    print(data.info())  # Информация о данных

    # Выделение признаков (X) и целевой переменной (Y)
    X = data.drop('quality', axis=1)  # Исключаем столбец 'quality'
    Y = data['quality']

    # Разделение данных на обучающий и тестовый наборы
    X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, random_state=42)

    # Построение модели множественной линейной регрессии
    model = LinearRegression()
    model.fit(X_train, Y_train)

    # Получение коэффициентов регрессии
    coefficients = pd.DataFrame({'Признак': X.columns, 'Коэффициент': model.coef_})
    print(coefficients)

    # Прогнозирование на тестовом наборе
    Y_pred = model.predict(X_test)

    # Оценка качества модели
    mse = mean_squared_error(Y_test, Y_pred)
    r2 = r2_score(Y_test, Y_pred)
    print(f'Среднеквадратичная ошибка (MSE): {mse:.2f}')
    print(f'Коэффициент детерминации (R^2): {r2:.2f}')

def task_1_3_3():
    x_data = np.array([0.0, 0.2, 0.4, 0.6, 0.8, 1.0])
    y_data = np.array([3.0, 6.0, 3.0, 6.0, 4.0, 3.0])

    # Построение полинома первой степени (прямой)
    A1 = np.vstack([x_data, np.ones(len(x_data))]).T
    m1, c1 = np.linalg.lstsq(A1, y_data, rcond=None)[0]

    # Построение полинома второй степени (параболы)
    A2 = np.vstack([x_data ** 2, x_data, np.ones(len(x_data))]).T
    a2, b2, c2 = np.linalg.lstsq(A2, y_data, rcond=None)[0]

    # Вычисление значений полиномов для построения графиков
    x_values = np.linspace(0, 1, 100)
    y_poly1 = m1 * x_values + c1
    y_poly2 = a2 * x_values ** 2 + b2 * x_values + c2

    # Построение графиков
    plt.figure(figsize=(10, 6))
    plt.plot(x_data, y_data, 'bo', label='Экспериментальные данные')
    plt.plot(x_values, y_poly1, 'r', label=f'Полином 1-й степени: y = {m1:.2f}x + {c1:.2f}')
    plt.plot(x_values, y_poly2, 'g', label=f'Полином 2-й степени: y = {a2:.2f}x^2 + {b2:.2f}x + {c2:.2f}')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Аппроксимация данных полиномами 1-й и 2-й степени')
    plt.legend()
    plt.grid(True)
    plt.show()

def main() :
    while True:

        choice = input("\nselect a task to open: \n \n1 = task 1.1.3, \n2 = task 1.1.5.1, \n3 = task 1.1.5.2, \n4 = task 1.1.5.3, \n5 = task 1.1.5.4, \n6 = task 1.2.1, \n7 = task 1.3.2, \n8 = task 1.3.3 \n(no task - if you want to exit, enter 'exit'): ")

        menu = {
            '1': task_1_1_3,
            '2': task_five_fun_one,
            '3': task_five_fun_two,
            '4': task_five_fun_three,
            '5': task_five_fun_four,
            '6': task_1_2_1,
            '7': task_1_3_2,
            '8': task_1_3_3,
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
