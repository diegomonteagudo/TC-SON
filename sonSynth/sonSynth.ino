#include <Keyboard.h> 
#include <Audio.h>
#include <Wire.h>
#include "FaustSynth.h"
#include <string.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "FaustSynth.h"
#include "chords.h"

#include <string.h>

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

FaustSynth faustSynth;
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

const int KEYBOARD_REPEAT_DELAY = 500; //d??lai entre premi??re et deuxi??me entr??e lorsqu'on reste appuy?? (d??pend du clavier)
const int REPEAT_DELAY_RANGE = 5; //tol??rance
const int KEYBOARD_MIN_DELAY = 100; //d??lai minimal g??n??ral
const int PERSISTENT_SYNTH_SUSTAIN = 500; //combien de temps maintenir une touche dans un synth?? persistent
const int DISPLAY_PRESSED_KEY = false;

const String notesNamesEN[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
const String notesNamesFR[12] = {"Do", "Do#", "R??", "R??#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si"};
const char correspondingKeys[12] = {'a', 'w', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j'};
const bool conventionFrancaise = false;

const char octaveUpKey = 'b';
const char octaveDownKey = 'v';

//synths
const int nombreSynths = 3;
String nomsSynths[nombreSynths] = {"guitare", "harpe", "sine"};
bool synthPersistent[nombreSynths] = {false, false, true}; //dans le m??me ordre que nombreSynths, dire si on peut rester appuy?? pour maintenir la note
bool toucheAllumee[12];

//samples
const int nombreSamples = 2;
const String nomsSamples[nombreSamples] = {"Piano", "Voice"};

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


int octave = 4;
String typeSelectedInstrument = "sample";
int selectedSynth = 0;
int selectedSample = 0;

//changer d'octave en restant dans les bornes
void changeOctave(int changement){
  if(changement == 1 && octave < 6){
    octave += 1;
    Serial.println(" /\\ +1 octave ("+String(octave)+") /\\ ");
  } else if (changement == -1 && octave > 2){
    octave -= 1;
    Serial.println(" \\/ -1 octave ("+String(octave)+") \\/ ");
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

//dire si un appui clavier doit effectuer une action ou ??tre ignor??
bool conditionClavier(int tempsActuel, int tempsDernierAppui){
  int diffTemps = tempsActuel - tempsDernierAppui;
  bool conditionDelaiMin = (diffTemps> KEYBOARD_MIN_DELAY); //d??lai minimal entre deux inputs
  bool conditionPremierDelai = abs(diffTemps - KEYBOARD_REPEAT_DELAY) > REPEAT_DELAY_RANGE; //d??lai interdit (premier d??lai en restant appuy??)
  return conditionDelaiMin && conditionPremierDelai;
}

//dire si l'instrument s??lectionn?? peut maintenir ses notes dans le temps (persistent)
bool selectedIsPersistent(){
  return (typeSelectedInstrument == "synth" && synthPersistent[selectedSynth]);
}

//pour l'instant communication Faust : pour l'instant 1 seul instrument, il faudra adapter cette fonction
void jouerNote(int octave, int distanceDo){
  int note = toMidi(octave, distanceDo);
  Serial.print("\n");
  Serial.print("Note jou??e : ");
  Serial.print(midiToName(note));
  Serial.print("\n");
  
  if((typeSelectedInstrument == "synth") && (selectedSynth != 0)){
    String variableFaustGate = "gate" + String(distanceDo);
    String variableFaustFreq = "frequence" + String(distanceDo);
    
    faustSynth.setParamValue(Stos(variableFaustGate),0);
    delay(10);
    faustSynth.setParamValue(Stos(variableFaustFreq),mtof(note));
    faustSynth.setParamValue(Stos(variableFaustGate),1);
    
  } else if (typeSelectedInstrument == "sample") {
    String nameFileToPlay = "SON/"+nomsSamples[selectedSample]+"/"+nomsSamples[selectedSample] + "_" + String(note)+".wav";
    switch(distanceDo) {
      case 0:
        playSdWav1.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 1:
        playSdWav2.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 2:
        playSdWav3.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 3:
        playSdWav4.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 4:
        playSdWav5.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 5:
        playSdWav6.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 6:
        playSdWav7.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 7:
        playSdWav8.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 8:
        playSdWav9.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 9:
        playSdWav10.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 10:
        playSdWav11.play(StoConstCharPointer(nameFileToPlay));
        break;
      case 11:
        playSdWav12.play(StoConstCharPointer(nameFileToPlay));
        break;
      default:
        Serial.println("Erreur switch case jouerNote");
        break;
      
    }
    
  }
}


//cas des synth??s persistents : ??teindre la note lorsqu'on appuie plus
void finirNote(int octave, int distanceDo){
  int note = toMidi(octave, distanceDo);
  //Serial.print("\n");
  //Serial.print("Fin de la note : ");
  //Serial.print(midiToName(note));

  String variableFaustGate = "gate" + String(distanceDo);
  faustSynth.setParamValue(Stos(variableFaustGate),0);
}



//void playFile(const char *filename)
//{
//  Serial.print("Sample choisi: ");
//  Serial.println(filename);
//
//  // Start playing the file.  This sketch continues to
//  // run while the file plays.
//  playSdWav1.play(filename);
//
//  // A brief delay for the library read WAV info
//  delay(25);
//
//  // Simply wait for the file to finish playing.
//  
//  
//}

// --------------------------------------
         // ** GUITARE ** 

const char correspondingKeysGuitar[20] = {'q', 'a', 'w', 's', 'e', 'd', 'r', 'f', 't', 'g', 'y', 'h','u','j', 'i', 'k', 'o', 'l','p',';'};
const float* chords[10] = { Cmajor, Dmajor, Emajor, Fmajor, Gmajor, Amajor, Bmajor, Cminor, Dminor, Eminor };
String chordsName[10] = {"C major", "D major", "E major", "F major", "G major", "A major", "B major", "C minor", "D minor", "E minor"};
unsigned long timeLastGuitarKeyPresses[20];

const int finger_delay = 5;
const int hand_delay = 220;

void strum_up(const float *chord, float velocity);
void strum_dn(const float *chord, float velocity);

// Fonction qui fait le son de guitard grattage vers le haut avec accord en param??tre
void strum_up(const float *chord, float velocity)
{
  if (chord[0] > 20.0) string1.noteOn(chord[0], velocity);
  delay(finger_delay);
  if (chord[1] > 20.0) string2.noteOn(chord[1], velocity);
  delay(finger_delay);
  if (chord[2] > 20.0) string3.noteOn(chord[2], velocity);
  delay(finger_delay);
  if (chord[3] > 20.0) string4.noteOn(chord[3], velocity);
  delay(finger_delay);
  if (chord[4] > 20.0) string5.noteOn(chord[4], velocity);
  delay(finger_delay);
  if (chord[5] > 20.0) string6.noteOn(chord[5], velocity);
  delay(finger_delay);
}

// Fonction qui fait le son de guitard grattage vers le bas avec accod en param??tre
void strum_dn(const float *chord, float velocity)
{
  if (chord[5] > 20.0) string1.noteOn(chord[5], velocity);
  delay(finger_delay);
  if (chord[4] > 20.0) string2.noteOn(chord[4], velocity);
  delay(finger_delay);
  if (chord[3] > 20.0) string3.noteOn(chord[3], velocity);
  delay(finger_delay);
  if (chord[2] > 20.0) string4.noteOn(chord[2], velocity);
  delay(finger_delay);
  if (chord[1] > 20.0) string5.noteOn(chord[1], velocity);
  delay(finger_delay);
  if (chord[0] > 20.0) string6.noteOn(chord[0], velocity);
  delay(finger_delay);
}

// --------------------------------------

void eteindreFaustGates(){
  for(int i = 0; i<12; i++){
    String variableFaustGate = "gate" + String(i);
    faustSynth.setParamValue(Stos(variableFaustGate),0);
    if(selectedIsPersistent()){
      toucheAllumee[i] = false;
    }
  }
}

//changer les instruments (en fonction du bouton appuy??)
//agit directement sur les variables globales
void changeInstrument(String typeNewInstrument){

  //instrument cible est un synth
  if(typeNewInstrument == "synth"){
    //instrument actuel est un synth (=> synth suivant)
    if(typeSelectedInstrument == "synth"){
      if(selectedSynth == nombreSynths - 1){
        selectedSynth = 0;
      } else {
        selectedSynth += 1;
      }
      
      //changer aussi dans faust (sauf si guitare)
      eteindreFaustGates();
      if(selectedSynth == 0){
        faustSynth.setParamValue(Stos(nomsSynths[nombreSynths-1]),0);
      } else if(selectedSynth == 1){
        faustSynth.setParamValue(Stos(nomsSynths[selectedSynth]),1);
      } else {
        faustSynth.setParamValue(Stos(nomsSynths[selectedSynth-1]),0);
        faustSynth.setParamValue(Stos(nomsSynths[selectedSynth]),1);
      }
    
    //instrument actuel est un sample (=> simplement passer aux synths)
    } else if(typeSelectedInstrument == "sample") {
      typeSelectedInstrument = "synth";
      if(selectedSynth > 0){ //si pas guitare activer faust instrument
        faustSynth.setParamValue(Stos(nomsSynths[selectedSynth]),1);
      }
    }
    Serial.print("\n -------------------------------------------\n");
    Serial.print("Instrument s??lectionn?? : " + nomsSynths[selectedSynth] + " (son synth??tique n??" + String(selectedSynth)+")");
    Serial.print("\n -------------------------------------------\n");
    
  }


  //instrument cible est un sample
  if(typeNewInstrument == "sample"){
    //instrument actuel est un synth (=> simplement passer aux samples)
    if(typeSelectedInstrument == "synth"){
      typeSelectedInstrument = "sample";
      if(selectedSynth > 0){ //si pas guitare activer faust instrument
        faustSynth.setParamValue(Stos(nomsSynths[selectedSynth]),0);
      }
    
    //instrument actuel est un sample (=> sample suivant)
    } else if(typeSelectedInstrument == "sample") {
      if(selectedSample == nombreSamples - 1){
        selectedSample = 0;
      } else {
        selectedSample += 1;
      }
    }
    Serial.print("\n -------------------------------------------\n");
    Serial.print("Instrument s??lectionn?? : " + nomsSamples[selectedSample] + " (sample n??" + String(selectedSample)+")");
    Serial.print("\n -------------------------------------------\n");
  }


  //jouer une note pour s'y retrouver en parcourant les instruments
  if(typeSelectedInstrument == "synth" && selectedSynth == 0){
    strum_up(chords[5], 1.0);
  } else {
    jouerNote(4,9);
    
    //malpropre
    if(selectedIsPersistent()){
      delay(500);
      finirNote(4,9);
    }
  }

  
  
}






int loopNumber = 0;

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  //pinMode(2, INPUT);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.1);
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
    timeLastKeyPresses[i] = 0;
    toucheAllumee[i] = false; //cas des synth??s persistents
  }
  // Guitar
  for(int i=0;i<20;i++){
    timeLastGuitarKeyPresses[i] = 0;
  }
}




void loop() {
  //Serial.print("\n D??but loop :");
  //Serial.println(loopNumber);
  unsigned long currentTime = millis(); //inexact plus on avance dans une it??ration mais pas grave
  
  bool currentSynthButtonState = digitalRead(0);
  bool currentSampleButtonState = digitalRead(1);

  if(!(typeSelectedInstrument == "synth" && selectedSynth == 0)){
    //gestion notes de musique : entr??es clavier
    if (Serial.available()){
      char keyboardChar = Serial.read();
      Keyboard.write(keyboardChar);
      if(keyboardChar != '\n'){
        if(DISPLAY_PRESSED_KEY){
          Serial.println("\n");
          Serial.println("Touche appuy??e : "+String(keyboardChar));
        }
    
        int iterateur = 0;
        bool trouve = false;
        //touches de notes
        while((trouve == false) && (iterateur < 12)){
          if (keyboardChar == correspondingKeys[iterateur]){
            if(conditionClavier(currentTime, timeLastKeyPresses[iterateur])){ //rien ne change dans le cas d'un synth qui se maintient dans le temps
              jouerNote(octave, iterateur);
            }
            timeLastKeyPresses[iterateur] = currentTime;
            if(selectedIsPersistent()){
              toucheAllumee[iterateur] = true;
            }
            trouve = true;
          }
          iterateur += 1;
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
          } else {
            Serial.print("\n");
            //Serial.print("test aucune correspondance touche (peut-??tre retour chariot)");
          }
        }
      }
    }
    
    
    
     //gestion notes de musiques : ??teindre les touches n'??tant plus appuy??es (dans le cas des synth??s persistants)
     if (selectedIsPersistent()){
        for(int i = 0; i<12; i++){
          if(toucheAllumee[i] == true && (currentTime - timeLastKeyPresses[i]) > PERSISTENT_SYNTH_SUSTAIN){
            finirNote(octave, i);
            toucheAllumee[i] = false;
          }
        }
      }

  } else {
     //gestion notes de musique : entr??es clavier
    if (Serial.available()){
      char keyboardChar = Serial.read();
      Keyboard.write(keyboardChar);
      if(keyboardChar != '\n'){
        if(DISPLAY_PRESSED_KEY){
          Serial.println("Touche appuy??e : "+String(keyboardChar));
        }
    
        int iterateur = 0;
        bool trouve = false;
    
        // Jouer de la Guitare
        while((trouve == false) && (iterateur < 20)){
          if (keyboardChar == correspondingKeysGuitar[iterateur]){
            if(conditionClavier(currentTime, timeLastGuitarKeyPresses[iterateur])){ //rien ne change dans le cas d'un synth qui se maintient dans le temps

                if(iterateur %2 ==0)
                {
                  strum_up(chords[iterateur/2], 1.0);
                  Serial.print("\n");
                  Serial.print("Accord jou?? : "+chordsName[iterateur/2]+"(up) \n");
                }
                else
                {
                  strum_dn(chords[(iterateur+1)/2], 1.0);
                  Serial.print("\n");
                  Serial.print("Accord jou?? : "+chordsName[iterateur/2]+"(down) \n");
                }

              
            }
            timeLastGuitarKeyPresses[iterateur] = currentTime;
            trouve = true;
          }
          iterateur += 1;
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

      //faire l'action quand le bouton passe de assur??ment libre ?? assur??ment appuy??
      if (synthButtonDefinitelyPressed) {
          changeInstrument("synth");
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

      //faire l'action quand le bouton passe de assur??ment libre ?? assur??ment appuy??
      if (sampleButtonDefinitelyPressed) {
          changeInstrument("sample");
      }
    }
  }



  //gestion du volume
  if (currentTime - timeLastPotentionReading > 200) {
    oldGain = currentGain;
    currentGain = analogRead(A0) / 1023.0;
    if (abs(oldGain - currentGain) > 0.03) {
      sgtl5000_1.volume(currentGain*0.1);
      Serial.print("\n");
      Serial.print("New gain :");
      Serial.print(currentGain);
    }
    timeLastPotentionReading = currentTime;
  }



  lastSynthButtonState = currentSynthButtonState;
  lastSampleButtonState = currentSampleButtonState;
  loopNumber += 1;

}
