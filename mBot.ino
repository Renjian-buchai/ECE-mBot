#include <MeMCore.h>

#include "sensor.hh"
#include "movement.hh"
#include "output.hh"
#include "mBot.hh"

mBot mBot;

#define TIMEOUT 2000        // Max microseconds to wait; choose according to max distance of wall
#define SPEED_OF_SOUND 340  // Update according to your own experiment

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
  mBot.led = MeRGBLed(0, 30);
  mBot.led.setpin(13);  
}

double distance;
uint16_t baseline;

int8_t running = 0;

uint16_t time = 100;
void loop() {
#if CALIBRATION
  while (analogRead(A7) < 100) {
    ++running;
  }

  if (running) {
    detectColour(mBot);
    running = 0;
  }
#else

  while (analogRead(A7) < 100) {
    ++running;
  }

  // Make sure that the thing only runs once you press the button
  // So that we can control how we release the mBot more easily
  if (!running) { return; }

  switch (mBot.line.readSensors()) {
    case S1_IN_S2_IN: [[fallthrough]]
    case S1_IN_S2_OUT: [[fallthrough]]
    case S1_OUT_S2_IN: 
      stopMotor(mBot);
      delay(100);

      switch (detectColour(mBot)) {
        case colours::RED:
          turnLeft(mBot);
          break;

        case colours::GREEN: [[fallthrough]];
        case colours::DARKGREEN:
          turnRight(mBot);
          break;

        case colours::BLUE: [[fallthrough]];
        case colours::LIGHTBLUE:
          doubleRightTurn(mBot);
          break;

        case colours::ORANGE:
          uTurn(mBot);
          break;

        case colours::PURPLE:
          doubleLeftTurn(mBot);
          break;

        case colours::WHITE:
          // celebrate(mBot);
          running = 0; 
          break;

        default:
          LOG("Gay!");
          break;
      }
      break;

    default:
    stillOnCooldown: 
      // Not technically distance, but may as well reuse the variable.
      distance = readIR();
      LOG("IR distance: ");
      LOG(distance);

      if (distance > 250.0f) {
        LOG("Turn left");
        nudgeLeft(mBot);
        break; 
      }

      LOG("US distance: ");

      distance = mBot.ultrasonicSensor.distanceCm(); 

      LOG(distance);

      if (distance < 8.0f) {
        LOG("Turn right");
        nudgeRight(mBot);
        break; 
      }

      moveForward(mBot);
      break;
  }
  
  LOG();

#endif
}
