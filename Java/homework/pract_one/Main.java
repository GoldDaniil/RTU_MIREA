import java.util.Scanner;//из пакета java.util вытаскиваем класс Scanner

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
        double ROUBLES_PER_YUAN = 11.91;

        System.out.print("введите сумму денег в китайских юанях: ");
        int yuan = getValidInt(scanner);

        double roubles = ROUBLES_PER_YUAN * yuan;
        String roubles_word = getRoubleWord(roubles);
        System.out.println("сумма в российских " + roubles_word + ": " + roubles);
    }

    public static void task2(Scanner scanner) {
        final double ROUBLES_PER_YUAN = 11.91;
        System.out.print("введите сумму денег в китайских юанях: ");
        int yuan = getValidInt(scanner);
        double roubles = ROUBLES_PER_YUAN * yuan;

        int last_digit_yuan = yuan % 10;
        int last_two_digits_yuan = yuan % 100;

        String yuan_word;

        if (last_two_digits_yuan >= 11 && last_two_digits_yuan <= 19) {
            yuan_word = "юаней";
        } else if (last_digit_yuan == 1) {
            yuan_word = "юань";
        } else if (last_digit_yuan >= 2 && last_digit_yuan <= 4) {
            yuan_word = "юанях";
        } else {
            yuan_word = "юаней";
        }

        String roubles_word = getRoubleWord(roubles);
        System.out.println("сумма в " + yuan_word + ": " + roubles + " российских " + roubles_word + ".");
    }

    public static String getRoubleWord(double roubles) {
        int roublesInt = (int) roubles;
        int last_digit_rouble = roublesInt % 10;
        int last_two_digits_rouble = roublesInt % 100;

        if (last_two_digits_rouble >= 11 && last_two_digits_rouble <= 19) {
            return "рублей";
        } else if (last_digit_rouble == 1) {
            return "рубль";
        } else if (last_digit_rouble >= 2 && last_digit_rouble <= 4) {
            return "рубля";
        } else {
            return "рублей";
        }
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
                }
            } else {
                System.out.println("неверный ввод, введите целое число");
                scanner.next();//cчитываем неправильный ввод и игнорируем его
            }
        }
        return number;
    }
}
