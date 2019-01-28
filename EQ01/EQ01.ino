#include <Servo.h>

// MSGEQ7
#include "MSGEQ7.h"
#define pinAnalogLeft A12
#define pinAnalogRight A13
#define pinReset 6
#define pinStrobe 4
#define MSGEQ7_INTERVAL ReadsPerSecond(20)
#define MSGEQ7_SMOOTH false

CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, pinAnalogLeft, pinAnalogRight> MSGEQ7;

Servo motorPWM;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;

int motorSpeed;
int pot1;           // motor control
int pot2;           // EQ sensitivity

int pos1;
int pos2;
int pos3;
int pos4;
int pos5;
int pos6;
int pos7;

unsigned long previousMillis = 0;
const long interval = 20;


void setup() {

  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  pinMode(2, OUTPUT);   // motor/servo PWM
  motorPWM.attach(2);   // motor/servo PWM

  servo7.attach(41);    // low fequency
  servo6.attach(43);
  servo5.attach(45);
  servo4.attach(47);
  servo3.attach(49);
  servo2.attach(51);
  servo1.attach(53);    // high frequency
  
  MSGEQ7.begin();       // start MSGEQ7

  Serial.begin(57600);

}

void loop() {


     unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {  //start timed event
          previousMillis = currentMillis;

          pot1 = analogRead(A4);        
          motorSpeed = map(pot1, 0,1023, 90,180);            
          motorPWM.write(motorSpeed);

          // Analyze without delay every interval
          bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);
  
          // 1st channel (here: left)
          Serial.print(MSGEQ7.get(MSGEQ7_0, 1));
          Serial.print(F(" \t"));
          
          Serial.print(MSGEQ7.get(MSGEQ7_1, 1));
          Serial.print(F(" \t"));
        
          Serial.print(MSGEQ7.get(MSGEQ7_2, 1));
          Serial.print(F(" \t"));
        
          Serial.print(MSGEQ7.get(MSGEQ7_3, 1));
          Serial.print(F(" \t"));
        
          Serial.print(MSGEQ7.get(MSGEQ7_4, 1));
          Serial.print(F(" \t"));
        
          Serial.print(MSGEQ7.get(MSGEQ7_5, 1));
          Serial.print(F(" \t"));
        
          Serial.print(MSGEQ7.get(MSGEQ7_6, 1));
          Serial.print(F(" \t"));

          pos1 = MSGEQ7.get(MSGEQ7_0, 1);
          pos2 = MSGEQ7.get(MSGEQ7_1, 1);
          pos3 = MSGEQ7.get(MSGEQ7_2, 1);
          pos4 = MSGEQ7.get(MSGEQ7_3, 1);
          pos5 = MSGEQ7.get(MSGEQ7_4, 1);
          pos6 = MSGEQ7.get(MSGEQ7_5, 1);
          pos7 = MSGEQ7.get(MSGEQ7_6, 1);

          // map servos for full scale

          pos1 = map(pos1,0,150,-20,50);
          pos2 = map(pos2,0,150,-20,50);
          pos3 = map(pos3,0,150,-20,50);
          pos4 = map(pos4,0,150,-20,50);
          pos5 = map(pos5,0,150,-20,50);
          pos6 = map(pos6,0,150,-20,50);
          pos7 = map(pos7,0,150,-20,50);

          // constrain servos so they don't run their end stops

          pos1 = constrain(pos1,8,50);
          pos2 = constrain(pos2,8,50);
          pos3 = constrain(pos3,8,50);
          pos4 = constrain(pos4,8,50);
          pos5 = constrain(pos5,8,50);
          pos6 = constrain(pos6,8,50);
          pos7 = constrain(pos7,8,50);

          Serial.print("***");
          Serial.print(pos1);
          Serial.print(F(" \t"));
          Serial.print(pos2);
          Serial.print(F(" \t"));
          Serial.print(pos3);
          Serial.print(F(" \t"));
          Serial.print(pos4);
          Serial.print(F(" \t"));
          Serial.print(pos5);
          Serial.print(F(" \t"));
          Serial.print(pos6);
          Serial.print(F(" \t"));
          Serial.println(pos7);


          // tune out mechanical differences in servos

          pos1 = pos1;
          pos2 = pos2;
          pos3 = pos3+3;
          pos4 = pos4+3;
          pos5 = pos5-5;
          pos6 = pos6-6;
          pos7 = pos7;    



          // write servo positions
          
          servo1.write(pos1);    
          servo2.write(pos2);
          servo3.write(pos3);
          servo4.write(pos4);
          servo5.write(pos5);
          servo6.write(pos6);
          servo7.write(pos7);


      } // end of timed event
}
