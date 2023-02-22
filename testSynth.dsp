import("stdfaust.lib");

res = 2;

frequence = hslider("frequence",262,20,10000,0.1);

gate = button("gate");

gain = hslider("gain",1,0,1,0.1);

process = gain*sy.combString(frequence,res,gate);
