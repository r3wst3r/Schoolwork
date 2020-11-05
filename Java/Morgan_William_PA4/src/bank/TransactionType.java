package bank;

public enum TransactionType {

    Deposit ("D"),
    Withdrawal ("W");

    private String symbol;

    TransactionType(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String toString() {
        return symbol;
    }
}