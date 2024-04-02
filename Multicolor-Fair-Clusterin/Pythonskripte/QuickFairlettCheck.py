# -*- coding: utf-8 -*-
"""
Skript which checks with handmade Points if Algorithms are working correctly
"""

import Points
import subprocess
import matplotlib.pyplot as plt
import csv
import math


def main():
    
    # Testdaten
    dataFileNames = ["Data/RandomGenerated/HandmadeFairlettPoints.csv", 
                     "Data/Subsamples/diabetes/diabetesSample-3.csv", 
                     "Data/RandomGenerated/HandmadeFairlettPoints2.csv"]
    
    outputFileNames = ["Data/OutputData/FairlettTests/RedCluteringTest.csv", 
                       "Data/OutputData/FairlettTests/BigRedCluteringTest.csv", 
                       "Data/OutputData/FairlettTests/SecondRedCluteringTest.csv"]
    
    plotTitles = ["Red Clustering", "Red Clustering Big", "Red-Clustering Second"]
    
    pictureFolder = "Data/OutputData/Pictures/FairlettTests/"
    
    # Welches Dataset wird benutzt?
    dSetID = 1
    
    numberOfClusters = 2
    
    # Punkte einlesen
    cleanPoints = get_raw_points(dataFileNames[dSetID])
    
    # Nur die Punkte selbst mit Farbe ausgeben
    show_clean_points(cleanPoints, plotTitles[dSetID] +" - Unclustered")
    
    # Algorithmus über Shell ausführen
    do_algorithm(dataFileNames[dSetID], outputFileNames[dSetID], maxCluster=numberOfClusters, doCompiling=True)
    
    # Punkte einlesen
    clusterdPoints, maxClusterRadius, maxFairlettRadius = Points.read_fair_points("../" + outputFileNames[dSetID])
    
    # Punkte mit Clustern zeigen
    show_clustered_points(clusterdPoints, plotTitles[dSetID]+" - Clustered", k=numberOfClusters)
    
    # Beides Als Bild abspeichern
    save_clean_plot("../" + pictureFolder + f"{plotTitles[dSetID]} (Unclustered).jpg", 
                    cleanPoints, plotTitles[dSetID] + " - Unclustered")
    save_clustered_plot("../" + pictureFolder + f"{plotTitles[dSetID]} (Clustered).jpg", 
                    clusterdPoints, plotTitles[dSetID] + " - Clustered")
    
    
    return





def get_raw_points(fileName, dim=2):
    # Rohe Liste holen
    csvFile = open("../" + fileName, "r")
    rawDataList = list(csv.reader(csvFile, delimiter=","))
    
    
    # Leere Liste für Punkte anlegen
    listOfPoints = []

    # Durch alle CSV-Daten durchgehen    
    for i in range(1, len(rawDataList)):
        # Metadata
        color = int(rawDataList[i][0])
        
        # Coordinates
        coords = []
        for k in range(1, 1+dim):
            coords.append(float(rawDataList[i][k]))
            
        # Point via Constructor
        newPoint = Points.Colorpoint(dim, False, -1, color, coords)
        
        # add Point to list
        listOfPoints.append(newPoint)
    
    return listOfPoints









# # # =========== Algorithmus ausführen =========== # # #
# # # Plot für die Punkte ohne das Clustering # # #
def do_algorithm(inputFileName, outputFileName, doCompiling=False, maxCluster=2):   
    # Programm kompilieren
    if(doCompiling):
        bash_command("cd .. && make buildProcessBar", ignoreStdout=False).communicate();
    
    
    # Shellcommand zusammensetzen
    command = f"cd .. && ./Fair-Clustering ./{inputFileName} ./{outputFileName} {maxCluster} r"
    print(command)
    # Prozess erzeugen
    process = bash_command(command, ignoreStdout=False)

    # Prozess starten
    process.communicate()
    print(f"Cluster made for Sample: {inputFileName}")
    
    return


# Kapselung des Bashcommands, der das mit der Shell regelt
def bash_command(cmd, ignoreStdout = True):
    # stdout wird weggeworfen
    if ignoreStdout:    
        return subprocess.Popen(cmd, shell=True, executable='/bin/bash', stdout=subprocess.DEVNULL)
    # Stdout vom Skript in Pythonkonsole
    return subprocess.Popen(cmd, shell=True, executable='/bin/bash')











# # # =========== Plots =========== # # #
# # # Plot für die Punkte ohne das Clustering # # #
def show_clean_points(listOfPoints, title):
    construct_clean_points_plot(listOfPoints, title).show()
    return

def save_clean_plot(fileName, listOfPoints, title):
    construct_clean_points_plot(listOfPoints, title).savefig(fileName)
    return


