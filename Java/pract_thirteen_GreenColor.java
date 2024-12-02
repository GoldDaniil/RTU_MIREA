package third;

public class GreenColor implements DrawAPI {
    @Override
    public void drawShape(String shapeType, int x, int y, int size) {
        System.out.println("drawing " + shapeType + " in green at (" + x + ", " + y + ") with size " + size);
    }
}
