package org.ioopm.calculator.ast;

public class Subtraction extends Binary{

    
    public Subtraction(SymbolicExpression lhs, SymbolicExpression rhs)
    {
        super(lhs, rhs);
    }


    public String getName() 
    {
        return "-";
    }


    public int getPriority()
    {
        return 40;
    }

}
