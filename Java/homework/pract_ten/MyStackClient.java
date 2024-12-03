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
