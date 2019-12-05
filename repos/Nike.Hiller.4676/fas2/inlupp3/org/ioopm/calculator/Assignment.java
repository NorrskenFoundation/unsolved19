package org.ioopm.calculator.ast;

public class Assignment extends Binary{


    private SymbolicExpression lhs;
    private SymbolicExpression rhs;
    
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs)
    {
        super(lhs, rhs);
    }


    public String getName() 
    {
        return "=";
    }

    public int getPriority()
    {
        return 10;
    }

    // public String assignIt(String lhs, double rhs)
    // {
    //     return (lhs = rhs);
    // }

}
