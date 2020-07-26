#include "ascii_codes.h"
#include "keywords.h"

        //    MACROS
#define _lo_(x) (x < '{' & x > '`')
#define _up_(x) (x < '[' & x > '@')
#define _nu_(x) (x < ':' & x > '/')
#define _al_(x) (_lo_(x) | _up_(x))
#define _an_(x) (_al_(x) | _nu_(x))
#define _id_sy_(x) ((x == ld) | (x == ds))
#define _ws_(x) ((x == sp) | (x == tb))
#define _nl_(x) ((x == nl) | (x == cr) | (x == sc))
#define _sy1_(x) (x < '0' & x > sp)
#define _sy2_(x) (x < 'A' & x > '9')
#define _sy3_(x) (x < 'a' & x > 'Z')
#define _sy4_(x) (x < 127 & x > 'z')
#define _sy_(x) (_sy1_(x) | _sy2_(x) | _sy3_(x) | _sy4_(x))
#define _pr_(x) (x < 127 & x > 31)

        //    FUNCTIONS


char lxScan( char c );
<<<<<<< HEAD

#define _sUK_ 0
#define _sSTART_ 2
#define _sSTOP_ 3
#define _sID_ 10
#define _sWS_ 11
#define _sNL_ 12
#define _sSY_ 13
#define _sNUM_ 14
#define _sSTR_ 15
#define _sSTR_END_ 16

char lxScan( char c ) {
  static byte scanType = _sUK_;
  static char last = 0;
  static char quote = 0;
  if ( c ) {
    if ( scanType == _sID_ ) {    //  scanning ID
      if ( _an_(c) | _id_sy_(c) ) {
        return scanType;
      }
    } else if ( scanType == _sWS_ ) {    //  scanning WS
      if ( _ws_(c) ) {
        return scanType;
      }
    } else if ( scanType == _sNUM_ ) {    //  scanning NU
      if ( _nu_(c) ) {
        return scanType;
      }
    } else if (scanType == _sSTR_) {      //  scanning STR
      if ( _pr_(c) ) {
        if ( !(c == quote) ) {      //  add
          return scanType;
        } else {
          scanType = _sSTR_END_;
          return scanType;
        }
      }
    } else if ( scanType == _sSY_ ) {    //  scanning NU
      if ( _sy_(c) ) {
        return scanType;
      }
    } else if ( scanType == _sNL_ ) {    //  scanning NL
      if ( _nl_(c) ) {
        return scanType;
      }
    }
    scanType = _sUK_; // ERROR:  not expectet type
    if ( scanType == _sUK_ ) {   //  detect start of type
      if ( _al_(c) | _id_sy_(c) ) {     //  identifier
        scanType = _sID_;
      } else if ( _ws_(c) ) {          //  whitespace
        scanType = _sWS_;
      } else if ( _nu_(c) ) {         //  number
        scanType = _sNUM_;
      } else if ( _nl_(c) ) {          //  new line
        scanType = _sNL_;
      } else if ( (c > sp) & (c < 127) ) {
        if ( c == qt | c == dq ) {
          quote = c;
          scanType = _sSTR_;         //  symbol
        } else {
          scanType = _sSY_;         //  symbol
        }
      }
      return scanType;
    }
  }
  return _sUK_;
=======
char lxIsIdStart( char c );
char lxIsId( char c );

#define _sID_ 1
#define _sWS_ 2
#define _sSY_ 3
#define _sNU_ 4

char lxScan( char c ) {
  static byte scanType = 0;
  if ( c ) {
    if ( scanType == _sID_ ) {    //  scanning ID
      if ( lxIsId(c) ) {
        return scanType;
      }
    } else if ( scanType == 0 ) {   //  detect start of type
      if ( lxIsIdStart(c) ) {
        scanType = _sID_;
        return scanType;
      }
    }
    scanType = 0; // not expectet type or end of current type;
  }
  return 0;
}

char lxIsIdStart( char c ) {
  if ( isAlpha(c) | ( c =='_' ) | ( c == '$' ) ) {
    return c;
  }
  return 0;
}

char lxIsId( char c ) {
  if ( lxIsIdStart(c) | isDigit(c) ) {
    return c;
  }
  return 0;
>>>>>>> parent of 9574ce6... 2nd test, recognizes Id, number, ws, nl, symbol
}
