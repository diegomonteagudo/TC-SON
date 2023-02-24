import("stdfaust.lib");

res = 2;

frequence0 = hslider("frequence0",261.63,20,6000,0.1);
frequence1 = hslider("frequence1",277.18,20,6000,0.1);
frequence2 = hslider("frequence2",293.66,20,6000,0.1);
frequence3 = hslider("frequence3",311.13,20,6000,0.1);
frequence4 = hslider("frequence4",329.63,20,6000,0.1);
frequence5 = hslider("frequence5",349.23,20,6000,0.1);
frequence6 = hslider("frequence6",369.99,20,6000,0.1);
frequence7 = hslider("frequence7",392.00,20,6000,0.1);
frequence8 = hslider("frequence8",440,20,6000,0.1);
frequence9 = hslider("frequence9",466.16,20,6000,0.1);
frequence10 = hslider("frequence10",493.88,20,6000,0.1);
frequence11 = hslider("frequence11",523.25,20,6000,0.1);

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

process = 
sy.combString(frequence0,res,gate0),sy.combString(frequence1,res,gate1),sy.combString(frequence2,res,gate2),sy.combString(frequence3,res,gate3),sy.combString(frequence4,res,gate4),sy.combString(frequence5,res,gate5),sy.combString(frequence6,res,gate6),sy.combString(frequence7,res,gate7),sy.combString(frequence8,res,gate8),sy.combString(frequence9,res,gate9),sy.combString(frequence10,res,gate10),sy.combString(frequence11,res,gate11) :> /(12)*gain;
