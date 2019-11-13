
---------  Plan for the assignment  ---------
---------  "A symbolic Calculator"  ---------


---------          Example          ---------
 -------------------------------------
|                                     |
|      Package                        |
|      |                              |
|      |--[Class]                     |
|      |  |                           |
|      |  |--[subclass]               |
|      |   ╲-[subclass]               |
|      |    -(subclass) -- DONE!      |
|       ╲                             |
|        -[Class]                     |
|                                     |
 -------------------------------------


 -------------------------------------------
|  Parsing the Calculator's Language (A)    |
 -------------------------------------------

org.ioopm.calculator.parser
|
 --CalculatorParser (All methods should be written in this class)


 -----------------------------
|  Implementing the AST (B)   |
 -----------------------------

org.ioopm.calculator.ast
|
 ╲-(root) [SymbolicExpression]
  ╲
   |-- [Binary] (All binary expressions have two subtrees)
   |  ╲-- [Addition]
   |  |-- [Subtraction]
   |  |-- [Multiplaction]
   |   ╲- [Division]
   |    - [Assignment]
   |
   |-- [Unary] (All unary expressions have one subtree)
   |  ╲-- [Sin]
   |  |-- [Cos]
   |  |-- [Exp]
   |   ╲- [Log]
   |    - [Negation]
   |
   |-- [Atom]
   |  ╲- [Variable]
   |   - [Constant]
   |
   |-- [Command]
      ╲- [Vars]
       - [Quit]

 --------------------------------------
|  Integration and Extension Part (C)  |
 --------------------------------------

 |-- Command
    ╲- [Clear]

 |-- Variable
    ╲- [Named_Constants]

      



