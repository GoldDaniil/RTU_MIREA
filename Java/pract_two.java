import java.util.Scanner; // из пакета java.util вытаскиваем класс Scanner

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int choice;

        do {
            System.out.println("select task:");
            System.out.println("1 - task one");
            System.out.println("2 - task two");
            System.out.println("3 - exit");
            System.out.print("enter task number: ");
            choice = getValidInt(scanner);

            switch (choice) {
                case 1:
                    task1(scanner);
                    break;
                case 2:
                    task2(scanner);
                    break;
                case 3:
                    System.out.println("ну вот:(");
                    break;
                default:
                    System.out.println("\nнеправильный выбор. введите 1, 2 или 3");
                    break;
            }
        } while (choice != 3);

        scanner.close();
    }

    public static void task1(Scanner scanner) {
        
        
    }

    public static void task2(Scanner scanner) {
        
    }

    public static int getValidInt(Scanner scanner) {
        int number = -1;
        while (true) {
            if (scanner.hasNextInt()) {
                number = scanner.nextInt();
                if (number >= 0) {
                    break;
                } else {
                    System.out.println("неверный ввод, введите положительное число");
                    scanner.next(); // cчитываем неправильный ввод и игнорируем его
                }
            } else {
                System.out.println("неверный ввод, введите целое число");
                scanner.next(); // cчитываем неправильный ввод и игнорируем его
            }
        }
        return number;
    }
}
