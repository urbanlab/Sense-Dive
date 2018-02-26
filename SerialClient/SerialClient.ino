/**********************************************************************************
  Client qui gère quatres TouchButton avec leur quatre retours visuels 
  de changements d'états.
  Les bundles OSC sont envoyés via serial.
 ***********************************************************************************/
#include <OSCBundle.h>

#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial);
#endif

#define NB_BUTTONS 4
#define TOUCHBUTTON1 5
#define TOUCHBUTTON2 6
#define TOUCHBUTTON3 7
#define TOUCHBUTTON4 8
#define LED1 A0
#define LED2 A1
#define LED3 A2
#define LED4 A3

int leds[] = {LED1, LED2, LED3, LED4};
int buttons[] = {TOUCHBUTTON1, TOUCHBUTTON2, TOUCHBUTTON3, TOUCHBUTTON4};

// --------------------------------------------------------------------------------------
//   Sending OSC Bundles on the network
// --------------------------------------------------------------------------------------
void sendOSCBundle (String path, float value)
{
  OSCBundle bundle;

  bundle.add(path.c_str()).add(value);

  //start a new SLIP Packet
  SLIPSerial.beginPacket();
  //send the data
  bundle.send(SLIPSerial);
  //end the packet
  SLIPSerial.endPacket();
  bundle.empty(); // empty the bundle to free room for a new one
}

// --------------------------------------------------------------------------------------
//   readButton : read button state
// --------------------------------------------------------------------------------------
void readButton(int idx) {
  if (digitalRead(buttons[idx]) == LOW) {
    digitalWrite(leds[idx], LOW);
  } else {
    digitalWrite(leds[idx], HIGH);
    // Send OSC bundle
    sendOSCBundle("/arduino/poteau", idx);
  }
}

// --------------------------------------------------------------------------------------
//   Setup Arduino
// --------------------------------------------------------------------------------------
void setup() {
  SLIPSerial.begin(9600);
  for (int i = 0; i < NB_BUTTONS; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
    delay(1000);
    digitalWrite(leds[i], LOW);
  }
}

// --------------------------------------------------------------------------------------
//   Loop Arduino
// --------------------------------------------------------------------------------------
void loop() {
  for (int i = 0; i < NB_BUTTONS; i++) {
    readButton(i);
  }
  delay(50); // Debounce delay, and anti-flood
}
