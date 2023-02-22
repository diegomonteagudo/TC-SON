
#include <Keyboard.h> 
#include <Audio.h>
#include <Wire.h>
#include "MyDsp.h"

// Instance myDsp pour faire du son
MyDsp myDsp;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,0,out,1);


void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.5);
  
  Serial.begin(9600); 
  while (!Serial) {
  }
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
        myDsp.setFreq(100);
    }
    if (keyboardChar == 'd')
    {
        myDsp.setFreq(150);
    }
    if (keyboardChar == 'r')
    {
        myDsp.setFreq(200);
    }
    if (keyboardChar == 'f')
    {
        myDsp.setFreq(250);
    }
    if (keyboardChar == 't')
    {
        myDsp.setFreq(300);
    }
    if (keyboardChar == 'g')
    {
        myDsp.setFreq(350);
    }
    if (keyboardChar == 'y')
    {
        myDsp.setFreq(400);
    }
    if (keyboardChar == 'h')
    {
        myDsp.setFreq(450);
    }
    if (keyboardChar == 'u')
    {
        myDsp.setFreq(500);
    }
    if (keyboardChar == 'j')
    {
        myDsp.setFreq(550);
    }
    if (keyboardChar == 'i')
    {
        myDsp.setFreq(600);
    }
    if (keyboardChar == 'k')
    {
        myDsp.setFreq(650);
    }
    if (keyboardChar == 'o')
    {
        myDsp.setFreq(700);
    }
    if (keyboardChar == 'l')
    {
        myDsp.setFreq(750);
    }
    if (keyboardChar == 'p')
    {
        myDsp.setFreq(800);
    }
    if (keyboardChar == 'm')
    {
        myDsp.setFreq(850);
    }

    
  }
}
