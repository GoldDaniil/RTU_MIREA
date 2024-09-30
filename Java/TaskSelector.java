package app;

import app2.Main2;
import vehicles.Car;
import vehicles.ElectricCar;
import java.util.Scanner;

public class TaskSelector {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input;

        while (true) {
            System.out.println("choose task: \n1 - first task,\n2 - second task,\n3 - third task");
            input = scanner.nextLine();

            if (input.equals("1")) {
                Car car = new Car("asdasd", "12345ABC", "gasoline");
                System.out.println("car information:");
                car.displayInfo();

                ElectricCar electricCar = new ElectricCar("sdfsdf", "98765XYZ", "electric", 100);
                System.out.println("electric carinformation:");
                electricCar.displayInfo();
            } else if (input.equals("2")) {
                Main2.main(null);
            } else if (input.equals("3") || input.equalsIgnoreCase("exit")) {
                System.out.println("exit:(");
                break;
            } else {
                System.out.println("error! enter again");
            }
        }
        scanner.close();
    }
}
