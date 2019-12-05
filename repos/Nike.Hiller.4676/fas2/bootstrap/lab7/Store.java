public class Store {
  private Register registers[];

  public Store(int amountRegisters) {
    int i = 0;
    while(amountRegisters > i) {
      this.registers[i] = new Register();
      i++;
    }
    this.registers[0].open();
  }

  public int getAverageQueueLength() {
    int totalLength = 0;
    for(Register r : this.registers) {
      totalLength = totalLength + r.getQueueLength();
    }
    int averageQueueLength = totalLength / registers.length;
    return averageQueueLength;
  }

  public void newCustomer(Customer c) {
    Register shortestRegisterQueue = this.registers[0];
    for(Register r : this.registers) {
      if(shortestRegisterQueue.getQueueLength() > r.getQueueLength()) {
        shortestRegisterQueue = r;
      }
    }
    shortestRegisterQueue.addToQueue(c);
  }

  public void step() {
    for(Register r : this.registers) {
      r.step();
    }
  }

  public void  openNewRegister() {
    for(Register r : this.registers) {
      if(!(r.isOpen())) {
        r.open();
      }
    }
  }

  public Queue getDoneCustomers() {
    Queue doneCustomers = new Queue();
    for(Register r : this.registers) {
      if(r.currentCustomerIsDone()) {
        doneCustomers.enqueue(r.removeCurrentCustomer());
      }
    }
    return doneCustomers;
  }

}
