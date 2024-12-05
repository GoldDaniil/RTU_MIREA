public class OrderBuilder {
    private String mainDish;
    private String sideDish;
    private String drink;
    private String dessert;

    public OrderBuilder setMainDish(String mainDish) {
        this.mainDish = mainDish;
        return this;
    }

    public OrderBuilder setSideDish(String sideDish) {
        this.sideDish = sideDish;
        return this;
    }

    public OrderBuilder setDrink(String drink) {
        this.drink = drink;
        return this;
    }

    public OrderBuilder setDessert(String dessert) {
        this.dessert = dessert;
        return this;
    }

    public Order build() {
        return new Order(mainDish, sideDish, drink, dessert);
    }
}
