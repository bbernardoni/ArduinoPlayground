#pragma once

#include <Arduino.h>

#define SAMPLE_RATE 224400

struct Notes{
  Notes():
    pwm(0),
    dir(true)
  {}
 
  void tick(){
    if(dir){ //up
      pwm++;
      if(pwm==255)
        dir = false;
    }else{
      pwm--;
      if(pwm==0)
        dir = true;
    }
    OCR2A = pwm;
  }

  void setNote(int note){
    if(note > 0){
      double midiFreq = 440.0*pow(2.0f, (note-69)/12.0f);
      //OCR1A = F_CPU / SAMPLE_RATE - 1;
    }
  }

  int pwm;
  boolean dir;
};
