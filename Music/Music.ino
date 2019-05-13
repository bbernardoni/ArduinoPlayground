#include "notes.h"
#include "song.h"

int bpm = 200;
float separation = (float)1/4;
int delayTime;
int tempo;
int length;

int speakerPin = 9;

void playNote(int note, int duration) {
  int tone = tones[note];
  long endTime = millis() + duration;
  Serial.println(millis());
  Serial.println(endTime);
  if(tone < 16383){
    while (millis() < endTime) {
      digitalWrite(speakerPin, HIGH);
      delayMicroseconds(tone);
      digitalWrite(speakerPin, LOW);
      delayMicroseconds(tone);
    }
  }else{
    while (millis() < endTime) {
      digitalWrite(speakerPin, HIGH);
      delayMicroseconds(tone/2);
      delayMicroseconds(tone/2);
      digitalWrite(speakerPin, LOW);
      delayMicroseconds(tone/2);
      delayMicroseconds(tone/2);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
  length = sizeof(beats) / sizeof(float);
  tempo = 1000L * 60L / bpm;
  delayTime = tempo * separation;
}

void loop() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == 0) {
      delay(beats[i] * (float)tempo - delayTime); // rest
    } else {
      playNote(notes[i] - 1, beats[i] * (float)tempo - delayTime);
    }
    delay(delayTime); // pause between notes
  }
}
