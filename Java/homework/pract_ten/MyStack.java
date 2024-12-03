import java.util.ArrayList;
import java.util.Scanner;

public class MyStack {
    private ArrayList<Object> list;

    public MyStack() {
        list = new ArrayList<>();
    }

    public boolean isEmpty() {
        return list.isEmpty();
    }

    public int getSize() {
        return list.size();
    }

    public Object peek() {
        if (!isEmpty()) {
            return list.get(list.size() - 1);
        }
        return null;
    }

    public Object pop() {
        if (!isEmpty()) {
            return list.remove(list.size() - 1);
        }
        return null;
    }

    public void push(Object o) {
        list.add(o);
    }

    public MyStack deepCopy() {
        MyStack copiedStack = new MyStack();
        copiedStack.list = new ArrayList<>(this.list);
        return copiedStack;
    }
}
