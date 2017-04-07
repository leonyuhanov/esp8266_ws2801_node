# esp8266_ws2801_node
Generalized WIFI ESP8266 Node for receiving LED data to drive WS2801 Pixels

I wont publish the server code but here is a generic snippet of the server:

//Connect to your WIFI network then set up a UDP Multicast as follows

WiFiUDP Udp;

//then trasnmit your LED Data block as follows with a 3mili delay

Udp.beginPacketMulticast(IPAddress(239, 0, 0, 57), udpPort, WiFi.localIP(), 1);
Udp.write(dataBlock, blockSize);
delay(3);
