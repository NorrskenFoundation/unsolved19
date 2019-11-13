import java.util.Scanner;

  public class Die {
  private int numberOfSides;
  private int value;

  public Die() {
    this.numberOfSides = 6;
    this.value = 1;
  }

  public Die(int numberOfSides) {
    if (numberOfSides < 0 ) {
      numberOfSides = 1;
    }
    this.numberOfSides = numberOfSides;
    this.value = 5;
  }

  public int roll() {
    this.value = (int) (Math.random() * numberOfSides) + 1;
    return this.get();
  }

  public int get() {
    return value;
  }

  public String toString() {
    return "Die("+ value + ")";
  }

  boolean equals(Die otherDie) {
    return (otherDie.numberOfSides == this.numberOfSides);
   }

  public static void main(String [] args) {
    Scanner sc = new Scanner(System.in);
    System.out.print("Number of sides: ");
    int sides = sc.nextInt();
    Die d = new Die(sides);
    Die p = new Die(5);

    System.out.println("Alea iacta est: " + d.roll());
    System.out.println(d);
    System.out.println("is " + d.equals(p));
  }
}

