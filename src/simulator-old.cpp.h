/*****************************
* Standalone Engine Simulator
* Aaron S. (Detonation) 2023
******************************
  DESCRIPTION
  ====================
  Insert words here that explain how the disaster of code below does stuff.
  Credit to Josh Stewart, google search, caffeine and THC for helping make this possible.

*/
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "simulator.h"
#include "generator.h"

/* Information Storage for Button */
const uint8_t button = 2; // set button pin
volatile boolean buttonState;
volatile boolean looping = false; // Store variable of outputs

/* Set Crank, Camshaft  */
const uint8_t crankPin = 8; // Crank sensor to ECU
const uint8_t camPin = 9;   // Crank sensor to ECU

/* Potentiometer RPM*/
const uint8_t rpmPot = A0;     // potentiometer
volatile uint16_t sensorValue; // Store variable from potentiometer
volatile uint32_t interval;

/* Potentiometer Pattern Select */
const uint8_t potPin2 = A1;
uint16_t sensorValue2;

/* Timer Setup */
volatile uint32_t outputSpeed;   // variable for output speed
volatile uint32_t minPulses = 1; // minimum number of pulses
volatile uint32_t maxPulses;     // maximum number of pulses
volatile uint32_t numPulses;
volatile uint32_t limitedPulses;
volatile uint32_t timerCount;
const int timerInterval = 1; // timer interval in milliseconds

/* Modified to be directly compatible with Ardustim */
volatile uint8_t currentPattern; // store the currently selected patter.
volatile uint8_t lastPattern;
volatile uint16_t patternLength;
volatile uint16_t currentIndex;  // store current pattern index.
volatile uint32_t pulseInterval; // stores the interval between pulses

extern wheels Wheels[];

void buttonInterrupt() // Rotary encoder switch state interrupt
{
  buttonState = digitalRead(button); // send the state of the switch to switchStateDebounce after we have waited 8ms
  if (buttonState == LOW)            // if the switchStateDebounce is (LOW)
  {
    looping = !looping; // toggle looping state
  }
}

void setup()
{
  currentPattern = 7; // DEBUG ONLY!!!!
  lastPattern = 7;    // DEBUG ONLY!!!!

  pinMode(button, INPUT_PULLUP); // set button to input with pullup

  pinMode(rpmPot, INPUT);  // set potentiometer as an input
  pinMode(potPin2, INPUT); // set potentiometer2 as input

  attachInterrupt(digitalPinToInterrupt(button), buttonInterrupt, CHANGE); // interrupt for rotary encoder rotation

  initBoard(); // Setup Timers for selected board.

  pinMode(crankPin, OUTPUT); // set crankPin as an output
  pinMode(camPin, OUTPUT);   // set camPin as an output

  simpleGenerate();
}
//  Wheels[currentPattern].selectedPattern == mtPattern[Wheels[currentPattern].patternLength];
// simpleGenerate();

void loop()
{

  
  sensorValue = analogRead(rpmPot);             // read the value of the potentiometer
  interval = map(sensorValue, 0, 1023, 255, 7); // convert the potentiometer value to a suitable range for the Timer1 compare value
  // pulseInterval = maxPulses / interval;                       // calculate the interval between pulses
}

ISR(TIMER1_COMPA_vect)
{
  if (looping == true)
  {

    // PORTB = pgm_read_byte(&Wheels[currentPattern].patternArray[currentIndex]); // Send indexed data to crank/cam pins
    PORTB = pgm_read_byte(&Wheels[currentPattern].selectedPattern[currentIndex]); // Send indexed data to crank/cam pins
    TCNT1 = 0;

    timerCount++; // increment the timer count
    if (timerCount >= interval)
    {
      if (++currentIndex == Wheels[currentPattern].patternLength) // walk the pattern
      {
        currentIndex = 0; // when the end of the pattern is reached go back to the start.
      }
      timerCount = 0;
    }
  }
}