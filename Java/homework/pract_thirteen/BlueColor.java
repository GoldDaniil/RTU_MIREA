public class BlueColor implements DrawAPI {
    @Override
    public void drawShape(String shapeType, int x, int y, int size) {
        System.out.println("drawing " + shapeType + " in blue at (" + x + ", " + y + ") with size " + size);
    }
}
