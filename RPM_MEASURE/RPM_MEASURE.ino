#include <Keyboard.h>

const byte interruptPin = 2;
unsigned long prevTime;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin), MeasureRPM, FALLING);

  Serial.begin(115200);

  Keyboard.begin();

  prevTime = millis();
}

void loop() {
  unsigned long currTime = millis();
  unsigned long timeDiff = currTime - prevTime;
  unsigned long rpm      = (60000 / timeDiff);

  if (rpm <= 60)
  {
    Keyboard.release('w');
  }
}

void MeasureRPM() {
  unsigned long currTime = millis();
  unsigned long timeDiff = currTime - prevTime;
  unsigned long rpm      = (60000 / timeDiff);

  prevTime = currTime;

  if (rpm >= 60)
  {
    // Press the key
    Keyboard.press('w');
  }
}
