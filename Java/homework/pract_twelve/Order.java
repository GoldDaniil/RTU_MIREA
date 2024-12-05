public class Order {
    private String mainDish;
    private String sideDish;
    private String drink;
    private String dessert;

    public Order(String mainDish, String sideDish, String drink, String dessert) {
        this.mainDish = mainDish;
        this.sideDish = sideDish;
        this.drink = drink;
        this.dessert = dessert;
    }

    public String getMainDish() {
        return mainDish;
    }

    public String getSideDish() {
        return sideDish;
    }

    public String getDrink() {
        return drink;
    }

    public String getDessert() {
        return dessert;
    }

    @Override
    public String toString() {
        return "order details:\n" +
                "main dish: " + mainDish + "\n" +
                "side dish: " + sideDish + "\n" +
                "drink: " + drink + "\n" +
                "dessert: " + dessert;
    }
}
