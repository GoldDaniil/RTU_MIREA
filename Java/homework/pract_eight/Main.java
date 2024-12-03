import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String[] months = {
                "январь", "февраль", "март", "апрель", "май",
                "июнь", "июль", "август", "сентябрь", "октябрь", "ноябрь", "декабрь"
        };
        int[] daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        Scanner scanner = new Scanner(System.in);

        while (true) {
            try {
                System.out.print("введи номер месяца (от 1 до 12): ");
                int month = scanner.nextInt();

                if (month < 1 || month > 12) {
                    System.out.println("недопустимое число = введите снова:");
                    continue;
                }

                if (month == 2) {
                    System.out.print("введи год: ");
                    int year = scanner.nextInt();
                    boolean isLeap = isLeapYear(year);
                    int days = isLeap ? 29 : 28;
                    String leapStatus = isLeap ? "является високосным" : "не является високосным";
                    System.out.println(months[month - 1] + " имеет " + days + " дней в " + year + " году, который " + leapStatus);
                } else {
                    System.out.println(months[month - 1] + " имеет " + daysInMonth[month - 1] + " дней.");
                }
                break;
            } catch (InputMismatchException e) {
                System.out.println("пожалуйста - введите целое число");
                scanner.nextLine();
            }
        }

        scanner.close();
    }

    public static boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
}
