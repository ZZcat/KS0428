/*This is where you write the code you want to run*/
#include "Arduino.h"
#include "KS0428.h"

// Figure out how to set IRremote as dep. of self
#include <IRremote.h>

#define IIC_SCL  A5
#define IIC_SDA  A4


unsigned char data_line = 0;

unsigned char delay_count = 0;

long ir_rec;

IRrecv irrecv(A0);
decode_results results;

volatile int pulsewidth;

void IIC_start()
{
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);}

void IIC_send(unsigned char send_data)
{
  for(char i = 0;i < 8;i++)
  {
      digitalWrite(IIC_SCL,LOW);
      delayMicroseconds(3);
      if(send_data & 0x01)
      {
        digitalWrite(IIC_SDA,HIGH);
      }
      else
      {
        digitalWrite(IIC_SDA,LOW);
      }
      delayMicroseconds(3);
      digitalWrite(IIC_SCL,HIGH);
      delayMicroseconds(3);
      send_data = send_data >> 1;
  }
}

void IIC_end()
{
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);}


void procedure(int myangle) {
  for (int i = 0; i <= 50; i = i + (1)) {
    pulsewidth = myangle * 11 + 500;
    digitalWrite(9,HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(9,LOW);
    delay((20 - pulsewidth / 1000));
  }
}

/// Z ?//

void ledDisplay (unsigned char *displayHex)
{
  IIC_start();
    IIC_send(0xc0);
    for(char i = 0;i < 16;i++)
    {
       IIC_send(displayHex[i]);
    }
    if(++delay_count >= 10)
    {
      delay_count = 0;
      data_line++;
      if(data_line >= 4)
      {
        data_line = 0;
      }
    }
    IIC_end();
    IIC_start();
    IIC_send(0x8A);
    IIC_end();
}

float checkdistance() { // Ultrasonic sensor
  digitalWrite(5, LOW);
  delayMicroseconds(2);
  digitalWrite(5, HIGH);
  delayMicroseconds(10);
  digitalWrite(5, LOW);
  float distance = pulseIn(4, HIGH) / 58.00;
  delay(10);
  return distance;
}

void rotateServo(int myangle) {
  for (int i = 0; i <= 50; i = i + (1)) {
    pulsewidth = myangle * 11 + 500;
    digitalWrite(9,HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(9,LOW);
    delay((20 - pulsewidth / 1000));
  }
}

void motor(int left, int right){
  if (left == -1) {
    digitalWrite(13, HIGH);
    analogWrite(11, 200);
  } else if (left == 0) {
    digitalWrite(13, LOW);
    analogWrite(11, 0);
  } else if (left == 1) {
    digitalWrite(13, LOW);
    analogWrite(11, 200);
  }

  if (right == -1) {
    digitalWrite(12, HIGH);
    analogWrite(3, 200);
  } else if (right == 0) {
    digitalWrite(12, LOW);
    analogWrite(3, 0);
  } else if (right == 1) {
    digitalWrite(12, LOW);
    analogWrite(3, 200);
  }
}

int lightL () {
 return analogRead(A1);
}

int lightR () {
 return analogRead(A2);
}

int getIR () {
    if (irrecv.decode(&results)) {
      ir_rec=results.value;
      Serial.println(ir_rec,HEX);
      irrecv.resume(); // Clear buffer and allow new data. Appears to capture first signal
    }
    return ir_rec;
}

void robotSetup () {

  irrecv.enableIRIn();
  pinMode(12, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(IIC_SCL,OUTPUT);
  pinMode(IIC_SDA,OUTPUT);
  digitalWrite(IIC_SCL,LOW);
  digitalWrite(IIC_SDA,LOW);
  IIC_start();
    IIC_send(0x40);
    IIC_end();
    IIC_start();
    IIC_send(0xc0);
    pulsewidth = 0;
    pinMode(9, OUTPUT);

  //procedure(90);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(IIC_SCL,OUTPUT);
  pinMode(IIC_SDA,OUTPUT);
  digitalWrite(IIC_SCL,LOW);
  digitalWrite(IIC_SDA,LOW);
  IIC_start();
    IIC_send(0x40);
    IIC_end();
    IIC_start();
    IIC_send(0xc0);
  pinMode(5, OUTPUT);
  pinMode(4, INPUT);
    pinMode(IIC_SCL,OUTPUT);
  pinMode(IIC_SDA,OUTPUT);
  digitalWrite(IIC_SCL,LOW);
  digitalWrite(IIC_SDA,LOW);
}


