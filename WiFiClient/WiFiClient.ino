
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


const char* ssid     = "urbanLab";
const char* password = "urbanLab";

  WiFiUDP Udp;
  const unsigned int localPort = 1234; 
  const int TouchPin1 = 15;
  const int TouchPin2 = 16;
  cosst int boutton1 = 13;


  
// --------------------------------------------------------------------------------------
//   Reading OSC Bundles on the network
// --------------------------------------------------------------------------------------
void sendOSCBundle(IPAddress ip, int port, String path, float value) {
  OSCBundle bundle;

  //Serial.print("Sending OSC Bundle to ");
  //Serial.print(" : " + path + "/");
  //Serial.println(value);

  //bundle.add("/position").add(value);
  bundle.add(path.c_str()).add(value);
  Udp.beginPacket(ip, port);
  bundle.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  bundle.empty(); // empty the bundle to free room for a new one
}



// --------------------------------------------------------------------------------------
void setup() {
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

  Serial.println("try sending something");
  sendOSCBundle(IPAddress(192,168,0,100), localPort, "/arduino/toto", 10);
  Serial.println("ok");
  
}

int value = 0;

// --------------------------------------------------------------------------------------
void loop() {

  int tele = analogRead(A0);
  int sensorValue1 = digitalRead(TouchPin1);
  int sensorValue2 = digitalRead(TouchPin2);
  int boutton1Value1 = digitalRead(boutton1);

  Serial.print("\t distance = ");
  Serial.println(tele);
  sendOSCBundle(IPAddress(192,168,0,100), localPort, String("/arduino/telemetre"), float(tele));
  if(sensorValue1 == 1)
  {
    Serial.println("poteau !");
    sendOSCBundle(IPAddress(192,168,0,100), localPort, "/arduino/poteau", 1);
  }
  if(sensorValue2 == 1)
  {
    Serial.println("poteau 2!");
    sendOSCBundle(IPAddress(192,168,0,100), localPort, "/arduino/poteau", 2);
  }
  if (boutton1Value1)
  {
    Serial.println("Boutton 1");
    sendOSCBundle(IPAddress(192,168,0,100), localPort, "/arduino/poteau", 3);
  }
  delay(400);
}

