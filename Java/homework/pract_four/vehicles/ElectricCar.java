package vehicles;

public class ElectricCar extends Car {
    private int batteryCapacity;

    public ElectricCar(String model, String license, String color, int year, String ownerName, String insuranceNumber, int batteryCapacity) {
        super(model, license, color, year, ownerName, insuranceNumber);
        this.batteryCapacity = batteryCapacity;
        this.engineType = "electric";
    }

    public int getBatteryCapacity() { return batteryCapacity; }
    public void setBatteryCapacity(int batteryCapacity) { this.batteryCapacity = batteryCapacity; }

    @Override
    public String vehicleType() {
        return "electric car";
    }

    @Override
    public String toString() {
        return super.toString() + ", battery capacity: " + batteryCapacity + " kWh";
    }
}
