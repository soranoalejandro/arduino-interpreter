/* test program for the lexer scanner and lexer evaluator
 * 
 * Alejando Solano, July 2020.
 * 
 * USE CASE
 * send source code thought the Arduino serial monitor (terminal)
 */

//  IMPORTANT, max size of the ram buffer for this test
//  set it to aprox 65% of your board total memory (RAM)

#include "scanner.h"

#define SERIAL_BAUDRATE 115200
#define AUTO_END_TIME  6700L

Scanner s = Scanner();
unsigned long lastScan = 0;
unsigned long elapsed = 0;
boolean haveData = false;
void printData();

void loop() {


  // detect automatic end of transission
  if ( haveData ) {
    elapsed = millis();
    elapsed = elapsed - lastScan;
    if ( elapsed > AUTO_END_TIME ) {
      s.end();
      haveData = false;
      // print data
      printData();
      s.begin();
    }
  }
}


void serialEvent() {
  while ( Serial.available() ) {
    byte c = Serial.read();
    s.scan(c);
  }
  lastScan = millis();
  haveData = true;
}

void printData() {
  Serial.print("\nInput bytes: ");
  Serial.print( (uint32_t)s.CharactersStat() );
  Serial.print(",  Token bytes: ");
  Serial.print( (uint32_t)s.tokenStat() );
  Serial.print(",  Data bytes: ");
  Serial.println( (uint32_t)s.dataStat() );
  Serial.print("\n");
  int n = s.length();
  byte l, x, d;
  //byte d, len;
  //Serial.println('\n');
  while ( n > 0 ) {
    d = s.get();  //  get scan code
    l = 0;  x = 0;
    if ( d < sWS ) {
      switch (d) {
        case sLID:  Serial.print("LC ");  break;
        case sUID:  Serial.print("UC ");  break;
        case sID:  Serial.print("ID ");  break;
        case sdAT:  Serial.print("DE ");  break;
        case sdHA:  Serial.print("DE ");  break;
        case sSTR:  Serial.print("STR ");  break;
        case sSTT:  Serial.print("STT ");  break;
      }
      if ( (d >= sLID) && (d <= sSTT) ) {
        l = 1;  x = 1;
      }
    }
    else if ( d < sEQ ) {
      switch (d) {
        case sWS:  Serial.print(' ');  break;
        case sNL:  Serial.print('\n');  break;
        case sLP:  Serial.print("( ");  break;
        case sRP:  Serial.print(") ");  break;
        case sLB:  Serial.print("[ ");  break;
        case sRB:  Serial.print("] ");  break;
        case sLC:  Serial.print("{ ");  break;
        case sRC:  Serial.print("} ");  break;
      }
    }
    else if ( d < sNUM ) {
      switch (d) {
        case sEQ:  Serial.print("= ");  break;
        case sDOT:  Serial.print(". ");  break;
        case sCM:  Serial.print(", ");  break;
        case sGT:  Serial.print("> ");  break;
        case sLT:  Serial.print("< ");  break;
      }
    }
    else if ( (d >= sNUM) && (d <= shNU) ) {
      switch (d) {
        case sNUM:  Serial.print("NUM ");  break;
        case snNU:  Serial.print("nNUM ");  break;
        case s0NU:  Serial.print("0NUM ");  break;
        case s2NU:  Serial.print("BIN ");  break;
        case s8NU:  Serial.print("OCT ");  break;
        case shNU:  Serial.print("HEX ");  break;
      }
      l = 1;
    }
    else if ( d < smPL ) {
      switch (d) {
        case sbAND:  Serial.print("& ");  break;
        case sbOR:  Serial.print("| ");  break;
        case sbXOR:  Serial.print("^ ");  break;
        case sbNOT:  Serial.print('!');  break;
        case sbyNOT:  Serial.print('~');  break;
      }
    }
    else if ( d < sSC ) {
      switch (d) {
        case smPL:  Serial.print("+ ");  break;
        case smMI:  Serial.print("- ");  break;
        case smMU:  Serial.print("* ");  break;
        case smDI:  Serial.print("/ ");  break;
        case smPE:  Serial.print("% ");  break;
      }
    }
    #define sSC 70      //  semi colon
#define sQST 71     //  question mark
#define sCOL 72     //  colon
#define sSYM 73     //  symbol
#define sEXT 74     //  extended ascii character, decimal 127 to 255
    else if ( d < sSTR_END ) {
      switch (d) {
        case sSC:  Serial.print("; ");  break;
        case sQST:  Serial.print('?');  break;
        case sCOL:  Serial.print(": ");  break;
        case sSYM:  Serial.print("SYM ");  break;
        case sEXT:  Serial.print("EXT ");  break;
      }
    }
    if ( l ) {
      ///Serial.print(" L:");
      ///Serial.print( (byte)s.get() );
      (byte)s.get();
    }
    if ( x ) {
      ///Serial.print(" X:");
      ///Serial.print( (byte)s.get() );
      (byte)s.get();
    }
    if ( l | x ) {
      ///Serial.write('\n');
      l = 0;  x = 0;
    }
    n = s.length();
    ///Serial.write(" n: ");
    ///Serial.print(n);
  }
}

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  while (!Serial) { ;}
  Serial.println("\t\tArduino Interpreter - Lexer\n");
}
