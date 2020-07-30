
//  return values of SCAN and LEXER functions

#define _sUK_ 0       //  Unknown character
#define _sSTART_ 2    //  Start of file
#define _sSTOP_ 3     //  End of file
#define _sEQ_ 7       //  equal sign
#define _sDOT_ 8      //  dot sign
#define _sCM_ 9       //  comma
#define _sID_ 10      //  valid JS variable name, has [_,$,az,AZ,09,] can't start with numbers
#define _sLC_ 11      //  all lowercase string, and potential JS keyword to be identified by lexer
#define _sUC_ 12      //  all uppercase string, and potential PY keyword to be identified by lexer
#define _sWS_ 13      //  white space
#define _sNL_ 14      //  new line
#define _sSE_ 15      //  separator { } [ ] ( ) ; and ,
#define _sNUM_ 16     //  number literal
#define _sSTR_ 17     //  string literal between single or double quotes '...' or "..."
#define _sSTR_END_ 18   //  correct string termination character, can be ' or "
#define _sSTT_ 19     //  string template
#define _sBWO_ 25     //  bitwise operator
#define _sMTH_ 26     //  basic math operator
#define _sCMP_ 27     //  comparator
#define _sQST_ 28     //  question mark
#define _sCOL_ 29     //  colon
#define _sSYM_ 30     //  symbol
#define _sSY1_ 31     //  symbol in first range os ascii map, after space ' ' character
#define _sSY2_ 32     //  symbol in second ascii range
#define _sSY3_ 33     //  symbol in second ascii range
#define _sSY4_ 34     //  symbol in second ascii range
#define _sEXT_ 35     //  extended ascii character, decimal 127 to 255
