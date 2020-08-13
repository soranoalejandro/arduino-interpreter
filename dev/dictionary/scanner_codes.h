#pragma once
//  return values of SCAN and LEXER functions

#define sUK 0       //  Unknown character
#define sSTART 250  //  Start of file
#define sSTOP 251   //  End of file

  #define sLID 10   //  all lowercase string, and potential JS keyword to be identified by lexer
  #define sUID 11   //  all uppercase string, and potential PY keyword to be identified by lexer
  #define sJS 12    //  valid JS variable keyword
  #define sPY 13    //  valid PY variable keyword
  #define sdHA 14   //  # decorator
  #define sdAT 15   //  @ decorator
  #define sID 16    //  valid JS variable name, has [_,$,az,AZ,09,] can't start with numbers
  #define sSTR 17     //  string literal between single or double quotes '...' or "..."
  #define sSTT 18     //  string template

#define sWS 20      //  white space
#define sNL 22      //  new line
#define sLP 24      //  ( SEPARATORS
#define sLB 25      //  [
#define sLC 26      //  {
#define sRP 27      //  )
#define sRB 28      //  ]
#define sRC 29      //  }

#define sEQ 30      //  equal sign
#define sDOT 31     //  dot sign
#define sCM 32      //  comma
#define sGT 35      //  > comparator
#define sLT 36      //  < comparator

  #define sNUM 40     //  number literal
  #define snNU 41     //  negative number literal
  #define s0NU 42     //  0 leading number literal
  #define s2NU 43     //  binary number literal
  #define s8NU 44     //  octal number literal
  #define shNU 45     //  hezadecimal number literal

#define sbAND 50    //  & bitwise operator
#define sbOR 51     //  | bitwise operator
#define sbXOR 52    //  ^ bitwise operator
#define sbNOT 53    //  ! bitwise operator
#define sbyNOT 54   //  ~ byte not operator

#define smPL 60     //  + basic math operator
#define smMI 61     //  - basic math operator
#define smMU 62     //  * basic math operator
#define smDI 63     //  / basic math operator
#define smPE 64     //  % basic math operator

#define sSC 70      //  semi colon
#define sQST 71     //  question mark
#define sCOL 72     //  colon
#define sSYM 73     //  symbol
#define sEXT 74     //  extended ascii character, decimal 127 to 255

#define sSTR_END 81 //  correct string termination character, can be ' or "
#define sBSL 83     //  Back slash escape sequence
#define sCMN 84     //  Comment or '/' math operator
