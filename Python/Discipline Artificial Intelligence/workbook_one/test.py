def check_variable_type(variable, expected_type):
    try:
        expected_type(variable)
        return True
    except ValueError:
        return False

def check_variables(variables):
    for var_name, expected_type in variables.items():
        while True:
            user_input = input(f"enter {var_name}: ")
            if check_variable_type(user_input, expected_type):
                variables[var_name] = expected_type(user_input)
                break
            else:
                print(f"error {expected_type.__name__}")

def main():
    # oпределяем словарь переменных и их ожидаемых типов
    variables = {
        'x': int,
        'y': float,
        'z': str
    }

    # проверка переменных
    check_variables(variables)

    # проверка проверки
    print("Variables:", variables)

if __name__ == "__main__":
    main()
