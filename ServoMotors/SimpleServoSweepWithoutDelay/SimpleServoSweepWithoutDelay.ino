// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int posLast = 0;
int d = 1;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
} 
 
 
void loop() 
{ 
  myservo.write(pos);
  pos = pos + d;
  posLast = pos;
  
  if(pos <= 2 && posLast > 2)
  {
    d = d * -1;
    posLast = 2;
  }
  
  if(pos >= 178 && posLast < 178)
  {
    d = d * -1;
    posLast = 178;
  }
} 
