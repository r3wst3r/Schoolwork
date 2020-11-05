package bank;

import java.text.NumberFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class Transaction {

    private String id;
    private static int idExt = 1;
    private LocalDate date;
    private TransactionType type;
    private double amount;
    private double balance;
    private String description;

    public Transaction(TransactionType type, double amount, double balance, String description) {
        this.type = type;
        this.amount = amount;
        this.balance = balance;
        this.description = description;
        this.date = LocalDate.now();
        this.id = DateTimeFormatter.ofPattern("yyyyMMdd").format(this.date) + "-" + idExt;
        idExt++;
    }

    public LocalDate getDate() {
        return date;
    }

    public TransactionType getType() {
        return type;
    }

    public double getAmount() {
        return amount;
    }

    public double getBalance() {
        return balance;
    }

    public String getDescription() {
        return description;
    }

    @Override
    public String toString() {
        NumberFormat nfc = NumberFormat.getCurrencyInstance();
        return id + " " + type + " " + DateTimeFormatter.ofPattern("MM/dd/yyyy").format(date) + " " + nfc.format(amount);
    }
}