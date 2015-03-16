int buttonPin = 2;
int ledPin = 13;

int buttonState = 0;
int numClicks = 0;

long interval = 0;
long constInterval = 0;
long resetInterval = 0;
long duration = 0;

boolean depress = false;

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
    //digitalWrite(ledPin, HIGH);
    interval = (constInterval - resetInterval) - interval;    
    interval = interval / 1000;
    duration = interval;
    depress = true;
    //Serial.println(interval);
  }
  
  if(depress)
  {
    numClicks++;
    depress = false;
    Serial.println(numClicks);
  }
  
  if(buttonState == LOW)
  {
    //digitalWrite(ledPin, LOW);
    interval = 0;
    resetInterval = constInterval;
  }
  
  //turn the light on only if button has been held for a certain amount of time
//  if(duration >= 1)
//    digitalWrite(ledPin, HIGH);
//  else
//    digitalWrite(ledPin, LOW);
  


}
