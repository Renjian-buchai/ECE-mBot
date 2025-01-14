#if !defined(MOVEMENT_HH)
#define MOVEMENT_HH

#include <MeMCore.h>
#include "mBot.hh"

void stopMotor(mBot& mBot) {
  mBot.left.run(0);
  mBot.right.run(0);
  return;
}

void moveForward(mBot& mBot) {
  mBot.left.run(-255);
  mBot.right.run(255);
  return;
}

/// @brief green
void turnRight(mBot& mBot) {
  mBot.left.run(-255);
  mBot.right.run(-255);
  delay(305);
  return;
}


/// @brief red 
void turnLeft(mBot& mBot) {
  mBot.left.run(255);
  mBot.right.run(255);
  delay(300);
  return;
}

/// @brief orange
void uTurn(mBot& mBot) {
  mBot.left.run(255);
  mBot.right.run(255);
  delay(600);
  return;
}

/// @brief purple
void doubleLeftTurn(mBot& mBot) {
  turnLeft(mBot);
  moveForward(mBot);
  delay(700);
  stopMotor(mBot);
  delay(100);
  turnLeft(mBot);
}

/// @brief blue 
void doubleRightTurn(mBot& mBot) {
  turnRight(mBot);
  moveForward(mBot);
  delay(720);
  stopMotor(mBot);
  delay(100);
  turnRight(mBot);
}


void nudgeLeft(mBot& mBot) {
  mBot.left.run(-180);
  mBot.right.run(255);
}

void nudgeRight(mBot& mBot) {
  mBot.left.run(-255);
  mBot.right.run(180);
}

/// @brief white
void celebrate(mBot& mBot) {
  MeBuzzer& buzzer = mBot.buzzer;

  // Bar 93
  buzzer.tone(466.16, 340);
  buzzer.tone(493.88, 140);
  buzzer.tone(415.3, 490);
  buzzer.tone(415.3, 80);
  buzzer.tone(466.16, 80);
  buzzer.tone(493.88, 80);
  buzzer.tone(554.37, 100);

  // Bar 94
  buzzer.tone(622.25, 210);
  buzzer.tone(659.25, 150);
  buzzer.tone(554.37, 320);
  buzzer.tone(1108.73, 140);
  buzzer.tone(1244.51, 140);
  buzzer.tone(1318.51, 140);

  // Bar 95
  buzzer.tone(1479.98, 140);
  buzzer.tone(739.99, 140);
  buzzer.tone(1108.73, 140);
  buzzer.tone(554.37, 140);
  buzzer.tone(1318.51, 140);
  buzzer.tone(1244.51, 140);
  buzzer.tone(1108.73, 140);
  buzzer.tone(1318.51, 140);

  // Bar 96
  buzzer.tone(1244.51, 70);
  buzzer.tone(1318.51, 70);
  buzzer.tone(1244.51, 70);
  buzzer.tone(1318.51, 70);
  buzzer.tone(1244.51, 70);
  buzzer.tone(1318.51, 70);
  buzzer.tone(1244.51, 70);
  buzzer.tone(1318.51, 70);
  buzzer.tone(1244.51, 290);
  buzzer.tone(622.25, 230);

  // Bar 97
  buzzer.tone(554.37, 140);
  buzzer.tone(622.25, 140);
  buzzer.tone(659.25, 140);
  buzzer.tone(622.25, 390);
  buzzer.tone(466.16, 330);

  // Bar 98
  buzzer.tone(554.37, 120);
  buzzer.tone(622.25, 120);
  buzzer.tone(493.88, 190);
  buzzer.tone(277.18, 140);
  buzzer.tone(987.77, 140);
  buzzer.tone(932.33, 140);
  buzzer.tone(554.37, 140);
  buzzer.tone(932.33, 140);

  // Bar 99
  buzzer.tone(987.77, 140);
  buzzer.tone(329.63, 140);
  buzzer.tone(932.33, 140);
  buzzer.tone(329.63, 140);
  buzzer.tone(1108.73, 190);
  buzzer.tone(1244.51, 190);
  buzzer.tone(1318.51, 170);

  // Bar 100
  buzzer.tone(1318.51, 80);
  buzzer.tone(1108.73, 80);
  buzzer.tone(932.33, 80);
  buzzer.tone(1108.73, 80);
  buzzer.tone(932.33, 80);
  buzzer.tone(783.99, 80);
  buzzer.tone(932.33, 80);
  buzzer.tone(739.99, 80);
  buzzer.tone(659.25, 80);
  buzzer.tone(622.25, 65);
  buzzer.tone(659.25, 65);
  buzzer.tone(739.99, 65);
  buzzer.tone(830.61, 400);

  buzzer.noTone();
}

#endif