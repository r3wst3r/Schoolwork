package loancompare;

import java.util.Scanner;

public class LoanCompare {

    public static void main(String[] args) {

        Scanner scan = new Scanner(System.in);

        // Enter a loan amount
        boolean goodValue = false;
        double loanAmount = 0.0;
        while (!goodValue) {
            try {
                System.out.print("Enter loan amount: ");
                loanAmount = getDouble(scan);
                goodValue = true;
            }

            catch (IllegalArgumentException e){
                System.out.println(e.getMessage());
            }
        }

        // Enter the number of years
        goodValue = false;
        int numOfYears = 0;
        while (!goodValue) {
            try {
                System.out.println("Enter the number of years as an integer: ");
                numOfYears = getInteger(scan);
                goodValue = true;
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }

        // Display the loans
        double interestRate = compareLoanInterest(loanAmount, numOfYears);
        System.out.println();

        // Display the selected amortization
        amortizeLoan(interestRate, loanAmount, numOfYears);
    } // end of main

    static double getDouble(Scanner scan) {
        String s = scan.nextLine();
        if (isDouble(s)) {
            return Double.parseDouble(s);
        } else
            throw new IllegalArgumentException("Did not provide a valid double.");
    }


    static boolean isDouble(String s) {
        try {
            Double.parseDouble(s);
            return true;
        } catch (Exception e) {
            return false;
        }

    }


    static int getInteger(Scanner sc) {
        String s = sc.nextLine();
        if (isInteger(s)) {
            return Integer.parseInt(s);
        } else
            throw new IllegalArgumentException("Did not provide a valid int.");
    }


    static boolean isInteger(String s) {
        try {
            Integer.parseInt(s);
            return true;
        }
        catch (Exception e) {
            return false;
        }
    }

    static double computeMonthlyPayment(double loanAmmount,
                                        double monthlyInterestRate,
                                        int numOfYears) {
        return loanAmmount * monthlyInterestRate /
                (1 - (Math.pow(1 / (1 + monthlyInterestRate),
                                    numOfYears * 12)));
    }

    static double compareLoanInterest(double loanAmount,
                                  int numOfYears) {
        System.out.printf("%6s   %20s %20s %20s\n",
                "Option", "Interest Rate",                  // <--- Table header
                "Monthly Payment","Total Payment");
        int index = 0;
        for (double annualInterestRate = 5.0;
        annualInterestRate <= 8.0;
        annualInterestRate += 1.0 / 8) {
            // Obtain monthly interest rate
            double monthlyInterestRate = annualInterestRate / 1200; //dividing by 1200 moves the decimal point over easier

            // Compute monthly payment
            double monthlyPayment = computeMonthlyPayment(loanAmount,
                                                            monthlyInterestRate,
                                                            numOfYears);
            double totalPayment = monthlyPayment * numOfYears * 12;

            // Display the results
            index++;
            System.out.printf("%6d   %19.3f%3 %20.2f %20.2f\n",
                    index, annualInterestRate, '%',
                    monthlyPayment, totalPayment);                  // in %19.3, the .3 indicates outputting  the float to 3 decimal places
        } // end of for loop
        return 0.0;
    }

    static void amortizeLoan(double interestRate,
                             double loanAmount,
                             int numOfYears){

    }



} // end of class
