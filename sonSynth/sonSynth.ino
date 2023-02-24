#include <Keyboard.h> 
#include <Audio.h>
#include <Wire.h>
#include "TestSynth.h"
#include <string.h>

TestSynth faustSynth;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(faustSynth,0,out,0);
AudioConnection patchCord1(faustSynth,0,out,1);


//gestion boutons
bool synthButtonDefinitelyPressed = false; 
bool sampleButtonDefinitelyPressed = false;

bool currentSynthButtonState;
bool currentSampleButtonState;

bool lastSynthButtonState = false;
bool lastSampleButtonState = false;

unsigned long timeOfLastSynthButtonDebounce = 0;
unsigned long timeOfLastSampleButtonDebounce = 0;

//gestion clavier notes
//bool keysDefinitelyPressed[12];
//bool currentKeysStates[12];
//bool lastKeysStates[12];
unsigned long timeLastKeyPresses[12];
char correspondingKeys[12] = {'q', 'z', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j'};

//gestion clavier octaves
unsigned long timeLastOctaveUpPress = 0;
unsigned long timeLastOctaveDownPress = 0;
char octaveUpKey = 'b';
char octaveDownKey = 'v';

//volume
unsigned long timeLastPotentionReading = 0;
float oldGain;
float currentGain;


int octave = 2;
String synthOrSample = "synth";
int whichSynth = 0;
int whichSample = 0;
int nombreSynths = 1;
int nombreSamples = 1;

//changer d'octave en restant dans les bornes
void changeOctave(int changement){
  if(changement == 1 && octave < 8){
    octave += 1;
    Serial.println(" /\\ +1 octave /\\ ");
  } else if (changement == -1 && octave > 2){
    octave -= 1;
    Serial.println(" \\/ -1 octave \\/ ");
  }
}

//midi to frequency
float mtof(float note){
  return pow(2.0,(note-69.0)/12.0)*440.0;
}

//to midi
int midiNote(int octave, int distanceDo) {
  return (octave+1)*12+distanceDo;
}

//conversion String -> std::string
std::string Stos(String myString){
  return std::string(myString.c_str());
}





//pour l'instant communication Faust : pour l'instant 1 seul instrument, il faudra adapter cette fonction pour qu'elle change d'action en fct de l'instrument
void jouerNote(int octave, int distanceDo, String ){
  int note = midiNote(octave, distanceDo);
  String variableFaustGate = "gate" + String(distanceDo);
  String variableFaustFreq = "frequence" + String(distanceDo);
  
  faustSynth.setParamValue(Stos(variableFaustGate),0);
  delay(10);
  faustSynth.setParamValue(Stos(variableFaustFreq),mtof(note));
  faustSynth.setParamValue(Stos(variableFaustGate),1);
}






void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  //pinMode(2, INPUT);
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.5);
  Serial.begin(9600);
  while (!Serial) {
  }
  Keyboard.begin();
  

  for(int i=0;i<12;i++){
    timeLastKeyPresses[i] = 1000; //l'infini
  }
}




void loop() {
  unsigned long currentTime = millis(); //inexact plus on avance dans une itération mais pas grave
  
  bool currentSynthButtonState = digitalRead(0);
  bool currentSampleButtonState = digitalRead(1);

  //gestion notes de musique
  if (Serial.available()){
    char keyboardChar = Serial.read();
    Keyboard.write(keyboardChar);
    if(keyboardChar != '\n'){
      Serial.println("Touche appuyée : "+String(keyboardChar));
  
      int iterateur = 0;
      bool trouve = false;
      while((trouve == false) && (iterateur < 12)){
        if (keyboardChar == correspondingKeys[iterateur]){
          if(currentTime - timeLastKeyPresses[iterateur]> 100){
            Serial.println("Piouuuu");
            jouerNote(octave, iterateur);
          }
          timeLastKeyPresses[iterateur] = currentTime;
          trouve = true;
        }
        iterateur += 1;
        Serial.println(iterateur);
      }
      if (!trouve) {
        if (keyboardChar == octaveUpKey) {
          if (currentTime - timeLastOctaveUpPress> 100) {
            changeOctave(1);
          }
          timeLastOctaveUpPress = currentTime;
        } else if (keyboardChar == octaveDownKey) {
          if (currentTime - timeLastOctaveDownPress> 100) {
            changeOctave(-1);
          }
          timeLastOctaveDownPress = currentTime;
        } else {
          Serial.print("test aucune correspondance touche (peut-être retour chariot)");
        }
      }
    }
  }

  //passer au synth suivant
  if (currentSynthButtonState != lastSynthButtonState) {
    timeOfLastSynthButtonDebounce = currentTime;
  }
  if ((currentTime - timeOfLastSynthButtonDebounce) > 50) {
    if (currentSynthButtonState != synthButtonDefinitelyPressed) {
      synthButtonDefinitelyPressed = currentSynthButtonState;

      //faire l'action quand le bouton passe de assurément libre à assurément appuyé
      if (synthButtonDefinitelyPressed) {
        if (synthOrSample == "sample") {
          synthOrSample = "synth";
        }
        whichSynth += 1;
        if (whichSynth > nombreSynths - 1){
          whichSynth = 0;
        }
        Serial.print("\n");
        Serial.print("Synth sélectionné n°: ");*
        Serial.print(whichSynth);
      }
    }
  }



  //gestion bouton octave up NON maintenant c'est le bouton pour changer de sample
  if (currentSampleButtonState != lastSampleButtonState) {
    timeOfLastSampleButtonDebounce = currentTime;
  }
  if ((currentTime - timeOfLastSampleButtonDebounce) > 50) {
    if (currentSampleButtonState != sampleButtonDefinitelyPressed) {
      sampleButtonDefinitelyPressed = currentSampleButtonState;

      //faire l'action quand le bouton passe de assurément libre à assurément appuyé
      if (sampleButtonDefinitelyPressed) {
        if (synthOrSample == "synth") {
          synthOrSample = "sample";
        }
        whichSample += 1;
        if (whichSample > nombreSamples - 1){
          whichSample = 0;
        }
        Serial.print("\n");
        Serial.print("Sample sélectionné n°: ");*
        Serial.print(whichSample);
      }
    }
  }





  //gestion du volume
  if (currentTime - timeLastPotentionReading > 200) {
    oldGain = currentGain;
    currentGain = analogRead(A0) / 1023.0;
    if (abs(oldGain - currentGain) > 0.05) {
      faustSynth.setParamValue("gain", currentGain);
      Serial.print("\n");
      Serial.print("New gain :");
      Serial.print(currentGain);
    }
    timeLastPotentionReading = currentTime;
  }



  lastSynthButtonState = currentSynthButtonState;
  lastSampleButtonState = currentSampleButtonState;

}
