/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#define LED_PIN  2
#define TRIGGER_PIN 6
#define ECHO_PIN 5

bool personDetected = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  
  long distance = measureDistance();
  
  if (distance < 150 && distance > 0) {  // This is where the LED On/Off happens
    digitalWrite(LED_PIN, LOW); // When the Red condition is met, the Green LED should turn off
    personDetected = true;
  }
  else {
    digitalWrite(LED_PIN, HIGH);
    personDetected = false;
  }

  Serial.println(distance);

  if (personDetected)
  {
    delay(5000);
  }
  else
  {
    delay(100);
  }
}

long measureDistance()
{
  long totalDistance = 0;

  for (int i = 0; i < 5; i++)
  {
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    totalDistance += (duration/2) / 29.1;
    delay(80);
  }

  return totalDistance / 5;
}

