#ifndef TIMERS_H
#define TIMERS_H
#include "main.h"

/* Timer setup for each available board */
// Nano 328p is currently the only working MCU

#if defined(NANO_328) // Tons of room left for more features
void initBoard()
{
  /* Setup Hardware Timer */
  cli(); // disable global interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 196; 
  TCCR1B |= (1 << WGM12);  // set the Timer1 mode to CTC (clear timer on compare match)
  
  TCCR1B |= (1 << CS10);   // Set pre-scaler of 1
  //TCCR1B = _BV(CS11); // Set pre-scaler of 8
  //TCCR1B = _BV(CS11) | _BV(CS10); // Set pre-scaler of 64
  //TCCR1B = _BV(CS12); // Set pre-scaler of 256
  //TCCR1B = _BV(CS12) | _BV(CS10); // Set pre-scaler of 1024

  TIMSK1 |= (1 << OCIE1A); // enable Timer1 overflow interrupt
  sei();            // Enable interrupts
}
#endif // end MCU

#if defined(NANO_168)
void initBoard()
{
  /* Setup Hardware Timer */
  cli(); // disable global interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  //OCR1A = (16000000 / 1024) * timerInterval / 1000 - 1; // set the output compare register A to generate an interrupt every `timerInterval` milliseconds
  OCR1A = 1;
  TCCR1B |= (1 << WGM12);  // set the Timer1 mode to CTC (clear timer on compare match)
  TCCR1B |= (1 << CS10);   // set the Timer1 pre-scaler
  TIMSK1 |= (1 << OCIE1A); // enable Timer1 overflow interrupt
  sei();            // Enable interrupts
}
#endif // end MCU

#if defined(ATTINY)   
void initBoard()
{
  cli();               // Disable interrupts
  TCCR0A = 0b10100001; // non-inverting OCR0A & OCR0B
  TCCR0B = 0b00000001; // Timer = ~32kHz
  sei();               // Enable interrupts
}
#endif // end MCU

#if defined(ATTINY88) 
void initBoard()
{
  /* Setup Hardware Timer */
  cli(); // disable global interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  //OCR1A = (16000000 / 1024) * timerInterval / 1000 - 1; // set the output compare register A to generate an interrupt every `timerInterval` milliseconds
  OCR1A = 1;
  TCCR1B |= (1 << WGM12);  // set the Timer1 mode to CTC (clear timer on compare match)
  TCCR1B |= (1 << CS10);   // set the Timer1 pre-scaler
  TIMSK1 |= (1 << OCIE1A); // enable Timer1 overflow interrupt
  sei();            // Enable interrupts
}
#endif // end MCU

#endif // end file