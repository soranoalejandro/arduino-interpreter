
//  return values of SCAN and LEXER functions

#define _sUK_ 0       //  Unknown character
#define _sSTART_ 2    //  Start of file
#define _sSTOP_ 3     //  End of file
#define _sCMN_ 4      //  Comment or '/' math operator
#define _sDE_ 5      //  # or @ decorator
#define _sEQ_ 7       //  equal sign
#define _sDOT_ 8      //  dot sign
#define _sCM_ 9       //  comma
#define _sLC_ 10      //  all lowercase string, and potential JS keyword to be identified by lexer
#define _sUC_ 11      //  all uppercase string, and potential PY keyword to be identified by lexer
#define _sID_ 12      //  valid JS variable name, has [_,$,az,AZ,09,] can't start with numbers
#define _sWS_ 13      //  white space
#define _sNL_ 14      //  new line
#define _sSE_ 15      //  separator { } [ ] ( ) ; and ,
#define _sNUM_ 16     //  number literal
#define _sSTR_ 17     //  string literal between single or double quotes '...' or "..."
#define _sSTR_END_ 18 //  correct string termination character, can be ' or "
#define _sSTT_ 19     //  string template
#define _sBSL_ 20     //  Back slash escape sequence
#define _sBWO_ 25     //  bitwise operator
#define _sMTH_ 26     //  basic math operator
#define _sCMP_ 27     //  comparator
#define _sQST_ 28     //  question mark
#define _sCOL_ 29     //  colon
#define _sSYM_ 30     //  symbol
#define _sEXT_ 31     //  extended ascii character, decimal 127 to 255
