int but1Pin = 4;
int but2Pin = 5;
int led1Pin = 2;
int led2Pin = 3;
int but1State = 0;
int but2State = 0;
int led1State = LOW;
int led2State = LOW;

long interval1 = 200;
long interval2 = 500;
long cur1int = 0;
long cur2int = 0;
long pre1int = 0;
long pre2int = 0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(but1Pin, INPUT);
  pinMode(but2Pin, INPUT);
  
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop()
{
  cur1int = millis();
  cur2int = millis();
  
  but1State = digitalRead(but1Pin);
  but2State = digitalRead(but2Pin); 
  
  //factory button, LED1, pin2, Right LED
  if(but1State == HIGH)  
  {
    interval1++;
    Serial.println(but1State);
  }
  
//  //ledpin 4 button state 2, led2, left led non homemade button
  if(but2State == HIGH)
  {
    interval2++;
    Serial.println(but2State);
  }
  
  //led1 (right LED)
  if(cur1int - pre1int > interval1)
  {
    pre1int = cur1int;
    ///Serial.println("Led1 ON");
    
    if(led1State == LOW)
      led1State = HIGH;
    else
      led1State = LOW;
    
    digitalWrite(led1Pin, led1State);    
  }
  
  //led2, left LED
  if(cur2int - pre2int > interval2)
  {
    pre2int = cur2int;
    
    if(led2State == LOW)
      led2State = HIGH;
    else
      led2State = LOW;
      
    digitalWrite(led2Pin, led2State);    
  }
  
  
}

