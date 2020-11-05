package cardgame;

public enum Suit {

    Heart('\u2661', "h"),
    Diamond('\u2662', "d"),
    Spade('\u2660', "s"),
    Club('\u2663', "c");


    private char symbol;
    private String value;

    Suit(char symbol, String value) {
        this.symbol = symbol;
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "" + symbol;
    }


}
