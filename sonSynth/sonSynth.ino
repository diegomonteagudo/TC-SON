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

int testInstrument = 0;

const int KEYBOARD_REPEAT_DELAY = 250; //délai entre première et deuxième entrée lorsqu'on reste appuyé (dépend du clavier)
const int REPEAT_DELAY_RANGE = 5; //tolérance
const int KEYBOARD_MIN_DELAY = 100; //délai minimal général

const String notesNamesEN[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
const String notesNamesFR[12] = {"Do", "Do#", "Ré", "Ré#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si"};
const char correspondingKeys[12] = {'q', 'z', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j'};
const bool conventionFrancaise = true;

const char octaveUpKey = 'b';
const char octaveDownKey = 'v';

//instruments
//String nomsSynths = ["harpe", "marimba"];
const int nombreSynths = 1;
const int nombreSamples = 1;

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

//gestion clavier octaves
unsigned long timeLastOctaveUpPress = 0;
unsigned long timeLastOctaveDownPress = 0;


//volume
unsigned long timeLastPotentionReading = 0;
float oldGain;
float currentGain;


int octave = 2;
String synthOrSample = "synth";
int whichSynth = 0;
int whichSample = 0;

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

String midiToName(int note){
  String noteName;
  if(conventionFrancaise){
    noteName = notesNamesFR[note%12] + String(octave);
  } else {
    noteName = notesNamesEN[note%12] + String(octave);
  }
  return noteName;
}

//to midi
int toMidi(int octave, int distanceDo) {
  return (octave+1)*12+distanceDo;
}

//conversion String -> std::string
std::string Stos(String myString){
  return std::string(myString.c_str());
}

//dire si un appui clavier doit effectuer une action ou être ignoré
bool conditionClavier(int tempsActuel, int tempsDernierAppui){
  int diffTemps = tempsActuel - tempsDernierAppui;
  bool conditionDelaiMin = (diffTemps> KEYBOARD_MIN_DELAY); //délai minimal entre deux inputs
  bool conditionPremierDelai = abs(diffTemps - KEYBOARD_REPEAT_DELAY) > REPEAT_DELAY_RANGE; //délai interdit (premier délai en restant appuyé)
  return conditionDelaiMin && conditionPremierDelai;
}


//pour l'instant communication Faust : pour l'instant 1 seul instrument, il faudra adapter cette fonction pour qu'elle change d'action en fct de l'instrument
void jouerNote(int octave, int distanceDo){
  int note = toMidi(octave, distanceDo);
  Serial.print("\n");
  Serial.print("Note jouée : ");
  Serial.print(midiToName(note));
  
  String variableFaustGate = "gate" + String(distanceDo);
  String variableFaustFreq = "frequence" + String(distanceDo);
  
  faustSynth.setParamValue(Stos(variableFaustGate),0);
  delay(10);
  faustSynth.setParamValue(Stos(variableFaustFreq),mtof(note));
  faustSynth.setParamValue(Stos(variableFaustGate),1);
}


//void changerInstrument(String typeSource, String typeDest, int whichSource, int whichDest){
//  if (typeSource==
//}



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

      //touches de notes
      while((trouve == false) && (iterateur < 12)){
        if (keyboardChar == correspondingKeys[iterateur]){
          if(conditionClavier(currentTime, timeLastKeyPresses[iterateur])){
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
        //touches changement d'octave
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
        } else if (keyboardChar == 'c'){ //test changement d'instrument (temporaire)
          Serial.println("test changement instrument");
          if (testInstrument == 0){
            testInstrument = 1;
            faustSynth.setParamValue("harpeStatus",0);
            faustSynth.setParamValue("marimbaStatus",1);
          } else {
            testInstrument = 0;
            faustSynth.setParamValue("harpeStatus",1);
            faustSynth.setParamValue("marimbaStatus",0);
          }
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
        Serial.print("Synth sélectionné n°: ");
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
        Serial.print("Sample sélectionné n°: ");
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
