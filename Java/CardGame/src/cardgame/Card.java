package cardgame;

import javax.swing.ImageIcon;

public class Card {

    private Suit suit;
    private Face face;
    private boolean faceUp;
    private int value;
    private ImageIcon cardPic;

    public Card(Face face, Suit suit, int value, boolean faceUp,
                ImageIcon cardPic){
        this.face = face;
        this.suit = suit;
        this.value = value;
        this.faceUp = faceUp;
        this.cardPic = cardPic;
    } // End of Constructor

    public Card(Face face, Suit suit, int value) {
        this(face, suit, value, false, null);
    }

    public Card() {
        this(null, null, 0, false, null);
    }

    public void flip() {
        faceUp = !faceUp;
    }

    public boolean isFaceUp() {
        return faceUp;
    }

    public void setFaceUp(boolean faceUp) {
        this.faceUp = faceUp;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public Suit getSuit() {
        return suit;
    }

    public Face getFace() {
        return face;
    }

    public ImageIcon getCardPic() {
        return cardPic;
    }

    @Override
    public String toString() {
        if (faceUp)
            return face.toString() + suit.toString();
        else return "XX";
    }

} //
