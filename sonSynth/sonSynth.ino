#include <Audio.h>
#include "TestSynth.h"

TestSynth faustSynth;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(faustSynth,0,out,0);
AudioConnection patchCord1(faustSynth,0,out,1);

int octave = 4;
int notePlacementInOctave = 9;
int noteMidi = 60;

bool octaveUpPressed = false;
bool octaveDownPressed = false;
bool noteButtonPressed = false;
bool enTrainDeJouerUneNote = false;

float oldGain;
float currentGain;

float mtof(float note){
  return pow(2.0,(note-69.0)/12.0)*440.0;
}

int midiNote(int octave, int distanceDo) {
  return (octave+1)*12+distanceDo;
}

void jouerNote(int note){
  faustSynth.setParamValue("gate",0);
  delay(10);
  faustSynth.setParamValue("frequence",mtof(note));
  faustSynth.setParamValue("gate",1);
  Serial.println("La note a bien été jouée");
}

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  //pinMode(2, INPUT);
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.5);
  Serial.begin(9600);
}

void loop() {

  //gestion bouton note
  if (digitalRead(0) && !noteButtonPressed) { // button is pressed
    noteButtonPressed = true;
    notePlacementInOctave = (notePlacementInOctave+1)%12;
    noteMidi = midiNote(octave,notePlacementInOctave);
    Serial.print("\n");
    Serial.print("Note pressée : ");
    Serial.print(noteMidi);
    jouerNote(noteMidi);
  }
  else if (!digitalRead(0) && noteButtonPressed) { //button is released
    noteButtonPressed = false;
  }

  //gestion bouton octave up
  if (digitalRead(1) && !octaveUpPressed) { // button is pressed
    octaveUpPressed = true;
    octave += 1;
    Serial.print("\n");
    Serial.print("Octave up : ");
    Serial.print(octave);
  }
  else if (!digitalRead(1) && octaveUpPressed) { //button is released
    octaveUpPressed = false;
  }

//  //gestion bouton octave down
//  if (digitalRead(2) && !octaveDownPressed) { // button is pressed
//    octaveDownPressed = true;
//    octave -= 1;
//    Serial.println("Octave down " + octave);
//  }
//  else if (!digitalRead(2) && octaveDownPressed) { //button is released
//    octaveDownPressed = false;
//  }

  oldGain = currentGain;
  currentGain = analogRead(A0)/1023.0;
  if (abs(oldGain-currentGain) > 0.05) {
    faustSynth.setParamValue("gain",currentGain);
    Serial.print("\n");
    Serial.print("New gain :");
    Serial.print(currentGain);
  }
  delay(150);
}
