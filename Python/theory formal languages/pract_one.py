#верно
class TaskOne:
    @staticmethod
    def precedence(op):
        if op in ('+', '-'):
            return 1
        if op in ('*', '/'):
            return 2
        if op == '^':  # степень
            return 3
        if op in ('!', '|', '#', '*', '@', '%', '=', '+'):
            return 4  # логические операции имеют приоритет выше арифметических
        return 0

    @staticmethod
    def is_valid_expression(expression):
        # разрешенные символы: цифры, буквы, операторы, скобки
        valid_chars = set('0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/^()!|#*+^@%=')
        return all(char in valid_chars or char == ' ' for char in expression)

    @staticmethod
    def infix_to_rpn(expression):
        stack = []
        output = []
        for char in expression:
            if char.isalnum():  # буквы или цифры
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

        return ' '.join(output)

    @staticmethod
    def run():
        while True:
            expression = input("введите арифметическое или логическое выражение (можно с пробелами), для выхода введите 'exit': ").replace(' ', '')

            # проверка выхода из программы
            if expression.lower() == 'exit':
                print(f"{Colors.MAGENTA}oh...okay;({Colors.RESET}")
                break

            # проверка входных данных
            if not TaskOne.is_valid_expression(expression):
                print(f"{Colors.RED}ошибка! выражение содержит недопустимые символы{Colors.RESET}")
                continue

            try:
                rpn = TaskOne.infix_to_rpn(expression)
                print("oбратная польская запись (ОПЗ):", rpn)
            except (IndexError, ValueError):
                print(f"{Colors.RED}ошибка - неверное выражение! {Colors.RESET}")


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
                            print("нельзя делить на 0")
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


#pyinstaller --onefile /Users/gold/PycharmProjects/untitled/.venv/main.py
