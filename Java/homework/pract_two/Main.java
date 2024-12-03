import java.util.Scanner;//из пакета java.util вытаскиваем класс Scanner
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int choice;

        System.out.println("hello world");

        do {
            System.out.println("\nselect task:");
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
                    MainTask2.launchTask2();
//                    task2(scanner);
                    break;
                case 3:
                    System.out.println("ну вот:(");
                    break;
                default:
                    System.out.println("\nerror choice- enter 1, 2 или 3");
                    System.out.println("select task:");
                    System.out.println("1 - task one");
                    System.out.println("2 - task two");
                    System.out.println("3 - exit");
                    System.out.print("enter task number: ");
                    break;
            }
        } while (choice != 3);

        scanner.close();
    }

    public static void task1(Scanner scanner) {
        System.out.println("\nselect the type of constructor to create a car:");
        System.out.println("1 - constructor with a full set of fields");
        System.out.println("2 - default constructor:");
        System.out.println("3 - constructor with fields (model and year)");
        int constructorChoice = getValidInt(scanner);
        Car car;

        switch (constructorChoice) {
            case 1:
                System.out.print("enter model: ");
                String model = scanner.next();
                System.out.print("enter number: ");
                String number = scanner.next();
                System.out.print("enter color: ");
                String color = scanner.next();
                System.out.print("enter year: ");
                int year = getValidInt(scanner);

                car = new Car(model, number, color, year);
                break;

            case 2:
                car = generateRandomCar();
                break;

            case 3:
                System.out.print("enter model: ");
                model = scanner.next();
                System.out.print("enter year: ");
                year = getValidInt(scanner);

                car = new Car(model, year);
                break;

            default:
                System.out.println("error!");
                return;
        }

        car.displayInfo();
    }

    public static Car generateRandomCar() {
        // Списки моделей, номеров и цветов
        List<String> models = Arrays.asList("Toyota Camry", "Honda Civic", "Ford Focus", "BMW 3 Series", "Mercedes-Benz C-Class",
                "Audi A4", "Hyundai Sonata", "Kia Optima", "Volkswagen Passat", "Skoda Octavia");
        List<String> numbers = Arrays.asList("A123BC 77", "B456DE 78", "C789FG 99", "D321HK 50", "E654JK 63",
                "F987LM 47", "G123OP 77", "H456QR 34", "I789ST 23", "J321UV 10",
                "K654WX 95", "L987YZ 01", "M123AB 77", "N456CD 78", "O789EF 99",
                "P321GH 50", "Q654IJ 63", "R987KL 47", "S123MN 77", "T456OP 34");
        List<String> colors = Arrays.asList("Black", "White", "Red", "Blue", "Green", "Yellow", "Silver", "Gray", "Brown", "Purple");

        Random random = new Random();

        String model = models.get(random.nextInt(models.size()));
        String number = numbers.get(random.nextInt(numbers.size()));
        String color = colors.get(random.nextInt(colors.size()));

        int year = random.nextInt(2024 - 1995 + 1) + 1995;

        return new Car(model, number, color, year);
    }

    public static int getValidInt(Scanner scanner) {
        int number = -1;
        while (true) {
            if (scanner.hasNextInt()) {
                number = scanner.nextInt();
                if (number >= 0) {
                    break;
                } else {
                    System.out.println("error, enter positive number");
                    System.out.println("select task:");
                    System.out.println("1 - task one");
                    System.out.println("2 - task two");
                    System.out.println("3 - exit");
                    System.out.print("enter task number: ");
                    scanner.next();
                }
            } else {
                System.out.println("error, enter integer number");
                System.out.println("select task:");
                System.out.println("1 - task one");
                System.out.println("2 - task two");
                System.out.println("3 - exit");
                System.out.print("enter task number: ");
                scanner.next();//cчитываем неправильный ввод и игнорируем его
            }
        }
        return number;
    }
}


class Car {
    private String model;
    private String number;
    private String color;
    private int year;

    public Car(String model, String number, String color, int year) {
        this.model = model;
        this.number = number;
        this.color = color;
        this.year = year;
    }

    public Car() {
        this.model = "unknown";
        this.number = "unknown";
        this.color = "unknown";
        this.year = 0;
    }

    public Car(String model, int year) {
        this.model = model;
        this.number = "unknown";
        this.color = "unknown";
        this.year = year;
    }

    public void displayInfo() {
        System.out.println(model + " " + number + " " + color + " " + year + " year");
    }
}
