package bank;

import java.text.NumberFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class Account {
    private int id;
    private double balance;
    private double annualInterestRate;
    private LocalDate dateCreated;

    public Account(int id, double balance, double annualInterestRate, LocalDate dateCreated) {
        this.id = id;
        this.balance = balance;
        this.annualInterestRate = annualInterestRate;
        this.dateCreated = dateCreated;
    }

    public Account(int id, double balance) {
        this(id, balance, 0.0, LocalDate.now());
    }

    public int getId() {
        return id;
    }

    public double getBalance() {
        return balance;
    }

    public double getAnnualInterestRate() {
        return annualInterestRate;
    }

    public LocalDate getDateCreated() {
        return dateCreated;
    }

    public void setBalance(double balance) {
        this.balance = balance;
    }

    public void setAnnualInterestRate(double annualInterestRate) {
        this.annualInterestRate = annualInterestRate;
    }

    public double getMonthlyInterestRate() {
        return annualInterestRate / 12.0;
    }

    public double getMonthlyInterest() {
        return getMonthlyInterestRate() * balance;
    }

    public double withdraw(double amount) {
        return (balance -= amount);
    }

    public double deposit(double amount) {
        return (balance += amount);
    }

    @Override
    public String toString() {
        NumberFormat nfp = NumberFormat.getPercentInstance();
        nfp.setMinimumFractionDigits(2);
        NumberFormat nfc = NumberFormat.getCurrencyInstance();
        return "ID: " + id + ", Balance: " + nfc.format(balance) + ", Annual Interest Rate: "
                + nfp.format(annualInterestRate) + ", Date Created: " + DateTimeFormatter.ofPattern("MM/dd/yyyy").format(dateCreated);
    }
}