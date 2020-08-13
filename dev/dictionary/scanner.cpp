/* scanner module of the arduino-interpreter project
 * release: 0.1
 * license: MIT, see LICENSE file
 * created: Alejandro Solano, July 2020
 * modified: August 12, 2020
 */
// include this library's description file
#include "scanner.h"

#define daXor(d) Xor ^= d;  data.write(d)
#define daAdd(d) data.write(d)
#define tokenSend(t) lastToken = t;  token.write(t)
#define dataSend(d) token.write(d)
//#define dataFlush() while ( data.available() ) { token.write( (byte)data.readFirst() ); }
#define dataFlush() while ( data.available() ) { Serial.print( (char)data.readFirst() ); }
#define stringSend(t) {tokenSend(t);  dataSend((byte)data.length());  dataSend(Xor);  dataFlush();  Serial.print('\n');}
#define numberSend(t) {tokenSend(t);  dataSend((byte)data.length());  dataFlush();  Serial.print('\n');}
#define token(t) {lastToken = t;  waitConsecutive = sUK;  token.write(t);  return;}
#define tokenReduce(t) {if (t != lastToken) {tokenSend(t);} waitConsecutive = sUK; return;}
#define tokenRemove(t) {lastToken = t;  waitConsecutive = sUK;  return;}

#define wait(t) {waitConsecutive = t;  return;}
//#define waitChar(t, s) {stop_char = s;  waitConsecutive = t;  return;}

#define waitID(t, d) {waitConsecutive = t;  data.clear(); Xor = d; daAdd(d);  return;}
#define waitDE(t) {waitConsecutive = t;  data.clear();  Xor = 0;  return;}
#define waitNUM(t, d) {waitConsecutive = t;  data.clear(); daAdd(d);  return;}
#define waitSTT() {waitConsecutive = sSTT;  data.clear();  Xor = 0;  return;}
#define waitSTR(s) {waitConsecutive = sSTR;  stop_char = s;  data.clear();  Xor = 0;  return;}
#define waitCMN(s) {waitConsecutive = sCMN;  stop_char = s;  return;}

