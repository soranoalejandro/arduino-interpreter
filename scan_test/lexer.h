#pragma once
/* Function:
 * divides code sentences into lexeme tokens ex:
 *  'var x = 523' gives -> keyword(var), id(x), symbol(=), number literal(555)
 * it has two steps:  character SCAN, LEXER.
 * SCAN recognize basic character sequence types.
 * LEXER resolves ambigueties and reconstrucs lexemes with mixed
 * character sequences, ex: '1.23e-12' has numbers, dot and + - sign sequences
 *   Alejandro Solano, july 2020.
 */
#ifndef Lexer_h
#define Lexer_h

#ifdef ARDUINO > 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "ascii_compare.h"
#include "keywords_js.h"
#include "lx_token_types.h"


        //    FUNCTIONS

//  SCAN function
inline char lx_scan( char c );

#endif
