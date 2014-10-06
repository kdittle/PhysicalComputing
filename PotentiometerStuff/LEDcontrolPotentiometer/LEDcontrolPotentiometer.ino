//LED brightness controlled by a poteniometer
int ledPin = 9;
int potentPin = 0;
int knobValue;
int readValue;

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //get knobe vluae from anaolgRead potent pin
  readValue = analogRead(potentPin);
  //map the knove value with map(kv, 0, 1023, 0, 255) 
  knobValue = map(readValue, 0, 1023, 0, 255);
  //analogWrite(ledPin, knobvalue)
  analogWrite(ledPin, knobValue);
}
