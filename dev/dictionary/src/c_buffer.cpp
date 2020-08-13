/*
  Buffer.h - Test library for Wiring - implementation
  Copyright (c) 2006 Alejandro Solano.  MIT License.
*/

#include <Arduino.h>

// include this library's description file
#include "c_buffer.h"

CBuffer::CBuffer(const size_t Size, byte* addr) {
  // initialize this instance's variables
  if (Size > 32767) size = 32767; else size = Size;
  base = addr;
  clear();
  clearStats();
  return;
}

int16_t CBuffer::available() {
  return Length;
}
int16_t CBuffer::availableForWrite() {
  return (size - Length);
}
int16_t CBuffer::write(byte d) {
  if ( availableForWrite() ) {
    // protect here latter
    tail++;
    tail %= size;
    data = (base+tail);
    *data = d;
    //Serial.println( (char)*data );
    ++Length;
    //Serial.println( Length );
    LengthStat = max( LengthStat, Length );
    TotalStat += 1;
    return 1;
  }
  LostStat += 1;
  return 0;
}
byte CBuffer::readFirst() {
  if ( available() ) {
    // protect here latter
    byte b;
    data = (base+head);
    b = *data;
    head++;
    head %= size;
    --Length;  return b;
  }
  return 0;
}
byte CBuffer::readLast() {
  if ( available() ) {
    // protect here latter
    byte b;
    data = (base+tail);
    b = *data;
    tail++;
    tail %= size;
    --Length;  return b;
  }
  return 0;
}
byte CBuffer::peekFirst() {
  if ( available() ) {
    // protect here latter
    byte b;
    data = (base+head);
    b = *data;
    return b;
  }
  return 0;
}
byte CBuffer::peekLast() {
  if ( available() ) {
    // protect here latter
    byte b;
    data = (base+tail);
    b = *data;
    return b;
  }
  return 0;
}
byte CBuffer::replaceFirst(byte d) {
  if ( available() ) {
    // protect here latter
    data = (base+head);
    *data = d;
    TotalStat += 1;
    return d;
  }
  return -1;
}
byte CBuffer::replaceLast(byte d) {
  if ( available() ) {
    // protect here latter
    data = (base+tail);
    *data = d;
    TotalStat += 1;
    return d;
  }
  return -1;
}
void CBuffer::clear() {
  Length = 0;  head = 1;  tail = 0;
  return;
}
size_t CBuffer::lengthStat() {
  return LengthStat;
}
uint32_t CBuffer::totalStat() {
  return TotalStat;
}
uint32_t CBuffer::lostStat() {
  return LostStat;
}
size_t CBuffer::length() {
  return Length;
}
void CBuffer::clearStats() {
  LengthStat = 0;  TotalStat = 0;  LostStat = 0;
  return;
}
