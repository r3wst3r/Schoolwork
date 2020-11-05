package cardgame;

import java.util.Iterator;

public class BlackjackHand extends Hand {

    @Override
    public Card add(Card card) {
        inHand.add(card);
        handValue += card.getValue();
        reduceHand();
        count++;

        return card;
    }

    @Override
    protected void calculateHandValue() {

    }

    private void reduceHand() {
        if (handValue > 21) {
            if (aceInHand())
                handValue -= 10;
        }
    }

    private boolean aceInHand() {
        boolean result = false;
        Card cardchk = null;
        Iterator<Card> scan = inHand.iterator();

        while (scan.hasNext() && !result) {
            cardchk = scan.next();
            if (cardchk.getValue() == 11) {
                cardchk.setValue(1);
                result = true;
            }
        }
        return result;
    }
}
