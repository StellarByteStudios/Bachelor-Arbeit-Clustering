# Implementierung von Fairen Clustering-Algorithmen
In diesem Repository ist gesammte Code für meine Bachelorarbeit hinterlegt. Darunter fallen die Applikation für das Ausführen der Clustering-Algorithmen, die Daten auf denen getestet wurde, sowie die Pythonskripte welche die Tests ausgeführt haben und der Latex-Code welcher meine Bachelorarbeit stellt.

## Aufgabe
Es wurden zwei verschiedene Algorithmen für das Fair-Clustering Problem, mit k-center als Zielfunktion, in C++ implementiert. Diese sollten auf mehreren Daten mit einander verglichen werden

## API
Es gibt ein Testskript, welche einige Funktionen der Algorithmen testet und ein Main-Skript, welches man benutzen kann um die Punkte zu clustern.
### C++ Programme & Makefile
#### Application API
Nachdem man das Programm kompiliert hat, kann man es aufrufen mit Kommandozeilen Argumente
Format:
1) Pfad er Inputdaten
2) Output-Pfad
3) Wie viele Cluster sollen gebildet werden
4) kind of Algorithm: 
    * "g" = Gonzalez
    * "r" = red-Clustering
    * "f" = fast-anchor-
    
Bsp: `./Fair-Clustering Data/Points.csv Data/ClusteredPoints.csv 5 r`


#### Makefile Kompilieren
* main-Skript: make build oder make buildProcessBar
* tests: buildTestProcess

#### Tests über Makefile
make runTests oder make runTestProcess

### Pythonskripte
Es gibt ein Haupt-Python Skript `Autoanalyzer.py` welches die anderen Skripte aufruft um mit `CleanData.py` die Daten zu reinigen, mit `AlgorithmDataCruncher.py` die Algorithmen auszuführen und die Daten abzuspeichern und zum Schluss mit `DataAnalyzer.py` die Analyse der geclusterten Daten auszuführen. Die Skripte verwenden die Klasse in `Points.py`

Die Metadaten können in `Autoanalyzer.py` geändert werden
* dataFolder:    Ordner in welchem die geclusterten Daten gespeichert werden sollen
* pictureFolder: Ordner in welchem die Bilder gespeichert werden sollen
* clusters:      Maximale Anzahl an Clustern welche bei der Analyse gebildet werden
* numOfSamples:  Wie viele Von den Sampels benutzt werden sollen (viel = dauert lang; max = 20 außer `CleanData.py` wird angepasst)
    
   