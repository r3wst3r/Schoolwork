package cardgame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;

public class BlackjackGUI extends JPanel {

    private JPanel topPanel = new JPanel();
    private JPanel dealerCardPanel = new JPanel();
    private JPanel playerCardPanel = new JPanel();
    //private JTextPane winLoseBox = new JTextPane();
    private JLabel winLoseLabel = new JLabel();
    private JButton hitButton = new JButton();
    private JButton dealButton = new JButton();
    private JButton stayButton = new JButton();
    private JButton playAgainButton = new JButton();
    private JLabel dealerLabel = new JLabel();
    private JLabel playerLabel = new JLabel();
    private JLabel dealerScoreLabel = new JLabel();
    private JLabel playerScoreLabel = new JLabel();
    private JPanel scorePanel = new JPanel();

    private Hand dealer = new BlackjackHand();   // to hold the dealer's hand
    private Hand player = new BlackjackHand();   // to hold the player's hand
    private Blackjack game = new Blackjack(dealer, player);

    private JLabel playerCard1;
    private JLabel playerCard2;
    private JLabel playerCardHit;
    private JLabel dealerCard0;
    private JLabel dealerCard1;
    private JLabel dealerCard2;
    private JLabel dealerCardHit;

    private int dealerGameTotal;
    private int playerGameTotal;

    public BlackjackGUI() {
        //Blackjack game = new Blackjack(dealer, player);
        System.out.println(game);

        topPanel.setBackground(new Color(0, 122, 0));
        dealerCardPanel.setBackground(new Color(0, 122, 0));
        playerCardPanel.setBackground(new Color(0, 122, 0));

        topPanel.setLayout(new FlowLayout());
        winLoseLabel.setText(" ");
        winLoseLabel.setFont(new Font("Helvectica Bold", 1, 20));
        dealButton.setText("  Deal");
        dealButton.addActionListener(new dealButton());
        hitButton.setText("  Hit");
        hitButton.addActionListener(new hitButton());
        hitButton.setEnabled(false);
        stayButton.setText("  Stand");
        stayButton.addActionListener(new stayButton());
        stayButton.setEnabled(false);
        playAgainButton.setText("  Play Again");
        playAgainButton.addActionListener(new playAgainButton());
        playAgainButton.setEnabled(false);

        dealerLabel.setText("  Dealer:  ");
        playerLabel.setText("  Player:  ");

        scorePanel.setLayout(new BoxLayout(scorePanel, BoxLayout.Y_AXIS));
        scorePanel.setAlignmentY(Component.CENTER_ALIGNMENT);
        scorePanel.setBackground(new Color(0, 122, 0));
        dealerScoreLabel.setText("  Dealer: 0");
        playerScoreLabel.setText("  Player: 0");
        scorePanel.add(dealerScoreLabel);
        scorePanel.add(playerScoreLabel);

        topPanel.add(winLoseLabel);
        topPanel.add(dealButton);
        topPanel.add(hitButton);
        topPanel.add(stayButton);
        topPanel.add(playAgainButton);
        playerCardPanel.add(playerLabel);
        dealerCardPanel.add(dealerLabel);

        setLayout(new BorderLayout());
        add(topPanel, BorderLayout.NORTH);
        add(dealerCardPanel, BorderLayout.CENTER);
        add(playerCardPanel, BorderLayout.SOUTH);
        add(scorePanel, BorderLayout.WEST);

        dealerGameTotal = 0;
        playerGameTotal = 0;
    }

    public void display() {
        JFrame frame = new JFrame("BlackJack");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(this);
        frame.setPreferredSize(new Dimension(700, 500));

        // Display the window
        frame.pack();
        frame.setVisible(true);
    }

    void updateScore(String outcome) {
        if (outcome.equals("Win")) {
            playerGameTotal++;
            playerScoreLabel.setText("  Player: " + playerGameTotal);
        } else if (outcome.equals("Lose")) {
            dealerGameTotal++;
            dealerScoreLabel.setText("  Dealer: " + dealerGameTotal);
        }
    }

