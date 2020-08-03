/*
  Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef c_buffer
#define c_buffer

// include types & constants of Wiring core API
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// library interface description
class CBuffer
{
  // user-accessible "public" interface
  public:
    CBuffer(const size_t Size, byte* addr);
    int8_t available();
    int8_t availableForWrite();
    int8_t write(byte);
    int8_t readFirst();
    int8_t readLast();
    int8_t peekFirst();
    int8_t peekLast();
  // library-accessible "private" interface
  protected:
    
    uint8_t size;
    uint8_t length;
    uint8_t writeAddress;
    uint8_t readAddress;
    byte* base;
    byte* data;
};

#endif
