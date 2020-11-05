package bank;

import java.time.LocalDate;

public class AccountSaving extends AccountPersonal {

    public AccountSaving(String custName, int id, double balance, double annualInterestRate, LocalDate dateCreated) {
        super(custName, id, balance, annualInterestRate, dateCreated);
    }

    public AccountSaving(String custName, int id, double balance) {
        super(custName, id, balance);
    }

    public double withdraw(double amount, String description) {
        return 0.0;
    }

    @Override
    public double withdraw(double amount) {
        return 0.0;
    }

    @Override
    public String toString(){
        String theory = "ID: " + this.getId() + ", Balance: " + this.getBalance() +
                ", Annual Interest Rate: " + (this.getAnnualInterestRate() * 100) + ", Date Created: " + this.getDateCreated() +
                "\n\tCustomer Name: " + this.getCustomerName() +
                "\n\tAccount Type: Saving\n";
        return theory;
    }

}
