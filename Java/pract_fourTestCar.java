package app;

import vehicles.ElectricCar;
import vehicles.Vehicle;
import vehicles.Car;

public class TestCar {
    public static void main(String[] args) {
        Vehicle car = new Car("toyota", "ABC123", "white", 2020, "asdsad", "123456789");
        System.out.println(car);

        car.setColor("black");
        System.out.println("updated Car: " + car);

        ElectricCar electricCar = new ElectricCar("tesla", "XYZ789", "red", 2021, "asg df", "987654321", 100);
        System.out.println(electricCar);

        electricCar.setBatteryCapacity(120);
        System.out.println("updated electric car: " + electricCar);
    }
}
