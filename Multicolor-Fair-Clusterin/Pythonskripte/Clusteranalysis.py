# -*- coding: utf-8 -*-
"""
Skript for reading, analysing and Showing ColoredPoints to test the Algorithm
"""

import csv
import matplotlib.pyplot as plt

class Colorpoint:
    def __init__(self, dim, isCenter, clustermember, color, coords):
        # Dimensionalität
        self.dim = dim
        
        # liste von Coordinaten
        self.coordinates = coords
        
        # Farbe
        self.color = color
        
        # Zentrum
        self.isCenter = isCenter
        
        # Zentrum
        self.cluster = clustermember
        
        
    # To-String-Methode für schönes anschauen
    def toStringLong(self):
        stringRep = "Dim: " + str(self.dim)
        stringRep +=";\t Center: " + str(self.isCenter)
        stringRep +=";\t Cluster: "  + str(self.cluster)
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
    
    
def main():
     
     fileName = "../Data/OutputData/ClusteredData (Old)/ClusterOut2D.csv"
          
     points, maxRadius = read_points(fileName)
     
     #print(points)
     
     # Punkte ausgeben
     for i in range(0, len(points)):
         print(points[i].toStringLong())
     
     show_points(points)
     show_points(points, maxRadius=maxRadius)
     #show_points(points, colorByCluster=False) 
     
     return
 
    
    
    
    

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
        
        #print(dim, center, cluster, color)
        #print(center)
        
        # Coordinates
        coords = []
        for k in range(4, 4+dim):
            coords.append(float(rawDataList[i][k]))
            
        # Point via Constructor
        newPoint = Colorpoint(dim, center, cluster, color, coords)
        
        # add Point to list
        listOfPoints.append(newPoint)
    
    
    return listOfPoints, maxRadius


main()