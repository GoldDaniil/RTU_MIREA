Vehicle.java:

package vehicles;

public abstract class Vehicle {
    private String model;
    private String license;
    private String color;
    private int year;
    private String ownerName;
    private String insuranceNumber;
    protected String engineType;

    public Vehicle(String model, String license, String color, int year, String ownerName, String insuranceNumber) {
        this.model = model;
        this.license = license;
        this.color = color;
        this.year = year;
        this.ownerName = ownerName;
        this.insuranceNumber = insuranceNumber;
    }

    public abstract String vehicleType();

    public String getModel() { return model; }
    public void setModel(String model) { this.model = model; }

    public String getLicense() { return license; }
    public void setLicense(String license) { this.license = license; }

    public String getColor() { return color; }
    public void setColor(String color) { this.color = color; }

    public int getYear() { return year; }
    public void setYear(int year) { this.year = year; }

    public String getOwnerName() { return ownerName; }
    public void setOwnerName(String ownerName) { this.ownerName = ownerName; }

    public String getInsuranceNumber() { return insuranceNumber; }
    public void setInsuranceNumber(String insuranceNumber) { this.insuranceNumber = insuranceNumber; }

    public String getEngineType() { return engineType; }

    @Override
    public String toString() {
        return "\nvehicle type: " + vehicleType() +
                ", model: " + model +
                ", license: " + license +
                ", color: " + color +
                ", year: " + year +
                ", owner: " + ownerName +
                ", insurance: " + insuranceNumber;
    }
}




TestCar.java:

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







ElectricVehicle.java:

package vehicles;

public interface ElectricVehicle {
    int getBatteryCapacity();
    void setBatteryCapacity(int batteryCapacity);
}




ElectricCar.java:

package vehicles;

public class ElectricCar extends Car implements ElectricVehicle {
    private int batteryCapacity;

    public ElectricCar(String model, String license, String color, int year, String ownerName, String insuranceNumber, int batteryCapacity) {
        super(model, license, color, year, ownerName, insuranceNumber);
        this.batteryCapacity = batteryCapacity;
        this.engineType = "electric";
    }

    @Override
    public int getBatteryCapacity() {
        return batteryCapacity;
    }

    @Override
    public void setBatteryCapacity(int batteryCapacity) {
        this.batteryCapacity = batteryCapacity;
    }

    @Override
    public String vehicleType() {
        return "electric car";
    }

    @Override
    public String toString() {
        return super.toString() + ", battery capacity: " + batteryCapacity + " kWh";
    }
}




Car.java:

package vehicles;

public class Car extends Vehicle {

    public Car(String model, String license, String color, int year, String ownerName, String insuranceNumber) {
        super(model, license, color, year, ownerName, insuranceNumber);
        this.engineType = "combustion";
    }

    @Override
    public String vehicleType() {
        return "car";
    }
}
