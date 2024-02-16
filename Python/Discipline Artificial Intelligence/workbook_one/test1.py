def check_variable_int_float(variable):
    """
    функция - которая проверяет - является ли переменная целым или числом с плавающей точкой
    """
    if isinstance(variable, (int, float)):
        return True
    else:
        return False

def check_variable_string(variable):
    """
    функция - которая проверяет - является ли переменная строкой
    """
    if isinstance(variable, str):
        return True
    else:
        return False

def main():
    """
    """
    while True:
        var1 = input("enter: ")
        if check_variable_int_float(var1):
            break
        else:
            print("error.")

    while True:
        var2 = input("enter: ")
        if check_variable_int_float(var2):
            break
        else:
            print("error.")

    while True:
        var3 = input("enter: ")
        if check_variable_string(var3):
            break
        else:
            print("должна быть строкой.")

    while True:
        var4 = input("enter: ")
        if check_variable_string(var4):
            break
        else:
            print("должна быть строкой.")

    # преобразование строковых значений в числа
    var1 = float(var1)
    var2 = float(var2)

    sum_result = var1 + var2

    print("sum:", sum_result)
    print(" :", var3 + ' and ' + var4)

# Вызов основной функции
if __name__ == "__main__":
    main()
