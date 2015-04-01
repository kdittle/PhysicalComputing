int x;
int y;

void setup() 
{
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  x = analogRead(0);
  y = analogRead(1);
  Serial.print(x);
  Serial.print(" , ");
  Serial.print(y);
  Serial.println();
  delay(1000);
}
