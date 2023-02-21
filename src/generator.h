#include "main.h"

uint16_t i;

volatile boolean crankState; // Store output state
volatile boolean camState;   // Store output state
volatile boolean rotation;

extern const byte crankPin;
extern const byte camPin;
extern const byte sensorPin; // Potentiometer input Pin

// Repeated patterns are very simple. Pattern must end on the desired triggers * 2
// To-Do add cam signals to

void dizzy()
{
  i++;
  if (i <= 7) // Cycle crankState 23 times.
  {
    crankState = !crankState;
    // digitalWrite(crankPin, crankState);
  }

  if (i == 8) // Hold for missing trigger for 1 cycle.
  {
    // Set i to 1 and start over.
    i = 1;
  }
}

void twelve_minus_one()
{
  i++;
  if (i <= 23) // Cycle crankState 23 times.
  {
    crankState = !crankState;
    // digitalWrite(crankPin, crankState);
  }

  if (i == 24) // Hold for missing trigger for 1 cycle.
  {
    i = 1; // Set i to 1 and start over.
  }
}

void sixty_minus_two()
{
  i++;
  if (i <= 121) // Cycle crankState
  {
    crankState = !crankState;
    // digitalWrite(crankPin, crankState);
  }

  if (i == 3) // Hold for missing trigger for 1 cycle.
  {
    // Set i to 1 and start over.
    i = 1;
  }
}

void thirty_six_minus_one()
{
  i++;
  if (i <= 71) // Cycle crankState
  {
    crankState = !crankState;
    // digitalWrite(crankPin, crankState);
  }

  if (i == 72) // Hold for missing trigger for 1 cycle.
  {
    // Set i to 1 and start over.
    i = 1;
  }
}

void twelve_minus_one_with_cam()
{
  // Rotation 2

  i++;
  if (i <= 23) // Cycle crankState
  {
    crankState = !crankState;
    // digitalWrite(crankPin, crankState);
  }

  if (i == 24) // Hold for missing trigger for 1 cycle.
  {
    // Set i to 1 and start over.
    
  }

  // Rotation 2

  if (i <= 40) // Cycle crankState
  {
    crankState = !crankState;
    // digitalWrite(crankPin, crankState);
  }

  if (i = (41 >= 43)) // Cycle crankState
  {
    camState = !camState;
    // digitalWrite(crankPin, crankState);
  }

    if (i <= 40) // Cycle crankState
  {
    crankState = !crankState;
    // digitalWrite(crankPin, crankState);
  }

  if (i == 24) // Hold for missing trigger for 1 cycle.
  {
    // Set i to 1 and start over.
    i = 1;
  }
}

/*
        /* 12-1 with cam 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // Teeth 1 and 2 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // Teeth 3 and 4 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // Teeth 5 and 6 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // Teeth 7 and 8 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // Teeth 9 and 10 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, // Tooth 11 and MISSING twelth 
                                            // 0,0,0,0,0,1,0,0,0,0,0,1,  Tooth 11 and WITHOUT MISSING twelth 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // 2nd rotation: Teeth 13 and 14 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // Teeth 15 and 16 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // Teeth 17 and 18 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // Teeth 19 and 20 
        0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 1, // Tooth 21 and 22,  2nd trigger on cam between teeth 21 and 22 for 25 deg 
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0  // Totth 23 and MISSING 24th 
        
*/
