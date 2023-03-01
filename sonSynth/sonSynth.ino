#include <Keyboard.h> 
#include <Audio.h>
#include <Wire.h>
#include "TestSynth.h"
#include <string.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "TestSynth.h"
#include "chords.h"

#include <string.h>

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

TestSynth faustSynth;
AudioSynthKarplusStrong  string1;        //xy=347.09093475341797,120
AudioSynthKarplusStrong  string2;        //xy=347.0909080505371,167
AudioSynthKarplusStrong  string3;        //xy=348.09093856811523,214.09090614318848
AudioSynthKarplusStrong  string5;        //xy=350.09093856811523,307.0908946990967
AudioPlaySdWav           playSdWav2;     //xy=349.34090423583984,548.8408889770508
AudioSynthKarplusStrong  string4;        //xy=351.09093856811523,262.09090995788574
AudioPlaySdWav           playSdWav3; //xy=350.25000953674316,589.8409004211426
AudioPlaySdWav           playSdWav4; //xy=350.25000953674316,629.8409004211426
AudioPlaySdWav           playSdWav7; //xy=350.25000953674316,756.8409061431885
AudioPlaySdWav           playSdWav1;     //xy=351.34092140197754,506.8408946990967
AudioPlaySdWav           playSdWav8; //xy=350.25000953674316,796.8409061431885
AudioSynthKarplusStrong  string6;        //xy=352.09093856811523,351.0909090042114
AudioPlaySdWav           playSdWav5; //xy=351.34092140197754,673.8409004211426
AudioPlaySdWav           playSdWav6; //xy=351.34092140197754,713.8409004211426
AudioPlaySdWav           playSdWav11; //xy=354.25,916.8409442901611
AudioPlaySdWav           playSdWav12; //xy=354.25000953674316,960.8409442901611
AudioPlaySdWav           playSdWav9; //xy=355.34092140197754,837.8409385681152
AudioPlaySdWav           playSdWav10; //xy=355.34092140197754,877.8409385681152
AudioMixer4              mixer5;         //xy=577.1136093139648,505.6818313598633
AudioMixer4              mixer9; //xy=577.0909423828125,746.3636322021484
AudioMixer4              mixer6;         //xy=577.8636093139648,585.4318313598633
AudioMixer4              mixer7;         //xy=577.6136093139648,664.4317512512207
AudioMixer4              mixer10; //xy=577.8409423828125,826.1136322021484
AudioMixer4              mixer11; //xy=577.5909423828125,905.1135520935059
AudioMixer4              mixer1;         //xy=670.0909614562988,173.09093475341797
AudioMixer4              mixer2;         //xy=813.0909614562988,325.0909061431885
AudioMixer4              mixer12; //xy=813.0909423828125,726.3636474609375
AudioMixer4              mixer8; //xy=813.8636016845703,638.4317054748535
AudioMixer4              mixer3;         //xy=958.0909614562988,422.0909061431885
AudioOutputI2S           i2s1;           //xy=1145.0909576416016,402.0909061431885
AudioConnection          patchCord1(string1, 0, mixer1, 0);
AudioConnection          patchCord2(string2, 0, mixer1, 1);
AudioConnection          patchCord3(string3, 0, mixer1, 2);
AudioConnection          patchCord4(string5, 0, mixer2, 1);
AudioConnection          patchCord5(playSdWav2, 0, mixer5, 2);
AudioConnection          patchCord6(playSdWav2, 1, mixer5, 3);
AudioConnection          patchCord7(string4, 0, mixer1, 3);
AudioConnection          patchCord8(playSdWav3, 0, mixer6, 0);
AudioConnection          patchCord9(playSdWav3, 1, mixer6, 1);
AudioConnection          patchCord10(playSdWav4, 0, mixer6, 2);
AudioConnection          patchCord11(playSdWav4, 1, mixer6, 3);
AudioConnection          patchCord12(playSdWav7, 0, mixer9, 0);
AudioConnection          patchCord13(playSdWav7, 1, mixer9, 1);
AudioConnection          patchCord14(playSdWav1, 0, mixer5, 0);
AudioConnection          patchCord15(playSdWav1, 1, mixer5, 1);
AudioConnection          patchCord16(playSdWav8, 0, mixer9, 2);
AudioConnection          patchCord17(playSdWav8, 1, mixer9, 3);
AudioConnection          patchCord18(string6, 0, mixer2, 2);
AudioConnection          patchCord19(playSdWav5, 0, mixer7, 0);
AudioConnection          patchCord20(playSdWav5, 1, mixer7, 1);
AudioConnection          patchCord21(playSdWav6, 0, mixer7, 2);
AudioConnection          patchCord22(playSdWav6, 1, mixer7, 3);
AudioConnection          patchCord23(playSdWav11, 0, mixer11, 0);
AudioConnection          patchCord24(playSdWav11, 1, mixer11, 1);
AudioConnection          patchCord25(playSdWav12, 0, mixer11, 2);
AudioConnection          patchCord26(playSdWav12, 1, mixer11, 3);
AudioConnection          patchCord27(playSdWav9, 0, mixer10, 0);
AudioConnection          patchCord28(playSdWav9, 1, mixer10, 1);
AudioConnection          patchCord29(playSdWav10, 0, mixer10, 2);
AudioConnection          patchCord30(playSdWav10, 1, mixer10, 3);
AudioConnection          patchCord31(faustSynth, 0, mixer3, 1);
AudioConnection          patchCord32(mixer5, 0, mixer8, 0);
AudioConnection          patchCord33(mixer9, 0, mixer8, 3);
AudioConnection          patchCord34(mixer6, 0, mixer8, 1);
AudioConnection          patchCord35(mixer7, 0, mixer8, 2);
AudioConnection          patchCord36(mixer10, 0, mixer12, 0);
AudioConnection          patchCord37(mixer11, 0, mixer12, 1);
AudioConnection          patchCord38(mixer1, 0, mixer2, 0);
AudioConnection          patchCord39(mixer2, 0, mixer3, 0);
AudioConnection          patchCord40(mixer12, 0, mixer3, 3);
AudioConnection          patchCord41(mixer8, 0, mixer3, 2);
AudioConnection          patchCord42(mixer3, 0, i2s1, 1);
AudioConnection          patchCord43(mixer3, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;

const int KEYBOARD_REPEAT_DELAY = 250; //délai entre première et deuxième entrée lorsqu'on reste appuyé (dépend du clavier)
const int REPEAT_DELAY_RANGE = 5; //tolérance
const int KEYBOARD_MIN_DELAY = 100; //délai minimal général
const int PERSISTENT_SYNTH_SUSTAIN = 500; //combien de temps maintenir une touche dans un synthé persistent

const String notesNamesEN[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
const String notesNamesFR[12] = {"Do", "Do#", "Ré", "Ré#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si"};
const char correspondingKeys[12] = {'q', 'z', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j'};
const char correspondingKeysGuitar[32] = {"a", "b" etc};
const bool conventionFrancaise = true;*

const char octaveUpKey = 'b';
const char octaveDownKey = 'v';

//synths
const int nombreSynths = 1;
String nomsSynths[nombreSynths] = {"guitar", "harpe"};
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
unsigned long timeLastKeyPressesGuitar[12];

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
