# -*- coding: utf-8 -*-
"""
Skript for automate feeding of the algorithms and analyzing their data
"""

import Points
import subprocess
import matplotlib.pyplot as plt
import os
import pandas as pd
import time

from PIL import Image


def main():
    
    # Parameter (Später noch über schleifen)
    maxCluster = 30
    numOfSamples = 15
    alg = "r"
    
    algPathAdd = "Gonzalez"
    if(alg == "r"):
        algPathAdd = "RedClustering"
    if(alg == "f"):
        algPathAdd = "FastClustering"
        
    pictureFolder = "../Data/OutputData/Pictures/{algPathAdd}Test"
    
    # # # Binary Kompilieren
    compileBinary()

    
    # # # Algorithmus ausführen
    timeBank = do_algorithm("bank", numOfSamples=numOfSamples, maxCluster=maxCluster)
    timeCensus = do_algorithm("census", numOfSamples=numOfSamples, maxCluster=maxCluster)
    timeDiabetes = do_algorithm("diabetes", numOfSamples=numOfSamples, maxCluster=maxCluster)
 
    timestamps = [timeBank, timeCensus, timeDiabetes]
    
    analyze_times(timestamps, pictureFolder, ["bank", "census", "diabetes"])

    # ====== Verarbeitung Bank ====== #
    do_analysis_of_sampleset("bank", pictureFolder, 
                             numOfSamples=numOfSamples, maxCluster=maxCluster)
    # ====== Verarbeitung Zensus ====== #
    do_analysis_of_sampleset("census", pictureFolder, 
                             numOfSamples=numOfSamples, maxCluster=maxCluster)
    # ====== Verarbeitung Diabetes ====== #
    do_analysis_of_sampleset("diabetes", pictureFolder, 
                             numOfSamples=numOfSamples, maxCluster=maxCluster)
    
    
    # ====== Große Bilder zusammensetzen ====== #
    clue_pictures_together(["bank", "census", "diabetes"], pictureFolder, maxCluster=maxCluster)    

    return

# # # Algorithmus sukzessive auf den einzelnen Sampels ausführen und abspeichern # # #
def do_algorithm(samplename, numOfSamples = 20, maxCluster = 20):
    algoTimer = []
    for i in range(0, numOfSamples):
        # # Bankdaten
        # Pfade algorithmisch zusammensetzen
        inputfile = f"Data/Subsamples/{samplename}/{samplename}Sample-{i}.csv"
        outputfolder = f"Data/OutputData/AutoanalyzerTest/{samplename}/Sample{i}/"
        outputfile = f"{samplename}{i}"
        # Shellcommand zusammensetzen
        command = f"cd .. && ./AlgFeeder.sh -i {inputfile} -o {outputfolder} -n {outputfile} -c {maxCluster}"
        # Prozess erzeugen
        process = bash_command(command)
        # Zeitmessung Starten
        startTime = time.process_time_ns();
        # Prozess starten
        process.communicate()
        # Zeitmessung stoppen
        algoTimer.append(time.process_time_ns() - startTime)
        print(f"Cluster made for Sample: {inputfile}")
    
    return algoTimer

# # # Analysiert die geclusterten Daten und gibt ein Diagramm dazu aus # # #
def do_analysis_of_sampleset(samplename, pictureFolder, numOfSamples = 20, maxCluster = 20):
    print(f"\n# --------- Working with {samplename} Data --------- # \n")
    
    # # # Einlesen der neuen Daten
    listOfRadiiLists = []
    for i in range(0, numOfSamples): 
        # Pfade algorithmisch zusammensetzen
        #inputfile = f"Data/Subsamples/{bank}/{bank}Sample-{i}.csv"
        outputfolder = f"Data/OutputData/AutoanalyzerTest/{samplename}/Sample{i}/"
        outputfile = f"{samplename}{i}"
        # Maximale Radien für jede Clustergröße holen
        radiiList = get_radii_of_subsample(outputfolder, outputfile, maxCluster)
        # radienverlauf hinszufügen
        listOfRadiiLists.append(radiiList)
        
    
    
    # # # Analyse der Daten
    # Radien in Pandas-Dataframe für weiterverarbeitung packen
    dfRadius = pd.DataFrame(listOfRadiiLists)#.transpose()
    #print(dfRadius.head())
    
    # erzeugen eines Analyse-Dataframes
    dfImportantValues = pd.DataFrame()
    # Index (Clustersize)
    dfImportantValues["clustersize"] = list(range(1, maxCluster+1))
    dfImportantValues["mean"] = dfRadius.mean()
    dfImportantValues["maxValue"] = dfRadius.max()
    dfImportantValues["minValue"] = dfRadius.min()
    dfImportantValues["upperQuantile"] = dfRadius.quantile(0.75)
    dfImportantValues["lowerQuantile"] = dfRadius.quantile(0.25)
    
    print(dfImportantValues.head(10))
    
    # Ordner erstellen, falls nicht vorhanden
    os.makedirs(pictureFolder, exist_ok=True) 
    print_radii(dfImportantValues, f"{pictureFolder}Unfair{samplename}(Cluster-{maxCluster}).jpg", f"{samplename} k-center")

    return






