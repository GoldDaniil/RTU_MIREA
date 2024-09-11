class Colors:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    RESET = '\033[0m'

# print(f"{Colors.RED}test{Colors.RESET}")
# print(f"{Colors.GREEN}test{Colors.RESET}")
# print(f"{Colors.YELLOW}test{Colors.RESET}")
# print(f"{Colors.BLUE}test{Colors.RESET}")
# print(f"{Colors.MAGENTA}test{Colors.RESET}")

def precedence(op):
    if op in ('+', '-'):
        return 1
    if op in ('*', '/'):
        return 2
    return 0

def is_valid_expression(expression):
    # проверка - выражение состоит только из допустимых символов
    valid_chars = set('0123456789+-*/()')
    return all(char in valid_chars or char == ' ' for char in expression)

def infix_to_rpn(expression):
    stack = []
    output = []
    for char in expression:
        if char.isdigit():
            output.append(char)
        elif char == '(':
            stack.append(char)
        elif char == ')':
            while stack and stack[-1] != '(':
                output.append(stack.pop())
            stack.pop()
        else:
            while stack and precedence(char) <= precedence(stack[-1]):
                output.append(stack.pop())
            stack.append(char)

    while stack:
        output.append(stack.pop())

    return ''.join(output)


def evaluate_rpn(rpn):
    stack = []
    for char in rpn:
        if char.isdigit():
            stack.append(int(char))
        else:
            b = stack.pop()
            a = stack.pop()
            if char == '+':
                stack.append(a + b)
            elif char == '-':
                stack.append(a - b)
            elif char == '*':
                stack.append(a * b)
            elif char == '/':
                if b == 0:
                    print(f"{Colors.RED}хули на 0 делишь{Colors.RESET}")
                    return None
                stack.append(a // b)
    return stack[0]


def main():
    while True:
        expression = input("введи алгебраическое выражение (можно с пробелами): ").replace(' ', '')

        # проверка входных
        if not is_valid_expression(expression):
            print(f"{Colors.RED}ошибка! выражение содержит недопустимые символы{Colors.RESET}")
            continue

        try:
            rpn = infix_to_rpn(expression)
            print("обратная польская запись (ОПЗ):", rpn)
            result = evaluate_rpn(rpn)
            if result is not None:
                print(f"{Colors.GREEN}результат: {Colors.RESET}", result)
            else:
                print(f"{Colors.RED}ошибка - неверное выражение! езе раз введите{Colors.RESET}")
        except (IndexError, ValueError):
            print(f"{Colors.RED}ошибка - неверное выражение! введите еще раз{Colors.RESET}")


if __name__ == "__main__":
    main()
