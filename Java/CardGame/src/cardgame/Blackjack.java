package cardgame;

public class Blackjack {

    public static final int DEALER_STANDS = 17;
    public static final int BLACKJACK = 21;

    private Hand dealer;        // to hold the dealers hand
    private Hand player;        // to hold the players hand
    private Deck deck;          // a set of cards

    public Blackjack(Hand dealer, Hand player) {
        this.dealer = dealer;
        this.player = player;
        deck = new Deck();
        deck.shuffle();
    }

    public void dealInitialCards() {
        dealer.add(deck.deal());
        dealer.add(deck.deal(true));
        player.add(deck.deal(true));
        player.add(deck.deal(true));
    }

    public Card hit(Hand who) {

        return who.add(deck.deal(true));
    }

    public int handValue(Hand who) {
        return who.getHandValue();
    }

    public void discard(Hand who, Card card) {
        who.remove(card);
    }

    public boolean isBlackjack(Hand who) {
        return who.getHandValue() == BLACKJACK;
    }

    public boolean isBust(Hand who) {
        return who.getHandValue() > BLACKJACK;
    }

    public Hand dealerPlays() {

        while (dealer.getHandValue() < DEALER_STANDS) {
            dealer.add(deck.deal());
        }

        return dealer;
    }

    public String winner() {
        String result = "";

        if (player.getHandValue() < dealer.getHandValue()
                && !isBust(dealer)) {
            result = "Lose";
        }
        else if (isBust(player)) {
            result = "Lose";
        }
        else if ((player.getHandValue() == dealer.getHandValue())
                && !isBust(dealer)) {
            result = "Push";
        }
        else {
            result = "Win";
        }

        return result;
    }

}
