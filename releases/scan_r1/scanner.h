/* scanner module of the arduino-interpreter project
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
// ensure this library description is only included once
#pragma once
#ifndef scanner
#define scanner
// include types & constants of Wiring core API
#include <Arduino.h>
#include "src/c_buffer.h"
#include "scanner_codes.h"
#include "src/ascii_compare.h"

#ifndef SCANNER_BUFFER
#define SCANNER_BUFFER 1200
#endif

class Scanner
{
  public:
    Scanner();
    void scan(byte c);
    void begin();
    void end();
    uint32_t CharactersStat();
    uint32_t tokenStat();
    uint32_t dataStat();
    size_t length();
    char get();
    
  private:
    uint16_t Line;
    uint16_t Column;
    uint32_t Character;
    char lastChar;
    byte lastToken;
    byte waitConsecutive;
    byte Xor;
    byte stop_char;
    byte aData[70];
    CBuffer data = CBuffer(sizeof(aData), aData);
    byte aToken[5200];
    CBuffer token = CBuffer(sizeof(aToken), aToken);
};

#endif
