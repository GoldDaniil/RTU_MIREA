package fourteen;

public class Coffee extends Beverage {
    @Override
    protected void brew() {
        System.out.println("brewing the coffee");
    }

    @Override
    protected void addExtras() {
        if (!getExtras().isEmpty()) {
            System.out.println("adding extras: " + String.join(", ", getExtras()));
        } else {
            System.out.println("adding sugar and milk");
        }
    }
}
