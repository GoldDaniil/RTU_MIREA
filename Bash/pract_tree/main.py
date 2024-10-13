import subprocess
import os
import random

class task_one:
    @staticmethod
    def run():
        print("запуск задания 1: taskone.jsonnet")
        if os.path.exists("taskone.jsonnet"):
            try:
                result = subprocess.run(["jsonnet", "taskone.jsonnet"], capture_output=True, text=True)
                print(result.stdout)
            except Exception as e:
                print(f"ошибка при запуска taskone.jsonnet: {e}")
        else:
            print("не найден файл")

class task_two:
    @staticmethod
    def run():
        print("запуск задания 2: tasktwo.dhall")
        if os.path.exists("tasktwo.dhall"):
            try:
                result = subprocess.run(["dhall", "decode", "<", "tasktwo.dhall"], capture_output=True, text=True)
                print(result.stdout)
            except Exception as e:
                print(f"ошибка при запуске tasktwo.dhall: {e}")
        else:
            print("не найден файл")

class task_three:
    BNF = '''
    E = seq1 | seq2 | seq3 | seq4 | seq5
    seq1 = 1 0
    seq2 = 1 0 0
    seq3 = 1 1
    seq4 = 1 0 1 1 0 1
    seq5 = 0 0 0
    '''

    @staticmethod
    def parse_bnf(text):
        grammar = {}
        rules = [line.split('=') for line in text.strip().split('\n')]
        for name, body in rules:
            grammar[name.strip()] = [alt.split() for alt in body.split('|')]
        return grammar

    @staticmethod
    def generate_phrase(grammar, start):
        if start in grammar:
            seq = random.choice(grammar[start])
            return ''.join([task_three.generate_phrase(grammar, name) for name in seq])
        return str(start)

    @staticmethod
    def run():
        print("запуск задания 3: БНФ-грамматика для строк")
        grammar = task_three.parse_bnf(task_three.BNF)
        for _ in range(10):
            print(task_three.generate_phrase(grammar, 'E'))

class task_four:
    BNF = '''
    E = P | Q | P Q | empty
    P = '(' E ')'
    Q = '{' E '}'
    empty = ''
    '''

    @staticmethod
    def parse_bnf(text):
        grammar = {}
        rules = [line.split('=') for line in text.strip().split('\n')]
        for name, body in rules:
            grammar[name.strip()] = [alt.split() for alt in body.split('|')]
        return grammar

    @staticmethod
    def generate_phrase(grammar, start):
        if start in grammar:
            seq = random.choice(grammar[start])
            return ''.join([task_four.generate_phrase(grammar, name) for name in seq])
        return str(start)

    @staticmethod
    def run():
        print("запуск задания 4: правильно расставленные скобки")
        grammar = task_four.parse_bnf(task_four.BNF)
        for _ in range(10):
            print(task_four.generate_phrase(grammar, 'E'))

class task_five:
    BNF = '''
    E = T | F | E '&' E | E '|' E | '~' E
    T = 'x' | 'y'
    F = 'x' | 'y'
    '''

    @staticmethod
    def parse_bnf(text):
        grammar = {}
        rules = [line.split('=') for line in text.strip().split('\n')]
        for name, body in rules:
            grammar[name.strip()] = [alt.split() for alt in body.split('|')]
        return grammar

    @staticmethod
    def generate_phrase(grammar, start):
        if start in grammar:
            seq = random.choice(grammar[start])
            return ''.join([task_five.generate_phrase(grammar, name) for name in seq])
        return str(start)

    @staticmethod
    def run():
        print("запуск задания 5: алгебра логики")
        grammar = task_five.parse_bnf(task_five.BNF)
        for _ in range(10):
            print(task_five.generate_phrase(grammar, 'E'))

def main():
    while True:
        print(f"{Colors.CYAN}\nвыберите задание:{Colors.RESET}")
        print("1. первое задание (Jsonnet)")
        print("2. второе задание (Dhall)")
        print("3. третье задание (БНФ-грамматика)")
        print("4. четвертое задание скобки")
        print("5. пятое задание алгебра логики")
        print(f"{Colors.RED}'exit' - выход{Colors.RESET}")

        choice = input("введите номер задания (1...5) или 'exit' для выхода: ").lower()

        if choice == '1':
            task_one.run()
        elif choice == '2':
            task_two.run()
        elif choice == '3':
            task_three.run()
        elif choice == '4':
            task_four.run();
        elif choice == '5':
            task_four.run();
        elif choice == 'exit':
            print(f"{Colors.MAGENTA}выход из программы...{Colors.RESET}")
            break
        else:
            print(f"{Colors.RED}введите корректный номер задания{Colors.RESET}")

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
