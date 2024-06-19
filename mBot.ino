#include <MeMCore.h> 

#include "sensor.hh"
#include "movement.hh"
#include "output.hh"
#include "mBot.hh"

mBot mBot; 

void setup() {
  pinMode(M1, OUTPUT); 
  pinMode(M2, OUTPUT); 
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT); 
  pinMode(A2, OUTPUT); 
  pinMode(A3, OUTPUT); 
  Serial.begin(9600);  

  mBot.ultrasonicSensor = MeUltrasonicSensor(PORT_1); 
  mBot.left = MeDCMotor(M1); 
  mBot.right = MeDCMotor(M2); 
}

double distance;
uint16_t baseline;

int8_t running; 

uint16_t time = 500; 
void loop() { 

  while (analogRead(A7) < 100) {
    ++running; 
  }

  if (running) {
    doubleLeftTurn(mBot, time); 
    stopMotor(mBot);

    time += 20; 

    running = 0; 
  }

  // Read ultrasonic sensing distance (choose an appropriate timeout)
  distance = mBot.ultrasonicSensor.distanceCm();

  LOG(distance); 

  if (distance < 10.0f) {
    LOG("Turn right"); 
    nudgeRight(); 
  }

  // Read IR sensing distance (turn off IR, read IR detector, turn on IR,
  // read IR detector, estimate distance)

  distance = readIR(); 
  LOG(distance);

  // Not technically distance, but may as well reuse the variable.
  if (distance > 300.0f) {  
    LOG("Turn left"); 
    nudgeLeft(); 
  }


  // if within black line, stop motor, detect colour, and take corresponding0
  // action

  delay(100); 

  // else if too near to left wall, nudge right
  // else if too near to right wall, nudge left
  // else move forward 
  LOG(); 
}
