class MaxElementFinder {
    public static Circle findMax(Circle[] circles) {
        if (circles == null || circles.length == 0) {
            return null;
        }
        Circle max = circles[0];
        for (Circle circle : circles) {
            if (circle.compareTo(max) > 0) {
                max = circle;
            }
        }
        return max;
    }
}
