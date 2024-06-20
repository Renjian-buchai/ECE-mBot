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
  DARKGREEN = 0b000,
  BLUE = 0b001,
  GREEN = 0b010,
  LIGHTBLUE = 0b011,
  RED = 0b100,
  PURPLE = 0b101,
  ORANGE = 0b110,
  WHITE = 0b111
};

// If you can't figure out what this is doing without comments, maybe you need a new brain.
[[nodiscard]] uint16_t readIR(mBot& mBot) {
  digitalWrite(mBot.lightPin0, HIGH);
  digitalWrite(mBot.lightPin1, HIGH);

  delay(2);

  uint16_t baseline = analogRead(mBot.iRPin);

  digitalWrite(mBot.lightPin0, LOW);
  digitalWrite(mBot.lightPin1, LOW);

  delay(2);
  uint16_t ret = analogRead(mBot.iRPin);

  return baseline - ret;
}

[[nodiscard]] uint16_t readRed(mBot& mBot) {
  digitalWrite(mBot.lightPin0, HIGH);
  digitalWrite(mBot.lightPin1, HIGH);

  delay(400);
  uint16_t ret = analogRead(mBot.lDRPin);
  delay(50);

  return ret;
}

[[nodiscard]] uint16_t readGreen(mBot& mBot) {
  digitalWrite(mBot.lightPin0, LOW);
  digitalWrite(mBot.lightPin1, HIGH);

  delay(400);
  uint16_t ret = analogRead(mBot.lDRPin);
  delay(50);

  return ret;
}

[[nodiscard]] uint16_t readBlue(mBot& mBot) {
  digitalWrite(mBot.lightPin0, HIGH);
  digitalWrite(mBot.lightPin1, LOW);

  delay(400);
  uint16_t ret = analogRead(mBot.lDRPin);
  delay(50);
  return ret;
}

static colours& operator|=(colours& lhs, colours rhs) {
  lhs = static_cast<colours>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
  return lhs;
}

colours detectColour(mBot& mBot) {
  uint16_t r, g, b;
  colours colour = colours::DARKGREEN;
  r = readRed(mBot);
  g = readGreen(mBot);
  b = readBlue(mBot);

  // Colour decoding
  LOG("red: ");
  LOG(r);
  if (r > 850) {
    colour |= colours::RED;
  }

  LOG("green: ");
  LOG(g);
  if (g > 765) {
    colour |= colours::GREEN;
  }

  LOG("blue: ");
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
  }
  mBot.led.show();
#endif

  LOG();

  return colour;
}

#endif