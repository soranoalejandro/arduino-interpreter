/* Test program for the 'scanner' module of the arduino-interpreter project
 * release: 0.1
 * USE:
 * -Send source code through the Arduino serial monitor,
 *  the scanner will store only tokens in RAM memory, 
 *  and print the data (if any) back to the serial port
 * -After an automatic end of transmission detection time,
 *  the program will print all the tokens and clear the RAM
 *  buffer  to start a new test
 * -See scanner_codes.h for the meaning of each token
 * license: MIT, see LICENSE file
 * created: Alejandro Solano, July 2020
 * modified: August 12, 2020
 */

//  IMPORTANT, max size of the scanner buffer for this test
//  set it to aprox 65% of your board total memory (RAM)
// 5000 for testing in mega, 1200 for arduino
#define SCANNER_BUFFER 5000   
#include "scanner.h"

#define SERIAL_BAUDRATE 115200  //  set 'newline' in the arduino serial monitor too
#define AUTO_END_TIME  8000L  // is unsigned long so must put L at the end of the number
//  millisecons to detect end of transmission and print out the tokens
//  adjust to give you more time to type/paste and send code from serial monitor
//  you can paste multiple lines or files at a time using alternative serial terminals like teraterm


Scanner s = Scanner();
unsigned long lastScan = 0;
unsigned long elapsed = 0;
boolean haveData = false;
void printData();


void loop() {
  if ( haveData ) {
    // detect automatic end of transission
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

//  scan received characters from the serial port
void serialEvent() {
  while ( Serial.available() ) {
    byte c = Serial.read();
    s.scan(c);
  }
  lastScan = millis();
  haveData = true;
}


void printData() {
  //  print byte size statistics
  Serial.print("\nInput bytes: ");
  Serial.print( (uint32_t)s.CharactersStat() );
  Serial.print(",  Token bytes: ");
  Serial.print( (uint32_t)s.tokenStat() );
  Serial.print(",  Data bytes: ");
  Serial.println( (uint32_t)s.dataStat() );
  Serial.print("\n");
  //  
  int n = s.length(); // current buffer length
  byte l, x, d;
  while ( n > 0 ) {
    d = s.get();      //  get token code
    l = 0;  x = 0;
    if ( d < sWS ) {  //  see scanner_codes.h file to understand each token code
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
        l = 1;  x = 1;    //  this token has aditional length and xor data
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
      l = 1;  //  this token has aditional length data
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
      ///Serial.print("Len:");  //  code to print ID or STRING lengths
      ///Serial.print( (byte)s.get() );
      ///Serial.print(" ");
      (byte)s.get();  //  read string length value without printing it
    }
    if ( x ) {
      ///Serial.print("Xor:");  //  code to print ID or STRING xor chexksums
      ///Serial.print( (byte)s.get() );
      ///Serial.print(" ");
      (byte)s.get();  //  read string xor value without printing it
    }
    if ( l | x ) {
      l = 0;  x = 0;
    }
    n = s.length();
  }
}

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  while (!Serial) { ;}
  Serial.println("\t\tArduino Interpreter - Lexer\n");
}
