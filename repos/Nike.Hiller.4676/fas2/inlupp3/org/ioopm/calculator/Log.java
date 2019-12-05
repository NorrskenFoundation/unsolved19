package org.ioopm.calculator.ast;

public abstract class Log extends Unary{


    public Log(SymbolicExpression leaf)
    {
        super(leaf);
    }

    public String getName() 
    {
        return "Log";
    }

    public int getPriority()
    {
        return 80;
    }


}
