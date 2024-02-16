def check_variable_int_float(variable):
    # функция - которая проверяет - является ли переменная целым или числом 
    # с плавающей точкой(дробным числом)и предоставляет пользователю возможность
    # вводить значение переменной до тех пор - пока не будет введен верный тип
    
    while True:
        try:
            variable = float, int (variable)  # преобразуем введенное значение в число
            return variable  # возвращаем значение - если успешно преобразовалось
        except ValueError:
            print("required type - integer/float \n")
            variable = input("try entering again: ")  # запрашиваем ввод снова



def main():
    # ввод переменных с клавиатуры с проверкой типа данных
    var1 = input("enter first number: ")
    var1 = check_variable_int_float(var1)

    var2 = input("enter second number: ")
    var2 = check_variable_int_float(var2)

    sum_result = var1 + var2

    print("sum:", sum_result)


if __name__ == "__main__":
    main()
