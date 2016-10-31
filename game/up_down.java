//author: thegamerift
import java.util.Scanner;
import java.util.Random;

public class GuessingGame{
   public static Scanner scanner = new Scanner(System.in);
   public static Random rand = new Random();
   public static void main(String[] args){
       guess();
   
   }
   public static void guess(){
      int pick = 0;
      int guesses = 0;
      int randomInt = rand.nextInt(1000) + 1; 
      while (pick != randomInt){ 
         System.out.println("Please enter a number between 1 and 1000");
         pick = scanner.nextInt();
         if (pick > randomInt){
            System.out.println("Too high");
         }
         if (pick < randomInt){
            System.out.println("too low");
         }
         System.out.println();
         guesses++;
      }
      System.out.println("CONGRATUALTIONS! YOU GUESSED THE NUMBER!!!");
      System.out.println("The number was " + randomInt);
      System.out.println("It took you " + guesses + " tries to get the number");
   }
}
