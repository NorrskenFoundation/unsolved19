package org.ioopm.calculator.ast;

public class Variable extends Atom{

    private String identifier;

    public Variable(String identifier)
    {
        this.identifier = identifier;
    }

}