# Kapselung des Bashcommands, der das mit der Shell regelt
def bash_command(cmd, ignoreStdout = True):
    # stdout wird weggeworfen
    if ignoreStdout:    
        return subprocess.Popen(cmd, shell=True, executable='/bin/bash', stdout=subprocess.DEVNULL)
    # Stdout vom Skript in Pythonkonsole
    return subprocess.Popen(cmd, shell=True, executable='/bin/bash')



def print_radii(dfRadius, picturePath, title):
    # Wie weit ist der Abstand der x-Beschriftung
    intervalls = max(int(len(dfRadius)/10),1)

    
    fig, ax = plt.subplots(figsize=(9,6))
    # Einfach eine Linie plotten wenn radii einfache Liste
    #ax.plot(list(range(1, len(radii)+1)), radii, # range in x Values um auf 1 zu shiften
    #        color = "brown", label = "Unfair")
    ax.plot(dfRadius["clustersize"], dfRadius["mean"],
            color = "brown", label = "Unfair (mean)")
    ax.plot(dfRadius["clustersize"], dfRadius[["maxValue", "minValue"]],
            color = "orange", linestyle = "dashed", alpha = 0.5, label = "Unfair (max/min)")
    #ax.boxplot(dfRadius, meanline = True)
    #ax.boxplot(dfRadius[["mean", "maxValue", "minValue","upperQuantile", "lowerQuantile"]])
    ax.set_xticks(list(range(1, len(dfRadius) + 1, intervalls)))
    ax.set_title(title)
    ax.set_xlabel("Cluster")
    ax.set_ylabel("max Radius")
    ax.legend()
    plt.savefig(picturePath)
    plt.show()
    

def get_radii_of_subsample(outputfolder, outputfile, maxCluster):
    # Liste für die berechneten Maximalen Radien
    radiiList = []
    
    # Radien aus den Files holen
    for i in range(1, maxCluster + 1):
        # Dateipfad generieren
        filename = f"../{outputfolder}/Clusterdata{outputfile}Cluster{i}.csv"
        # nur die Radien auslesen mit Hilfsmethode
        _, maxRadius = Points.read_points(filename)
        # Anfügen des einen Radius
        radiiList.append(maxRadius)

    return radiiList


def analyze_times(timestamps, picturePath, labels):
    # Ordner erstellen, falls nicht vorhanden
    os.makedirs(picturePath, exist_ok=True) 
    
    intervalls = max(int(len(timestamps[0])/10),1)
    
    fig, ax = plt.subplots(figsize=(9,6))
    for i in range(0, len(labels)):
        ax.plot(range(0, len(timestamps[0])), [e / 1_000_000 for e in timestamps[i]], label = labels[i])

    ax.set_xticks(list(range(1, len(timestamps[0]) + 1, intervalls)))
    ax.set_title("CPU Times of Algorithm Excecution")
    ax.set_xlabel("Sample")
    ax.set_ylabel("time in ms")
    ax.legend()
    plt.savefig(picturePath + "Timinganalysis1.jpg")
    plt.show()   
    
    return


def clue_pictures_together(samplename, pictureFolder, maxCluster):
    print("\n# --------- Cluing Pictures together --------- #\n")
    images = [Image.open(x) for x in [f"{pictureFolder}Unfair{samplename[0]}(Cluster-{maxCluster}).jpg", 
                                      f"{pictureFolder}Unfair{samplename[1]}(Cluster-{maxCluster}).jpg", 
                                      f"{pictureFolder}Unfair{samplename[2]}(Cluster-{maxCluster}).jpg"]]
    widths, heights = zip(*(i.size for i in images))
    
    total_width = sum(widths)
    max_height = max(heights)
    
    new_im = Image.new('RGB', (total_width, max_height))
    
    x_offset = 0
    for im in images:
      new_im.paste(im, (x_offset,0))
      x_offset += im.size[0]
    
    new_im.save(f"{pictureFolder}UnfairBig(Cluster-{maxCluster}).jpg")
    
    return

main()
