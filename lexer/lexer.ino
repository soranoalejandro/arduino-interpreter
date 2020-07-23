#include "lexer.h"

//  COPY OF THE ARDUINO 'AnalogReadSerial' BASIC EXAMPLE FILE FROM THE IDE, will be modified for the initial tests

const int analogInPin = A0;  // Analog input pin
const int analogOutPin = 9; // Analog output pin
int sensorValue = 0;    int outputValue = 0;    // value read from the pot, value output to the PWM (analog out)

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(analogOutPin, outputValue);
  
  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.print(outputValue);
  Serial.print("OP code is:  '");
  Serial.print(op);
  Serial.println("'");
  
  delay(1200);
}
