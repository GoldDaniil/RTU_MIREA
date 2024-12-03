package fourteen;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class BeverageMaker extends JFrame {
    private JComboBox<String> beverageChoice;
    private JTextArea outputArea;
    private JButton prepareButton;
    private JCheckBox cinnamonBox, chocolateBox;

    public BeverageMaker() {
        setTitle("beverage maker");
        setSize(500, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(null);

        JLabel label = new JLabel("choose beverage:");
        label.setBounds(50, 20, 150, 30);
        add(label);

        beverageChoice = new JComboBox<>(new String[]{"tea", "coffee"});
        beverageChoice.setBounds(200, 20, 120, 30);
        add(beverageChoice);

        prepareButton = new JButton("prepare");
        prepareButton.setBounds(150, 70, 100, 30);
        add(prepareButton);

        cinnamonBox = new JCheckBox("add cinamon");
        cinnamonBox.setBounds(50, 110, 150, 30);
        add(cinnamonBox);

        chocolateBox = new JCheckBox("add chocolate");
        chocolateBox.setBounds(200, 110, 150, 30);
        add(chocolateBox);

        outputArea = new JTextArea();
        outputArea.setBounds(50, 160, 380, 180);
        outputArea.setEditable(false);
        add(outputArea);

        prepareButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String choice = (String) beverageChoice.getSelectedItem();
                Beverage beverage;
                if ("tea".equals(choice)) {
                    beverage = new Tea();
                } else {
                    beverage = new Coffee();
                }

                if (cinnamonBox.isSelected()) {
                    beverage.addExtraIngredient("cinnamon");
                }
                if (chocolateBox.isSelected()) {
                    beverage.addExtraIngredient("chocolate");
                }

                java.io.ByteArrayOutputStream baos = new java.io.ByteArrayOutputStream();
                java.io.PrintStream ps = new java.io.PrintStream(baos);
                java.io.PrintStream old = System.out;
                System.setOut(ps);

                beverage.prepare();

                System.out.flush();
                System.setOut(old);

                outputArea.setText(baos.toString() +
                        "\npreparation time: " + beverage.getPreparationTime() + " seconds");
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            BeverageMaker maker = new BeverageMaker();
            maker.setVisible(true);
        });
    }
}
