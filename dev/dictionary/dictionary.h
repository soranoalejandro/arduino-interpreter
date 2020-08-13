/*
  dictionary.h - word and strings store with basic compression
  2020, Alejandro Solano.  MIT License.
*/
// ensure this library description is only included once
#pragma once
#ifndef dictionary
#define dictionary
// include types & constants of Wiring core API
#include <Arduino.h>
#include "src/c_buffer.h"
#include "scanner_codes.h"
#include "src/ascii_compare.h"


class Dictionary
{
  public:
    Dictionary();
    uint8_t add(const CBuffer*, byte Xor);
    
  private:
    uint8_t lxor;
};

#endif
