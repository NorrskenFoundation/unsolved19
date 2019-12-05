package org.ioopm.calculator.ast;

public class Sin extends Unary{

    
    public Sin(SymbolicExpression leaf)
    {
        super(leaf);
    }


    public String getName() 
    {
        return "Sin";
    }

    public int getPriority()
    {
        return 80;
    }


}
