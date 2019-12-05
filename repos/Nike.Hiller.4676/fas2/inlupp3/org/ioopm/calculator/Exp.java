package org.ioopm.calculator.ast;

public abstract class Exp extends Unary{


    public Exp(SymbolicExpression leaf)
    {
        super(leaf);
    }



    public String getName() 
    {
        return "Exp";
    }

    public int getPriority()
    {
        return 80;
    }

}
