import("stdfaust.lib");

// djembeModelCustom(freq) = _ <: par(i,nModes,pm.modeFilter(modeFreqs(i),modeT60s(i),modeGains(i))) :> /(nModes)
// with{
//     nModes = 10;
//     theta = 0; // angle
//     modeFreqs(i) = freq + 200*i;
//     modeT60s(i) = (nModes-i)*0.03;
//     modeGains(i) = cos((i+1)*theta)/float(i+1)*(1/(i+1));
// };

// djembe(freq,strikePosition,strikeSharpness,gain,trigger) =
// pm.strike(strikePosition,strikeSharpness,gain,trigger) : djembeModelCustom(freq);

oscsin(freq) = rdtable(tablesize, os.sinwaveform(tablesize), int(os.phasor(tablesize,freq)))
with {
    tablesize = 256;
};

frequence0 = hslider("frequence0",261.63,20,6000,0.1);
frequence1 = hslider("frequence1",277.18,20,6000,0.1);
frequence2 = hslider("frequence2",293.66,20,6000,0.1);
frequence3 = hslider("frequence3",311.13,20,6000,0.1);
frequence4 = hslider("frequence4",329.63,20,6000,0.1);
frequence5 = hslider("frequence5",349.23,20,6000,0.1);
frequence6 = hslider("frequence6",369.99,20,6000,0.1);
frequence7 = hslider("frequence7",392.00,20,6000,0.1);
frequence8 = hslider("frequence8",415.30,20,6000,0.1);
frequence9 = hslider("frequence9",440.00,20,6000,0.1);
frequence10 = hslider("frequence10",466.16,20,6000,0.1);
frequence11 = hslider("frequence11",493.88,20,6000,0.1);

gate0 = button("gate0");
gate1 = button("gate1");
gate2 = button("gate2");
gate3 = button("gate3");
gate4 = button("gate4");
gate5 = button("gate5");
gate6 = button("gate6");
gate7 = button("gate7");
gate8 = button("gate8");
gate9 = button("gate9");
gate10 = button("gate10");
gate11 = button("gate11");


gain = hslider("gain",1,0,1,0.1);

harpeStatus = hslider("harpe",1,0,1,1);
res = 2;
harpeIns = sy.combString(frequence0,res,gate0),sy.combString(frequence1,res,gate1),sy.combString(frequence2,res,gate2),sy.combString(frequence3,res,gate3),sy.combString(frequence4,res,gate4),sy.combString(frequence5,res,gate5),sy.combString(frequence6,res,gate6),sy.combString(frequence7,res,gate7),sy.combString(frequence8,res,gate8),sy.combString(frequence9,res,gate9),sy.combString(frequence10,res,gate10),sy.combString(frequence11,res,gate11) :> *(harpeStatus);


// djembeStatus = hslider("djembe",0,0,1,1);
// djembeIns = djembe(frequence0, 0.3, 1, 1, gate0),djembe(frequence1, 0.3, 1, 1, gate1),djembe(frequence2, 0.3, 1, 1, gate2),djembe(frequence3, 0.3, 1, 1, gate3),djembe(frequence4, 0.3, 1, 1, gate4),djembe(frequence5, 0.3, 1, 1, gate5),djembe(frequence6, 0.3, 1, 1, gate6),djembe(frequence7, 0.3, 1, 1, gate7),djembe(frequence8, 0.3, 1, 1, gate8),djembe(frequence9, 0.3, 1, 1, gate9),djembe(frequence10, 0.3, 1, 1, gate10),djembe(frequence11, 0.3, 1, 1, gate11) :> *(djembeStatus);

sineStatus = hslider("sine",0,0,1,1);
sineIns = gate0*oscsin(frequence0),gate1*oscsin(frequence1),gate2*oscsin(frequence2),gate3*oscsin(frequence3),gate4*oscsin(frequence4),gate5*oscsin(frequence5),gate6*oscsin(frequence6),gate7*oscsin(frequence7),gate8*oscsin(frequence8),gate9*oscsin(frequence9),gate10*oscsin(frequence10),gate11*oscsin(frequence11) :> *(sineStatus);

process = (harpeIns,sineIns) :> *(gain);

