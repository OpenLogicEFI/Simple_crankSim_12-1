/*
* 12-1 Crank Trigger Simulator simple enough for ATTINY
* Aaron (Detonation) 2020
*/

int sensorPin = A0;              // potentiometer
int sensorValue = 0;            // store value from sensor

unsigned long val = 0;                    //value used with map
const int crankpin =  5;      // Crank sensor to ECU

int ledState = LOW;            // trigger
int ledState2 = LOW;           // dead area

unsigned long previousMicros = 0;      // will store last variable of ledstate
unsigned long interval = 500;          // interval at which to trigger (milliseconds)
unsigned long time = 0;
unsigned long previousTime = 0;      // will store last variable of Time
float Hz = 0;
int i = 0;


void setup(){
  pinMode(crankpin, OUTPUT); // set the digital pin as output
  delay(1000);    // wait for shit to calm down
}


void loop()
{
  sensorValue = analogRead(sensorPin);
  interval = map(sensorValue, 0, 1023, 24, 4092);        // interval 0-1024 real/ x - x out

  unsigned long currentMicros = micros();

  time = currentMicros - previousMicros;
  if (time > interval)                             // 12 cycles of HIGH to LOW
  {
    previousMicros = currentMicros;
    i++;
    if (i <= 23)
    {
      ledState = !ledState;                      //  1 -> 0 -> 1 -> 0 SuckSqeezeBangBlow Turbo Noises here
      digitalWrite(crankpin, ledState);
    }

   
    if (i == 24)
    {                                       //dead spot
      time = currentMicros - previousTime;       
      previousTime = currentMicros;                 
      Hz = 1000000.0 / time;
      i = 1;
    }
  }
}
