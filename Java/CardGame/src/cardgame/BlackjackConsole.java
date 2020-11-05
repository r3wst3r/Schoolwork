package cardgame;

import java.util.Scanner;

public class BlackjackConsole {

    private static final char HIT = 'H';
    private static final char STAND = 'S';
    private int dealerGameTotal;
    private int playerGameTotal;
    private Scanner keyboard;
    private Blackjack blackjack;
    private Hand playerHand;
    private Hand dealerHand;

    public BlackjackConsole() {
        playerHand = new BlackjackHand();
        dealerHand = new BlackjackHand();
        blackjack = new Blackjack(dealerHand, playerHand);

        dealerGameTotal = 0;
        playerGameTotal = 0;

        keyboard = new Scanner(System.in);
    }

    public void run() {
        int dealerTotal = 0;
        int playerTotal = 0;
        boolean done = false;
        String hitStandMsg = "Hit (H) OR Stand (S)";
        String playAgainMsg = "Play again? (Y/N)";
        String continueMsg = "Press Enter to Continue";
        String roundOverMsg = "";
        char choice;
        String outome;

        do {
            dealerTotal = 0;
            playerTotal = 0;

            blackjack.dealInitialCards();

            choice = displayBoard(hitStandMsg);
            while (choice == HIT && playerTotal < blackjack.BLACKJACK) {
                blackjack.hit(playerHand);
                if (blackjack.handValue(playerHand) < blackjack.BLACKJACK) {
                    choice = displayBoard(hitStandMsg);
                }
                else {
                    displayBoard(continueMsg);
                    choice = STAND;
                }
                playerTotal = blackjack.handValue(playerHand);
            }

            if (playerTotal <= blackjack.BLACKJACK) {
                dealerHand.getInHand().get(0).flip();
                displayBoard(continueMsg);

                while (blackjack.handValue(dealerHand) < blackjack.DEALER_STANDS) {
                    blackjack.hit(dealerHand);
                    displayBoard(continueMsg);
                }
            }

            // who won
            String outcome = blackjack.winner();
            if (outcome.equals("Win")) {
                playerGameTotal++;
                roundOverMsg = "Player Won! " + playAgainMsg;
            }
            else if (outcome.equals("Lose")) {
                dealerGameTotal++;
                roundOverMsg = "Dealer Won! " + playAgainMsg;
            }
            else {
                roundOverMsg = "Push " + playAgainMsg;
            }

            choice = displayBoard(roundOverMsg);

            if (choice != 'Y') {
                done = true;
            }
            else {
                dealerHand.removeAll();
                playerHand.removeAll();
                blackjack = new Blackjack(dealerHand, playerHand);
            }

        } while (!done);
    }

    private char displayBoard(String message) {
        String strLine = "---------------------------------------------------";
        System.out.println();
        System.out.println(strLine);
        System.out.println(String.format("Player: %7d || Dealer: %7d", playerGameTotal, dealerGameTotal));
        System.out.println(strLine);
        System.out.print("Dealer: ");
        for (Card c : dealerHand) {
            System.out.print(c + " ");
        }
        if (dealerHand.getInHand().get(0).isFaceUp()) {
            System.out.print(String.format(" Value: %3d", blackjack.handValue(dealerHand)));
        }
        for (int i = 0; i < 5; i++) {
            System.out.println();
        }
        System.out.print("Player: ");
        for (Card c : playerHand) {
            System.out.print(c + " ");
        }
        System.out.print(String.format("   Value: %3d", blackjack.handValue(playerHand)));
        System.out.println();
        System.out.println(strLine);
        System.out.println(message);
        System.out.println(strLine);
        String choice = keyboard.nextLine();
        if (choice.length() > 0) {
            return Character.toUpperCase(choice.charAt(0));
        }
        else
            return ' ';


    }

}
