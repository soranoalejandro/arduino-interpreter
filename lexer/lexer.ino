/* test program for the lexer scanner and lexer evaluator
 * 
 * Alejando Solano, July 2020.
 */

//  IMPORTANT, max size of the ram buffer for this test
//  set it to aprox 65% of your board total memory (RAM)

#define TEST_BUFFER_SZ  5500

//  Console baudrate
#define TEST_SERIAL_BAUDRATE  230400
//  Automatic end of file detection time in milliseconds - default
#define TEST_AUTO_END_TIME  2900

//  USE CASE
//  send source code thought the Arduino serial monitor (terminal)

//  TEST FOR SPEED
//  you may send a file of any arbitrary size (even greater than the buffer)
//  this will test the speed of the scanner stage of the lexer (still under development)
//  for a graphical representation of the processing use the previous commit '2dn test' of his repository

//  test any c, python, javascript... existing source code files, open libraries are good candidates.


unsigned long stamp, lastChar;
unsigned long elapsed, time_us;

char tk[TEST_BUFFER_SZ];      //  an ARRAY to hold generated -outgoing- data
unsigned indx = 0;            //  current index of outgoing data buffer

//  include the LEXER code to test it (mus have acces to the 2 variables above)
#include "lexer.h"


//  initial arduino setup funtion
void setup() {
  Serial.begin(TEST_SERIAL_BAUDRATE);
  while (!Serial) { ;} // wait for serial port to connect.
  // print title
  Serial.println("\t\tArduino Interpreter - Lexer");
  Serial.println("\t\t___________________________\n");
  Serial.println("Type source code to put the lexer up to speed !!!.\n");
}

unsigned int count;
unsigned long inCount, outCount;
char in, scan;


void loop() {
  byte cc;
  byte bu[30];
  cc = Serial.available();
  if ( cc > 19 ) {
    //  set bytes to load = 20. 
    cc = 20;
    //  add 20 to total in bytes counter
    inCount += cc;
    //  load 20 incomming chars into a buffer
    for (byte i = 0; i < cc; i++) {
      bu[i] = (char)Serial.read();
    }
    cc = 0;
    stamp = micros();   //  record start time
    //  MAIN SCAN INSTRUCTION
    //  REPEATED 20 times mannually to ignore the small delay in for loops
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    lx_scan(bu[cc++]);
    //  record time of last character processeed
    lastChar = micros();
    elapsed = lastChar - stamp;
    //  add to incremental processing time value
    time_us += elapsed;
    
    //  mark a new start (this time in milliseconds
    //  for the 400ms second automatic end of file detection
    elapsed = lastChar - stamp;
    lastChar = millis();
    
    //  if buffer is about to be overrrun 
    if (indx > (TEST_BUFFER_SZ - 100) ) {
      outCount += indx;     //  keep count of al lossed data for report 
      indx = 0;             //  reset the buffer
    }
  }


  //  automatic end of file detecton timer1
  elapsed = millis();
  elapsed -= lastChar;

  //  end of file detected
  if ( (elapsed > TEST_AUTO_END_TIME) && (indx > 0) ) {
    //  print the buffer, SCAN CODES will only show a '.'
    char val;
    for (unsigned int n = 0; (n < indx) ; n++) {
      val = tk[n];
      if ( val < 32) {
        if ( ( val != _sWS_ ) && ( val != _sNL_ ) && ( val != _sCMN_ ) )
        
        lx_print_code(val);
      } 
      else {
        Serial.print(val);
        if ( val != ';' ) {
          Serial.print(" ");
        }
        else {
          Serial.println("");
        }
      }
    }
    outCount += indx;
    //  print inpud file and generated byte sizes
    Serial.println("\n");  Serial.print(inCount);  Serial.print(" Bytes in / ");
    Serial.print(outCount);  Serial.print("Bytes out, in ");
    //  print total execution time in microseconds 0.000_001s
    Serial.print(time_us);  Serial.println(" us.");

    //  calculate and print SCANNER average speed
    float f;
    
    //  of input stream
    f = (float)(inCount * 8L);  f /= (float)time_us;  Serial.print(f);  Serial.print(" Mib/s  /  ");
    f = (float)inCount;  f *= 1000.0;  f /= (float)time_us;  Serial.print(f);  Serial.println(" KByte/s  in");
    
    //  of output stream
    f = (float)(outCount * 8L); f /= (float)time_us;  Serial.print(f);  Serial.print(" Mib/s  /  ");
    f = (float)outCount;  f *= 1000.0;  f /= (float)time_us;  Serial.print(f);  Serial.println(" KByte/s  out\n");

    //  reset buffer index,  
    indx = 0;  inCount = 0; outCount = 0;  time_us = 0;
  }
  
}
