/*
  Test.h - Test library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include core Wiring API
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// include this library's description file
#include "c_buffer.h"

// include description files for other libraries used (if any)
//#include "HardwareSerial.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

CBuffer::CBuffer(const size_t Size, byte* addr)
{
  // initialize this instance's variables
  if (Size > 127) size = 127; else size = (uint8_t)Size;
  base = addr;
  length = 0;
  readAddress = 0;
  writeAddress = 0;
  return;
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries


int8_t CBuffer::available() {
  return length;
}
int8_t CBuffer::availableForWrite() {
  return (size - length);
}
int8_t CBuffer::write(byte d) {
  if ( availableForWrite() ) {
    // protect here latter
    Serial.print("badd:");  Serial.println((uint16_t)base);
    Serial.print("wadd:");  Serial.println(writeAddress);
    data = (base+writeAddress);
    Serial.print("dadd:");  Serial.println((uint16_t)data);
    *data = d;
    Serial.print("value:");  Serial.println(*data);
    writeAddress++;
    Serial.print("wadd:");  Serial.println(writeAddress);
    writeAddress %= size;
    Serial.print("wadd:");  Serial.println(writeAddress);
    ++length;  return 1;
  }
  return 0;
}
int8_t CBuffer::readFirst() {
  if ( available() ) {
    // protect here latter
    byte b;
    data = (base+readAddress);
    Serial.print("badd:");  Serial.println((uint16_t)base);
    Serial.print("radd:");  Serial.println(readAddress);
    Serial.print("dadd:");  Serial.println((uint16_t)data);
    Serial.print("value:");  Serial.println(*data);
    b = *data;
    Serial.print("value:");  Serial.println(*data);
    readAddress++;
    Serial.print("radd:");  Serial.println(readAddress);
    readAddress %= size;
    Serial.print("radd:");  Serial.println(readAddress);
    --length;  return b;
  }
  return -1;
}
int8_t CBuffer::readLast() {
  return -1;
}
int8_t CBuffer::peekFirst() {
  if ( available() ) {
    // protect here latter
    byte b;
    b = *(data+readAddress);
    return b;
  }
  return -1;
}
int8_t CBuffer::peekLast() {
  return -1;
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
