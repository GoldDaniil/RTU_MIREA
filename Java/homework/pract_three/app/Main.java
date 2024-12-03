package app;

import vehicles.Car;
import vehicles.ElectricCar;

public class Main {

    public static void main(String[] args) {
        Car car = new Car("john", "12345ABC", "gasoline");
        System.out.println("car information:");
        car.displayInfo();

        System.out.println();

        ElectricCar electricCar = new ElectricCar("jane", "98765XYZ", "electric", 85);
        System.out.println("electric car information:");
        electricCar.displayInfo();
    }
}
