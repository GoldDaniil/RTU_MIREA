class TaskOne:
    @staticmethod
    def precedence(op):
        if op in ('+', '-'):
            return 1
        if op in ('*', '/'):
            return 2
        return 0

    @staticmethod
    def is_valid_expression(expression):
        # проверка - выражение состоит только из допустимых символов
        valid_chars = set('0123456789+-*/()')
        return all(char in valid_chars or char == ' ' for char in expression)

    @staticmethod
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
                while stack and TaskOne.precedence(char) <= TaskOne.precedence(stack[-1]):
                    output.append(stack.pop())
                stack.append(char)

        while stack:
            output.append(stack.pop())

        return ''.join(output)

    @staticmethod
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

    @staticmethod
    def run():
        while True:
            expression = input("введите алгебраическое выражение (можно с пробелами), для выхода введите 'exit': ").replace(' ', '')

            # проверка выхода из программы
            if expression.lower() == 'exit':
                print(f"{Colors.MAGENTA}oh...okay;({Colors.RESET}")
                break

            # проверка входных
            if not TaskOne.is_valid_expression(expression):
                print(f"{Colors.RED}ошибка! выражение содержит недопустимые символы{Colors.RESET}")
                continue

            try:
                rpn = TaskOne.infix_to_rpn(expression)
                print("обратная польская запись (ОПЗ):", rpn)
                result = TaskOne.evaluate_rpn(rpn)
                if result is not None:
                    print(f"{Colors.GREEN}результат: {Colors.RESET}", result)
                else:
                    print(f"{Colors.RED}ошибка - неверное выражение! езе раз введите{Colors.RESET}")
            except (IndexError, ValueError):
                print(f"{Colors.RED}ошибка - неверное выражение! введите еще раз{Colors.RESET}")

class RPNCalculator:
    def evaluate_rpn(self, rpn):
        stack = []
        for char in rpn:
            if char.isdigit():
                stack.append(int(char))
            else:
                try:
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
                            print("нах на 0 делишь")
                            return None
                        stack.append(a // b)
                except IndexError:
                    print("ошибка: неверное выражение")
                    return None
        return stack[0] if stack else None

    def run(self):
        while True:
            rpn_expression = input("введите выражение в ОБЗ (или 'exit' для выхода): ")

            if rpn_expression.lower() == 'exit':
                print(f"{Colors.MAGENTA};({Colors.RESET}")
                break

            result = self.evaluate_rpn(rpn_expression)
            if result is not None:
                print(f"результат: {result}")
            else:
                print(f"{Colors.RED}ошибка: неверное выражение, попробуйте снова{Colors.RESET}")

def main():
    while True:
        print(f"{Colors.CYAN}выберите задание:{Colors.RESET}")
        print("1.преобразование выражения в ОПЗ")
        print("2.калькулятор ОПЗ")
        print(f"{Colors.RED}'exit' - выход{Colors.RESET}")

        choice = input("введите номер задания (1/2) или 'exit' для выхода: ").lower()

        if choice == '1':
            TaskOne.run()
        elif choice == '2':
            calculator = RPNCalculator()
            calculator.run()
        elif choice == 'exit':
            print(f"{Colors.MAGENTA};({Colors.RESET}")
            break
        else:
            print(f"{Colors.RED}введите еще раз{Colors.RESET}")

class Colors:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    RESET = '\033[0m'

if __name__ == "__main__":
    main()


# print(f"{Colors.RED}test{Colors.RESET}")
# print(f"{Colors.GREEN}test{Colors.RESET}")
# print(f"{Colors.YELLOW}test{Colors.RESET}")
# print(f"{Colors.BLUE}test{Colors.RESET}")
# print(f"{Colors.MAGENTA}test{Colors.RESET}")

