# -*- coding: utf-8 -*-
"""
Skript for automate feeding of the algorithms and analyzing their data
"""

import Points
import subprocess
import matplotlib.pyplot as plt
import os


def main():
    
    # Parameter (Später noch über schleifen)
    inputfile = "Data/Subsamples/bank/bankSample-0.csv"
    outputfolder = "Data/OutputData/Autoanalyzer/bank/Sample0/"
    outputfile = "bank0"
    maxCluster = 20
    pictureFolder = "../Data/OutputData/Pictures/FirstDiagrams/"
    
    # # # Algorithmus ausführen
    
    # Shellcommand zusammensetzen
    command = f"cd .. && ./AlgFeeder.sh -i {inputfile} -o {outputfolder} -n {outputfile} -c {maxCluster}"
    
    #print(command)
    
    # Prozess erzeugen
    process = bash_command(command)
    # Prozess starten
    process.communicate()
    
    # Wenn man die Ausgabe als String haben will
    # outputString = process.communicate()[0]


    # # # Einlesen der neuen Daten
    radiiList = get_radii_of_subsample(outputfolder, outputfile, maxCluster)
    
        

    # TO-DO: Analyse der Radien
    
    
    # # # Analyse der Daten
    # Ordner erstellen, falls nicht vorhanden
    os.makedirs(pictureFolder, exist_ok=True) 
    print_radii(radiiList, pictureFolder+"TestPic1.jpg", "Bank k-median")
    
    
    return



# Kapselung des Bashcommands, der das mit der Shell regelt
def bash_command(cmd): 
    return subprocess.Popen(cmd, shell=True, executable='/bin/bash')


def print_radii(radii, picturePath, title):
    intervalls = max(int(len(radii)/10),1)
    print(f"Intervalls: {intervalls}")
    
    fig, ax = plt.subplots(figsize=(9,6))
    ax.plot(list(range(1, len(radii)+1)), radii, # range in x Values um auf 1 zu shiften
            color = "brown", label = "Unfair")
    ax.set_xticks(list(range(1, len(radii) + 1, intervalls)))
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
