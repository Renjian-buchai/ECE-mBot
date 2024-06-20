#if !defined(MBOT_HH)
#define MBOT_HH

#include <MeMCore.h>

struct mBot {
  MeUltrasonicSensor ultrasonicSensor;
  MeDCMotor left;
  MeDCMotor right;
  MeBuzzer buzzer;
  MeLineFollower line;
  MeRGBLed led; 
  uint8_t lightPin0; 
  uint8_t lightPin1; 
  uint8_t iRPin; 
  uint8_t lDRPin; 
};

#endif