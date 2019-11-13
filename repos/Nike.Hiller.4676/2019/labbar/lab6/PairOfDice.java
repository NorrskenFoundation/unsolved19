import java.util.Scanner;

public class PairOfDice {
  private Die dieOne;
  private Die dieTwo;

  public PairOfDice(int numberOfSides) {
    dieOne = new Die(numberOfSides);
    dieTwo = new Die(numberOfSides);
  }

  public int rollDice() {
    return (dieOne.roll() + dieTwo.roll());
  }

  public int dieOneGet() {
    return dieOne.get();
  }

  public int dieTwoGet() {
    return dieTwo.get();
  }

  public String toString() {
    return "DieOne("+ dieOne.get() + ")"+ "DieTwo("+ dieTwo.get() + ")";
  }

  public static void main(String [] args) {
    Scanner sc = new Scanner(System.in);
    System.out.println("Nr of sides:");
    int sides = sc.nextInt();
    PairOfDice pd = new PairOfDice(sides);
    System.out.println("values are :" + pd);
  }


}
