package bank;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.DecimalFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class AccountTest {

    public static void main(String[] args) {
        Scanner sc = null;
        Map<Integer, AccountPersonal> accounts = new HashMap<>();

        try {
            sc = new Scanner(new File("src/accounts.txt"));
        }
        catch(IOException e) {
            e.printStackTrace();
        }

        while (sc.hasNextLine()) {

            String type = sc.nextLine();
            String name = sc.nextLine();
            int id;
            id = Integer.parseInt(sc.nextLine());
            double balance = Double.parseDouble(sc.nextLine());
            double air = Double.parseDouble(sc.nextLine());
            LocalDate date = LocalDate.parse(sc.nextLine(), DateTimeFormatter.ofPattern("MM/dd/yyyy"));

            if (type.equals("Checking")) {
                double overdraftamount = Double.parseDouble(sc.nextLine());
                accounts.put(id, new AccountChecking(name, id, balance, air, date, overdraftamount));
            }
            else {
                accounts.put(id, new AccountSaving(name, id, balance, air, date));
            }
        }

        accounts.put(4444, new AccountSaving("Jennifer Lopez", 4444, 250.0, 0.02, LocalDate.now()));

        accounts.get(1111).deposit(100.00);
        accounts.get(1111).deposit(200.00);
        accounts.get(1111).deposit(150.00);
        accounts.get(1111).deposit(accounts.get(1111).getMonthlyInterest());

        accounts.get(2222).deposit(500.00);
        accounts.get(2222).withdraw(100.00);
        accounts.get(2222).withdraw(50.00);
        accounts.get(2222).withdraw(75.00);
        accounts.get(2222).deposit(accounts.get(2222).getMonthlyInterest());

        accounts.get(3333).withdraw(50.00);
        accounts.get(3333).withdraw(600.00);
        accounts.get(3333).deposit(250.00);
        accounts.get(3333).deposit(accounts.get(3333).getMonthlyInterest());

        accounts.get(4444).withdraw(125.00);
        accounts.get(4444).deposit(100.00);
        accounts.get(4444).deposit(350.00);
        accounts.get(4444).deposit(accounts.get(4444).getMonthlyInterest());

        List<Integer> keyList = new ArrayList<>(accounts.keySet());
        Collections.sort(keyList);
        for (Integer key : keyList) {
            System.out.println(accounts.get(key));
        }

        writeTransactions(accounts, "transactions.txt");
    }

    public static void writeTransactions(Map<Integer, AccountPersonal> map, String fileName) {
        PrintWriter writer = null;
        DecimalFormat df = new DecimalFormat("0.00");

        try {
            writer = new PrintWriter(fileName, "UTF-8");
        }
        catch (IOException e) {
            e.printStackTrace();
        }

        List<Integer> keyList = new ArrayList<>(map.keySet());
        Collections.sort(keyList);

        for (Integer key : keyList) {
            writer.println(key);
            writer.println(map.get(key).getTransactions().size());
            List<Transaction> tlist = map.get(key).getTransactions();
            for (Transaction t : tlist) {
                writer.println(t.getType() + " | " + t.getDate() + " | " + df.format(t.getAmount()) + " | " + df.format(t.getBalance()));
            }
        }

        writer.close();
    }
}