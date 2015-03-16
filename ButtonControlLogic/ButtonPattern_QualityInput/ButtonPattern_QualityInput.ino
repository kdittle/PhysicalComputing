int buttonPin = 2;
int ledPin = 13;

int buttonState = 0;
int numClicks = 0;

long interval = 0;
long constInterval = 0;
long resetInterval = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  constInterval = millis();
  
  if(buttonState == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    interval = (constInterval - resetInterval) - interval;
    interval = interval / 1000;
  }
  if(buttonState == LOW)
  {
    digitalWrite(ledPin, LOW);
    interval = 0;
    resetInterval = constInterval;
  }
  
  Serial.println(interval);
  
}
