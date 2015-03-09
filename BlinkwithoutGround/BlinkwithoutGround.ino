int powerPinG1 = 12;
int powerPinG2 = 11;
int powerPinG3 = 10;

int groundPin1 = 4;
int groundPin2 = 3;
int groundPin3 = 2;


void setup()
{
  pinMode(powerPinG1, OUTPUT);
  pinMode(powerPinG2, OUTPUT);  
  pinMode(powerPinG3, OUTPUT);
  pinMode(groundPin1, OUTPUT);
  pinMode(groundPin2, OUTPUT);
  pinMode(groundPin3, OUTPUT);
}

void loop()
{
 digitalWrite(powerPinG1, HIGH);
 digitalWrite(powerPinG2, LOW);
 digitalWrite(powerPinG3, LOW);
 delay(1000);
 digitalWrite(groundPin1, LOW);
 digitalWrite(groundPin2, LOW);
 digitalWrite(groundPin3, LOW);
 delay(1000);
 
 digitalWrite(powerPinG1, LOW);
 digitalWrite(powerPinG2, HIGH);
 digitalWrite(powerPinG3, LOW);
 delay(1000);
 digitalWrite(groundPin1, LOW);
 digitalWrite(groundPin2, LOW);
 digitalWrite(groundPin3, LOW);
 delay(1000);
 
 digitalWrite(powerPinG1, LOW);
 digitalWrite(powerPinG2, LOW);
 digitalWrite(powerPinG3, HIGH);
 delay(1000);
 digitalWrite(groundPin1, LOW);
 digitalWrite(groundPin2, LOW);
 digitalWrite(groundPin3, LOW);
 delay(1000);
}
