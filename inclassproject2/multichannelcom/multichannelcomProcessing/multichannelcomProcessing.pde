import processing.serial.*;
Serial port;

void setup()
{
  println("Available serial ports:");
  println(Serial.list());
 
  port = new Serial(this, Serial.list()[1], 9600);
}

void draw()
{
  port.write(keyCode);
  /*
  port.write(keyCode)); //this is your flaf ID for which LED to address
  port.write(Val); // were val is the  valueof the led brightness
  port.write(10);
  */
  //Create rest of code to get the value of the brightness to send
}

void keyPressed()
{
  println("pressed " + int(key) + " " + keyCode);
}

