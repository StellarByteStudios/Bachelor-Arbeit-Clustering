# -*- coding: utf-8 -*-
"""
Splitting Test-Pipeline into pieces

In This file. The Data written in CSV files is read and graphs are made
"""

import Points
import matplotlib.pyplot as plt
import os
import pandas as pd

from PIL import Image

def analyzeDatasetzs(pictureFolder = "Data/OutputData/Final/Pictures/", 
                     dataFolder = "Data/OutputData/Final/AnalyzedSubsamples/", 
                     maxCluster = 15, 
                   numOfSamples = 5, algs = ["g", "r", "f"]):
        
    # Großen Gemeinsamen leeren Plot bauen
    # Für jede Algorithmusart einmal durchgehen
    for i in range(0, 3):
        
        # # # Daten einlesen
        #analyze_times(timestamps, pictureFolder, ["bank", "census", "diabetes"], algorithm=alg)
        
        # ====== Verarbeitung Bank ====== #
        do_analysis_of_sampleset("bank", pictureFolder, dataFolder, 
                                 numOfSamples=numOfSamples, maxCluster=maxCluster, algorithm=algs[i])
        # ====== Verarbeitung Zensus ====== #
        do_analysis_of_sampleset("census", pictureFolder, dataFolder, 
                                 numOfSamples=numOfSamples, maxCluster=maxCluster, algorithm=algs[i])
        # ====== Verarbeitung Diabetes ====== #
        do_analysis_of_sampleset("diabetes", pictureFolder, dataFolder, 
                                 numOfSamples=numOfSamples, maxCluster=maxCluster, algorithm=algs[i])
    
    
    # ====== Große Bilder zusammensetzen ====== #
    clue_pictures_together(["bank", "census", "diabetes"], pictureFolder, maxCluster=maxCluster, numOfSamples=numOfSamples, algorithm=algs[0])    

    return

# # # Analysiert die geclusterten Daten und gibt ein Diagramm dazu aus # # #
def do_analysis_of_sampleset(samplename, pictureFolder, dataFolder, numOfSamples = 20, maxCluster = 20, algorithm="g"):
    print(f"\n# --------- Working with {samplename} Data --------- # \n")
    
    # Zusammensetzen des Pfades
    algPathAdd = "GonzalezClustering"
    if(algorithm == "r"):
        algPathAdd = "RedClustering"
    if(algorithm == "f"):
        algPathAdd = "FastClustering"
    
    # # # Einlesen der neuen Daten
    listOfRadiiLists = []
    for i in range(0, numOfSamples): 
        # Pfade algorithmisch zusammensetzen
        #inputfile = f"Data/Subsamples/{bank}/{bank}Sample-{i}.csv"
        outputfolder = f"{dataFolder}{algPathAdd}/{samplename}/Sample{i}/"
        outputfile = f"{samplename}{i}"
        # Maximale Radien für jede Clustergröße holen
        radiiList = get_radii_of_subsample(outputfolder, outputfile, maxCluster, algorithm=algorithm)
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
    print(f"picture Path: {pictureFolder}/{algPathAdd}-{samplename}(Cluster-{maxCluster}).jpg")
    build_plot_axis(dfImportantValues, 
                f"{pictureFolder}/{algPathAdd}-{samplename}(Samples-{numOfSamples})(Cluster-{maxCluster}).jpg", 
                f"{algPathAdd} - {samplename} k-center", algorithm=algorithm)

    return


def build_plot_axis(dfRadius, picturePath, title, algorithm="g"):
    # Wie weit ist der Abstand der x-Beschriftung
    intervalls = max(int(len(dfRadius)/10),1)

    
    fig, ax = plt.subplots(figsize=(9,6))
    
    if(algorithm == "g"):
        # Unfaire Beschriftung
        ax.plot(dfRadius["clustersize"], dfRadius["mean"],
                color = "brown", label = "Unfair (mean)")
        ax.plot(dfRadius["clustersize"], dfRadius[["maxValue", "minValue"]],
                color = "orange", linestyle = "dashed", alpha = 0.5, label = "Unfair (max/min)")
    else:
        # Faire Beschriftung
        ax.plot(dfRadius["clustersize"], dfRadius["mean"],
                color = "brown", label = "Fair (mean)")
        ax.plot(dfRadius["clustersize"], dfRadius[["maxValue", "minValue"]],
                color = "orange", linestyle = "dashed", alpha = 0.5, label = "Fair (max/min)")
    
    ax.set_xticks(list(range(1, len(dfRadius) + 1, intervalls)))
    ax.set_title(title)
    ax.set_xlabel("Cluster")
    ax.set_ylabel("max Radius")
    ax.legend()
    plt.savefig(picturePath, dpi=400)
    plt.show()
    


