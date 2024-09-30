package vehicles2;

public class ElectricCar extends Car {
    private int batteryCapacity;

    public ElectricCar(String ownerName, String insuranceNumber, int batteryCapacity) {
        super(ownerName, insuranceNumber, "electric");
        this.batteryCapacity = batteryCapacity;
    }

    public int getBatteryCapacity() {
        return batteryCapacity;
    }

    public void setBatteryCapacity(int batteryCapacity) {
        this.batteryCapacity = batteryCapacity;
    }

    @Override
    public void displayInfo() {
        super.displayInfo();
        System.out.println("battery Capacity: " + batteryCapacity + " kWh");
    }
}
