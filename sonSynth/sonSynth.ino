#include <Keyboard.h> 
#include <Audio.h>
#include <Wire.h>
#include "TestSynth.h"
#include <string.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

TestSynth faustSynth;
AudioPlaySdWav playSdWav1;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioControlSGTL5000 sgtl5000_1;
AudioConnection patchCord0(playSdWav1,0,faustSynth,0);
AudioConnection patchCord1(playSdWav1,1,faustSynth,1);
AudioConnection patchCord2(faustSynth,0,out,0);
AudioConnection patchCord3(faustSynth,1,out,1);

const int KEYBOARD_REPEAT_DELAY = 250; //délai entre première et deuxième entrée lorsqu'on reste appuyé (dépend du clavier)
const int REPEAT_DELAY_RANGE = 5; //tolérance
const int KEYBOARD_MIN_DELAY = 100; //délai minimal général
const int PERSISTENT_SYNTH_SUSTAIN = 500; //combien de temps maintenir une touche dans un synthé persistent

const String notesNamesEN[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
const String notesNamesFR[12] = {"Do", "Do#", "Ré", "Ré#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si"};
const char correspondingKeys[12] = {'q', 'z', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j'};
const bool conventionFrancaise = true;

const char octaveUpKey = 'b';
const char octaveDownKey = 'v';

//synths
const int nombreSynths = 1;
String nomsSynths[nombreSynths] = {"harpe"};
bool synthPersistent[nombreSynths] = {false}; //dans le même ordre que nombreSynths, dire si on peut rester appuyé pour maintenir la note
bool toucheAllumee[12];

//samples
const int nombreSamples = 5;
const String nomsSamples[nombreSamples] = {"Meow_new.WAV", "Woof440_8bit_mono.WAV", "Bam440_8bit_mono.WAV", "Beach440_8bit_mono.WAV", "Xylo440_8bit_mono.WAV"};

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
String synthOrSample = "sample";
int selectedSynth = 0;
int selectedSample = 0;

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

//conversion String -> const char *
const char* StoConstCharPointer(String myString){
  return myString.c_str();
}

//dire si un appui clavier doit effectuer une action ou être ignoré
bool conditionClavier(int tempsActuel, int tempsDernierAppui){
  int diffTemps = tempsActuel - tempsDernierAppui;
  bool conditionDelaiMin = (diffTemps> KEYBOARD_MIN_DELAY); //délai minimal entre deux inputs
  bool conditionPremierDelai = abs(diffTemps - KEYBOARD_REPEAT_DELAY) > REPEAT_DELAY_RANGE; //délai interdit (premier délai en restant appuyé)
  return conditionDelaiMin && conditionPremierDelai;
}


//pour l'instant communication Faust : pour l'instant 1 seul instrument, il faudra adapter cette fonction
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
  
  if(synthOrSample == "sample"){
    const char * nomFichierAJouer = StoConstCharPointer(nomsSamples[selectedSample]);
    playFile(nomFichierAJouer);
  }
}


//cas des synthés persistents : éteindre la note lorsqu'on appuie plus
void finirNote(int octave, int distanceDo){
  int note = toMidi(octave, distanceDo);
  Serial.print("\n");
  Serial.print("Fin de la note : ");
  Serial.print(midiToName(note));

  String variableFaustGate = "gate" + String(distanceDo);
  faustSynth.setParamValue(Stos(variableFaustGate),0);
}


//void changerInstrument(String typeSource, String typeDest, int whichSource, int whichDest){
//  if (typeSource==
//}

void playFile(const char *filename)
{
  Serial.print("Sample choisi: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playSdWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(25);

  // Simply wait for the file to finish playing.
  
  
}

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  //pinMode(2, INPUT);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  audioShield.enable();
  audioShield.volume(0.5);
  Serial.begin(9600);
  while (!Serial) {
  }
  Keyboard.begin();
  
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  //audioShield.inputSelect(SDCARD_CS_PIN);

  for(int i=0;i<12;i++){
    timeLastKeyPresses[i] = 1000; //l'infini
    toucheAllumee[i] = false; //cas des synthés persistents
  }
}




void loop() {
  unsigned long currentTime = millis(); //inexact plus on avance dans une itération mais pas grave
  
  bool currentSynthButtonState = digitalRead(0);
  bool currentSampleButtonState = digitalRead(1);

  //gestion notes de musique : entrées clavier
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
          if(conditionClavier(currentTime, timeLastKeyPresses[iterateur])){ //rien ne change dans le cas d'un synth qui se maintient dans le temps
            jouerNote(octave, iterateur);
          }
          timeLastKeyPresses[iterateur] = currentTime;
          trouve = true;
        }
      }
      
      if (!trouve) {
        //touches changement d'octave
        if (keyboardChar == octaveUpKey) {
          if (conditionClavier(currentTime, timeLastOctaveUpPress)) {
            changeOctave(1);
          }
          timeLastOctaveUpPress = currentTime;
        } else if (keyboardChar == octaveDownKey) {
          if (conditionClavier(currentTime, timeLastOctaveDownPress)) {
            changeOctave(-1);
          }
          timeLastOctaveDownPress = currentTime;
        } else if (keyboardChar == 'c'){
          Serial.println("test changement sample");
          selectedSample = (selectedSample+1)%nombreSamples;
        } else {
          Serial.print("test aucune correspondance touche (peut-être retour chariot)");
        }
      }
    }
  }



  //gestion notes de musiques : éteindre les touches n'étant plus appuyées (dans le cas des synthés persistants)
  if (synthOrSample == "synth" && synthPersistent[selectedSynth]){
    for(int i = 0; i<12; i++){
      if(toucheAllumee[i] == true && timeLastKeyPresses[i] > PERSISTENT_SYNTH_SUSTAIN){
        finirNote(octave, i);
        toucheAllumee[i] = false;
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
        selectedSynth += 1;
        if (selectedSynth > nombreSynths - 1){
          selectedSynth = 0;
        }
        Serial.print("\n");
        Serial.print("Synth sélectionné n°: ");
        Serial.print(selectedSynth);
      }
    }
  }



  //passer au sample suivant
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
        selectedSample += 1;
        if (selectedSample > nombreSamples - 1){
          selectedSample = 0;
        }
        Serial.print("\n");
        Serial.print("Sample sélectionné n°: ");
        Serial.print(selectedSample);
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
