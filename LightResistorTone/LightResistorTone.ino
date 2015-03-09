int speakerPin = 11;
int photocellPin = 0;

int numTones = 10;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
//          mid C C# D D# E F F# G G# A



void setup() 
{
  
//  for (int i = 0; i < numTones; i++)
//  {
//    tone(speakerPin, tones[i]);
//    delay(500);
//  }
//  
//  noTone(speakerPin);
    //pinMode(buttonPin, INPUT);
}

void loop() 
{
  int reading = analogRead(photocellPin);
  int pitch = 200 + reading / 4;
  tone(speakerPin, pitch);
}
