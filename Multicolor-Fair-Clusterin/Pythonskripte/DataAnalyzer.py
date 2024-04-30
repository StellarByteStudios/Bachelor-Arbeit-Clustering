# -*- coding: utf-8 -*-
"""
Splitting Test-Pipeline into pieces

In This file. The Data written in CSV files is read and graphs are made
"""

import Points
import matplotlib.pyplot as plt
import os
import pandas as pd
import csv

from PIL import Image

def analyzeDatasetzs(pictureFolder = "../Data/OutputData/Final/Pictures/", 
                     dataFolder = "../Data/OutputData/Final/AnalyzedSubsamples/", 
                     maxCluster = 15, 
                   numOfSamples = 5, algs = ["g", "r", "f"]):
        
    
    
    # Einmal für jedes Datenset durchgehen
    for dataSet in ["bank", "census", "diabetes"]:
        # Großen Gemeinsamen leeren Plot bauen
        # Variablen für gemeinsamen Plot erzeugen
        fig, ax = plt.subplots(figsize=(9,6))
    
        # Für jede Algorithmusart einmal durchgehen
        for i in range(0, 3):
            # Verarbeitung der Radius-Daten
            do_analysis_of_sampleset(dataSet, pictureFolder, dataFolder, axis=ax,
                                     numOfSamples=numOfSamples, maxCluster=maxCluster, algorithm=algs[i])
        
        # Rest vom Graph zusammensetzen
        ax.set_title(f"Max Radius Comparison of all Algorithms with {dataSet}-Data")
        ax.set_xlabel("Cluster")
        ax.set_ylabel("max Radius")
        ax.legend()
        plt.savefig(f"{pictureFolder}/Collective Analysis {dataSet}(Cluster-{maxCluster}).jpg", dpi=400)
        plt.show()



    # Analyse der Laufzeiten    
    for alg in algs:
        # Daten einlesen
        timestamps = read_timestamps_from_csv(dataFolder, algorithm=alg)
        # Plot bauen
        analyze_times(timestamps, pictureFolder, ["bank", "census", "diabetes"], algorithm=alg)
    
    # ====== Große Bilder zusammensetzen ====== #
    clue_pictures_together(["bank", "census", "diabetes"], pictureFolder, maxCluster=maxCluster)
    
    
    # Analyse für das Center-Aware Problem von Fast-Anchor
    fast_anchor_maxline_analysis("census", pictureFolder, dataFolder, numOfSamples=10)
    
    return







# # # Analysiert die geclusterten Daten und gibt ein Diagramm dazu aus # # #
def do_analysis_of_sampleset(samplename, pictureFolder, dataFolder, axis=False, numOfSamples = 20, maxCluster = 20, algorithm="g"):
    print(f"\n# --------- Working with {samplename} Data --------- # \n")
    
    # Zusammensetzen des Pfades
    algPathAdd = "GonzalezClustering"
    if(algorithm == "r"):
        algPathAdd = "RedClustering"
    if(algorithm == "f"):
        algPathAdd = "FastClustering"
    
    # # # Einlesen der neuen Daten
    listOfRadiiLists = []
    listOfFairlettRadius = []
    for i in range(0, numOfSamples): 
        # Pfade algorithmisch zusammensetzen
        outputfolder = f"{dataFolder}{algPathAdd}/{samplename}/Sample{i}/"
        outputfile = f"{samplename}{i}"
        # Maximale Radien für jede Clustergröße holen
        radiiList, fairlettRadius = get_radii_of_subsample(outputfolder, outputfile, maxCluster, algorithm=algorithm)
        # radienverlauf hinszufügen
        listOfRadiiLists.append(radiiList)
        # Fairlettgröße hinzufügen
        listOfFairlettRadius.append(fairlettRadius)
        
    
    
    # # # Analyse der Daten
    # Radien in Pandas-Dataframe für weiterverarbeitung packen
    dfRadius = pd.DataFrame(listOfRadiiLists)#.transpose()
    
    # erzeugen eines Analyse-Dataframes
    dfImportantValues = pd.DataFrame()
    # Index (Clustersize)
    dfImportantValues["clustersize"] = list(range(1, maxCluster+1))
    dfImportantValues["mean"] = dfRadius.mean()
    dfImportantValues["maxValue"] = dfRadius.max()
    dfImportantValues["minValue"] = dfRadius.min()
    dfImportantValues["upperQuantile"] = dfRadius.quantile(0.75)
    dfImportantValues["lowerQuantile"] = dfRadius.quantile(0.25)
    
    # Median des Fairlett-Radius bilden
    fairRadiusMean = sum(listOfFairlettRadius) / len(listOfFairlettRadius)  
    
    print(dfImportantValues.head(10))
    
    # Ordner erstellen, falls nicht vorhanden
    os.makedirs(pictureFolder, exist_ok=True) 

    # Entscheidung ob einfach nur einzeler Graph oder alles in einen Großen
    if axis == False:
        plot_single_dataset(dfImportantValues, 
                   f"{pictureFolder}/{algPathAdd}-{samplename}(Samples-{numOfSamples})(Cluster-{maxCluster}).jpg", 
                   f"{algPathAdd} - {samplename} k-center", algorithm=algorithm)
    else:
        build_plot_axis(axis, dfImportantValues, fairlettRadiusMean=fairRadiusMean, algorithm=algorithm)

    return



