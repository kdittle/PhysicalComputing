int powerPinG1 = 12;
int powerPinG2 = 11;
int powerPinG3 = 10;

int groundPin1 = 4;
int groundPin2 = 3;
int groundPin3 = 2;

int digit;
int digitL;
int input;


void setup()
{
  Serial.begin(9600);
  
  pinMode(powerPinG1, OUTPUT);
  pinMode(powerPinG2, OUTPUT);  
  pinMode(powerPinG3, OUTPUT);
  pinMode(groundPin1, OUTPUT);
  pinMode(groundPin2, OUTPUT);
  pinMode(groundPin3, OUTPUT);
}

void loop()
{
  
  while(Serial.available() > 0)
  {
    input = Serial.read();
    
    if(input >= 48 && input <= 57)
    {
      digit = input;
      digitL = digit + digitL * 10;
    }
  }
  
 if(digitL == 49)
 {
   //power pins
   digitalWrite(powerPinG1, HIGH);
   digitalWrite(powerPinG2, LOW);
   digitalWrite(powerPinG3, LOW);
   
   //ground pins
   digitalWrite(groundPin1, LOW);
   digitalWrite(groundPin2, HIGH);
   digitalWrite(groundPin3, HIGH);
 }
 
 if(digitL == 50)
 {
  digitalWrite(powerPinG1, HIGH);
  digitalWrite(powerPinG2, LOW);
  digitalWrite(powerPinG3, LOW);
  
  digitalWrite(groundPin1, HIGH);
  digitalWrite(groundPin2, LOW);
  digitalWrite(groundPin3, HIGH);
 }
 
 if(digitL == 51)
 {
   digitalWrite(powerPinG1, HIGH);
   digitalWrite(powerPinG2, LOW);
   digitalWrite(powerPinG3, LOW);
  
   digitalWrite(groundPin1, HIGH);
   digitalWrite(groundPin2, HIGH);
   digitalWrite(groundPin3, LOW);
 }
 
//  if(digitL == 52)
//  {
//    digitalWrite(powerPinG1, LOW);
//    digitalWrite(powerPinG2, LOW);
//    digitalWrite(powerPinG3, LOW);
//    
//    digitalWrite(groundPin1, HIGH);
//    digitalWrite(groundPin2, HIGH);
//    digitalWrite(groundPin3, HIGH);
//  }

// 
////   //second group
if(digitL == 52)
{
 digitalWrite(powerPinG1, LOW);
 digitalWrite(powerPinG2, HIGH);
 digitalWrite(powerPinG3, LOW);

 digitalWrite(groundPin1, LOW);
 digitalWrite(groundPin2, HIGH);
 digitalWrite(groundPin3, HIGH);

}
 
 if(digitL == 53)
 {
 digitalWrite(powerPinG1, LOW);
 digitalWrite(powerPinG2, HIGH);
 digitalWrite(powerPinG3, LOW);
 
 digitalWrite(groundPin1, HIGH);
 digitalWrite(groundPin2, LOW);
 digitalWrite(groundPin3, HIGH);
 
 }
 
 if(digitL == 54)
 {
 digitalWrite(powerPinG1, LOW);
 digitalWrite(powerPinG2, HIGH);
 digitalWrite(powerPinG3, LOW);

 digitalWrite(groundPin1, HIGH);
 digitalWrite(groundPin2, HIGH);
 digitalWrite(groundPin3, LOW);
 }
 
//
////   //third group
if(digitL == 55)
{
 digitalWrite(powerPinG1, LOW);
 digitalWrite(powerPinG2, LOW);
 digitalWrite(powerPinG3, HIGH);

 digitalWrite(groundPin1, LOW);
 digitalWrite(groundPin2, HIGH);
 digitalWrite(groundPin3, HIGH);

}
 
 if(digitL == 56)
 {
 digitalWrite(powerPinG1, LOW);
 digitalWrite(powerPinG2, LOW);
 digitalWrite(powerPinG3, HIGH);

 digitalWrite(groundPin1, HIGH);
 digitalWrite(groundPin2, LOW);
 digitalWrite(groundPin3, HIGH);

 }
 
 if(digitL == 57)
 {
 digitalWrite(powerPinG1, LOW);
 digitalWrite(powerPinG2, LOW);
 digitalWrite(powerPinG3, HIGH);

 digitalWrite(groundPin1, HIGH);
 digitalWrite(groundPin2, HIGH);
 digitalWrite(groundPin3, LOW);

 }


//// Turn off all groups
if(input == 32)
{
 digitalWrite(powerPinG1, LOW);
 digitalWrite(powerPinG2, LOW);
 digitalWrite(powerPinG3, LOW);
 delay(1);
 digitalWrite(groundPin1, HIGH);
 digitalWrite(groundPin2, HIGH);
 digitalWrite(groundPin3, HIGH);
 delay(1);
}

if(input >= 10 || input <= 13 || input == 32)
 {
   input = 0;
   digitL = 0;
   Serial.flush();
 }
}
 
