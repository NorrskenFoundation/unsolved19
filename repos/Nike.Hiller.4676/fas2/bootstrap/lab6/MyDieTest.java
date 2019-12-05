import java.util.Scanner;

public class MyDieTest {

  public static void main(String [] args) {
    Scanner sc = new Scanner(System.in);
    System.out.print("Number of wanted sides: ");
    int sides = sc.nextInt();
    Die d = new Die(sides);
    int dieValue = 0;
    for (int i = 0; i < 10; ++i) {
      dieValue += d.roll();
    }
    System.out.println("sum is: " + dieValue);
  }

}

