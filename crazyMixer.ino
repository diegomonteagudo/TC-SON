#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
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
AudioMixer4              faustSynth;         //xy=357.3408889770508,439.8408851623535
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
AudioControlSGTL5000     3eb6dd83.30c792; //xy=993.0909576416016,301.0909080505371
AudioControlSGTL5000     58070727.0ad628; //xy=999.0908355712891,255.09090995788574
// GUItool: end automatically generated code
