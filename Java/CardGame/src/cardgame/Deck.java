package cardgame;

import javax.swing.ImageIcon;
import java.util.Random;

public class Deck {

    private Card[] cards;
    private int nextCard;
    // This is game specific
    private int[] cardValues = {0, 11, 2, 3, 4, 5, 6, 7, 8, 9,
                                10, 10, 10,10};
    private ImageIcon cardBackImg;

    public Deck() {
        cards = new Card[52];
        nextCard = 0;
        int index = 0;
        cardBackImg = null;

        for (Suit s : Suit.values()) {
            for (Face f : Face.values()) {
                String imageName = "images/" + f.getName() +
                        s.getValue() + ".jpg";
                cards[index] = new Card(f, s, cardValues[f.getValue()],
                        false, new ImageIcon(imageName));
                index++;
            }
        }
    }

    public Deck(String imageName) {
        this();
        cardBackImg = new ImageIcon(imageName);
    }

    public void setCardBackImg(String imageName) {
        cardBackImg =new ImageIcon(imageName);
    }

    public ImageIcon getCardBackImg() {
        return cardBackImg;
    }

    public void shuffle() {
        Random r = new Random();

        for (int i = cards.length - 1; i > 0; i--) {
            int j = r.nextInt(i + 1);   // get a random index from 0 to i.

            // Swap j with i
            Card temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
        }
    }

    public void reset() {
        for (Card card : cards) {
            card.setValue(cardValues[card.getFace().getValue()]);
            card.setFaceUp(false);
        }
        nextCard = 0;
        shuffle();
    }

    public Card deal() {
        return deal(false);
    }

    public Card deal(boolean faceUp) {
        if (nextCard > cards.length) {
            throw new IndexOutOfBoundsException();
        }

        Card c = cards[nextCard];
        nextCard++;
        c.setFaceUp(faceUp);
        return c;
    }

    public boolean isEmpty() {
        return nextCard == 52;
    }

    public int getNextCard() {
        return nextCard + 1;
    }

    @Override
    public String toString() {
        String result = "";
        int count = 0;
        for (Card card : cards) {
            card.flip();
            result += card.toString() + " ";
            card.flip();
            count++;
            if (count == 13) {
                result += "\n";
                count = 0;
            }
        }
        return result;

    } // end of function


}
