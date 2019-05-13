#include "floppy.h"

Floppy floppy(2,3);

void setup(){
  floppy.setup();

  resetAll();
  delay(1000);

  Serial.begin(9600);
  initTimer();
}

void resetAll(){
  floppy.setNote(-1);
  floppy.setDir(HIGH); // Go in reverse
 
  for (byte i=0; i<floppy.maxPosn; i++){
    floppy.toggleStepPin();
    delay(5);
  }

  floppy.curPosn = 0;
  floppy.setDir(LOW);
}

void initTimer(){
  //set timer2 interrupt at 200kHz
  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS21);
  OCR2A = 19;// = (16*10^6) / (200*10^3 * 8) - 1
  TIMSK2 |= (1 << OCIE2A);
  sei();
}

ISR(TIMER2_COMPA_vect){
  floppy.tick();
}

const int five[] = {48,50,52,53,55};
const int ode[] = {2,2,3,4,4,3,2,1,0,0,1,2,2,1,1,2,2,3,4,4,3,2,1,0,0,1,2,1,0,0};
const int len[] = {200,450,700,950};
const int odeLen[] = {1,1,1,1,1,1,1,1,1,1,1,1,2,0,3,1,1,1,1,1,1,1,1,1,1,1,1,2,0,3};

void loop(){
  //chromat();
  odeToJoy();
  //readSerial();
}

void chromat(){
  for(int i=40; i<80; i++){
    Serial.println(i);
    floppy.setNote(i);
    delay(450);
    floppy.setNote(-1);
    delay(50);
  }
}

void odeToJoy(){
  for(int i=0; i<30; i++){
    floppy.setNote(five[ode[i]]);
    delay(len[odeLen[i]]);
    floppy.setNote(-1);
    delay(50);
  }
}

void readSerial(){
  while(Serial.available()){
    char cmd = Serial.read();
    switch(cmd){
    case 'C': floppy.setNote(60); break;
    case 'd': floppy.setNote(61); break;
    case 'D': floppy.setNote(62); break;
    case 'e': floppy.setNote(63); break;
    case 'E': floppy.setNote(64); break;
    case 'F': floppy.setNote(65); break;
    case 'g': floppy.setNote(66); break;
    case 'G': floppy.setNote(67); break;
    case 'a': floppy.setNote(68); break;
    case 'A': floppy.setNote(69); break;
    case 'b': floppy.setNote(70); break;
    case 'B': floppy.setNote(71); break;
    case 'c': floppy.setNote(72); break;
    default:  floppy.setNote(-1); break;
    }
    Serial.println(cmd);
  }
}
