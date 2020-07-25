#include "ascii_codes.h"
#include "keywords.h"

        //    FUNCTIONS

char lxScan( char c );
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
}
