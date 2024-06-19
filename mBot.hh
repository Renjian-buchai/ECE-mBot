#if !defined(MBOT_HH) 
#define MBOT_HH

#include <MeMCore.h>

struct mBot {
  MeUltrasonicSensor ultrasonicSensor; 
  MeDCMotor left; 
  MeDCMotor right; 
  MeBuzzer buzzer; 
}; 

#endif 