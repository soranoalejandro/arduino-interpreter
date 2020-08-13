/*
  Buffer.cpp - Test library for Wiring - implementation
  Copyright (c) 2006 Alejandro Solano.  MIT License.
*/
// ensure this library description is only included once
#pragma once
#ifndef c_buffer
#define c_buffer
// include types & constants of Wiring core API

#include <Arduino.h>


class CBuffer
{
  public:
    CBuffer(const size_t Size, byte* addr);
    int16_t available();
    int16_t availableForWrite();
    int16_t write(byte);
    byte readFirst();
    byte readLast();
    byte peekFirst();
    byte peekLast();
    byte replaceFirst(byte);
    byte replaceLast(byte);
    size_t length();
    size_t lengthStat();
    uint32_t totalStat();
    uint32_t lostStat();
    void clearStats();
    void clear();
    
  private:
    uint16_t size;
    uint16_t Length;
    uint16_t LengthStat;
    uint32_t TotalStat;
    uint32_t LostStat;
    uint16_t tail;
    uint16_t head;
    byte* base;
    byte* data;
};

#endif
