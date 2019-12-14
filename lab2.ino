#include "button.h"
#include "pitches.h"
#include "buzzer.h"

#define PIN_BUZZER 33
#define PIN_BUTTON 43

const int sensorPin = A0;
const float voltsPerMeasurement = 5.0/1024.0;
const float maxDistance = 20.0;

const int notes[] = {NOTE_DS4, NOTE_SILENCE};
const double durations[] = {1, 1};
const int melodyLength = 2;

Button button(PIN_BUTTON);
Buzzer buzzer(PIN_BUZZER);

bool isActivated = false;

void setup()
{
  buzzer.setMelody(notes, durations, melodyLength);
}

void loop() 
{
  float distance = readDistance();
  if (!isActivated && distance <= maxDistance) {
    isActivated = true;
    buzzer.turnSoundOn();
  }
  
  if (isActivated && button.wasPressed()) {
    isActivated = false;
    buzzer.turnSoundOff();
  }

  buzzer.playSound();
}

float readDistance(){
  float volts = readAnalog() * voltsPerMeasurement;
  return pow(14.7737/volts, 1.2134);
}

float readAnalog()
{
  int sum = 0;
  int maxV = -5000;
  int minV = 5000;
  int n = 15;
  for (int i = 0; i < n; i++)
  {
    int cur = analogRead(sensorPin);
    if (cur > maxV)
    {
      maxV = cur;
    }
    if (cur < minV)
    {
      minV = cur;
    }
    sum += cur;
    delay(6);
  }
  return (sum - maxV - minV) / (float)(n - 2);
}
