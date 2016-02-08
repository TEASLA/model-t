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

#include <SoftwareSerial.h>

#define LED_PIN  2
#define POT_ON_PIN 3
#define PUMP_TEA_PIN 4
#define ECHO_PIN 5
#define TRIGGER_PIN 6

#define BLE_TX 11
#define BLE_RX 10

bool personDetected = false;
long lastActionEpoch;
SoftwareSerial bleSerial(11,10); // RX - 11, TX - 10

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED_PIN, OUTPUT);
  pinMode(POT_ON_PIN, OUTPUT);
  pinMode(PUMP_TEA_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(POT_ON_PIN, LOW);
  digitalWrite(PUMP_TEA_PIN, HIGH);

  bleSerial.begin(9600);
  bleSerial.print("$");
  bleSerial.print("$");
  bleSerial.print("$");
  delay(100);
  bleSerial.println("SU,96");
  delay(100);
  bleSerial.println("---");

  Serial.begin(9600);
  Serial.setTimeout(50);

  lastActionEpoch = 0;
}

// the loop function runs over and over again forever
void loop() {

  int action = getActionBle();

  if (action == 0)
  {
    // If there has been no activity then turn off the LED.
    if (millis() - lastActionEpoch > 10000)
    {
      digitalWrite(LED_PIN, HIGH);
    }
    
    return;
  }

  Serial.println(action);

  lastActionEpoch = millis();
  // LED strip ON.
  if (action == 1)
  {
    digitalWrite(LED_PIN, LOW);
  }
  // LED strip OFF.
  else if (action == 3)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  // Make some tea.
  else if (action == 2)
  {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(POT_ON_PIN, LOW);
    digitalWrite(PUMP_TEA_PIN, LOW);
    delay(15000);
    digitalWrite(PUMP_TEA_PIN, HIGH);
  }
  // Machine OFF.
  else if (action == 4)
  {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(POT_ON_PIN, HIGH);
  }
  // Machine ON.
  else if (action == 5)
  {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(POT_ON_PIN, LOW);
  }
  else
  {
    Serial.print("Unknown command of - "); Serial.println(action);
  }
  
  /*long distance = measureDistance();
  
  if (distance < 150 && distance > 0) {
    digitalWrite(LED_PIN, LOW);
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
  }*/
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

int getActionBle()
{
  if ( bleSerial.available() > 0 ) {
    // read a numbers from serial port
    int count = bleSerial.parseInt();// print out the received number
    return count;
  }
  else
  {
    return 0;
  }
  /*
  byte commandBuffer[10];
  byte bytesRead = bleSerial.readBytes((char*)commandBuffer, 10);

  if (bytesRead == 0)
  {
    return 0;
  }

  byte command = commandBuffer[0];
  if (command == '1')
  {
    return 1;
  }
  else if (command == '2')
  {
    return 2;
  }
  else if (command == '3')
  {
    return 3;
  }
  else if (command == '4')
  {
    return 4;
  }
  else if (command == '5')
  {
    return 5;
  }
  else
  {
    return 10;
  }*/
}

