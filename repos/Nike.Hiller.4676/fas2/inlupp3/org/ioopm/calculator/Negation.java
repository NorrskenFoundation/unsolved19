package org.ioopm.calculator.ast;

import org.ioopm.calculator.ast.SymbolicExpression;

public class Negation extends Unary{

    public Negation(SymbolicExpression leaf)
    {
        super(leaf);
    }

    public String getName()
    {
        return "-";
    }

    public int getPriority()
    {
        return 20;
    }

}