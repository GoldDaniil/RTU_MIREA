public class MainTask2 {
    public static void launchTask2() {
        CarTask2 car1 = new CarTask2("Mazda 6", "A123BC 77", "Black", 2015);
        CarTask2 car2 = new CarTask2();  // конструктор по умолчанию
        CarTask2 car3 = new CarTask2("Honda Accord", 2019);  // конструктор с моделью и годом

        System.out.println(car1.to_String());
        System.out.println(car2.to_String());
        System.out.println(car3.to_String());

        System.out.println("car 1 age: " + car1.getCarAge() + "years");
        System.out.println("car 2 age: " + car2.getCarAge() + "years");
        System.out.println("car 3 age: " + car3.getCarAge() + "years");
    }
}

class CarTask2 {
    private String model;
    private String license;
    private String color;
    private int year;

    private static final int CURRENT_YEAR = 2024;

    public CarTask2(String model, String license, String color, int year) {
        this.model = model;
        this.license = license;
        this.color = color;
        this.year = year;
    }

    public CarTask2() {
        this.model = "unknown";
        this.license = "unknown";
        this.color = "unknown";
        this.year = 0;
    }

    public CarTask2(String model, int year) {
        this.model = model;
        this.license = "unknown";
        this.color = "unknown";
        this.year = year;
    }

    public String to_String() {
        return model + " " + license + " " + color + " " + year;
    }

    // геттеры и сеттеры для всех полей
    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getLicense() {
        return license;
    }

    public void setLicense(String license) {
        this.license = license;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public int getCarAge() {
        return CURRENT_YEAR - this.year;
    }
}