    class dealButton implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            dealerCardPanel.add(dealerLabel);
            playerCardPanel.add(playerLabel);

            dealerCard0 = new JLabel(new ImageIcon("images/BlueCardBack.jpg"));
            System.out.println(game);
            game.dealInitialCards();

            Card dealerCard = null;
            Iterator<Card> dealerScan = dealer.iterator();
            int count = 0;
            while (dealerScan.hasNext()) {
                dealerCard = dealerScan.next();
                if (count == 0)
                    dealerCard1 = new JLabel(dealerCard.getCardPic());
                else
                    dealerCard2 = new JLabel(dealerCard.getCardPic());

                count++;
            }

            Iterator<Card> playerScan = player.iterator();
            count = 0;
            while (playerScan.hasNext()) {
                Card playerCard = playerScan.next();
                if (count == 0)
                    playerCard1 = new JLabel(playerCard.getCardPic());
                else
                    playerCard2 = new JLabel(playerCard.getCardPic());

                count++;
            }

            dealerCardPanel.add(dealerCard0);
            dealerCardPanel.add(dealerCard2);

            playerCardPanel.add(playerCard1);
            playerCardPanel.add(playerCard2);

            dealerLabel.setText("  Dealer:  " + dealerCard.getValue());
            playerLabel.setText("  Player:  " + game.handValue(player));

            hitButton.setEnabled(true);
            stayButton.setEnabled(true);
            dealButton.setEnabled(false);

            if (game.isBlackjack(player)) {
                hitButton.setEnabled(false);
                stayButton.setEnabled(false);
                dealButton.setEnabled(false);
                playAgainButton.setEnabled(true);
                winLoseLabel.setText("BlackJack");
                updateScore("Win");
            }

            add(dealerCardPanel, BorderLayout.CENTER);
            add(playerCardPanel, BorderLayout.SOUTH);
        }
    }

    class hitButton implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            Card hitCard = game.hit(player);
            playerCardHit = new JLabel(hitCard.getCardPic());
            playerCardPanel.add(playerCardHit);
            playerCardPanel.repaint();

            if (game.isBust(player)) {
                winLoseLabel.setText("Bust");
                hitButton.setEnabled(false);
                dealButton.setEnabled(false);
                stayButton.setEnabled(false);
                playAgainButton.setEnabled(true);
                updateScore("Lose");
            }

            playerLabel.setText("  Player:   " + game.handValue(player));
        }
    }

    class stayButton implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {

            dealerCardPanel.remove(dealerCard0);
            dealerCardPanel.add(dealerCard1);

            dealer = game.dealerPlays();
            dealerCardPanel.removeAll();
            dealerCardPanel.add(dealerLabel);
            dealerLabel.setText(" " + dealerLabel.getText());

            Card dealerHitCard = null;
            Iterator<Card> dealerScan = dealer.iterator();
            while (dealerScan.hasNext()) {
                dealerHitCard = dealerScan.next();
                dealerCardHit = new JLabel(dealerHitCard.getCardPic());
                dealerCardPanel.add(dealerCardHit);
            }

            dealerLabel.setText("Dealer: " + game.handValue(dealer));
            playerLabel.setText("Player: " + game.handValue(player));

            winLoseLabel.setText(game.winner());
            updateScore(game.winner());
            hitButton.setEnabled(false);
            stayButton.setEnabled(false);

            playAgainButton.setEnabled(true);
        }
    }

    class playAgainButton implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {

            dealerLabel.setText("Dealer: ");
            playerLabel.setText("Player: ");
            winLoseLabel.setText("");
            dealer = new BlackjackHand();
            player = new BlackjackHand();
            game = new Blackjack(dealer, player);

            dealerCardPanel.removeAll();
            playerCardPanel.removeAll();

            hitButton.setEnabled(false);
            stayButton.setEnabled(false);
            playAgainButton.setEnabled(false);
            dealButton.setEnabled(true);
        }
    }
}




