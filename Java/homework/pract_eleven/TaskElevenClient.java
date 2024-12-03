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
