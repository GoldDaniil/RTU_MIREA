class task_one:

class task_two:
    
class task_tree:
        
class task_four:           
            
class task_five:

def main():
    while True:
        print(f"{Colors.CYAN}выберите задание:{Colors.RESET}")
        print("1.первое задание")
        print("2.второе задание")
        print("3.третье задание")
        print("4.четверторе задание")
        print("5.пятое задание")
        print(f"{Colors.RED}'exit' - выход{Colors.RESET}")

        choice = input("введите номер задания (1...5) или 'exit' для выхода: ").lower()

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
