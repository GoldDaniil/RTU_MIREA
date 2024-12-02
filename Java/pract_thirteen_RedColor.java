package third;

public class RedColor implements DrawAPI {
    @Override
    public void drawShape(String shapeType, int x, int y, int size) {
        System.out.println("drawing " + shapeType + " in red at (" + x + ", " + y + ") with size " + size);
    }
}
