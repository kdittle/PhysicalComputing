int ledPin = 9;
int digit = 0;
int digitL = 0;
int brightness = 0;
int input = 0;
int count = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
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
    
//    for(count; count < digitL; count++)
//    {
//      Serial.println(digitL);
//    }
    
    if(input >= 10 || input <= 13)
    {
      input = 0;
      brightness = digitL; 
      digitL = 0;
      Serial.flush();
    }    
  }
  
        
    analogWrite(ledPin, brightness);
    Serial.println(brightness);
    delay(30);
}