def construct_clean_points_plot(listOfPoints, title):
    fig, ax = plt.subplots(figsize=(5,5))
    
    # Ersten zwei Coordinaten
    firstCoordinate = [point.coordinates[0] for point in listOfPoints]
    secondCoordinate = [point.coordinates[1] for point in listOfPoints]
    
    # Einfärben
    colors = [point.color for point in listOfPoints]

    # Punkte Plotten
    ax.scatter(firstCoordinate, secondCoordinate, alpha=0.5, c=colors)
    
    ax.set_title(title)   
    
    # Zentren Markieren
    for i in range(0, len(listOfPoints)):
        if(listOfPoints[i].isCenter):
            ax.scatter(listOfPoints[i].coordinates[0], listOfPoints[i].coordinates[1], marker="+", s=250, c="black")
            
    return plt




# # # Plot für die Punkte welche geclusterd wurden # # #
def show_clustered_points(listOfPoints, title, k=2):
    construct_clustered_points_plot(listOfPoints, title, k).show()
    return

def save_clustered_plot(fileName, listOfPoints, title, k=2):
    construct_clustered_points_plot(listOfPoints, title, k).savefig(fileName)
    return


def construct_clustered_points_plot(listOfPoints, title, k):
    fig, ax = plt.subplots(figsize=(5,5))
    
    # Ersten zwei Coordinaten
    firstCoordinate = [point.coordinates[0] for point in listOfPoints]
    secondCoordinate = [point.coordinates[1] for point in listOfPoints]
    
    # Einfärben nach Cluster
    colors = [point.cluster for point in listOfPoints]
    
    # Radien Holen
    radii = get_radii_of_clustering(listOfPoints, k)
    print(radii)

 
    # Punkte zeichen
    ax.scatter(firstCoordinate, secondCoordinate, alpha=0.5, c=colors)
    
    ax.set_title(title)   
    
    # Zentren Markieren
    for i in range(0, len(listOfPoints)):
        if(listOfPoints[i].isCenter):
            ax.scatter(listOfPoints[i].coordinates[0], listOfPoints[i].coordinates[1], marker="+", s=250, c="black")
            circle = plt.Circle((listOfPoints[i].coordinates[0], listOfPoints[i].coordinates[1]),
                                    color="black", fill=False)
            circle.set_radius(radii[listOfPoints[i].cluster])
            ax.add_artist(circle)
            
    # Linien zwischen Fairlett ziehen
    for fairID in range(0, math.ceil(len(listOfPoints)/2)):
        # Durch Liste durch gehen und Punkte suchen
        fairlettPartners = []
        for i in range(0, len(listOfPoints)):
            if(listOfPoints[i].fairlettID == fairID):
                fairlettPartners.append(listOfPoints[i])
        
        # Nun Linie zwischend diesen beiden ziehen
        if(len(fairlettPartners) > 1):
            
            plt.plot([fairlettPartners[0].coordinates[0],fairlettPartners[1].coordinates[0]], 
                     [fairlettPartners[0].coordinates[1],fairlettPartners[1].coordinates[1]])
            #print(f"Linie gezogen Nr {fairID}")
        #else:
            #print(f"fairlettID {fairID} existiert nicht")
            
    return plt













# # # =========== Utility =========== # # #
# # # Alle Radien der Cluster bestimmen # # #
# Berechne den Radius eines bestimmten Clusters
def get_radius_of_cluster(clusterID, clustered_points):
    n = len(clustered_points)
    
    # Zentrum des CLuster finden
    center = -1
    for i in range(0, n):
        if (clustered_points[i].cluster == clusterID):    
            # Zentrum abspeichern
            if (clustered_points[i].isCenter):
                center = clustered_points[i]
    
    # Fehlerfall kein Zentrum gefunden
    if (center == -1):
        print(f"Das Cluster {clusterID} besitz kein Zentrum")
        return -1
    
    # Abstand zu allen Clustermitgliedern messen
    max_radius = -1
    for i in range(0, n):
        if (clustered_points[i].cluster == clusterID):    
            # Nach neuem Radius prüfen
            if (center.dist_to(clustered_points[i]) > max_radius):
                # Radius aktuallisieren
                max_radius = center.dist_to(clustered_points[i])
    
    return max_radius


# Berechnet alle Radien
def get_radii_of_clustering(clustered_points, k):
    # Liste für die Radien
    radii = []
    
    # Laufvariablen
    clu = 0
    highes_cluster = k
    
    # Durch jedes Cluster gehen und radius suchen
    while (clu < highes_cluster):
        # Radius eines Clusters mit der ID clu berechnen
        radius_of_cluster = get_radius_of_cluster(clu, clustered_points)
        # Diesen Radius der Liste hinzufügen
        radii.append(radius_of_cluster)
        
        # Gelöschtes Cluster ist nicht mehr vorhanden belegt aber den Index
        # dadurch ist ggf highes_cluster größer als k        
        if(radius_of_cluster < 0):
            highes_cluster += 1
        
        clu += 1
    
    return radii









main()

