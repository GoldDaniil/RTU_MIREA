package fourteen;

public class Tea extends Beverage {
    @Override
    protected void brew() {
        System.out.println("steeping the tea");
    }

    @Override
    protected void addExtras() {
        if (!getExtras().isEmpty()) {
            System.out.println("adding extras: " + String.join(", ", getExtras()));
        } else {
            System.out.println("adding lemon");
        }
    }
}

