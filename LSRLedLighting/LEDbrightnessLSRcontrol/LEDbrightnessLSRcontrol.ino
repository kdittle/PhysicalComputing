int ledPin = 13;
int photocellPin = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  int reading = analogRead(photocellPin);
  
  analogWrite(ledPin, reading);
}
