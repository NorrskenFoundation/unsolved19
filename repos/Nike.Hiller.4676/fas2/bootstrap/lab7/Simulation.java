import java.util.Random
public class Simulation {
  private Store store;
  private int time;
  private int intensity;
  private int maxGroceries;
  private int thresholdForNewRegister;
  private int CustomersServed;
  private int maxWait;
  private int averageWait;
  private Random random = new Random();

  public Simulation(int intensity, int maxGroceries, int thresholdForNewRegister) {
    this.store = new Store();
    this.time = 0;
    this.intensity = intensity;
    this.maxGroceries = maxGroceries;
    this.thresholdForNewRegister = thresholdForNewRegister;

  }

  public void updateCustomersServed(int served) {
      this.nrCustomersServed = nrCustomersServed + served;
  }

  public void updateMaxWait() {

  }

  public void step() {
    this.store.step();
    Random random = this.random.nextInt(100);
    if(random < this.intensity) {
      Customer customer = new Customer(this.time, this.random.nextInt((this.maxGroceries - 1) + 1) + 1);
    }
    if(store.getAverageQueueLength() > this.thresholdForNewRegister) {
      this.store.openNewRegister();
    }
    Queue allDoneCustomers = this.store.getDoneCustomers();
    updateCustomersServed(allDoneCustomers.length());
  }





}
