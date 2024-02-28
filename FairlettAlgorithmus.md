# Fairlett Algorithmus (1:1 mit Ausreißern)
Hier möchte ich mal etwas kleinschrittiger festhalten wie der Algorithmus zum Bilden der Fairletts abläuft

## Anlegen der Grundstrukturen
```cpp
Graph graph;
GraphData gData;
CapacityMap capacity(graph);
```

## Anlegen aller Knoten
* Bestimmen, welche Ausprägung des Kritischen Features weniger Knoten hat
* Definiere $n$ als Anzahl aller Punkte in den Daten
  * Diese Ausprägung wird die Farbe Rot
  * Die andere Ausprägung wird Blau
> es gilt: |Rote-Knoten| < |Blaue-Knoten|
* wähle für weitere erklärung |Rote-Knoten| := $n_r$ und |Blaue-Knoten| := $n_b$
> es gilt: $n_r$ < $n_b$ < $n$
* Füge jetzt alle roten Knoten in den Graphen ein. Dadurch ist der i-te rote Knoten in den Daten auch an i-ter Stelle im Graphen und hat die entsprechende ID
> ID roter Knoten geht von $0$ bis $(n_r - 1)$
* Füge jetzt alle blauen Knoten ein. Diese kommen dann direkt nach den roten
> ID blauer Knoten geht von $n_r$ bis $(n_r + n_b - 1)= n - 1$
> der i-te blaue Knoten hat im Graphen die ID $n_r + i$
* Es wird die Quelle s hinzugefügt
* Es wird die Senke t hinzugefügt
> ID der Quelle s = $n$  
> ID der Senke t = $n + 1$


## Finden der Fairlets
### Basiskanten
* Füge eine Kante von s zu allen roten Punkten mit Kapazität 1 in den Graphen ein
* Füge eine Kante von allen blauen Punkten zu t mit Kapazität 1 in den Graphen ein
* Alle möglichen Radien R berechnen und Abspeichern (das sind $n²$ viele)
### Radius finden
* Für jeden potRad in R
  * für jeden roten Punkt rot
    * für jeden blauen Punkt blau
      * Teste ob die Distanz d(rot, blau) < potRad
      * Falls ja, füge Kante arc(rot, blau) mit Kapazität 1 in Graphen ein
  * Erreicht der max-Flow Value $n_r$ dann haben wir alle roten Punkte gematched und wir wissen unseren Fairlett-Radius
> Diese Iterationen müssen ganz Außen stehen, da für jede neue Runde ein neuer Graphen erzeugt werden muss  
> Definiere den Fairlett-Radius als $r_{fair}$

### Fairletts ausrechnen und markieren
#### Echte 1:1 Fairlets
* Baue jetzt den Graphen wieder wie oben genannt auf, aber bei dem Test jetzt Distanz d(rot, blau) < $r_{fair}$
* Berechne den maximalen Fluss
* Setzte den Fairlettcounter auf 0
* Für jede Kante in Main-Arcs
  * Prüfe ob ihr Flusswert 1 ist
  * Falls ja:
    * Auslesen des roten Knoten mit `Node redNode = graph.source(gData.mainArcs.at(0));`
    * Auslesen des blauen Knoten mit `Node blueNode = graph.target(gData.mainArcs.at(0));`
    * Node ID umrechnen, wievielter roter oder blauer Knoten ist das
    * Entsprechende Knoten in den Main Daten die Fairlett-ID mit Fairlettcounter überschreiben
#### Ausreißer
* Für jede Kante in den Target-Arcs
  * Prüfe ob ihr Flusswert 0 ist
  * Falls ja:
    * Rechne Targetindex um, welcher blaue Knoten das ist
    * Entsprechende Knoten in den Main Daten die Fairlett-ID mit -2 Überschreiben
> Definiere für Fairlett-ID:  
>   ID >= 0: Fairlettzugehörigkeit
>   ID = -1: Fehler/Defaultwert
>   ID = -2: Ausreißer