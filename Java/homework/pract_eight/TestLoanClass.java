import java.util.Scanner;

public class TestLoanClass {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        double annualInterestRate = 0;
        int numberOfYears = 0;
        double loanAmount = 0;
        boolean validInput = false;

        while (!validInput) {
            try {
                System.out.print("введи годовую процентную ставку, например, 8.25: ");
                annualInterestRate = input.nextDouble();
                if (annualInterestRate <= 0) {
                    throw new IllegalArgumentException("год процентная ставка должна быть больше 0.");
                }
                validInput = true;
            } catch (IllegalArgumentException e) {
                System.out.println("ошибка: " + e.getMessage());
                input.nextLine();
            }
        }

        validInput = false;

        while (!validInput) {
            try {
                System.out.print("введи срок кредита в годах ");
                numberOfYears = input.nextInt();
                if (numberOfYears <= 0) {
                    throw new IllegalArgumentException("срок кредита должен быть больше 0");
                }
                validInput = true;
            } catch (IllegalArgumentException e) {
                System.out.println("ошибка = " + e.getMessage());
                input.nextLine();
            }
        }

        validInput = false;

        while (!validInput) {
            try {
                System.out.print("введи сумму кредита в руб, например, 120000.95: ");
                loanAmount = input.nextDouble();
                if (loanAmount <= 0) {
                    throw new IllegalArgumentException("сумма кредита должна быть больше 0");
                }
                validInput = true;
            } catch (IllegalArgumentException e) {
                System.out.println("словил ошибку = " + e.getMessage());
                input.nextLine();
            }
        }

        Loan loan = new Loan(annualInterestRate, numberOfYears, loanAmount);

        System.out.println("дата кредита = " + loan.getLoanDate().toString());
        System.out.println("ежемесячный платеж кредиту = "
                + (int)(loan.getMonthlyPayment() * 100) / 100.0 + " руб");
        System.out.println("общая стоимость кредита = "
                + (int)(loan.getTotalPayment() * 100) / 100.0 + " руб");

        input.close();
    }
}
