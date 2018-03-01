/**********************************************************************************
  Client qui gère quatres TouchButton avec leur quatre retours visuels 
  de changements d'états.
  Les bundles OSC sont envoyés via serial.
 ***********************************************************************************/
#define DEBOUNCE_DELAY 0 // Impose 25 Messages per Second, i.e. 25 FPS
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
//   readButton : read button state
// --------------------------------------------------------------------------------------
void readButton(int idx) {
  if (digitalRead(buttons[idx]) == LOW) {
    digitalWrite(leds[idx], LOW);
  } else {
    digitalWrite(leds[idx], HIGH);
    //Serial.print("/arduino/poteau/");
    Serial.println(String(idx+1)); // Sending 1,2,3,4 instead of 0,1,2,3
  }
}

// --------------------------------------------------------------------------------------
//   Setup Arduino
// --------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
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
  delay(DEBOUNCE_DELAY); // Debounce delay, and anti-flood
}
