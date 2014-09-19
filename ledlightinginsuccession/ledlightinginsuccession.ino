const int ledPin1 = 9;
const int ledPin2 = 10;
const int ledPin3 = 11;

byte pinBrightness1 = 0;
byte pinBrightness2 = 0;
byte pinBrightness3 = 0;

int pb1 = 0;
int pb2 = 0;
int pb3 = 0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop()
{
    for (pb1 = 0; pb1 < 255; pb1++)
    {
      pinBrightness1 = pb1;
      analogWrite(ledPin1, pinBrightness1);
      delay(5);
    }
    delay(30);
    
    if(pinBrightness1 >= 125)
    {
      for (pb2 = 0; pb2 < 255; pb2++)
      {
        pinBrightness2 = pb2;
        analogWrite(ledPin2, pinBrightness2);
        delay(5);
      }
    }
    
    delay(30);
    
    if(pinBrightness2 >= 125)
    {
      for (pb3 = 0; pb3 < 255; pb3++)
      {
        pinBrightness3 = pb3;
        analogWrite(ledPin3, pinBrightness3);
        delay(5);
      }
    }
  
}
