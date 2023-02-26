      ////////////////////////
      /// GUITARE KEYBOARD ///
      ////////////////////////

  // Son de guitare joué par les touches du clavier //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Keyboard.h>

// Fichier qui définie les différents accord joué à la guitare
#include "chords.h"

AudioSynthKarplusStrong  string1;
AudioSynthKarplusStrong  string2;
AudioSynthKarplusStrong  string3;
AudioSynthKarplusStrong  string4;
AudioSynthKarplusStrong  string5;
AudioSynthKarplusStrong  string6;
AudioMixer4              mixer1;
AudioMixer4              mixer2;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(string1, 0, mixer1, 0);
AudioConnection          patchCord2(string2, 0, mixer1, 1);
AudioConnection          patchCord3(string3, 0, mixer1, 2);
AudioConnection          patchCord4(string4, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, mixer2, 0);
AudioConnection          patchCord6(string5, 0, mixer2, 1);
AudioConnection          patchCord7(string6, 0, mixer2, 2);
AudioConnection          patchCord8(mixer2, 0, i2s1, 0);
AudioConnection          patchCord9(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

const int finger_delay = 5;
const int hand_delay = 220;

int chordnum=0;

void setup() {
  AudioMemory(15);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  mixer1.gain(0, 0.15);
  mixer1.gain(1, 0.15);
  mixer1.gain(2, 0.15);
  mixer1.gain(3, 0.15);
  mixer2.gain(1, 0.15);
  mixer2.gain(2, 0.15);
  delay(700);

  Serial.begin(9600); 
  while (!Serial) {}
  Keyboard.begin();
}

void strum_up(const float *chord, float velocity);
void strum_dn(const float *chord, float velocity);

void loop() 
{
  const float *chord;

  if (Serial.available()) 
  { 
    
    // Lire la touche tapé :
    char keyboardChar = Serial.read();
    Keyboard.write(keyboardChar); 
    
    // Faire des sons selon les touches :

    if (keyboardChar == 'a')
    {
          chord = Cmajor;
          Serial.println("Cmajor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 'q')
    {
          chord = Cmajor;
          Serial.println("Cmajor Down");
          strum_dn(chord, 1.0);
    }

    
    if (keyboardChar == 'z')
    {
          chord = Dmajor;
          Serial.println("Dmajor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 's')
    {
          chord = Dmajor;
          Serial.println("Dmajor Down");
          strum_dn(chord, 1.0);
    }

    if (keyboardChar == 'e')
    {
          chord = Emajor;
          Serial.println("Emajor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 'd')
    {
          chord = Emajor;
          Serial.println("Emajor Down");
          strum_dn(chord, 1.0);
    }

    if (keyboardChar == 'r')
    {
          chord = Fmajor;
          Serial.println("Fmajor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 'f')
    {
          chord = Fmajor;
          Serial.println("Fmajor Down");
          strum_dn(chord, 1.0);
    }
    
    if (keyboardChar == 't')
    {
          chord = Gmajor;
          Serial.println("Gmajor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 'g')
    {
          chord = Gmajor;
          Serial.println("Gmajor Down");
          strum_dn(chord, 1.0);
    }

    if (keyboardChar == 'y')
    {
          chord = Amajor;
          Serial.println("Amajor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 'h')
    {
          chord = Amajor;
          Serial.println("Amajor Down");
          strum_dn(chord, 1.0);
    }

    if (keyboardChar == 'u')
    {
          chord = Bmajor;
          Serial.println("Bmajor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 'j')
    {
          chord = Bmajor;
          Serial.println("Bmajor Down");
          strum_dn(chord, 1.0);
    }

    if (keyboardChar == 'i')
    {
          chord = Cminor;
          Serial.println("Cminor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 'k')
    {
          chord = Cminor;
          Serial.println("Cminor Down");
          strum_dn(chord, 1.0);
    }

    if (keyboardChar == 'o')
    {
          chord = Dminor;
          Serial.println("Dminor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 'l')
    {
          chord = Dminor;
          Serial.println("Dminor Down");
          strum_dn(chord, 1.0);
    }

    if (keyboardChar == 'p')
    {
          chord = Eminor;
          Serial.println("Eminor Up");
          strum_up(chord, 1.0);
    }
    if (keyboardChar == 'm')
    {
          chord = Eminor;
          Serial.println("Eminor Down");
          strum_dn(chord, 1.0);
    }

     
  }

  
}

// Fonction qui fait le son de guitard grattage vers le haut avec accod en paramètre
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

// Fonction qui fait le son de guitard grattage vers le bas avec accod en paramètre
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
