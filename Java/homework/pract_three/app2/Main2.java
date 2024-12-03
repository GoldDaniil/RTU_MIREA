package app2;

import vehicles2.Car;
import vehicles2.ElectricCar;

public class Main2 {

    public static void main(String[] args) {
        Car car = new Car("alice", "98765QWERTY", "gasoline");
        System.out.println("car information:");
        car.displayInfo();

        System.out.println();

        ElectricCar electricCar = new ElectricCar("bob", "12345ZXCVB", 150);
        System.out.println("electric car information:");
        electricCar.displayInfo();

        System.out.println();

        System.out.println("accessing fields using methods:");
        System.out.println("car owner: " + car.getOwnerName());
        System.out.println("electric car owner: " + electricCar.getOwnerName());

        System.out.println("electric car engine type: " + electricCar.getEngineType());

        System.out.println("car insurance: " + car.getInsuranceNumber());
    }
}
