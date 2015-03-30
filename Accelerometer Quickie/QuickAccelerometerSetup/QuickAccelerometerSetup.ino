int xRead;
int xRest;
double gX;

int yRead;
int yRest;
double gY;
int xSensorPin = 0;
int ySensorPin = 1;

int printTrigger = 0;

void setup()
{
  Serial.begin(9600);
  
  xRest = analogRead(xSensorPin);
//  Serial.print("X Rest Value: ");
//  Serial.print(xRest);
  
  yRest = analogRead(ySensorPin);
//  Serial.print("Y Rest Value: ");
//  Serial.print(yRest);
}

void loop()
{ 
  xRead = analogRead(xSensorPin) - xRest;
  yRead = analogRead(ySensorPin) - yRest;
  
  gX = xRead;
  gY = yRead;
  
  float values[] = {gX, gY, 0};
  
  if(Serial.available() > 0)
  {
    printTrigger = Serial.read();
  }
  
  if(printTrigger == 114)
  {
    Serial.print(values[0]);
    Serial.print(",");
    
    Serial.print(values[1]);
    Serial.print(",");
    
    Serial.print(values[2]);
    Serial.print(",");
    
    Serial.println();
    Serial.flush();
    
    printTrigger = 0;
  }
}
