#include <Audio.h>
#include "pitch_shift2.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Keyboard.h>
pitch_shift2 pitchWav;
AudioPlaySdWav           playSdWav1;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(playSdWav1,0,pitchWav,0);
AudioConnection patchCord1(playSdWav1,1,pitchWav,1);
AudioConnection patchCord2(pitchWav,0,out,0);
AudioConnection patchCord3(pitchWav,1,out,1);


#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

AudioControlSGTL5000     sgtl5000_1;
void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playSdWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(25);

  // Simply wait for the file to finish playing.
  
  
}

void setup() {
   Serial.begin(9600);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  audioShield.enable();
  audioShield.volume(0.3);
  audioShield.inputSelect(SDCARD_CS_PIN);
  //pitchWav.setParamValue("w",512);
  //pitchWav.setParamValue("x",256);
  //pitchWav.setParamValue("s",4);
  Keyboard.begin();
}

void loop() {
  /*
  playFile("Woof440_8bit.WAV");
  //pitchWav.setParamValue("s",1);
   delay(1000);
  playFile("Beach440_8bit.WAV");
   delay(1000);
  playFile("Bam440_8bit.WAV");
   delay(1000);
  playFile("Xylo440_8bit.WAV");
  pitchWav.setParamValue("s",1);
  delay(1000);
  pitchWav.setParamValue("s",6);
  delay(1000);
 
  
  //pitchWav.setParamValue("s",8);
  */
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

        playFile("Meow_new.WAV");
      //  pitchWav.setParamValue("notes",6);
    }
    if (keyboardChar == 'f')
    {
        
        playFile("Meow_new.WAV");
         pitchWav.setParamValue("notes",8);
    }
    if (keyboardChar == 'g')
    {
      
        playFile("Woof440_8bit_mono.WAV");
        pitchWav.setParamValue("notes",4);
    }
    if (keyboardChar == 'h')
    {
        
        playFile("Woof440_8bit_mono.WAV");
        pitchWav.setParamValue("notes",6);
    }
    if (keyboardChar == 'i')
    {
        pitchWav.setParamValue("s",6);
        playFile("Meow_new.WAV");
    }

  }

}
