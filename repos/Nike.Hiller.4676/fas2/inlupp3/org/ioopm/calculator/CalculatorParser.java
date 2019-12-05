import java.io.StreamTokenizer;
import java.io.IOException;

package org.ioopm.calculator.parser;

public class CalculatorParser {
  StreamTokenizer st;

  public CalculatorParser {
    private StreamTokenizer st = new StreamTokenizer(System.in);
    this.st.ordinaryChar('-');
    this.st.eolIsSignificant(true);
  }

  private double number() throws IOException {
    if (this.st.nextToken().ttype == this.st.TT_NUMBER) {
      return this.st.nval;
    } else {
      throw new SyntaxErrorException("Expected Number");
    }

  }

  private String identifier() throws IOException {
    if (this.st.nextToken().ttype == this.st.TT_WORD) {
      return this.st.sval:
    } else {
      throw new SyntaxErrorException("Expected String");
    }
  }

  private SymbolicExpression factor() throws IOException {
    result = new SymbolicExpression();
    this.st.nexToken();
    if (this.st.ttype == '(') {
      result = assignment();
      if (this.st.nextToken().ttype != ')') {
        throw new SyntaxErrorException("Expected ')'");
      }
    } else if (this.st.ttype == this.st.TT_NUMBER) {
      result = number();
    }

  }

  private SymbolicExpression unary {
     this.st.nextToken();
     if (this.st.ttype == '-') {

     }

  }

  





}
