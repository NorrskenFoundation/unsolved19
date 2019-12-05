package org.ioopm.calculator.ast;

public class Division extends Binary{


    
    public Division(SymbolicExpression lhs, SymbolicExpression rhs)
    {
        super(lhs, rhs);
    }


    public String getName() 
    {
        return "/";
    }


    public int getPriority()
    {
        return 60;
    }
    
}
