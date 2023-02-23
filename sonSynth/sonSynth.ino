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

//gestion boutons
bool noteButtonDefinitelyPressed = false; 
bool octaveUpButtonDefinitelyPressed = false;
bool octaveDownButtonDefinitelyPressed = false;

bool currentNoteButtonState;
bool currentOctaveUpButtonState;
//bool currentOctaveDownButtonState;

bool lastNoteButtonState = false;
bool lastOctaveUpButtonState = false;
//bool lastOctaveDownButtonState = false;

unsigned long timeOfLastNoteButtonDebounce = 0;
unsigned long timeOfLastOctaveUpButtonDebounce = 0;



//volume
unsigned long tpsDepuisLecturePotentio = 0;
float oldGain;
float currentGain;

//midi to frequency
float mtof(float note){
  return pow(2.0,(note-69.0)/12.0)*440.0;
}


//to midi
int midiNote(int octave, int distanceDo) {
  return (octave+1)*12+distanceDo;
}

//communication Faust
void jouerNote(int note){
  faustSynth.setParamValue("gate1",0);
  delay(10);
  faustSynth.setParamValue("frequence1",mtof(note));
  faustSynth.setParamValue("gate1",1);
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
  currentNoteButtonState = digitalRead(0);
  currentOctaveUpButtonState = digitalRead(1);
  


  //gestion bouton note 
  if (currentNoteButtonState != lastNoteButtonState) {
    timeOfLastNoteButtonDebounce = millis();
  }
  if ((millis() - timeOfLastNoteButtonDebounce) > 50) {
    if (currentNoteButtonState != noteButtonDefinitelyPressed) {
      noteButtonDefinitelyPressed = currentNoteButtonState;

      //jouer note quand le bouton passe de assurément libre à assurément appuyé
      if (noteButtonDefinitelyPressed) {
        notePlacementInOctave = (notePlacementInOctave+1)%12;
        noteMidi = midiNote(octave,notePlacementInOctave);
        Serial.print("\n");
        Serial.print("Note pressée : ");
        Serial.print(noteMidi);
        jouerNote(noteMidi);
      }
    }
  }



  //gestion bouton octave up 
  if (currentOctaveUpButtonState != lastOctaveUpButtonState) {
    timeOfLastOctaveUpButtonDebounce = millis();
  }
  if ((millis() - timeOfLastOctaveUpButtonDebounce) > 50) {
    if (currentOctaveUpButtonState != octaveUpButtonDefinitelyPressed) {
      octaveUpButtonDefinitelyPressed = currentOctaveUpButtonState;

      //jouer note quand le bouton passe de assurément libre à assurément appuyé
      if (octaveUpButtonDefinitelyPressed) {
        octave += 1;
        Serial.print("\n");
        Serial.print("Octave up : ");
        Serial.print(octave);
      }
    }
  }





  //gestion du volume
  tpsDepuisLecturePotentio += millis() - tpsDepuisLecturePotentio;
  if (tpsDepuisLecturePotentio > 200) {
    oldGain = currentGain;
    currentGain = analogRead(A0) / 1023.0;
    if (abs(oldGain - currentGain) > 0.05) {
      faustSynth.setParamValue("gain", currentGain);
      Serial.print("\n");
      Serial.print("New gain :");
      Serial.print(currentGain);
    }
  }



  lastNoteButtonState = currentNoteButtonState;
  lastOctaveUpButtonState = currentOctaveUpButtonState;

}
