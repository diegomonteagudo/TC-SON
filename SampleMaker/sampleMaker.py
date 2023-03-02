import librosa
import os
import numpy as np
import shutil
import soundfile

MIN_OCTAVE = 2
MAX_OCTAVE = 6
FACTEUR_ARBITRAIRE_UP = -0.05
FACTEUR_ARBITRAIRE_DOWN = -0.005

def toMidi(octave, distance):
    return (octave+1)*12+distance

#très arbitraire, sert à compenser la perte/gain de volume après pitch shifting. risque d'overdrive !!!
def compensation_volume(steps):
    if steps == 0:
        return 1.0
    if steps < 0:
        return (FACTEUR_ARBITRAIRE_UP*steps + 1)
    if steps > 0:
        return (FACTEUR_ARBITRAIRE_DOWN*steps + 1)

print("\n----------------------------------")
print("|   Fast sample maker for DSPS   |")
print("----------------------------------\n\n\n")
print("Mettre 5 Do OU 1 note aléatoire source dans Source au format InstrumentName_MidiNote.wav")
print("Attention source en Mono 16 bits PCM et sample rate ??? kHz")
print("Attention nombre midi doit être de 36 à 95\n\n")

inputs = sorted(os.listdir("./Source"))

if inputs is None :
    print("ERREUR : aucun fichier dans Source")

try:
    analyse_nom = inputs[0].split("_")
except Exception as e:
    print("Erreur split _ :",e)

instrument_name = analyse_nom[0]

os.mkdir("./"+instrument_name)

#mode à 5 entrées en Do de l'octave 2 à 6
if len(inputs) == 5:
    input("Fichiers source trouvés. Mode 5 entrées Do. Appuyer sur une touche pour commencer \n")
    
    for i in range(MIN_OCTAVE,MAX_OCTAVE+1):
        fileDoReference = "./Source/"+inputs[i-MIN_OCTAVE]
        audio, sampleRate = librosa.load(fileDoReference, sr=44100, mono=True)
        print("Source : "+fileDoReference+", sample rate : "+str(sampleRate))

        for j in range(0,12):
            outputFileName = "./"+instrument_name+"/"+instrument_name+"_"+str(toMidi(i, j))+".wav"
            #si fichier d'origine = juste le copier sans pitch shifting
            if j == 0:
                shutil.copyfile(fileDoReference,outputFileName)
            else:
                shifted_audio = librosa.effects.pitch_shift(audio, sr=sampleRate, n_steps=j)
                soundfile.write(outputFileName, shifted_audio, sampleRate, 'PCM_16')
            print(outputFileName+" done !")

#mode à 1 seule entrée
elif len(inputs) == 1:
    noteReference = int((analyse_nom[1])[:2])
    fileReferenceName = "./Source/"+inputs[0]
    input("Fichiers source trouvés. Mode 1 entrée (ref midi = "+str(noteReference)+".\n Appuyer sur une touche pour commencer \n")
    
    noteMin = toMidi(MIN_OCTAVE,0)
    noteMax = toMidi(MAX_OCTAVE,11)
    audio, sampleRate = librosa.load(fileReferenceName, sr=44100, mono=True)
    print("Source : "+fileReferenceName+", sample rate : "+str(sampleRate))

    for i in range(noteMin, noteMax+1):
        outputFileName = "./"+instrument_name+"/"+instrument_name+"_"+str(i)+".wav"
        steps = i-noteReference
        compensation = compensation_volume(steps)
        #si fichier d'origine = juste le copier sans pitch shifting
        if i == noteReference:
            shutil.copyfile(fileReferenceName,outputFileName)
        else:
            shifted_audio = librosa.effects.pitch_shift(audio, sr=sampleRate, n_steps=steps)
            shifted_audio *= compensation
            soundfile.write(outputFileName, shifted_audio, sampleRate, 'PCM_16')
        print(outputFileName+" done! Facteur volume : "+str(compensation))

else:
    print("Erreur dans le nombre de fichiers en entrée : "+str(len(inputs)))

print("Tout fini !")