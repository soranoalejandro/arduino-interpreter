/* Function:
 * divides code sentences into lexeme tokens ex:
 *  'var x = 523' gives -> keyword(var), id(x), symbol(=), number literal(555)
 * it has two steps:  character SCAN, LEXER.
 * SCAN recognize basic character sequence types.
 * LEXER resolves ambigueties and reconstrucs lexemes with mixed
 * character sequences, ex: '1.23e-12' has numbers, dot and + - sign sequences
 *   Alejandro Solano, july 2020.
 */
#include "ascii_and_variable_names.h"
#include "keywordsJS.h"
#include "LX_token_types.h"

//  repetitive instructions, need them to be INLINE FUNTIONS but arduino compiler still refuses
#define daXorE(d) Xor ^= d;  Sum += d;  tk[indx++] = d;  ++cnt
#define daXorL(d) Xor ^= d;  Sum += d;  data[cnt++] = d
#define daStaE(d) tk[indx++] = d;  ++cnt
#define daStaL(d) data[cnt++] = d
#define daPass(d) tk[indx++] = d
#define tkCode(t) {tk[indx++] = t;  return t;}
#define tkPass(t, d) {tk[indx++] = t;  daPass(d);  return t;}
#define tkReduce(t) {tk[indx++] = t;  scanType = t;  return t;}
#define tkcnt(t) {cnt = 0;  tk[indx++] = t; scanType = t;  return t;}
#define tkNumL(t, d) {tk[indx++] = t;  cnt = 0;  daStaE(d);  scanType = t;  return t;}
#define tkStrL(t) {tk[indx++] = t;  cnt = 0;  Xor = 0;  Sum = 0;  scanType = t;  return t;}
#define tkIdL(t, d) {tk[indx++] = t;  cnt = 0;  Xor = 0;  Sum = 0;  daXorE(d);  scanType = t;  return t;}


static char data[14];
static byte scanType = _sUK_;
static byte cnt = 0;
static byte Xor = 0;
static byte Sum = 0;
static char quote = 0;

        //    FUNCTIONS

//  SCAN function
inline char lx_scan( char c );
//  SCAN function code to string (for testing and debuggin purposes)
inline void lx_print_code( char c );

// _sLC_ 10        _sUC_ 11        _sID_ 12
// _sWS_ 13        _sNL_ 14        _sSE_ 15
// _sNUM_ 16       _sSTR_ 17       _sSTR_END_ 18     _sSTT_ 19        _sBSL_ 20
        //    FUNCTION DEFINITIONS

inline char lx_scan( char c ) {
   
  //  ignores character hex 00
  if ( c ) {
    // _sLC_ 10        _sUC_ 11        _sID_ 12
    // _sWS_ 13        _sNL_ 14        _sSE_ 15
    // _sNUM_ 16       _sSTR_ 17       _sSTR_END_ 18     _sSTT_ 19        _sBSL_ 20
    //  is expecting a middle character of recognized type
    if ( scanType ) {
      if ( scanType == _sID_ ) {
        if ( _an_(c) || _id_sy_(c) ) {
          daXorE(c);  return _sID_; }
      } else if ( scanType == _sWS_ ) {
        if ( _ws_(c)) return _sWS_;
      } else if ( scanType == _sNL_ ) {
        if ( _nl_(c)) return _sNL_;
      } else if ( scanType == _sNUM_ ) {
        if ( _nu_(c)) {
          daStaE(c);  return _sNUM_; }
      }
    }
    
    
    //  charactar not expected as middle char, set new type to unknown
    scanType = _sUK_; // ERROR:  not expectet type
        
    //  determines start of a new string type
    //  detect start of type
    
    //  ascii is lowercase, symbol 4 or extended ascii
    if ( _aA_(c) ) {
      
      //  is lower than symbol 4 range in ascii
      if ( _as4_(c) ) tkIdL ( _sID_, c )  //  lowercase            
      
      // is separator or symbol 4 range
      if ( _s4ex_(c) ) {
        //  is { or } separator
        if ( (c == lc) || (c == rc) )     //  separator
          tkPass( _sSE_, c )
        //  is | bitwise operator
        if ( c == pi ) tkPass( _sBWO_, c) //  'or' bitwise operator
        tkPass( _sBWO_, c )               //  not '~' bitwise operator
      }
      
      //  then it is ascii extended character
      tkPass( _sEXT_, c )                 //  extended ascii chareter
    }

    
    //  is uppercase A or symbol 3
    if ( _Ad_(c) ) {
      
      if ( _As3_(c) ) tkIdL( _sID_, c )   //  uppercase                
      //  is [ or ] separator
      if ( (c == lb) || (c == rb) )       //  separator
        tkPass( _sSE_, c )
      if ( c == us ) tkIdL ( _sID_, c )   //  underscore, valid JS or PY identifier
      if ( c == ca ) tkPass( _sBWO_, c )  //  'xor' bitwise operator
      if ( c == bt ) tkCode( _sSTT_ )     //  JS string template
      tkCode( _sBSL_ )                    //  '\' backslash escape sequence
    }

    //  is digit or symbol 2
    if ( _ds1_(c) ) {

      if ( _ds2_(c) ) tkNumL( _sNUM_, c )   //  number literal
      //  is = sign
      if ( c == eq ) tkCode( _sEQ_ )        //  equal sign
      //  symbol 2 lower than equal sign
      if ( _s2lo_(c) ) {
        //  is ; separator
        if ( c == sc ) tkPass( _sSE_, c )   //  separator
        if ( c == lt ) tkPass( _sCMP_, c )  //  compare operator
        tkCode( _sCOL_ );                   //  colon ':'
      }
      //  symbol 2 greater tha equal sign
      if ( c == gt ) tkPass( _sCMP_, c )    //  compare operator
      if ( c == qm ) tkCode( _sQST_ )       //  question mark
      tkPass( _sSYM_, c )                   //  symbol 2, '@'
    }

    //  is symbol 1
    if ( _s1ws_(c) ) {
      
      //  symbol 1 greater than equal sign
      if ( _s1hi_(c) ) {
        //  is ( or ) separator
        if ( (c == lp) || (c == rp) )       //  separator
          tkPass( _sSE_, c )
        if ( c == dt ) tkCode( _sDOT_ )     //  dot sign
        if ( c == cm ) tkCode( _sCM_ )      //  comma
        tkPass( _sMTH_, c )                 //  basic math operator
      }
      //  symbol 1 lower than equal sign
      //  single and double quotes ', "
      if ( (c == qt) || (c == dq) )         //  string literal
        tkStrL( _sSTR_ )
      //  amperes and
      if ( c == aa ) tkPass( _sBWO_, c )    //  bitwise operator
      if ( c == ds ) tkIdL( _sID_, c )      //  dollar sign, valid identifier
      if ( c == bg ) tkPass( _sBWO_, c )    //  '!' bitwise operator
      if ( c == pe ) tkPass( _sMTH_, c )    //  '%' basic math operator
      tkPass( _sSYM_, c );                  //  symbol 1, '#'
    }
    
    // is space or lower control character
    if ( _ws_(c) ) tkReduce( _sWS_ )        //  white space
    if ( _nl_(c) ) tkReduce( _sNL_ )        //  new line
    if ( _stx_(c) ) tkCode( _sSTART_ )      //  start of text
    if ( _etx_(c) ) tkCode( _sSTOP_ )       //  end of text

    return _sUK_;    //  unknown
  }
  //  character hex 00
  return _sUK_;
}

inline void lx_print_code( char c ) {
  return;
}
