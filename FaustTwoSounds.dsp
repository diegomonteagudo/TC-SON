import("stdfaust.lib");

res = 2;

frequence1 = hslider("frequence1",262,20,6000,0.1);
frequence2 = hslider("frequence2",440,20,6000,0.1);

gate1 = button("gate1");
gate2 = button("gate2");

gain = hslider("gain",1,0,1,0.1);

process = sy.combString(frequence1,res,gate1),sy.combString(frequence2,res,gate2) :> /(2)*gain;
