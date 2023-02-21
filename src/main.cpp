/********************************************************************************************
* Standalone Engine Simulator
* Aaron S. (Detonation) 2023
******************************
  DESCRIPTION
  ====================
  Very simple 12-1 Crankshaft Trigger Simulator
********************************************************************************************/

#include <Arduino.h>
#include "main.h"

// Pins
const byte sensorPin = A0; // Potentiometer input Pin
const byte crankPin = 8;   // Crankshaft simulation output
const byte camPin = 9;     // Crankshaft simulation output

uint16_t interval; // Store value used to compare to Micros count

uint16_t timerCount;

extern volatile boolean crankState; // Store output state
extern volatile boolean camState;   // Store output state

uint16_t sensorValue; // Store pot value

void setup()
{
  initBoard(); // Setup Timers for selected board.

  pinMode(sensorPin, INPUT); // set potentiometer as an input
  pinMode(crankPin, OUTPUT); // set crankPin as an output
  pinMode(camPin, OUTPUT);   // set camPin as an output

  crankState = 1;
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  interval = map(sensorValue, 0, 1023, 255, 7);
}

ISR(TIMER1_COMPA_vect)
{
  PORTB = (crankState); // Send indexed data to crank/cam pins

  digitalWrite(crankPin, crankState);
  TCNT1 = 0;

  timerCount++; // increment the timer count
  if (timerCount > interval)
  {
    twelve_minus_one_with_cam();

    timerCount = 0;
  }
}
