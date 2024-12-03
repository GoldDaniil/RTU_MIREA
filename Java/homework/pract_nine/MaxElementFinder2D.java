class MaxElementFinder2D {
    public static <T extends Comparable<T>> T findMax(T[][] array) {
        if (array == null || array.length == 0) {
            return null;
        }
        T max = array[0][0];
        for (T[] row : array) {
            for (T element : row) {
                if (element.compareTo(max) > 0) {
                    max = element;
                }
            }
        }
        return max;
    }
}
