package cardgame;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public abstract class Hand implements Iterable<Card> {

    protected List<Card> inHand;
    protected int handValue;
    protected int count;

    public Hand() {
        inHand = new ArrayList<>();
        handValue = 0;
        count = 0;
    }

    protected abstract void calculateHandValue();
    public abstract Card add(Card card);

    public int getHandValue() {
        calculateHandValue();
        return handValue;
    }

    public List<Card> getInHand() {
        return inHand;
    }

    @Override
    public Iterator<Card> iterator() {
        return inHand.iterator();
    }

    public Card remove(Card card) {
        int index = inHand.indexOf(card);
        return inHand.remove(index);
    }

    public Card remove(int index) {
        handValue -= inHand.get(index).getValue();
        return remove(inHand.get(index));
    }

    public void removeAll() {
        handValue = 0;
        inHand.clear();
    }

    @Override
    public String toString() {
        String result = "";
        Card cardstr = null;
        Iterator<Card> scan = inHand.iterator();
        while (scan.hasNext()) {
            cardstr = scan.next();
            result += cardstr + "\n";
        }

        return result;
    }
}
