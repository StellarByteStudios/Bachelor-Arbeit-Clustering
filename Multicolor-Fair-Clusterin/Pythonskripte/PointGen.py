# -*- coding: utf-8 -*-
"""
Skript for creating ColoredPoints to test the Algorithm
"""
import random
import matplotlib.pyplot as plt

class Colorpoint:
    def __init__(self, dim, coords, color):
        # Dimensionalität
        self.dim = dim
        
        # liste von Coordinaten
        self.coordinates = coords
        
        # Farbe
        self.color = color
        
        
    # To-String-Methode für schönes anschauen
    def toStringLong(self):
        stringRep = "Dim: " + str(self.dim) + ";\tColor: " + str(self.color) + ";\tCoords: ["
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
    
    # Anfangsbedingungen
    numberOfPoints = 100
    fileName = "Points2D.txt"
    dimensions = 2
    colors = 3
    
    # Punkte erstellen
    points = createListOfPoints(numberOfPoints, dim = dimensions, colors = colors)
    
    # Punkte ausgeben
    for i in range(0, len(points)):
        print(points[i].toString())
    
    # Punkte mit ersten zwei koordinaten plotten
    show_Points(points)   
    
    # Punkte in Textdatei speichern
    with open(fileName, 'w') as f:
        # Kopf direkt weglassen
        # f.write('Format: dim,color,coord1,coord2,...,coordn\n')
        for i in range(0, len(points)):
            f.write(points[i].toString())
            f.write('\n')
    
    return



def createListOfPoints(numberOfPoints = 100, dim = 2, colors = 2):
    # Liste für die Punkte
    listOfPoints = []
    
    # viele Punkte generieren
    for i in range(0, numberOfPoints):
        listOfPoints.append(createRandomPoint(dim = dim, colors = colors))

    return listOfPoints



def createRandomPoint(dim = 2, colors = 2, borderLow = 0, borderHigh = 100):
    
    # Zufällige Koordinaten bestimmen
    coords = []
    
    for i in range(0, dim):
        coords.append((random.random() * (borderHigh - borderLow)) + borderLow)
        
    color = random.randint(0, colors-1)
    return Colorpoint(dim, coords, color)



def show_Points(listOfPoints):
    fig, ax = plt.subplots()
    firstCoordinate = [point.coordinates[0] for point in listOfPoints]
    secondCoordinate = [point.coordinates[1] for point in listOfPoints]
    colors = [point.color for point in listOfPoints]
    # Einfach zwei Achsen Zeigen, falls mehr zur verfügung stehen
    ax.scatter(firstCoordinate, secondCoordinate, alpha=0.5, c=colors)
    plt.show()
    return

main()