/*
      Coded for the NodeMCU module
      //Pin out for module
      GND GND   -   Green
      D5  CLK   -   Red
      D6
      D7  DATA  -   Black
*/      

//Wifi Stuff
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
//SPI for APA102 driver
#include "SPI.h"
//Custom WS2801 Driver
#include "ws2801led.h"

const short int numLeds = 100;
const byte bytesPerLed = 3;
ws2801led leds = ws2801led(numLeds, bytesPerLed, 255);

unsigned int udpPort = 1000;
WiFiUDP Udp;
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_KEY";
short int packetSize=0;
unsigned short int cnt=0;

//Testing
unsigned long timeTestData[3] = {0,0,0};
byte testByte=0;

void setup()
{
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setFrequency(1500000);
  SPI.writeBytes(leds.LEDs, leds._frameLength);
  //delay at least 1 second + random 2 seconds before conecting to router
  delay(1000+random(2000));
  WiFi.mode(WIFI_STA);
  wifiConnect();
  Udp.beginMulticast(WiFi.localIP(), IPAddress(239, 0, 0, 57), udpPort);
}

void wifiConnect()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
  }
}

void pollUDP()
{
   packetSize = Udp.parsePacket();
   if(packetSize)
   {
      timeTestData[0] = micros();
      Udp.read(leds.LEDs, leds._frameLength);
      Udp.flush();  
      SPI.writeBytes(leds.LEDs, leds._frameLength);
      timeTestData[1] = micros();
      timeTestData[2] = timeTestData[1]-timeTestData[0];
      
      if(testByte==0 && leds.LEDs[0]==255 || leds.LEDs[0]-1==testByte || testByte==leds.LEDs[0] || testByte==255 && leds.LEDs[0]==0)
      {
        Serial.println(leds.LEDs[0]);
      }
      else
      {
        Serial.print("\r\nUDP Trasnmit took\t");
        Serial.print(timeTestData[2]);
        Serial.print("\tPrevious Packet !!!!!! DROPPED !!!!!!\r\n");
      }
      testByte = leds.LEDs[0]; 
   }
}

void renderLEDs()
{
  SPI.writeBytes(leds.LEDs, leds._frameLength);
}

void loop()
{
  pollUDP();
  delay(1);
}