Scanner::Scanner() {
  begin();
  return;
}
void Scanner::scan(byte c) {
  ++Character;  // lastChar = c;
  //  scan consecutive character
  if (waitConsecutive) {
    boolean sendToken = false;
    if ( waitConsecutive < sWS ) {
      switch ( waitConsecutive ) {
        case sLID:
          if ( _lo_(c) ) { daXor(c);  return; }
          if ( _id_(c) ) { waitConsecutive = sID;  daXor(c);  return; }
          // END: check for lc keyword, send token + data
          sendToken = true;
        break;
        case sUID:
          if ( _up_(c) ) { daXor(c);  return; }
          if ( _id_(c) ) { waitConsecutive = sID;  daXor(c);  return; }
          // END: check for lc keyword, send token + data
          sendToken = true;
        break;
        case sID:
          if ( _id_(c) ) { daXor(c);  return; }
          // END: check for lc keyword, send token + data
          sendToken = true;
        break;
        case sdHA:
          if ( _pr_(c) ) { daXor(c);  return; }
          sendToken = true;
        break;
        case sdAT:
          if ( _pr_(c) ) { daXor(c);  return; }
          sendToken = true;
        break;
        case sSTR:
          if (c != stop_char) {
            if ( _pr_(c) || _ws_(c) ) { daXor(c);  return; }
          }
          sendToken = true;
        break;
        case sSTT:
          if (c != stop_char) {
            if ( _pr_(c) || _ws_(c) || _nl_(c) ) { daXor(c);  return; }
          }
          sendToken = true;
        break;
      }
      if (sendToken) stringSend(waitConsecutive);
      if ((waitConsecutive == sSTR) || (waitConsecutive == sSTT)) {
        waitConsecutive = sUK; return;
      }
    }
    else if ( waitConsecutive < sbAND ) {
      switch ( waitConsecutive ) {
        case sNUM:
          if ( _nu_(c) ) { daAdd(c);  return; }
          sendToken = true;
        break;
        case s0NU:
          if ( _nu_(c) && ( c < '8' ) ) { waitConsecutive = s8NU;  daAdd(c);  return; }
          if ( (c=='b') || (c=='B') ) { waitConsecutive = s2NU;  daAdd(c);  return; }
          if ( (c=='o') || (c=='O') ) { waitConsecutive = s8NU;  daAdd(c);  return; }
          if ( (c=='x') || (c=='X') ) { waitConsecutive = shNU;  daAdd(c);  return; }
          sendToken = true;
        break;
        case s2NU:
          if ( (c=='0') || (c=='1') ) { daAdd(c);  return; }
          sendToken = true;
        break;
        case s8NU:
          if ( _nu_(c) && ( c < '8' ) ) { daAdd(c);  return; }
          sendToken = true;
        break;
        case shNU:
          if ( _nu_(c) || ((c >= 'a')&&(c <= 'f')) || ((c >= 'A')&&(c <= 'F')) ) { daAdd(c);  return; }
          sendToken = true;
        break;
      }
      if (sendToken) numberSend(waitConsecutive);
    }
    else {
      switch ( waitConsecutive ) {
        case sCMN:
          if ( stop_char == 0 ) {
            if ( c == sl ) {stop_char = nl;  return;}
            if ( c == ak ) {stop_char = ak;  return;}
            tokenSend( smDI );
          }
          else if ( stop_char == nl ) {
            if ( _nl_(c) ) tokenReduce( sNL );
            return;
          }
          else if ( stop_char == ak ) {
            if ( c == ak ) {stop_char = sl;  return;}
            return;
          }
          else if ( stop_char == sl ) {
            if ( c == sl ) {wait( sUK );  return;}  // end multiline comment
            stop_char = ak;  return;  // wait a new asterisk
          }
        break;
      }
    }
    
    // character not expected
    waitConsecutive = sUK;
  }
  //  identify start of sequence
  
  //  ascii is lowercase, symbol 4 or extended ascii
  if ( a_A(c) ) {
    //  is lower than symbol 4 range in ascii
    if ( a_s4(c) ) waitID( sLID, c )     //  lowercase
    // is separator or symbol 4 range
    if ( s4_ex(c) ) {
      if (c == lc) token( sLC )     //  is { or } separator
      if (c == rc) token( sRC )
      //  is | bitwise operator
      if ( c == pi ) token( sbOR )  //  'or' bitwise operator
      token( sbyNOT ) }     //  '~' byte not operator
    token( sEXT )     //  extended ascii chareter
  }
  //  is uppercase A or symbol 3
  if ( A_d(c) ) {
    if ( A_s3(c) ) waitID( sUID, c )    //  uppercase                
    if (c == lb) token( sLB )       //  is [ or ] separator
    if (c == rb) token( sRB )
    if (c == us) waitID( sID, c )   //  underscore, valid JS or PY identifier
    if (c == ca) token( sbXOR )     //  'xor' bitwise operator
    if (c == bt) waitSTT()          //  JS string template
    token( sBSL )     //  '\' backslash escape sequence
  }

  //  is digit or symbol 2
  if ( d_s1(c) ) {

    if ( d_s2(c) ) {
      if ( c == '0' ) waitNUM( s0NU, c )  //  0 leading number literal
      else waitNUM( sNUM, c )       //  number literal
    }
    //  is = sign
    if ( c == eq ) token( sEQ )     //  equal sign
    //  symbol 2 lower than equal sign
    if ( s2_lo(c) ) {
      //  is ; separator
      if ( c == sc ) token( sSC )   //  semicolon ';'separator
      if ( c == lt ) token( sLT )   //  less than compare operator
      token( sCOL )   //  colon ':'
    }
    //  symbol 2 greater tha equal sign
    if ( c == gt ) token( sLT )     //  greater than compare operator
    if ( c == qm ) token( sQST)     //  question mark
    if ( c == at ) waitDE( sdAT )     //  '@' decorator
  }

  //  is symbol 1
  if ( s1_ws(c) ) {
    
    //  symbol 1 greater than equal sign
    if ( s1_hi(c) ) {
      if ( c == dt ) token( sDOT )    //  dot sign
      if ( c == pl ) token( smPL )    //  + sign
      if ( c == ak ) token( smMU )    //  * sign
      if ( c == hy ) token( smMI )    //  - sign
      if ( c == cm ) token( sCM )     //  comma
      if ( c == sl ) waitCMN( 0 )  //  / slash, possible comment
    }
    //  symbol 1 lower than equal sign
    if (c == lp) token( sLP )         //  is ( or ) separator
    if (c == rp) token( sRP )
    if ( c == aa ) token( sbAND )     //  & bitwise AND
    if ( (c == qt) || (c == dq) )     //  string literal, single and double quotes ', "
      waitSTR( c )   // pass the single or double quote as stop character
    if ( c == bg ) token( sbNOT )     //  '!' bitwise operator
    if ( c == pe ) token( smPE )      //  '%' basic math operator
    if ( c == ds ) waitID( sID, c )   //  dollar sign, valid identifier
    if ( c == ha ) waitDE( sdHA )  //  '#' decorator
  }
  
  // is space or lower control character
  // if ( _ws_(c) ) tokenRemove( sWS )    //  white space, don't emmit whitespaces tokens
  if ( _ws_(c) ) token( sWS )             //  white space, emmit all whitespaces tokens, to preserve visual structure for the test
  if ( _nl_(c) ) tokenReduce( sNL )       //  new line, reduce repeated newline tokens to one newline token
  if ( _stx_(c) ) token( sSTART )   //  start of text
  if ( _etx_(c) ) token( sSTOP )    //  end of text

  return;    ///  unknown
}
void Scanner::begin() {
  Line = 0;  Column = 0;  Character = 0;  lastChar = 0;  lastToken = sUK;
  data.clear();  token.clear();
  data.clearStats();  token.clearStats();
  Xor = 0;  stop_char = 0;  waitConsecutive = sUK;
  return;
}
void Scanner::end() {
  scan(0);
  return;
}
char Scanner::get() {
  return token.readFirst();
}
size_t Scanner::length() {
  return token.length();
}
uint32_t Scanner::CharactersStat() {
  return Character;
}
uint32_t Scanner::tokenStat() {
  return token.totalStat();
}
uint32_t Scanner::dataStat() {
   return data.totalStat();
}
