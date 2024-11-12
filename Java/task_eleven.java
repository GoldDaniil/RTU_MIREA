import java.util.ArrayList;
import java.util.Scanner;

public class TaskEleven {
    private ArrayList<Object> list;

    public TaskEleven() {
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
            return list.get(0);
        }
        return null;
    }

    public Object dequeue() {
        if (!isEmpty()) {
            return list.remove(0);
        }
        return null;
    }

    public void enqueue(Object o) {
        list.add(o);
    }
}

class TaskElevenClient {
    public static void main(String[] args) {
        TaskEleven queue = new TaskEleven();
        Scanner scanner = new Scanner(System.in);

        System.out.println("введи пять строк:");
        for (int i = 0; i < 5; i++) {
            String input = scanner.nextLine();
            queue.enqueue(input);
        }

        System.out.println("строки:\n");
        while (!queue.isEmpty()) {
            System.out.println(queue.dequeue());
        }

        scanner.close();
    }
}
