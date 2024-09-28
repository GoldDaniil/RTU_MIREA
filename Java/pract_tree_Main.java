package app;

import vehicles.Car;
import vehicles.ElectricCar;

public class Main {

    public static void main(String[] args) {
        Car car = new Car("John Doe", "12345ABC", "gasoline");
        System.out.println("car Information:");
        car.displayInfo();

        System.out.println();

        ElectricCar electricCar = new ElectricCar("Jane Doe", "98765XYZ", "electric", 85);
        System.out.println("electric car information:");
        electricCar.displayInfo();
    }
}
