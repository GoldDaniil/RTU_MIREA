def validate_rpn_expression(rpn_expression):
    valid_operators = {'+', '-', '*', '/'}
    operand_count = 0

    for token in rpn_expression:
        if token.isdigit():
            operand_count += 1
        elif token in valid_operators:
            if operand_count < 2:  # для выполнения операции нужно минимум 2 операнда
                return False, "ошибка: недостаточно операндов для выполнения операции."
            operand_count -= 1
        else:
            return False, f"ошибка: недопустимый символ '{token}'."

    if operand_count != 1:  # После завершения выражения в стеке должен остаться один результат
        return False, "ошибка: неправильное количество операндов."

    return True, "корректное выражение."


def calculate_rpn_expression(rpn_expression):
    operand_stack = []

    for token in rpn_expression:
        if token.isdigit():
            operand_stack.append(int(token))
        else:
            second_operand = operand_stack.pop()
            first_operand = operand_stack.pop()

            if token == '+':
                operand_stack.append(first_operand + second_operand)
            elif token == '-':
                operand_stack.append(first_operand - second_operand)
            elif token == '*':
                operand_stack.append(first_operand * second_operand)
            elif token == '/':
                operand_stack.append(first_operand / second_operand)

    return operand_stack[0]


def main():
    user_input_expression = input(
        "введите выражение в обратной польской нотации (через пробелы) или введи 'exit' чтобы выйти.: ").split()

    if 'exit' in user_input_expression:
        print("эх...ок(")
        return

    # проверка корректность введенного выражения
    is_valid_expression, validation_message = validate_rpn_expression(user_input_expression)
    if not is_valid_expression:
        print(validation_message)
        return

    rpn_result = calculate_rpn_expression(user_input_expression)
    print(f"результат: {rpn_result}")

if __name__ == "__main__":
    main()
