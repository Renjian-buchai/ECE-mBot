#if !defined(SENSOR_HH)
#define SENSOR_HH

#include <MeMCore.h> 
#include "output.hh"
#include "mBot.hh"

enum class light { 
  IR = 0b00, 
  BLUE = 0b10,
  GREEN = 0b01, 
  RED = 0b11
}; 

enum class colours : uint8_t {
  RED       = 0b001, 
  GREEN     = 0b010, 
  BLUE      = 0b100,
  LIGHTBLUE = 0b110, 
  ORANGE    = 0b011, 
  PURPLE    = 0b101, 
  WHITE     = 0b111, 
  NONE      = 0b000
}; 

colours& operator|=(colours& lhs, colours rhs) {
  lhs = static_cast<colours>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs)); 
  return lhs; 
}

int16_t readIR() {  // Code for turning on the IR emitter only
  digitalWrite(A2, HIGH); 
  digitalWrite(A3, HIGH); 

  delay(50); 

  int16_t baseline = analogRead(A1); 

  digitalWrite(A2, LOW); 
  digitalWrite(A3, LOW); 

  delay(50); 
  int16_t ret = analogRead(A1);
  delay(50); 

  return baseline - ret;  
}

int16_t readRed() {  // Code for turning on the red LED only
  digitalWrite(A2, HIGH); 
  digitalWrite(A3, HIGH); 

  delay(200); 
  int16_t ret = analogRead(A0); 
  delay(50); 

  return ret; 
}

int16_t readGreen() {  // Code for turning on the green LED only
  digitalWrite(A2,LOW); 
  digitalWrite(A3, HIGH); 

  delay(200); 
  int16_t ret = analogRead(A0);  
  delay(50); 

  return ret; 
}

int16_t readBlue() {  
  digitalWrite(A2, HIGH); 
  digitalWrite(A3,LOW); 

  delay(200); 
  int16_t ret = analogRead(A0);
  delay(50); 
  return ret; 
}

colours detectColour() {
  int16_t r, g, b; 
  // Shine Red, read LDR after some delay
  r = readRed(); 
  // Shine Green, read LDR after some delay
  g = readGreen(); 
  // Shine Blue, read LDR after some delay
  b = readGreen(); 
  // Run algorithm for colour decoding

  return colours::NONE; 
}

#endif 