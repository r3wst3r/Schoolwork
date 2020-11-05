package bank;

import java.time.LocalDate;

public class AccountChecking extends AccountPersonal {

    private double overdraftLimit = 0.0;

    public AccountChecking(String custName, int id, double balance, double annualInterestRate, LocalDate dateCreated, double odLimit) {
        super(custName, id, balance, annualInterestRate, dateCreated);
        this.overdraftLimit = odLimit;
    }

    public AccountChecking(String custName, int id, double balance, double odLimit) {
        super(custName, id, balance);
        this.overdraftLimit = odLimit;
    }

    public double getOverdraftLimit() {
        return overdraftLimit;
    }

    public void setOverdraftLimit(double overdraftLimit) {
        this.overdraftLimit = overdraftLimit;
    }

    public double withdraw(double amount, String description) {
        return 0.0;
    }

    @Override
    public double withdraw(double amount){
        return 0.0;
    }

    @Override
    public String toString(){
        String theory = "ID: " + this.getId() + ", Balance: " + this.getBalance() +
                ", Annual Interest Rate: " + (this.getAnnualInterestRate() * 100) + "%, Date Created: " + this.getDateCreated() +
                "\n\tCustomer Name: " + this.getCustomerName() +
                "\n\tAccount Type: Checking, $" + this.getOverdraftLimit() + "\n";
        return theory;
    }
}
