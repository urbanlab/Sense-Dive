/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>


const char* ssid     = "erasme-guests";
const char* password = "guests@erasme";

WiFiUDP Udp;
const unsigned int localPort1 = 1234; 
const unsigned int localPort2 = 1235; 
const int TouchPin1 = 15;
const int TouchPin2 = 16;
const int boutton1 = 13;
const int boutton2 = 2;
const IPAddress adresse  = IPAddress(192, 168, 0, 101);


  
// --------------------------------------------------------------------------------------
//   Reading OSC Bundles on the network
// --------------------------------------------------------------------------------------
void sendOSCBundle(IPAddress ip, int port, String path, float value)
{
  OSCBundle bundle;



  bundle.add(path.c_str()).add(value);
  Udp.beginPacket(ip, port);
  bundle.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  bundle.empty(); // empty the bundle to free room for a new one

  Serial.println("Send to\t:");
  Serial.print(ip);
  Serial.print("\t");
  Serial.print(path);
  Serial.print("\t");
  Serial.println(value);
}



// --------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
  if (WiFi.localIP() == adresse)
    Serial.println("J'envoie des infos à moi meme...");
  Serial.println("try sending something");
  sendOSCBundle(adresse, localPort1, "/arduino/toto", 10);
  Serial.println("ok");
  Serial.println("Begin of the loop");
}

int value = 0;

// --------------------------------------------------------------------------------------
void loop() 
{
	int tele = analogRead(A0);
  int sensorValue1 = digitalRead(TouchPin1);
  int sensorValue2 = digitalRead(TouchPin2);
  int boutton1Value = digitalRead(boutton1);
  int boutton2Value = digitalRead(boutton2);

  /*Serial.print("\t distance = ");
  Serial.println(tele);*/

  sendOSCBundle(adresse, localPort1, String("/arduino/telemetre"), float(tele));
  sendOSCBundle(adresse, localPort2, String("/arduino/telemetre"), float(tele));
  if(sensorValue1)
  {
    sendOSCBundle(adresse, localPort1, "/arduino/poteau", 1);
		sendOSCBundle(adresse, localPort2, "/arduino/poteau", 1);
  }
  if(sensorValue2)
  {
    sendOSCBundle(adresse, localPort1, "/arduino/poteau", 2);
		sendOSCBundle(adresse, localPort2, "/arduino/poteau", 2);
  }
  if (boutton1Value)
  {
    sendOSCBundle(adresse, localPort1, "/arduino/poteau", 3);
		sendOSCBundle(adresse, localPort2, "/arduino/poteau", 3);
  }
  if (boutton2Value)
  {
    sendOSCBundle(adresse, localPort1, "/arduino/poteau", 4);
		sendOSCBundle(adresse, localPort2, "/arduino/poteau", 4);
  }
  delay(300);
}

