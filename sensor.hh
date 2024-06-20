#if !defined(SENSOR_HH)
#define SENSOR_HH

#include <MeMCore.h>
#include "output.hh"
#include "mBot.hh"

#define CALIBRATION 0

/// @brief documentation purposes only 
[[maybe_unused]] enum class lights {
  IR = 0b00,
  BLUE = 0b10,
  GREEN = 0b01,
  RED = 0b11
};

enum class colours : uint8_t {
  RED = 0b100,
  GREEN = 0b010,
  BLUE = 0b001,
  DARKGREEN = 0b000,
  LIGHTBLUE = 0b011,
  ORANGE = 0b110,
  PURPLE = 0b101,
  WHITE = 0b111,
};

static colours& operator|=(colours& lhs, colours rhs) {
  lhs = static_cast<colours>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
  return lhs;
}

// If you can't figure out what this is doing without comments, maybe you need a new brain.
[[nodiscard]] int16_t readIR() {  
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);

  delay(2);

  int16_t baseline = analogRead(A1);

  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);

  delay(2);
  int16_t ret = analogRead(A1);

  return baseline - ret;
}

[[nodiscard]] int16_t readRed() {  
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);

  delay(400);
  int16_t ret = analogRead(A0);
  delay(50);

  return ret;
}

[[nodiscard]] int16_t readGreen() {  
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);

  delay(400);
  int16_t ret = analogRead(A0);
  delay(50);

  return ret;
}

[[nodiscard]] int16_t readBlue() {
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);

  delay(400);
  int16_t ret = analogRead(A0);
  delay(50);
  return ret;
}

[[nodiscard]] colours detectColour(mBot& mBot) {
  int16_t r, g, b;
  colours colour = colours::DARKGREEN;
  // Shine Red, read LDR after some delay
  r = readRed();
  // Shine Green, read LDR after some delay
  g = readGreen();
  // Shine Blue, read LDR after some delay
  b = readBlue();
  // Run algorithm for colour decoding

  // Serial.print("red: ");
  LOG(r);
  if (r > 850) {
    colour |= colours::RED;
  }

  // Serial.print("green: ");
  LOG(g);
  if (g > 765) {
    colour |= colours::GREEN;
  }

  // Serial.print("blue: ");
  LOG(b);
  if (b > 905) {
    colour |= colours::BLUE;
  }

#if CALIBRATION
  switch (colour) {
    case colours::RED:
      LOG("RED");
      mBot.led.setColor(255, 0, 0); 
      break;

    case colours::GREEN: [[fallthrough]];
    case colours::DARKGREEN:
      LOG("GREEN");
      mBot.led.setColor(0, 255, 0); 
      break;

    case colours::BLUE: [[fallthrough]];
    case colours::LIGHTBLUE:
      LOG("BLUE");
      mBot.led.setColor(0, 0, 255); 
      break;

    case colours::ORANGE:
      mBot.led.setColor(255, 125, 0); 
      LOG("ORANGE");
      break;

    case colours::PURPLE:
      mBot.led.setColor(255, 0, 255); 
      LOG("PURPLE");
      break;

    case colours::WHITE:
      mBot.led.setColor(255, 255, 255); 
      LOG("WHITE");
      break;

    default:
      LOG("Gay!");
      break;
  }
  mBot.led.show(); 
#endif

  LOG();

  return colour;
}

double readUltrasonic() {
  constexpr int ultrasonic = 12; 
  constexpr int timeout = 2000; 
  constexpr int speedOfSound = 340; 
  
  pinMode(ultrasonic, OUTPUT);
  digitalWrite(ultrasonic, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonic, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonic, LOW);

  pinMode(ultrasonic, INPUT);
  return pulseIn(ultrasonic, HIGH, timeout) / 2.0 / 1000000 * speedOfSound * 100;
}

#endif