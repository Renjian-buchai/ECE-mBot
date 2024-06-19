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
  mBot.line = MeLineFollower(PORT_2); 
}

double distance;
uint16_t baseline;

int8_t running; 
int8_t nudge; 

uint16_t time = 100; 
void loop() {
  
  while (analogRead(A7) < 100) {
    ++running; 
  }

  if (running) {
    detectColour(); 
    running = 0; 
  }

  // nudge = 0;  

  // moveForward(mBot); 

  // while (analogRead(A7) < 100) {
  //   ++running; 
  // }

  // switch (mBot.line.readSensors()) {
  //   case S1_IN_S2_IN: 
  //     stopMotor(mBot); 
  //     break; 
    
  //   default: 
  //     moveForward(mBot); 
  //     break; 
  // }

  // // Read ultrasonic sensing distance (choose an appropriate timeout)
  // distance = mBot.ultrasonicSensor.distanceCm(15);

  // LOG(distance); 

  // while (distance < 8.0f) {
  //   LOG("Turn right"); 
  //   nudgeRight(mBot);  
  //   distance = mBot.ultrasonicSensor.distanceCm(15); 
  // }

  // // Read IR sensing distance (turn off IR, read IR detector, turn on IR,
  // // read IR detector, estimate distance)

  // distance = readIR(); 
  // LOG(distance);

  // // Not technically distance, but may as well reuse the variable.
  // while (distance > 250.0f) {  
  //   LOG("Turn left"); 
  //   nudgeLeft(mBot); 
  //   distance = readIR(); 
  // }

  // // if within black line, stop motor, detect colour, and take corresponding0
  // // action
  // delay(100); 

  // // else if too near to left wall, nudge right
  // // else if too near to right wall, nudge left
  // // else move forward 
  // LOG(); 
}
