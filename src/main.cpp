/********************************************************************************************
* Standalone Engine Simulator
* Aaron S. (Detonation) 2023
******************************
  DESCRIPTION
  ====================
  Very Simple 12/1 Signal Generator Trigger Simulator
********************************************************************************************/

#include <Arduino.h>
#include "main.h"

// Pins
const byte sensorPin = A0; // Potentiometer input Pin
const byte crankPin = 8;   // Crankshaft simulation output
// const byte camPin = 9;     // Crankshaft simulation output

uint16_t interval; // Store value used for RPM control
uint16_t i;        // Store value to walk the pattern

uint16_t timerCount; // Store count to be compared to interval
bool looping;        // Store value for output on/off

boolean crankState; // Store output state
// boolean camState;   // Store output state

uint16_t sensorValue; // Store pot value

void setup()
{
  initBoard(); // Setup Timers for selected board.

  pinMode(sensorPin, INPUT); // set potentiometer as an input
  pinMode(crankPin, OUTPUT); // set crankPin as an output
  // pinMode(camPin, OUTPUT);   // set camPin as an output
}

void loop()
{
  sensorValue = analogRead(sensorPin);           // Read the pot
  interval = map(sensorValue, 0, 1023, 420, 12); // Map the pot to some sane values giving a good RPM range.
  
  // If the pot is at lowest value stop the output.
  if (sensorValue > 1)
  {
    looping = true;
  }
  else
  {
    looping = false;
  }
}

ISR(TIMER1_COMPA_vect)
{
  digitalWrite(crankPin, crankState);

  TCNT1 = 0;

  if (looping == true)
  {
    timerCount++; // increment the timer count
    if (timerCount > interval)
    {
      i++;
      if (i <= 23) // Cycle crankState
      {
        crankState = !crankState;
      }
      if (i == 24) // Hold for missing trigger for 1 cycle.
      {
        i = 1; // Set i to 1 and start over.
      }
      timerCount = 0;
    }
  }
}