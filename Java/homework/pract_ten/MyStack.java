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

class MyStackClient {
    public static void main(String[] args) {
        MyStack stack = new MyStack();
        Scanner scanner = new Scanner(System.in);

        System.out.println("введи пять строк:");
        for (int i = 0; i < 5; i++) {
            String input = scanner.nextLine();
            stack.push(input);
        }

        System.out.println("строки в обратном порядке:");
        while (!stack.isEmpty()) {
            System.out.println(stack.pop());
        }

        scanner.close();
    }
}