# # # Holt aus den geklusterten Daten die maximalen Radien raus# # #
def get_radii_of_subsample(outputfolder, outputfile, maxCluster, algorithm="g"):
    # Liste für die berechneten Maximalen Radien
    radiiList = []
    
    # Radien aus den Files holen
    for i in range(1, maxCluster + 1):
        # Dateipfad generieren
        filename = f"../{outputfolder}/Clusterdata{outputfile}Cluster{i}.csv"
        # nur die Radien auslesen mit Hilfsmethode
        if(algorithm == "g"):
            _, maxClusterRadius = Points.read_points(filename)
        else:
            _, maxClusterRadius, _ = Points.read_fair_points(filename)
        # Anfügen des einen Radius
        radiiList.append(maxClusterRadius)

    return radiiList




# # # Erstellt einen Graphen für die Prozessorzeiten # # #
def analyze_times(timestamps, picturePath, labels, algorithm="g"):
    # Zusammensetzen des Pfades
    algorithmName = "Gonzalez-Algorithm"
    if(algorithm == "r"):
        algorithmName = "Red-Clustering"
    if(algorithm == "f"):
        algorithmName = "Fast-Clustering"
    
    # Ordner erstellen, falls nicht vorhanden
    os.makedirs(picturePath, exist_ok=True) 
    
    intervalls = max(int(len(timestamps[0])/10),1)
    
    fig, ax = plt.subplots(figsize=(9,6))
    for i in range(0, len(labels)):
        ax.plot(range(0, len(timestamps[0])), [e / 1_000_000 for e in timestamps[i]], label = labels[i])

    ax.set_xticks(list(range(0, len(timestamps[0]) + 1, intervalls)))
    ax.set_title(f"CPU Times of {algorithmName} Excecution")
    ax.set_xlabel("Sample")
    ax.set_ylabel("time in ms")
    ax.legend()
    plt.savefig(picturePath + f"/Timinganalysis {algorithmName}.jpg", dpi=400)
    plt.show()   
    
    return




# # # Packt die Bilder der Verschiedenen Datensätzen zu einem Bild dazu # # #
def clue_pictures_together(samplename, pictureFolder, maxCluster, numOfSamples = 20, algorithm="g"):
    print("\n# --------- Cluing Pictures together --------- #\n")
    
    # Zusammensetzen des Pfades
    algPathAdd = "GonzalezClustering"
    if(algorithm == "r"):
        algPathAdd = "RedClustering"
    if(algorithm == "f"):
        algPathAdd = "FastClustering"
    
    images = [Image.open(x) for x in [f"{pictureFolder}/{algPathAdd}-{samplename[0]}(Samples-{numOfSamples})(Cluster-{maxCluster}).jpg", 
                                      f"{pictureFolder}/{algPathAdd}-{samplename[1]}(Samples-{numOfSamples})(Cluster-{maxCluster}).jpg", 
                                      f"{pictureFolder}/{algPathAdd}-{samplename[2]}(Samples-{numOfSamples})(Cluster-{maxCluster}).jpg"]]
    widths, heights = zip(*(i.size for i in images))
    
    total_width = sum(widths)
    max_height = max(heights)
    
    new_im = Image.new('RGB', (total_width, max_height))
    
    x_offset = 0
    for im in images:
      new_im.paste(im, (x_offset,0))
      x_offset += im.size[0]
     
    if(algorithm == "g"): 
        new_im.save(f"{pictureFolder}UnfairBig(Cluster-{maxCluster}).jpg")
    else:
        new_im.save(f"{pictureFolder}/{algPathAdd}-FairClued(Cluster-{maxCluster}).jpg")
    
    return