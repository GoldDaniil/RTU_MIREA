public class Circle extends Shape {
    private int x, y, radius;

    public Circle(int x, int y, int radius, DrawAPI drawAPI) {
        super(drawAPI);
        this.x = x;
        this.y = y;
        this.radius = radius;
    }

    @Override
    public void draw() {
        drawAPI.drawShape("circle", x, y, radius);
    }

    @Override
    public String toString() {
        return "circle at (" + x + ", " + y + "), radius: " + radius;
    }
}
