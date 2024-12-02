package third;

import java.util.ArrayList;
import java.util.List;

public class ShapeManager {
    private List<Shape> shapes = new ArrayList<>();

    public void addShape(Shape shape) {
        shapes.add(shape);
        System.out.println("shape added: " + shape);
    }

    public void eraseShape(Shape shape) {
        if (shapes.remove(shape)) {
            System.out.println("shape erased: " + shape);
        } else {
            System.out.println("shape not found");
        }
    }

    public void displayAllShapes() {
        System.out.println("current shapes:");
        for (Shape shape : shapes) {
            System.out.println(shape);
        }
    }

    public int getShapeCount() {
        return shapes.size();
    }
}
