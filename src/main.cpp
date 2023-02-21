/********************************************************************************************
* Standalone Engine Simulator
* Aaron S. (Detonation) 2023
******************************
  DESCRIPTION
  ====================
  Very simple 12-1 Crankshaft Trigger Simulator
********************************************************************************************/

#include <Arduino.h>

// Pins
const byte sensorPin = A0; // Potentiometer input Pin
const byte crankPin = 5;   // Crankshaft simulation output
const byte camPin = 5;     // Crankshaft simulation output

volatile boolean crankState; // Store output state
volatile boolean camState;   // Store output state

volatile uint16_t sensorValue; // Store pot value

uint16_t previousMicros = 0;
uint16_t interval; // Store value used to compare to Micros count
uint16_t time;
uint16_t previousTime = 0;
uint16_t i = 0;

void setup()
{

  pinMode(crankPin, OUTPUT); // Set crankPin as output
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  interval = map(sensorValue, 0, 1023, 24, 4092);

  uint32_t currentMicros = micros();

  time = currentMicros - previousMicros;
  if (time > interval)
  {
    previousMicros = currentMicros;
    i++;

    if (i <= 23) // Cycle crankState 23 times.
    {
      crankState = !crankState;
      digitalWrite(crankPin, crankState);
    }

    if (i == 24) // Hold for missing trigger for 1 cycle.
    {
      // Set i to 1 and start over.
      time = currentMicros - previousTime;
      previousTime = currentMicros;
      i = 1;
    }
  }
}
