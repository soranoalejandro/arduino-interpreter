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
        case _sNU_:
        Serial.print("Number    ");
        break;
        default:
        Serial.print("End       ");
        break;
      }
      Serial.print("   ");
      if ( !scan ) {
        Serial.print("\n");
      }
    }
    if ( scan ) {
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
