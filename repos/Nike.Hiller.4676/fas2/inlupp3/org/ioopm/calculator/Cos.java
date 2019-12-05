package org.ioopm.calculator.ast;

public abstract class Cos extends Unary{


    public Cos(SymbolicExpression leaf)
    {
        super(leaf);
    }

    public String getName() 
    {
        return "Cos";
    }

    public int getPriority()
    {
        return 80;
    }


}
