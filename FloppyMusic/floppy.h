#pragma once

#include <Arduino.h>

const unsigned int midiPeriods[128] PROGMEM = { 
    6116, 5772, 5448, 5143, 4854, 4582, 4324, 4082, 3853, 3636, 3432, 3240, 3058, 2886, 2724, 2571, 2427, 2291, 2162, 2041, 1926, 1818, 1716, 
    1620, 1529, 1443, 1362, 1286, 1213, 1145, 1081, 1020, 963, 909, 858, 810, 764, 722, 681, 643, 607, 573, 541, 510, 482, 455, 429, 405, 382, 
    361, 341, 321, 303, 286, 270, 255, 241, 227, 215, 202, 191, 180, 170, 161, 152, 143, 135, 128, 120, 114, 107, 101, 96, 90, 85, 80, 76, 72, 
    68, 64, 60, 57, 54, 51, 48, 45, 43, 40, 38, 36, 34, 32, 30, 28, 27, 25, 24, 23, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 12, 11, 11, 10, 9, 
    9, 8, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4 };

struct Floppy{
  Floppy(byte _stepPin, byte _dirPin, byte _maxPosn = 158):
    stepPin(_stepPin),
    dirPin(_dirPin),
    maxPosn(_maxPosn),
    curPosn(0),
    stepState(LOW),
    curDir(LOW),
    curPeriod(0),
    curTick(0)
  {}
 
  void setup(){
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
  }
 
  void tick(){
    if (curPeriod > 0){
      curTick++;
      if (curTick >= curPeriod){
        step();
        curTick=0;
      }
    }
  }
 
  void step(){
    if(curPosn >= maxPosn)
      setDir(HIGH);
    else if(curPosn <= 0)
      setDir(LOW);

    if(curDir == HIGH)
      curPosn--;
    else
      curPosn++;

    toggleStepPin();
  }
 
  void setDir(int dir){
    digitalWrite(dirPin, dir);
    curDir = dir;
  }
 
  void toggleStepPin(){
    stepState = ~stepState;
    digitalWrite(stepPin, stepState);
  }
 
  void setNote(int note){
    if(note < 0)
      curPeriod = 0;
    else
      curPeriod = pgm_read_word_near(midiPeriods + note);
  }
 
  byte stepPin;
  byte dirPin;
 
  /*The maximum track position for each step-control pin. 3.5" Floppies have
  80 tracks, 5.25" have 50.  These should be doubled, because each tick is now
  half a position (use 158 and 98). */
  byte maxPosn;
  byte curPosn;
 
  //Variables to keep track of state of each pin. LOW = forward, HIGH=reverse
  int stepState;
  int curDir;
 
  //Current period assigned to each pin.  0 = off.  Each period is of the length specified by the RESOLUTION
  //variable above.  i.e. A period of 10 is (RESOLUTION x 10) microseconds long.
  unsigned int curPeriod;
  unsigned int curTick;
};
