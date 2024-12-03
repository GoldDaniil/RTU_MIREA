package vehicles;

public class Car {
    private String ownerName;
    private String insuranceNumber;
    protected String engineType;

    // конструктор
    public Car(String ownerName, String insuranceNumber, String engineType) {
        this.ownerName = ownerName;
        this.insuranceNumber = insuranceNumber;
        this.engineType = engineType;
    }

    // геттер
    public String getOwnerName() {
        return ownerName;
    }

    // cеттер
    public void setOwnerName(String ownerName) {
        this.ownerName = ownerName;
    }

    // геттер
    public String getInsuranceNumber() {
        return insuranceNumber;
    }

    // cеттер
    public void setInsuranceNumber(String insuranceNumber) {
        this.insuranceNumber = insuranceNumber;
    }

    // геттер 
    public String getEngineType() {
        return engineType;
    }

    // сеттер
    public void setEngineType(String engineType) {
        this.engineType = engineType;
    }

    public void displayInfo() {
        System.out.println("owner: " + ownerName);
        System.out.println("insurance: " + insuranceNumber);
        System.out.println("engine Type: " + engineType);
    }
}
