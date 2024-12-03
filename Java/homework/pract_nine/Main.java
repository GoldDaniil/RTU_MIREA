import java.util.ArrayList;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Main main = new Main();
        while (true) {
            System.out.println("\nвыбери задание:");
            System.out.println("1 - удаление дубликатов из списка+");
            System.out.println("2 - линейный поиск в массиве+");
            System.out.println("3 - поиск наибольшего элемента в массиве Circle+");
            System.out.println("4 - поиск наибольшего элемента в двумерном массиве Circle+");
            System.out.println("5 - тест стеков+");
            System.out.println("6 - выйти");

            int choice = getUserChoice(scanner);
            switch (choice) {
                case 1:
                    taskRemoveDuplicates(scanner);
                    break;
                case 2:
                    taskLinearSearch(scanner);
                    break;
                case 3:
                    taskFindMaxInArray(scanner);
                    break;
                case 4:
                    taskFindMaxIn2DArray(scanner);
                    break;
                case 5:
                    taskTestStacks(scanner);
                    break;
                case 6:
                    System.out.println("бро...");
                    return;
                default:
                    System.out.println("введи еще раз");
                    break;
            }
        }
    }

    private static int getUserChoice(Scanner scanner) {
        while (true) {
            try {
                System.out.print("\nвведи номер задания: ");
                return scanner.nextInt();
            } catch (InputMismatchException e) {
                System.out.println("введи целое число");
                scanner.next();
            }
        }
    }

    private static void taskRemoveDuplicates(Scanner scanner) {
        System.out.println("введите элементы списка через пробел:");
        scanner.nextLine();
        String input = scanner.nextLine();
        ArrayList<String> list = new ArrayList<>(Arrays.asList(input.split(" ")));
        ArrayList<String> uniqueList = Utils.removeDuplicates(list);
        System.out.println("список без дубликатов: " + uniqueList);
    }

    private static void taskLinearSearch(Scanner scanner) {
        System.out.println("введите элементы массива через пробел:");
        scanner.nextLine();
        int[] array = parseArray(scanner.nextLine());
        if (array == null) return;

        System.out.print("введите элемент для поиска: ");
        scanner.nextLine();
        int target = getIntegerInput(scanner);
        int index = LinearSearch.findElement(array, target);
        System.out.println("результат поиска: " + (index >= 0 ? "найден на позиции " + index : "не найден"));
    }

    private static void taskFindMaxInArray(Scanner scanner) {
        System.out.println("введите радиусы окружностей через пробел:");
        scanner.nextLine();
        double[] radii = parseDoubleArray(scanner.nextLine());
        if (radii == null) return;

        Circle[] circles = Arrays.stream(radii).mapToObj(Circle::new).toArray(Circle[]::new);
        Circle maxCircle = MaxElementFinder.findMax(circles);
        System.out.println("наибольший круг: " + maxCircle);
    }

    private static void taskFindMaxIn2DArray(Scanner scanner) {
        System.out.println("введи радиусы окружностей для двумерного массива (по строкам через ;):");
        scanner.nextLine();
        String[] rows = scanner.nextLine().split(";");
        Circle[][] circleArray = new Circle[rows.length][];

        for (int i = 0; i < rows.length; i++) {
            double[] radii = parseDoubleArray(rows[i].trim());
            if (radii == null) return;
            circleArray[i] = Arrays.stream(radii).mapToObj(Circle::new).toArray(Circle[]::new);
        }

        Circle maxCircle = MaxElementFinder2D.findMax(circleArray);
        System.out.println("наибольший круг в двумерном массиве: " + maxCircle);
    }

    private static int[] parseArray(String input) {
        try {
            return Arrays.stream(input.trim().split(" "))
                    .mapToInt(Integer::parseInt)
                    .toArray();
        } catch (NumberFormatException e) {
            System.out.println("введи целые числа");

            return null;
        }
    }

    private static double[] parseDoubleArray(String input) {
        try {
            return Arrays.stream(input.trim().split(" "))
                    .mapToDouble(Double::parseDouble)
                    .toArray();
        } catch (NumberFormatException e) {
            System.out.println("введи целые числа");
            return null;
        }
    }

    private static int getIntegerInput(Scanner scanner) {
        while (true) {
            try {
                return scanner.nextInt();
            } catch (InputMismatchException e) {
                System.out.println("введи целое число");
                scanner.next();
            }
        }
    }

    private static void taskTestStacks(Scanner scanner) {
        System.out.println("тест GenericStack на основе массива:");
        GenericStack<Integer> arrayStack = new GenericStack<>();
        arrayStack.push(1);
        arrayStack.push(2);
        arrayStack.push(3);
        System.out.println("содержимое стека (array): " + arrayStack);
        System.out.println("верхний элемент (array): " + arrayStack.peek());
        System.out.println("извлеченный элемент (array): " + arrayStack.pop());
        System.out.println("содержимое стека после извлечения (array): " + arrayStack);

        System.out.println("\nтест GenericStackInheritance на основе ArrayList:");
        GenericStackInheritance<Integer> listStack = new GenericStackInheritance<>();
        listStack.push(1);
        listStack.push(2);
        listStack.push(3);
        System.out.println("содержимое стека (list): " + listStack);
        System.out.println("верхний элемент (list): " + listStack.peek());
        System.out.println("извлеченный элемент (list): " + listStack.pop());
        System.out.println("содержимое стека после извлечения (list): " + listStack);
    }
}
