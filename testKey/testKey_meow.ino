
#include <Keyboard.h> 
#include <Audio.h>
#include <Wire.h>
#include "MyDsp.h"
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14
// Instance myDsp pour faire du son


AudioPlaySdWav           playSdWav1;     
AudioEffectReverb        reverb1;        
AudioEffectWaveshaper    waveshape1;     
AudioOutputI2S           i2s1;           
AudioConnection          patchCord1(playSdWav1, 0, waveshape1, 0);
AudioConnection          patchCord2(playSdWav1, 1, reverb1, 0);
AudioConnection          patchCord3(reverb1, 0, i2s1, 1);
AudioConnection          patchCord4(waveshape1, 0, i2s1, 0);

AudioControlSGTL5000     sgtl5000_1;
void setup() {

 
  
  Serial.begin(9600); 
  while (!Serial) {
  }
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))
  ) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  else Serial.println("OK");

  Keyboard.begin();
}

void loop() {
  if (Serial.available()) 
  { 
    // Lire la touche tapé
    char keyboardChar = Serial.read();
    Keyboard.write(keyboardChar); 

    // Afficher la touche tapé
    Serial.println(keyboardChar); 
    
    // Faire des son selon la touche
    if (keyboardChar == 'e')
    {
        playSdWav1.play("SDTEST1.WAV");
    }

  }
}
