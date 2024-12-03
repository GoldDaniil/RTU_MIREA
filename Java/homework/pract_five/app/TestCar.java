package app;

import vehicles.ElectricCar;
import vehicles.Car;

public class TestCar {
    public static void main(String[] args) {
        Car car = new Car("asdasdas", "ABC123", "white", 2020, "asdasda", "123456789");
        System.out.println(car);

        car.setColor("black");
        System.out.println("updated car: " + car);

        ElectricCar electricCar = new ElectricCar("asdasdd", "XYZ789", "red", 2021, "asddsa", "987654321", 100);
        System.out.println(electricCar);

        electricCar.setBatteryCapacity(120);
        System.out.println("updated electric car: " + electricCar);
    }
}
