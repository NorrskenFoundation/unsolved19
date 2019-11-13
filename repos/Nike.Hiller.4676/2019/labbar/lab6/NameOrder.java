import java.util.Scanner;

public class  NameOrder {

  public static void main(String[] args) {

    Scanner sc = new Scanner(System.in);
    System.out.println("write one string, press enter, write another and press enter");
    String name1 = sc.nextLine();
    String name2 = sc.nextLine();
    if (name1.compareTo(name2) > 0 ) {
      System.out.println( "name one is biggest. " + name1 + " " + name2);
    }
    else {
      System.out.println("name two is biggest. " + name2 + " " + name1);
    }

  }
}
