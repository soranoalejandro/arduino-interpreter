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
      token = "";             //  save and discard array
      if ( (prev != 0) & (prev != _sNL_)& (prev != _sWS_) ) {
        Serial.print("   ");
      }
      switch ( scan ) {
        case _sID_:
        Serial.print("ID");
        break;
        case _sWS_:
        //Serial.print("");
        break;
        case _sNL_:
        //Serial.print("LINE\n");
        break;
        case _sSY_:
        Serial.print("SYM");
        break;
        case _sNU_:
        Serial.print("NUM");
        break;
        default:
        Serial.print("???   ");
        break;
      }
      if ( (scan == _sID_) | (scan == _sNU_) | (scan == _sSY_) ) {
        Serial.print(" ");
      }
      if ( !scan | ( scan == _sNL_ ) ) {
        Serial.print("\n");
      }
    }
    if ( (scan == _sID_) | (scan == _sNU_) | (scan == _sSY_) ) {
      token += in;
      Serial.print(in);
    }
    prev = scan;
  }
  //delay(20);
}
