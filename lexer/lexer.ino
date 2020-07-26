#include "lexer.h"
String token = "";        // a String to hold incoming data
bool _letter_, _upper_, _lower_, _digit_, _underscore_, _dollarsign_;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  token.reserve(200);
  token = "";
  // prints title with ending line break
  Serial.println("\n\t\tArduino Interpreter - Lexer\n");
}

void loop() {
  if (Serial.available()) {
    char in = (char)Serial.read();
    static char prev = 0;
    char scan = lxScan( in );
    if ( scan != prev ) {     //  new token, print type
<<<<<<< HEAD
      token = "";             //  save and discard array
      if ( (prev != 0) & (prev != _sNL_)& (prev != _sWS_) ) {
        if ( scan != _sSTR_END_ ) {
          Serial.print("   ");
        }
=======
      if ( prev ) {           //  if previous token had data, reprint it, then clear the buffer
        Serial.print("   length:   ");
        Serial.print( token.length() );
        Serial.print("   ");
        Serial.print( token );
        Serial.print("\n");
      }
      token = "";             //  save and discard array
      if ( prev & (!scan) ) {           //  re-scan
        scan = lxScan( in );
>>>>>>> parent of 9574ce6... 2nd test, recognizes Id, number, ws, nl, symbol
      }
      Serial.print("Type:   ");
      switch ( scan ) {
        case _sID_:
        Serial.print("Identifier");
        break;
        case _sWS_:
        Serial.print("Whitespace");
        break;
        case _sSY_:
        Serial.print("Symbol    ");
        break;
<<<<<<< HEAD
        case _sNUM_:
        Serial.print("NUM");
=======
        case _sNU_:
        Serial.print("Number    ");
>>>>>>> parent of 9574ce6... 2nd test, recognizes Id, number, ws, nl, symbol
        break;
        case _sSTR_:
        Serial.print("STR");
        break;
        case _sSTR_END_:
        break;
        default:
        Serial.print("End       ");
        break;
      }
<<<<<<< HEAD
      if ( (scan == _sID_) | (scan == _sNUM_) | (scan == _sSY_) | (scan == _sSTR_) ) {
        Serial.print(" ");
      }
      if ( !scan | ( scan == _sNL_ ) ) {
        Serial.print("\n");
      }
    }
    if ( (scan == _sID_) | (scan == _sNUM_) | (scan == _sSY_) ) {
      token += in;
      Serial.print(in);
    } else if ( (scan == _sSTR_) | (scan == _sSTR_END_) ) {
=======
      Serial.print("   ");
      if ( !scan ) {
        Serial.print("\n");
      }
    }
    if ( scan ) {
>>>>>>> parent of 9574ce6... 2nd test, recognizes Id, number, ws, nl, symbol
      token += in;
      Serial.print(in);
    }
    prev = scan;
  }
  delay(500);
}

//void serialEvent() {
//  
//}
