import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

public class OrderAppGUI extends JFrame {
    private JComboBox<String> mainDishBox;
    private JComboBox<String> sideDishBox;
    private JComboBox<String> drinkBox;
    private JComboBox<String> dessertBox;

    private JTextArea orderDisplay;

    private String[] defaultMainDishes = {"pizza", "burger", "pasta"};
    private String[] defaultSideDishes = {"fries", "salad", "rice"};
    private String[] defaultDrinks = {"water", "soda", "juice"};
    private String[] defaultDesserts = {"ice cream", "cake", "fruit"};

    public OrderAppGUI() {
        setTitle("restaurant order builder");
        setSize(500, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        int userChoice = JOptionPane.showOptionDialog(
                this,
                "как хотите задать данные для заказа?",
                "выбор способа задания данных",
                JOptionPane.YES_NO_CANCEL_OPTION,
                JOptionPane.QUESTION_MESSAGE,
                null,
                new Object[]{"случайный выбор", "ввод вручную", "использовать предопределенные"},
                "случайный выбор"
        );

        if (userChoice == 0) {
            generateRandomOrder();
            displayConfirmation("заказ создан случайным образом");
        } else if (userChoice == 1) {
            createManualInputPanel();
        } else {
            createDefaultSelectionPanel();
        }
    }

    private void generateRandomOrder() {
        Random random = new Random();
        Order order = new OrderBuilder()
                .setMainDish(defaultMainDishes[random.nextInt(defaultMainDishes.length)])
                .setSideDish(defaultSideDishes[random.nextInt(defaultSideDishes.length)])
                .setDrink(defaultDrinks[random.nextInt(defaultDrinks.length)])
                .setDessert(defaultDesserts[random.nextInt(defaultDesserts.length)])
                .build();
        displayOrder(order);
    }

    private void createManualInputPanel() {
        JPanel inputPanel = new JPanel(new GridLayout(4, 2, 5, 5));

        JTextField mainDishField = new JTextField();
        JTextField sideDishField = new JTextField();
        JTextField drinkField = new JTextField();
        JTextField dessertField = new JTextField();

        inputPanel.add(new JLabel("введите основное блюдо:"));
        inputPanel.add(mainDishField);
        inputPanel.add(new JLabel("введите гарнир:"));
        inputPanel.add(sideDishField);
        inputPanel.add(new JLabel("введите напиток:"));
        inputPanel.add(drinkField);
        inputPanel.add(new JLabel("введите десерт:"));
        inputPanel.add(dessertField);

        int result = JOptionPane.showConfirmDialog(this, inputPanel, "ввод данных", JOptionPane.OK_CANCEL_OPTION);
        if (result == JOptionPane.OK_OPTION) {
            Order order = new OrderBuilder()
                    .setMainDish(mainDishField.getText())
                    .setSideDish(sideDishField.getText())
                    .setDrink(drinkField.getText())
                    .setDessert(dessertField.getText())
                    .build();
            displayOrder(order);
            displayConfirmation("заказ успешно создан");
        } else {
            displayConfirmation("отменен ввод данных");
        }
    }

    private void createDefaultSelectionPanel() {
        JPanel inputPanel = new JPanel(new GridLayout(4, 2, 5, 5));

        mainDishBox = new JComboBox<>(defaultMainDishes);
        sideDishBox = new JComboBox<>(defaultSideDishes);
        drinkBox = new JComboBox<>(defaultDrinks);
        dessertBox = new JComboBox<>(defaultDesserts);

        inputPanel.add(new JLabel("основное блюдо:"));
        inputPanel.add(mainDishBox);
        inputPanel.add(new JLabel("гарнир:"));
        inputPanel.add(sideDishBox);
        inputPanel.add(new JLabel("напиток:"));
        inputPanel.add(drinkBox);
        inputPanel.add(new JLabel("десерт:"));
        inputPanel.add(dessertBox);

        int result = JOptionPane.showConfirmDialog(this, inputPanel, "выбор данных", JOptionPane.OK_CANCEL_OPTION);
        if (result == JOptionPane.OK_OPTION) {
            Order order = new OrderBuilder()
                    .setMainDish((String) mainDishBox.getSelectedItem())
                    .setSideDish((String) sideDishBox.getSelectedItem())
                    .setDrink((String) drinkBox.getSelectedItem())
                    .setDessert((String) dessertBox.getSelectedItem())
                    .build();
            displayOrder(order);
            displayConfirmation("заказ успешно создан");
        } else {
            displayConfirmation("отменен выбор данных");
        }
    }

    private void displayOrder(Order order) {
        if (orderDisplay == null) {
            orderDisplay = new JTextArea();
            orderDisplay.setEditable(false);
            add(new JScrollPane(orderDisplay), BorderLayout.CENTER);
        }
        orderDisplay.setText(order.toString());
    }

    private void displayConfirmation(String message) {
        JOptionPane.showMessageDialog(this, message, "информация", JOptionPane.INFORMATION_MESSAGE);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            OrderAppGUI app = new OrderAppGUI();
            app.setVisible(true);
        });
    }
}
