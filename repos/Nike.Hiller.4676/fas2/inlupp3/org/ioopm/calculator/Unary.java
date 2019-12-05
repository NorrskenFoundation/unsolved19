package org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression{

    private SymbolicExpression leaf = null;


    public Unary(SymbolicExpression leaf)
    {
        this.leaf = leaf;
    }
}
