package cardgame;

public enum Face {

    // Values
    Ace(1, 'A', "Ace"),
    Two(2, '2', "2"),
    Three(3, '3', "3"),
    Four(4, '4', "4"),
    Five(5, '5', "5"),
    Six(6, '6', "6"),
    Seven(7, '7', "7"),
    Eight(8, '8', "8"),
    Nine(9, '9', "9"),
    Ten(10, 'T', "10"),
    Jack(11, 'J', "Jack"),
    Queen(12, 'Q', "Queen"),
    King(13, 'K', "King");

    private int value;
    private char symbol;
    private String name;

    Face(int value, char symbol, String name) {
        this.value = value;
        this.symbol = symbol;
        this.name = name;
    }

    public int getValue() {
        return value;
    }

    public String getName(){
        return name;
    }

    @Override
    public String toString() {
        return "" + symbol;
    }

}   // End of Class
