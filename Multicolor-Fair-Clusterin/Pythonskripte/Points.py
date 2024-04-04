# -*- coding: utf-8 -*-
"""
Own Module for Pointclass
"""

import csv
import matplotlib.pyplot as plt
import math

class Colorpoint:
    def __init__(self, dim, isCenter, clusterAffiliation, color, coords, fairlettID=-1):
        # Dimensionalität
        self.dim = dim
        
        # liste von Coordinaten
        self.coordinates = coords
        
        # Farbe
        self.color = color
        
        # Zentrum
        self.isCenter = isCenter
        
        # Clusterzugehörigkeit
        self.cluster = clusterAffiliation
        
        # Fairlettpartner
        self.fairlettID = fairlettID
        
        
    # To-String-Methode für schönes anschauen
    def toStringLong(self):
        stringRep = "Dim: " + str(self.dim)
        stringRep +=";\t Center: " + str(self.isCenter)
        stringRep +=";\t Cluster: "  + str(self.cluster)
        stringRep +=";\t FairlettID: "  + str(self.fairlettID)
        stringRep += ";\tColor: " + str(self.color) + ";\tCoords: ["
        for i in range(0, self.dim - 1):
            stringRep += str(self.coordinates[i]) + ", "
        stringRep += str(self.coordinates[self.dim - 1]) + "]"
        return stringRep
    
    # To-String-Metode für die Datei später
    # Format: dim,color,coord1,coord2,...,coordn
    def toString(self):
        stringRep = str(self.dim) + "," + str(self.color) + ","
        for i in range(0, self.dim - 1):
            stringRep += str(self.coordinates[i]) + ","
        stringRep += str(self.coordinates[self.dim - 1])
        return stringRep
    
    
    # =========== Bisher nur gebraucht fürs Testen und darstellen =========== # 
    # Euclidische Distanz zwischen zwei Punkten
    def dist_to(self, other):
        
        # Sanaty check: Dimensionen Stimmen
        if(len(self.coordinates) != len(other.coordinates)):
            print(f"Dimensions not matching: {len(self.coordinates)} != {len(other.coordinates)}")
            # Fehlercode
            return -1
        
        # Initialize distance to zero
        distance = 0
        
        # Loop through each coordinate in the point2
        for coord1, coord2 in zip(self.coordinates, other.coordinates):
            # Add the square of the difference of coordinates to the distance
            distance += (coord2 - coord1) ** 2
        
        # Take the square root of the sum to get the Euclidean distance
        distance = math.sqrt(distance)
        
        return distance



def show_points(listOfPoints, colorByCluster = True, maxRadius = -1):
    fig, ax = plt.subplots(figsize=(5,5))
    
    # Ersten zwei Coordinaten
    firstCoordinate = [point.coordinates[0] for point in listOfPoints]
    secondCoordinate = [point.coordinates[1] for point in listOfPoints]
    
    # Einfärben
    if(colorByCluster):
        colors = [point.cluster for point in listOfPoints]
    else:
        colors = [point.color for point in listOfPoints]
        
        
    ax.scatter(firstCoordinate, secondCoordinate, alpha=0.5, c=colors)
    
    # Zentren Markieren
    for i in range(0, len(listOfPoints)):
        if(listOfPoints[i].isCenter):
            ax.scatter(listOfPoints[i].coordinates[0], listOfPoints[i].coordinates[1], marker="+", s=250, c="black")
            # ggf. Radius hinzufügen
            if(maxRadius != -1):
                circle = plt.Circle((listOfPoints[i].coordinates[0], listOfPoints[i].coordinates[1]),
                                    color="black", fill=False)
                circle.set_radius(maxRadius)
                ax.add_artist(circle)
            
    
    plt.show()
    return





# # # =========== Reading of Points =========== # # #
# # # Einlesen von einfach geclusterten Punkten # # #
def read_points(fileName):
    csvFile = open(fileName, "r")
    rawDataList = list(csv.reader(csvFile, delimiter=","))
    
    pointsData = parse_points_from_list(rawDataList)
    
    return pointsData



def parse_points_from_list(rawDataList):
    
    numberOfPoints = len(rawDataList)
    firstPoint = 0
    maxRadius = -1
    
    # abfangen, dass erste Zeile der MaxRadius ist
    if(rawDataList[0][0] == "maxRadius"):
        firstPoint = 1
        maxRadius = float(rawDataList[0][1])
    
    listOfPoints = []
    
    for i in range(firstPoint, numberOfPoints):
        # Metadata
        dim = int(rawDataList[i][0])
        center = bool(int(rawDataList[i][1]))
        cluster = int(rawDataList[i][2])
        color = int(rawDataList[i][3])
        
        # Coordinates
        coords = []
        for k in range(4, 4+dim):
            coords.append(float(rawDataList[i][k]))
            
        # Point via Constructor
        newPoint = Colorpoint(dim, center, cluster, color, coords)
        
        # add Point to list
        listOfPoints.append(newPoint)
    
    
    return listOfPoints, maxRadius





# # # Einlesen von punkten mit Fairletts # # #
def read_fair_points(fileName):
    csvFile = open(fileName, "r")
    rawDataList = list(csv.reader(csvFile, delimiter=","))
    
    pointsData = parse_fair_points_from_list(rawDataList)
    
    return pointsData


def parse_fair_points_from_list(rawDataList):
    
    numberOfPoints = len(rawDataList)
    firstPoint = 0
    maxClusterRadius = -1
    maxFairlettRadius = -1
    
    
    # abfangen, dass erste Zeile der MaxRadius ist
    if(rawDataList[0][0] == "maxClusterRadius"):
        firstPoint = 1
        maxClusterRadius = float(rawDataList[0][1])
        maxFairlettRadius = float(rawDataList[0][3])
        
    
    listOfPoints = []
    
    for i in range(firstPoint, numberOfPoints):
        # Metadata
        dim = int(rawDataList[i][0])
        center = bool(int(rawDataList[i][1]))
        cluster = int(rawDataList[i][2])
        fairlett = int(rawDataList[i][3])
        anchor = int(rawDataList[i][4])
        color = int(rawDataList[i][5])
        
        #print(dim, center, cluster, color)
        #print(center)
        
        # Coordinates
        coords = []
        for k in range(6, 6+dim):
            coords.append(float(rawDataList[i][k]))
            
        # Point via Constructor
        newPoint = Colorpoint(dim, center, cluster, color, coords, fairlettID=fairlett)
        
        # add Point to list
        listOfPoints.append(newPoint)
    
    
    return listOfPoints, maxClusterRadius, maxFairlettRadius