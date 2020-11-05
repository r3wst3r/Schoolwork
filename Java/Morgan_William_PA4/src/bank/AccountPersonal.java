package bank;

import java.time.LocalDate;
import java.util.ArrayList;

import java.util.List;

public class AccountPersonal extends Account {

    private String customerName;
    private List<Transaction> transactions;

    public AccountPersonal(String custName, int id, double balance, double annualInterestRate, LocalDate dateCreated) {
        super(id, balance, annualInterestRate, dateCreated);
        this.customerName = custName;
        this.transactions = new ArrayList<Transaction>();
    }

    public AccountPersonal(String custName, int id, double balance) {
        super(id, balance, 0.0, LocalDate.now());
        this.customerName = custName;
        this.transactions = new ArrayList<Transaction>();
    }

    public String getCustomerName() {
        return customerName;
    }

    public void setCustomerName(String customerName) {
        this.customerName = customerName;
    }

    public List<Transaction> getTransactions() {
        return transactions;
    }

    @Override
    public double withdraw(double amount) {
        return this.getBalance() - amount;
    }

    public double withdraw(double amount, String description) {
        return 0.0;
    }

    public double deposit(double amount) {
        return 0.0;
    }

    public double deposit(double amount, String description) {
        return 0.0;
    }

    @Override
    public String toString() {
        return "Account Personal toString() called";
    }
}
