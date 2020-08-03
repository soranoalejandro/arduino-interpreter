/* test program for the lexer scanner and lexer evaluator
 * 
 * Alejando Solano, July 2020.
 */
 

//  IMPORTANT, max size of the ram buffer for this test
//  set it to aprox 65% of your board total memory (RAM)

/*  Console baudrate */
#define TEST_SERIAL_BAUDRATE 9600
/*  Automatic end of file detection time in milliseconds - default */
#define TEST_AUTO_END_TIME  2900

//  USE CASE
//  send source code thought the Arduino serial monitor (terminal)

/* TEST FOR SPEED
 *  you may send a file of any arbitrary size (even greater than the buffer)
 *  this will test the speed of the scanner stage of the lexer (still under development)
 *  for a graphical representation of the processing use the previous commit '2dn test' of his repository
 *  test any c, python, javascript... existing source code files, open libraries are good candidates.
 */
#include "c_buffer.h"
#include "lexer.h"
//extern "C"{
//  #include "lexer.h"
//};

static byte arr[20];
size_t arrSize = sizeof(arr);
CBuffer smallBuffer = CBuffer( arrSize, arr );


void c_buffer_test();

//  initial arduino setup funtion
void setup() {
  Serial.begin(TEST_SERIAL_BAUDRATE);
  while (!Serial)
  Serial.println("\t\tArduino Interpreter - Lexer");
  Serial.println("\t\t___________________________\n");
  Serial.println("Type source code to put the lexer up to speed !!!.\n");
  delay(500);  //c_buffer_test();
}

void loop() {
  c_buffer_test();
  delay(2000);
}

void c_buffer_test() {
  byte b;
  smallBuffer.write(3);
  delay(2000);
  smallBuffer.write(11);
  delay(2000);
  
  smallBuffer.readFirst();
  delay(2000);
  smallBuffer.readFirst();
  delay(2000);
  smallBuffer.readFirst();
  delay(2000);
}
