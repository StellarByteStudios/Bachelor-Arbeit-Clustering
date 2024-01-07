# -*- coding: utf-8 -*-
"""
Skript for automate feeding of the algorithms and analyzing their data
"""

import Points
import subprocess
import matplotlib.pyplot as plt
import os
import pandas as pd



def main():
    
    # Parameter (Später noch über schleifen)
    inputfile = "Data/Subsamples/bank/bankSample-0.csv"
    outputfolder = "Data/OutputData/Autoanalyzer/bank/Sample0/"
    outputfile = "bank0"
    maxCluster = 20
    pictureFolder = "../Data/OutputData/Pictures/FirstDiagrams/"
    numOfSamples = 20
    
    # # # Algorithmus ausführen
    for i in range(0, numOfSamples):
        # Pfade algorithmisch zusammensetzen
        inputfile = f"Data/Subsamples/bank/bankSample-{i}.csv"
        outputfolder = f"Data/OutputData/Autoanalyzer/bank/Sample{i}/"
        outputfile = f"bank{i}"
        # Shellcommand zusammensetzen
        command = f"cd .. && ./AlgFeeder.sh -i {inputfile} -o {outputfolder} -n {outputfile} -c {maxCluster}"
        # Prozess erzeugen
        process = bash_command(command)
        # Prozess starten
        process.communicate()
        print(f"Cluster made for Sample: {inputfile}")
    
        # Wenn man die Ausgabe als String haben will
        # outputString = process.communicate()[0]


    # # # Einlesen der neuen Daten
    listOfRadiiLists = []
    for i in range(0, numOfSamples): 
        # Pfade algorithmisch zusammensetzen
        inputfile = f"Data/Subsamples/bank/bankSample-{i}.csv"
        outputfolder = f"Data/OutputData/Autoanalyzer/bank/Sample{i}/"
        outputfile = f"bank{i}"
        # Maximale Radien für jede Clustergröße holen
        radiiList = get_radii_of_subsample(outputfolder, outputfile, maxCluster)
        # radienverlauf hinszufügen
        listOfRadiiLists.append(radiiList)
        
    
    
    # # # Analyse der Daten
    # RAdien in Pandas-Dataframe für weiterverarbeitung packen
    dfRadius = pd.DataFrame(listOfRadiiLists)#.transpose()
    print(dfRadius.head())
    
    # erzeugen eines Analyse-Dataframes
    dfImportantValues = pd.DataFrame()
    # Index (Clustersize)
    dfImportantValues["clustersize"] = list(range(1, maxCluster+1))
    dfImportantValues["mean"] = dfRadius.mean()
    dfImportantValues["maxValue"] = dfRadius.max()
    dfImportantValues["minValue"] = dfRadius.min()
    dfImportantValues["upperQuantile"] = dfRadius.quantile(0.75)
    dfImportantValues["lowerQuantile"] = dfRadius.quantile(0.25)
    
    #dfRadius["median"] = -1 
    #dfRadius.loc[dfRadius["sex"] == "Female", "kritFeature"] = 1
    
    #listAvarageMaxRadius = []
    #for i in range(0, numOfSamples):
        #radiiOfIndex
    
    print(dfImportantValues.head(10))
    
    # Ordner erstellen, falls nicht vorhanden
    os.makedirs(pictureFolder, exist_ok=True) 
    #print_radii(radiiList, pictureFolder+"TestPic1.jpg", "Bank k-median")
    print_radii(dfImportantValues, pictureFolder+"TestPic2(mean).jpg", "Bank k-median")
    
    
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

main()
