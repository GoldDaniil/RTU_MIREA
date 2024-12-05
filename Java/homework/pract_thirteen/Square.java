public class Square extends Shape {
    private int x, y, sideLength;

    public Square(int x, int y, int sideLength, DrawAPI drawAPI) {
        super(drawAPI);
        this.x = x;
        this.y = y;
        this.sideLength = sideLength;
    }

    @Override
    public void draw() {
        drawAPI.drawShape("square", x, y, sideLength);
    }

    @Override
    public String toString() {
        return "square at (" + x + ", " + y + "), side length: " + sideLength;
    }
}
