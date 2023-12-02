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
     
     fileName = "../ClusterOut2D.csv"
          
     points = read_points(fileName)
     
     #print(points)
     
     # Punkte ausgeben
     for i in range(0, len(points)):
         print(points[i].toStringLong())
     
     show_points(points)   
     
     return
 
    
    
    
    

def show_points(listOfPoints, colorByCluster = True):
    fig, ax = plt.subplots()
    
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
    
    plt.show()
    return

def read_points(fileName):
    csvFile = open(fileName, "r")
    rawDataList = list(csv.reader(csvFile, delimiter=","))
    
    pointsData = parse_points_from_list(rawDataList)
    
    return pointsData


def parse_points_from_list(rawDataList):
    
    numberOfPoints = len(rawDataList)
    
    listOfPoints = []
    
    for i in range(0, numberOfPoints):
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
    
    
    return listOfPoints


main()