#pragma once
#include "ascii_codes.h"

//  the names implies LIMITS between character groups in ascii, ex:
//  A_d implies the limmit between Upercase A range and digit 9 range
//  the condition gives true for the first element in its name, A inthe example above
#define a_A(c) (c > '`')    //  a lower case start
#define a_s4(c) (c < '{')   //  z lower case end
#define s4_ex(c) (c < 127)  //  s4 or exended ascii
#define A_d(c) (c > '@')    //  A upper case start
#define A_s3(c) (c < '[')   //  Z uppercase end
#define d_s1(c) (c > '/')   //  0 digit start
#define d_s2(c) (c < ':')   //  9 digit end
#define s1_ws(c) (c > sp)   //  greater than ' ' space character
#define s1_hi(c) (c > ')')  //  s1 upper half
#define s2_lo(c) (c < '=')  //  s2 lower half


//  RANGE and multi range comparators, ex: 'is alphanumeric'.

//  Will be used less whenever possible because range are slower than limits
#define _lo_(x) ((x < '{') & (x > '`'))   //  lower case range
#define _up_(x) ((x < '[') && (x > '@'))   //  upper case range
#define _nu_(x) ((x < ':') && (x > '/'))   //  digits range
#define _al_(x) (_lo_(x) || _up_(x))   //  letters -upper and lower case- range
#define _an_(x) (_al_(x) || _nu_(x))   //  alphanumeric range -upper, lower and digits
#define _id_sy_(x) ((x == us) || (x == ds)) //  extra JS id symbols '_' and '$'
#define _id_(x) (_an_(x) || _id_sy_(x)) //  JS id,  alphanumeric, symbols '_' and '$'
#define _de_sy_(x) ((x == at) || (x == ha)) //  extra JS decorator symbols '@' and '#'
#define _ws_(x) ((x == sp) || (x == tb))    //  whitespace symbols
#define _nl_(x) ((x == nl) || (x == cr))    //  new line symbols
#define _stx_(x) (x == 2)                   //  start of text
#define _etx_(x) (x == 3)                   //  end of text
#define _sy1_(x) ((x < '0') && (x > sp))   //  symbols range 1
#define _sy2_(x) ((x < 'A') && (x > '9'))  //  symbols range 2
#define _sy3_(x) ((x < 'a') && (x > 'Z'))  //  symbols range 3
#define _sy4_(x) ((x < 127) && (x > 'z'))  //  symbols range 4
#define _sy_(x) (_sy1_(x) || _sy2_(x) || _sy3_(x) || _sy4_(x))  //  symbols range ALL
#define _pr_(x) ((x < 127) & (x > 32))    //  printable characters
