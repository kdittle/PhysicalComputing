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
}

void keyPressed()
{
  println("pressed " + int(key) + " " + keyCode);
}

