#include <IR.h>
#ifndef SoftwareSerial_h
#error Sketch must include SoftwareSerial.h
#endif


#ifndef KS0428_h
#define KS0428_h
 
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

void ledDisplay (unsigned char *displayHex);
float checkdistance();
void motor(int left, int right);
void rotateServo(int myangle);
void robotSetup();
int lightL();
int lightR();
int getIR();
#endif
