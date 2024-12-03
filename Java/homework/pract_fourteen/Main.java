public class Main {
    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(() -> {
            BeverageMaker maker = new BeverageMaker();
            maker.setVisible(true);
        });
    }
}

