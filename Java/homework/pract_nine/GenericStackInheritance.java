class GenericStackInheritance<E> extends ArrayList<E> {
    public int getSize() {
        return size();
    }

    public E peek() {
        if (isEmpty()) {
            throw new IllegalStateException("cтек пуст");
        }
        return get(size() - 1);
    }

    public void push(E o) {
        add(o);
    }

    public E pop() {
        if (isEmpty()) {
            throw new IllegalStateException("cтек пуст");
        }
        return remove(size() - 1);
    }

    @Override
    public String toString() {
        return "cтек: " + super.toString();
    }
}
