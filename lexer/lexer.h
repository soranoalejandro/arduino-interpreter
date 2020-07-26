#include "ascii_codes.h"
#include "keywords.h"

        //    FUNCTIONS

char lxScan( char c );
char lxIsIDStart( char c );
char lxIsID( char c );
char lxIsWS( char c );
char lxIsSY( char c );
char lxIsNL( char c );

#define _sUK_ 0
#define _sSTART_ 2
#define _sSTOP_ 3
#define _sID_ 10
#define _sWS_ 11
#define _sNL_ 12
#define _sSY_ 13
#define _sNU_ 14

char lxScan( char c ) {
  static byte scanType = _sUK_;
  if ( c ) {
    if ( scanType == _sID_ ) {    //  scanning ID
      if ( lxIsID(c) ) {
        return scanType;
      }
    } else if ( scanType == _sWS_ ) {    //  scanning WS
      if ( lxIsWS(c) ) {
        return scanType;
      }
    } else if ( scanType == _sNU_ ) {    //  scanning NU
      if ( isDigit(c) ) {
        return scanType;
      }
    } else if ( scanType == _sSY_ ) {    //  scanning NU
      if ( lxIsSY(c) ) {
        return scanType;
      }
    } else if ( scanType == _sNL_ ) {    //  scanning NL
      if ( lxIsNL(c) ) {
        return scanType;
      }
    }
    scanType = _sUK_; // ERROR:  not expectet type
    if ( scanType == _sUK_ ) {   //  detect start of type
      if ( lxIsIDStart(c) ) {     //  identifier
        scanType = _sID_;
        return scanType;
      }
      if ( lxIsWS(c) ) {          //  whitespace
        scanType = _sWS_;
        return scanType;
      }
      if ( isDigit(c) ) {         //  number
        scanType = _sNU_;
        return scanType;
      }
      if ( lxIsNL(c) ) {          //  new line
        scanType = _sNL_;
        return scanType;
      }
      if ( (c > 32) & (c < 127) ) {
        scanType = _sSY_;         //  symbol
        return scanType;
      }
    }
  }
  return _sUK_;
}

char lxIsIDStart( char c ) {          //  is letter, underscore or dollar sign
  if ( isAlpha(c) | ( c == ld ) | ( c == ds ) ) {
    return c;
  }
  return 0;
}

char lxIsID( char c ) {               //  is letter, underscore, dollar sign or number
  if ( lxIsIDStart(c) | isDigit(c) ) {
    return c;
  }
  return 0;
}

char lxIsWS( char c ) {
  if ( (c == sp) | (c == tb) ) {      //  is space, or tabulator
    return c;
  }
  return 0;
}

char lxIsSY( char c ) {
  if ( (c > 'c') & (c < 127) ) {      //  is symbol
    if ( !( isAlpha(c) | isDigit(c) | lxIsWS(c) ) ) {
      return c;
    }
  }
  return 0;
}

char lxIsNL( char c ) {
  if ( (c == nl) | (c == cr) | (c == sc) ) {      //  new line or carriage return
    return c;
  }
  return 0;
}
