#include "Notes.h"

Notes notes;

ISR(TIMER1_COMPA_vect) {
  notes.tick();
}

void setupTimers()
{
  pinMode(11, OUTPUT); // A Hi
  pinMode(3, OUTPUT);  // B Lo

  // set up timer 2 for pwm
  ASSR &= ~(_BV(EXCLK) | _BV(AS2));
  TCCR2A = _BV(COM2A1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS20);

  OCR2A = 0x7F;

  // set up timer 1 for interrupts
  cli();
  TCCR1A = 0;
  TCCR1B = _BV(WGM12) | _BV(CS10);
  OCR1A = 141;
  TIMSK1 |= _BV(OCIE1A);
  sei();
}


void setup(){
  Serial.begin(115200);
  notes.setNote(69+12);
  setupTimers();
}

void loop(){
  while(true);
}
