package fourteen;

import java.util.ArrayList;
import java.util.List;

public abstract class Beverage {
    private List<String> extras = new ArrayList<>();
    private int preparationTime;

    public final void prepare() {
        long startTime = System.currentTimeMillis();

        boilWater();
        brew();
        pourInCup();
        if (addCondiments()) {
            addExtras();
        }

        long endTime = System.currentTimeMillis();
        preparationTime = (int) ((endTime - startTime) / 1000);
    }

    private void boilWater() {
        System.out.println("boiling water");
    }

    private void pourInCup() {
        System.out.println("pouring into cup");
    }

    protected abstract void brew();
    protected abstract void addExtras();

    protected boolean addCondiments() {
        return true;
    }

    public void addExtraIngredient(String extra) {
        extras.add(extra);
    }

    public List<String> getExtras() {
        return extras;
    }

    public int getPreparationTime() {
        return preparationTime;
    }
}
