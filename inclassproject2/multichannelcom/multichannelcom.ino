int ledA = 9;
int ledB = 11;
int id;
int digit;
int digitL;

void setup()
{
  Serial.begin(9600);
  
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop()
{    
  byte input = Serial.read();
  
  if(input >= 65 && input <= 90)
  {
    id = input;
  }
  
  if(input >= 48 && input <= 57)
  {
    digit = input;
    digitL = digit + digitL * 10;
  }
  
  switch(id)
  {
    case 65:
    {
      analogWrite(ledA, digitL);
      analogWrite(ledB, 0);
      break;
    }
    case 66:
    {
      analogWrite(ledB, digitL);
      analogWrite(ledA, 0);
      break;
    }
    case 67:
    {
      analogWrite(ledA, digitL);
      analogWrite(ledB, digitL);
      break;
    }
    case 68:
    {
      analogWrite(ledA, 0);
      analogWrite(ledB, 0);
      break;
    }
  }
  
  Serial.flush();
}

