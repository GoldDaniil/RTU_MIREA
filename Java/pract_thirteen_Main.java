package third;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        ShapeManager manager = new ShapeManager();
        Scanner scanner = new Scanner(System.in);

        System.out.println("shape drawer");

        while (true) {
            System.out.println("\noptions:");
            System.out.println("1 - draw circle");
            System.out.println("2 - draw square");
            System.out.println("3 - erase shape");
            System.out.println("4 - display all shapes");
            System.out.println("5   display shape count");
            System.out.println("6 - exit");

            System.out.print("enter choice: ");
            int choice = scanner.nextInt();

            switch (choice) {
                case 1 -> {
                    Shape circle = createShape(scanner, "circle");
                    manager.addShape(circle);
                    circle.draw();
                }
                case 2 -> {
                    Shape square = createShape(scanner, "square");
                    manager.addShape(square);
                    square.draw();
                }
                case 3 -> {
                    System.out.println("error- use display");
                }
                case 4 -> manager.displayAllShapes();
                case 5 -> System.out.println("total shapes: " + manager.getShapeCount());
                case 6 -> {
                    System.out.println(":(");
                    scanner.close();
                    return;
                }
                default -> System.out.println("error choice");
            }
        }
    }

    private static Shape createShape(Scanner scanner, String shapeType) {
        System.out.println("choose color:");
        System.out.println("1 - red");
        System.out.println("2 - green");
        System.out.println("3 - blue");

        int colorChoice = scanner.nextInt();
        DrawAPI drawAPI = switch (colorChoice) {
            case 1 -> new RedColor();
            case 2 -> new GreenColor();
            case 3 -> new BlueColor();
            default -> {
                System.out.println("error choice - def to red");
                yield new RedColor();
            }
        };

        if ("circle".equalsIgnoreCase(shapeType)) {
            System.out.print("enter x-coordinate: ");
            int x = scanner.nextInt();
            System.out.print("enter y-coordinate: ");
            int y = scanner.nextInt();
            System.out.print("enter radius: ");
            int radius = scanner.nextInt();
            return new Circle(x, y, radius, drawAPI);
        } else {
            System.out.print("enter x-coordinate: ");
            int x = scanner.nextInt();
            System.out.print("enter y-coordinate: ");
            int y = scanner.nextInt();
            System.out.print("enter side length: ");
            int sideLength = scanner.nextInt();
            return new Square(x, y, sideLength, drawAPI);
        }
    }
}