# # # Printet die Ergebnisse eines einzigen algorithmus in einen Graphen # # #
def plot_single_dataset(dfRadius, picturePath, title, algorithm="g"):
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
    








# # # Fügt einem gegebenen Graphen die Daten eines Algorithmuses hinzu # # #
def build_plot_axis(axis, dfRadius, fairlettRadiusMean=0, algorithm="g"):
    # Wie weit ist der Abstand der x-Beschriftung
    intervalls = max(int(len(dfRadius)/10),1)
    
    # Bessere Beschriftung
    algName = "Gonzalez-Clustering"
    algColor = "tab:blue"
    if(algorithm == "r"):
        algName = "Red-Clustering"
        algColor = "orangered"
    if(algorithm == "f"):
        algName = "Fast-Clustering"
        algColor = "tab:green"

    if(algorithm == "g"):
        # Unfaire Beschriftung
        axis.plot(dfRadius["clustersize"], dfRadius["mean"],
                color = algColor, label = f"Unfair {algName} (mean)")
    else:
        # Faire Beschriftung
        axis.plot(dfRadius["clustersize"], dfRadius["mean"],
                 color = algColor, label = f"Fair {algName} (mean)")
        axis.axhline(y=fairlettRadiusMean, color = algColor, linestyle='--', label=f"Max Farlett of {algName}")

    
    axis.set_xticks(list(range(1, len(dfRadius) + 1, intervalls)))








# # # Holt aus den geklusterten Daten die maximalen Radien raus# # #
def get_radii_of_subsample(outputfolder, outputfile, maxCluster, algorithm="g"):
    # Liste für die berechneten Maximalen Radien
    radiiList = []
    
    # Radien aus den Files holen
    for i in range(1, maxCluster + 1):
        # Dateipfad generieren
        filename = f"{outputfolder}/Clusterdata{outputfile}Cluster{i}.csv"
        # nur die Radien auslesen mit Hilfsmethode
        if(algorithm == "g"):
            _, maxClusterRadius = Points.read_points(filename)
            maxFairlettRadius = 0 # Nur der Fall, wenn keine Fairletts gebildet werden
        else:
            _, maxClusterRadius, maxFairlettRadius = Points.read_fair_points(filename)
        # Anfügen des einen Radius
        radiiList.append(maxClusterRadius)

    #print(f"Der Fairlettradius der eingelesen wurde ist: {maxFairlettRadius}")
    return radiiList, maxFairlettRadius



# # # Liest die Zeitstempel von der CSV Datei ein # # #
def read_timestamps_from_csv(dataFolder, algorithm="g"):
    # Zusammensetzen des Pfades
    # Welcher Algorithmus?
    algPathAdd = "GonzalezClustering"
    if(algorithm == "r"):
        algPathAdd = "RedClustering"
    if(algorithm == "f"):
        algPathAdd = "FastClustering"
        
    pathOfFile = f"{dataFolder}{algPathAdd}-TimeStamps.csv"
    
    # Datei öffnen
    csvFile = open(pathOfFile, "r")
    
    # Datei zu einer Liste konvertieren
    stampsList = list(csv.reader(csvFile, delimiter=","))
    
    # Strings zu zahlen Umwandeln
    numericList = []
    for i in range(1, len(stampsList)):
        timesOfSample = []
        
        for k in range(1, len(stampsList[0])):
            timesOfSample.append(float(stampsList[i][k]))
        
        numericList.append(timesOfSample)
            
    # Liste noch Transformieren für die richtige Ausgabe
    transformedList = [list(values) for values in zip(*numericList)]

    return transformedList




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
    
    images = []
    
    # Alte Bildtypen
    #images = [Image.open(x) for x in [f"{pictureFolder}/{algPathAdd}-{samplename[0]}(Samples-{numOfSamples})(Cluster-{maxCluster}).jpg", 
    #                                  f"{pictureFolder}/{algPathAdd}-{samplename[1]}(Samples-{numOfSamples})(Cluster-{maxCluster}).jpg", 
    #                                  f"{pictureFolder}/{algPathAdd}-{samplename[2]}(Samples-{numOfSamples})(Cluster-{maxCluster}).jpg"]]
    
    # Neue Bildtypen
    for i in range(0, len(samplename)):
        pathToPicture = f"{pictureFolder}/Collective Analysis {samplename[i]}(Cluster-{maxCluster}).jpg"
        # print(f"Bild wird geladen: {pathToPicture}")
        images.append(Image.open(pathToPicture))
    
    
    widths, heights = zip(*(i.size for i in images))
    
    # Horizontal zusammenfügen
    """
    total_width = sum(widths)
    max_height = max(heights)
    
    new_im = Image.new('RGB', (total_width, max_height))
    
    x_offset = 0
    for im in images:
      new_im.paste(im, (x_offset,0))
      x_offset += im.size[0]
    """
    
    # Vertikal zusammenfügen
    max_width = max(widths)
    total_height = sum(heights)
    
    new_im = Image.new('RGB', (max_width, total_height))
    
    y_offset = 0
    for im in images:
      new_im.paste(im, (0,y_offset))
      y_offset += im.size[1]
    
    # Alter Name
    #if(algorithm == "g"): 
    #    new_im.save(f"{pictureFolder}Gonzalez-UnfairNew(Cluster-{maxCluster}).jpg")
    #else:
    #    new_im.save(f"{pictureFolder}/{algPathAdd}-FairCluedNew(Cluster-{maxCluster}).jpg")
    new_im.save(f"{pictureFolder}/Collective Clued(Cluster-{maxCluster}).jpg")
    
    return



