import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String[] months = {
                "январь", "февраль", "март", "апрель", "май",
                "июнь", "июль", "август", "сентябрь", "октябрь", "ноябрь", "декабрь"
        };
        int[] daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        Scanner scanner = new Scanner(System.in);

        while (true) {
            try {
                System.out.print("введи номер месяца (от 1 до 12): ");
                int month = scanner.nextInt();

                if (month < 1 || month > 12) {
                    System.out.println("недопустимое число = введите снова:");
                    continue;
                }

                if (month == 2) {
                    System.out.print("введи год: ");
                    int year = scanner.nextInt();
                    boolean isLeap = isLeapYear(year);
                    int days = isLeap ? 29 : 28;
                    String leapStatus = isLeap ? "является високосным" : "не является високосным";
                    System.out.println(months[month - 1] + " имеет " + days + " дней в " + year + " году, который " + leapStatus);
                } else {
                    System.out.println(months[month - 1] + " имеет " + daysInMonth[month - 1] + " дней.");
                }
                break;
            } catch (InputMismatchException e) {
                System.out.println("пожалуйста - введите целое число");
                scanner.nextLine();
            }
        }

        scanner.close();
    }

    public static boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
public class Loan {
    private double annualInterestRate;
    private int numberOfYears;
    private double loanAmount;
    private java.util.Date loanDate;

    public Loan() {
        this(2.5, 1, 1000);
    }

    public Loan(double annualInterestRate, int numberOfYears, double loanAmount) {
        if (annualInterestRate <= 0) {
            throw new IllegalArgumentException("Годовая процентная ставка должна быть больше 0.");
        }
        if (numberOfYears <= 0) {
            throw new IllegalArgumentException("Срок кредита должен быть больше 0.");
        }
        if (loanAmount <= 0) {
            throw new IllegalArgumentException("Сумма кредита должна быть больше 0.");
        }

        this.annualInterestRate = annualInterestRate;
        this.numberOfYears = numberOfYears;
        this.loanAmount = loanAmount;
        loanDate = new java.util.Date();
    }

    /** Возвращает годовую процентную ставку */
    public double getAnnualInterestRate() {
        return annualInterestRate;
    }

    /** Присваивает новую годовую процентную ставку */
    public void setAnnualInterestRate(double annualInterestRate) {
        if (annualInterestRate <= 0) {
            throw new IllegalArgumentException("Годовая процентная ставка должна быть больше 0.");
        }
        this.annualInterestRate = annualInterestRate;
    }

    /** Возвращает количество лет */
    public int getNumberOfYears() {
        return numberOfYears;
    }

    /** Присваивает новое количество лет */
    public void setNumberOfYears(int numberOfYears) {
        if (numberOfYears <= 0) {
            throw new IllegalArgumentException("Срок кредита должен быть больше 0.");
        }
        this.numberOfYears = numberOfYears;
    }

    /** Возвращает сумму кредита */
    public double getLoanAmount() {
        return loanAmount;
    }

    /** Присваивает новую сумму кредита */
    public void setLoanAmount(double loanAmount) {
        if (loanAmount <= 0) {
            throw new IllegalArgumentException("Сумма кредита должна быть больше 0.");
        }
        this.loanAmount = loanAmount;
    }

    /** Вычисляет и возвращает ежемесячный платеж по кредиту */
    public double getMonthlyPayment() {
        double monthlyInterestRate = annualInterestRate / 1200;
        double monthlyPayment = loanAmount * monthlyInterestRate /
                (1 - (1 / Math.pow(1 + monthlyInterestRate, numberOfYears * 12)));
        return monthlyPayment;
    }

    /** Вычисляет и возвращает общую стоимость кредита */
    public double getTotalPayment() {
        double totalPayment = getMonthlyPayment() * numberOfYears * 12;
        return totalPayment;
    }

    /** Возвращает дату взятия кредита */
    public java.util.Date getLoanDate() {
        return loanDate;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

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
