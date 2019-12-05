package org.ioopm.calculator.ast;

public class Constant extends Atom{

    private double value;

    public Constant(double value) 
    {
        this.value = value;
    }

    public boolean isConstant()
    {
        return true;
    }

    public double getValue()
    {
        return this.value;
    }

}