# # # Nochmals Separate Analyse für das Center-Aware Problem von Fast-Anchor # # #
def fast_anchor_maxline_analysis(samplename, pictureFolder, dataFolder, numOfSamples = 20, maxCluster = 30):
    print(f"\n# --------- Working with {samplename} Data --------- # \n")
    
    # Zusammensetzen des Pfades
    algPathAdd = "FastClustering"
    
    # # # Einlesen der neuen Daten
    listOfRadiiLists = []
    for i in range(0, numOfSamples): 
        # Pfade algorithmisch zusammensetzen
        outputfolder = f"{dataFolder}{algPathAdd}/{samplename}/Sample{i}"
        outputfile = f"{samplename}{i}"
        # Maximale Radien für jede Clustergröße holen
        radiiList, fairlettRadius = get_radii_of_subsample(outputfolder, outputfile, maxCluster, algorithm="f")
        # radienverlauf hinszufügen
        listOfRadiiLists.append(radiiList)
        
    
    
    # # # Analyse der Daten
    # Radien in Pandas-Dataframe für weiterverarbeitung packen
    dfRadius = pd.DataFrame(listOfRadiiLists)
    
    # erzeugen eines Analyse-Dataframes
    dfImportantValues = pd.DataFrame()
    # Index (Clustersize)
    dfImportantValues["clustersize"] = list(range(1, maxCluster+1))
    dfImportantValues["mean"] = dfRadius.mean()
    dfImportantValues["maxValue"] = dfRadius.max()
    dfImportantValues["minValue"] = dfRadius.min()
    dfImportantValues["upperQuantile"] = dfRadius.quantile(0.75)
    dfImportantValues["lowerQuantile"] = dfRadius.quantile(0.25)
    
    # Ordner erstellen, falls nicht vorhanden
    os.makedirs(pictureFolder, exist_ok=True) 
    print_radii(dfImportantValues,  
                f"{pictureFolder}/Fast-Anchor Edge-Case.jpg", 
                f"Fast-Clustering census Edge-Case Example", algorithm="f", fairlettRadius=fairlettRadius)

    return


# # # Plot für einzelnen Algorithmus # # #
def print_radii(dfRadius, picturePath, title, algorithm="f", fairlettRadius=-1):
    
    # Zusammensetzen der Beschriftung
    algorithmName = "Gonzalez-Algorithm"
    if(algorithm == "r"):
        algorithmName = "Red-Clustering"
    if(algorithm == "f"):
        algorithmName = "Fast-Clustering"
    
    
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
                color = "brown", label = "max Radius (mean)")
        ax.plot(dfRadius["clustersize"], dfRadius["maxValue"],
                color = "red", linestyle = "dashed", alpha = 0.5, label = "max Radius (max)")
        ax.plot(dfRadius["clustersize"], dfRadius["minValue"],
                color = "green", linestyle = "dashed", alpha = 0.5, label = "max Radius (min)")
        if (fairlettRadius >= 0):
            ax.axhline(y=fairlettRadius, linestyle='--', label="Mean Farlett Radus")
    

    ax.set_xticks(list(range(1, len(dfRadius) + 1, intervalls)))
    ax.set_title(title)
    ax.set_xlabel("Cluster")
    ax.set_ylabel("max Radius")
    ax.legend()
    plt.savefig(picturePath, dpi=400)
    plt.show()