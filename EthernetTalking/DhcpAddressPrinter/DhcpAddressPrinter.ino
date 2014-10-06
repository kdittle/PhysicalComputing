/*
  DHCP-based IP printer
 
 This sketch uses the DHCP extensions to the Ethernet library
 to get an IP address via DHCP and print the address obtained.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 12 April 2011
 modified 9 Apr 2012
 by Tom Igoe
 
 */
 
//
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUDP.h>

int led = 6;
int brightness;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  
  0x90, 0xA2, 0xDA, 0x0F, 0xBB, 0x49 };
IPAddress ip(169,254,15,128); //Overrides IP given to DHCP

//creates variable with the port that we should listen to
unsigned int localPort = 8888; 

//creates a buffer
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

//Don't know what the fuck it does but its important
EthernetUDP Udp;


// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    // this check is only needed on the Leonardo:
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    // start the Ethernet connection:
    Ethernet.begin(mac, ip);
    // print your local IP address: (DOESN'T CHANGE FUNCTION, ONLY WRITES OUT IP TO MAKE SURE ITS WORKING)
    Serial.print("My IP address: ");
    for (byte thisByte = 0; thisByte < 4; thisByte++) {
        // print the value of each byte of the IP address:
        Serial.print(Ethernet.localIP()[thisByte], DEC);
        Serial.print("."); 
    }
    Serial.println();
    Udp.begin(localPort);
}

void loop() {
    int packetSize = Udp.parsePacket();
    //if UDP is available then write to the serial that packets are being recieved
    if (Udp.available()){
        Serial.print("Recieved");
        
        //Does stuff
        Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);   
        //itterate through the packet
        for(int i = 0; i < packetSize; i++){
          // make digit the value in the array packetBuffer
          int digit = packetBuffer[i];
          // if digit was a ASCII digit then assign it to brightness
          if (digit >= 48 && digit <= 57){
            brightness = (digit - 48) + (brightness * 10);
          }
        }
        Serial.println(brightness);
        analogWrite(led, brightness);
      }
      brightness = 0;
      
      delay(10);
  
}


