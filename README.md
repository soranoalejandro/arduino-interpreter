Casual experiment for implementing a code interpreter for 'JavaScript'
or other scripting languages. Goal: make the two elemental components
for interpreting code from a file, CLI or stream.

Those components are:

   Lexer	to interpret symbols ( { ( ; : ) operators ( + - * / ^ & ) and keywords ( function, if, var... )
   Parser	to join those building blocks and output the program structure in 'AST' format

Expected results: get tokens from lexer, get an Abstract Syntax Tree from the parser, Have fun!

//	to be tested on arduino uno and mega during development.