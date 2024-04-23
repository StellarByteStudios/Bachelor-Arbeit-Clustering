# Bachelor-Arbeit Notizen

## Allgemeine Notizen
### Termine
**Abgabe der Arbeit: 07.06.2024**

* [x] Treffen mit Melanie und Daniel am 7.11 um 10:30
* [x] Treffen mit Daniel am 20.11 um 15:00
* [x] Treffen mit Daniel am 5.12 um 10:30
* [x] Treffen mit Daniel ~~(Melanie?)~~ am 8.1 um 13:00
* [x] Vortrag von Irina zu ihrer Bachelor-Arbeit am 17.1 um 10:30
* [x] Treffen mit Daniel und Melanie am 18.1 um 12:00
* [x] Treffen mit Daniel am 12.3 um 11:00
* [x] Treffen mit Daniel am 26.3 um 10:30
* [x] Treffen mit Daniel am 9.4 um 12:15
* [x] Treffen mit Daniel am 22.4 um 15:00
* [ ] Treffen mit Daniel am 6.5 um 15:00

### Fragen an Besprechung
* [ ] Sollen die Einschübe wie zu Bipatitem Matching und Flusseigenschaften im Inhaltsverzeichniss auftauchen oder nicht?






#### Alte Fragen
* [x] Erste Augenscheinliche vergleiche lassen vermuten, Red-Clustering ist im Average besser
    * [ ] Plane noch graphen zu einem Bild zusammen zu schmelzen
    * [ ] Vielleicht mal mit Min-Cost-Flow probieren (Capacity Scaling)


#### Nach der Besprechung
* [ ] Regeln zum schreiben von Knuth durchlesen
* [ ] Technisches Schreiben von Peter Rechenberg suchen (in)



</br> 


---
### To-Dos







---
### Notizen zum Thema/Code
Beispiel für einen Max-Flow in Lemon: https://gist.github.com/huanyud/45f98d8bf8d6df66d3e7ab3e9a85af90

!! Lemon Lib ist sehr einschränkend was auslagern in Funktionen betrifft !!


#### Versionen von Sprachen und Libraries
* MatPlotLib: 3.8.0
* Numpy: 1.26.4
* Pandas: 2.2.1
* pip: 23.3.1
* Python: 3.11.8








---
#### Daten
* Diabetes:
    * Punktwerte: age, time in hospital
    * Fair-Attribut: gender (Verhältniss: Male 47055 / Female 54708 ≈ 0.86)
        * Es gibt genau 3 Unknown von 101766 Instanzen
            * -> Rausschmeißen?
    * Sample size: 1000
    * ~~Wird nicht repoduzierbar sein, da es sich bei den Referenzierten Daten lediglich um die Messungen handelt und sonst keine Patientendaten vorhanden sind. Auch sind nur die Daten von 70 Patienten dabei, was einiges weniger ist als 1000~~
* Bank calls:
    * Punktwerte:  age, balance, duration of call (Bereitsteller der Daten warnt vor der Verwendung von duration, aber für Benchmarking ok)
    * Fair-Attribut: marital ~~status (married <-> not married [einige Möglichkeiten] (wähle mal Divorced, Never-Married und Widowed als not married))~~ es gibt single, married und divorced. Zahle single und divorced zusammen (Verhältniss: 27214 married / 17997 not-married ≈ 1.51)
    * Sample size: 1000
    * Wähle `bank-full.csv`
        * Größerer Datensatz um selbst besser Randomisiert zu Samplen
        * nicht additional, da es sich um Metadaten und nicht um anrufspezifische Daten handelt
        * Sind sortiert nach Datum
* Census:
    * Punkwerte: age, fnlwgt(erklärung adult.names), education-num, capital-gain, hours-perweek
    * Fair-Attribut: gender (Gibt nur Spalte Sex) (Verhältniss: Male 21790 / Female 10771 ≈ 2.02)
    * Sample size: 600
    * Es existiert ein Train-Test-Split, für mich irrelevant 
    * --> wähle die Traindaten -> `adult.data`

</br></br></br>










---
## Hauptaufgaben/Plan

* [x] Gitprojekt aufsetzen
    * [x] Projektstrukur anlegen
    * [x] ersten C++ Code schreiben
    * [x] Auf GitHub hochladen
* [x] Irinas Arbeit Lesen
    * [x] Gelesen bis S.13
* [x] Gonzalez implementieren
* [x] Ein- Ausgabe normen
* [x] Subsamples machen
* [x] Skript für automatisches Testen
* [x] Linken der Libary
* [x] Daten reproduzierbar aus Paper? *so halb irgendwie*
* [x] Gozalez soll auch Zentren zurückgeben
* [x] Danielgespräch Liste
    * [x] Zentrendistanz bei Wahl auf 0 setzten
    * [x] Liste um Zentren zurück zu geben
    * [x] Matching/Flussalgorithmen durchlesen `LibLemon`
        * Max Flow (PreFlow Alg)
        * Ins Repo mit rein packen
    * [ ] ~~Sanaty-Check (Distanzen zu Zentrum mit Max Radius Gegenchecken)~~
* [x] Diabetes Datensatz hinzufügen
* [x] Samplesize an paper anpassen anpassen
* [x] Laufzeitmessung
* [x] Erste Zeilen für Bachelor-Arbeit verfassen
* [x] Redclusring impementieren und Testen
* [x] Fast-Anchor-Clustering
    * [x] Fairlettfinder anpassen
    * [x] Neue Clusteringklasse schreiben
    * [x] Testen des Algorithmus
    * [x] Vergleichen der verschiedenen Algorithmen



--- 
### Als Nächstes
* [ ] Schreiben
    * [ ] Weiter an Latex-Text schreiben


</br></br></br>






---
## Quellen
### Algemeine Links
* Paper "Fair Clustering Through Fairlets" von Flavio Chierichetti, Ravi Kumar, Silvio Lattanzi, Sergei Vassilvitskii https://arxiv.org/abs/1802.05733
    * Dataset: Diabetis (Falsch Zitiert): https://archive.ics.uci.edu/dataset/34/diabetes
        * GitHub Dataset: https://github.com/guptakhil/fair-clustering-fairlets/blob/master/data/diabetic_data.csv
    * Dataset: Diabetis (richtiger): https://archive.ics.uci.edu/dataset/296/diabetes+130-us+hospitals+for+years+1999-2008
    * Dataset: Zensus: https://archive.ics.uci.edu/dataset/2/adult
    * Dataset: Bank Telefon: https://archive.ics.uci.edu/dataset/222/bank+marketing

</br></br></br></br></br>




















---
## Logging
* Di: 17.10
    * Gespräch mit Melanie in dem das Vormat der Bachelorarbeit etwas besprochen wurde
    * Pad aufsetzen um Notizen zu machen
    * Belesen zum Thema verbinden von C/C++ und Python
* Mi: 18.10
    * Erster Entwurf der BA von Irina geschickt bekommen
* Mo: 23.10
    * Irinas Arbeit angefangen zu lesen (bis S. 13 gekommen)
* Fr: 27.20
    * Irinas Arbeit weiter lesen im Zug
* Mo: 30.10
    * Erster Code in C++ anschauen
* Do: 2.11
    * Umkopieren des Rumprobiercodes in geeignetes Verzeichniss
    * Anlegen des Git-Hub-Repos
* Fr: 3.11
    * Informieren über File I/O
    * Bisschen versucht rumzucoden
        * wenig erfolgreich
* Mo: 6.11
    * Weiter an File I/O rumprobiert
        * Diesmal erfolgreich Text eingelesen und wiedergegeben
            * Nächstemal vielleicht mit eingabe, welche Datei eingelesen werden soll
* Di: 7.11
    * [x] Treffen mit Melanie und Daniel zur Besprechung
* Mo: 13.11
    * Versucht GitLabs mit Github zu koppeln (erfolglos...)
* Di: 14.11
    * Erfolgreich den Doppelpush zwischen GitLabs und GitHub eingerichtet
    * erstes sichten der Daten [Diabetes sieht nicht so gut aus für den Anfang]
    * Versucht Euklidische Punkte als Klasse zu implementieren
        * leider nicht weit gekommen, da immer noch Speicherfehler auftreten
            * IDE neustarten hilft -> nicht deterministisch...
* Mi: 15.11
    * Fehlersuche nach dem Speicherfehler
        * liegt an den deletes. Fehler tritt nach Ende der Main auf
* Fr: 17.11
    * Weiterentwicklung der Punkteklasse (jetzt auch mit Farbe)
    * Umsteigen von char* zu strings
    * Python-Skript geschrieben um Punkte zu generieren
        * Dimensionen und Farbauswahl wählbar
* Mo: 20.11
    * Alles final auf Strings umgestellt
    * in den Header-Dateien immer `using namespace std;` dazugepackt
    * Parser um Punkte einzulesen geschrieben
        * Kann Punkte beliebiger dimensionalität einlesen
        * Format ist gleich dessen, welches mein Python-Skript produziert
* Di: 21.11
    * MakeFile für Projekt angelegt
    * einige Compiler-Warnings behoben
    * vergeblich versucht Linux zum laufen zu bekommen
        * Amydia (StellarBuntu) booted einfach in einen Blackscreen
    * Linux doch zum Laufen bekommen
        * Aktuell nur über PS/2 angeschlossene Tastatur möglich Linux zu booten
        * Vieles noch installiert
        * Noch kein Pushen nach Git-Lab möglich
            * Bleibt noch zu testen
    * Erste Versuche auch neue VM für den Laptop aufzusetzten und diese zu syncen mit Github
        * noch nicht erfolgreich
* Mi: 22.11 **(Wie man Git Setup macht)**
    * Erfolgreich GitLab Zugang gelegt
    * Lesezeichen auf StellarBuntu angelegt
    * Übertragen des Pads auf das Repo zum Backup
    * Github & GitLab Zugang für Lena-Bachelor-VM
    * Beide Repos geklont und synced
    * GitHub-Desktop auf VM installiert 
* Fr: 24.11
    * Eclipse Makefile Project auf Lena Aufgesetzt
* Sa: 25.11
    * Eclipse aufsetzten in StellarBuntu
* Mo: 27.11
    * Weiter neues Projekt mit bereits vorhandenem Füllen
    * Builddirektory auf Hauptprojekt umgestellt. So keine Blöde Directory-Navigation
        * Bei der Runconfig auf Zahnrad -> Build-Settings -> Build in Project Directory
            * Dort kann man auch die Makebefehle anpassen für build und clean
                * Vielleicht selbes für Run selber festlegen
        * Dementsprechend Makefile angepasst
        * Muss noch genau so auf Amydia angepasst werden
        * Makefile so angepasst, das Programm selben namen wie Projekt hat. Dadurch funktioniert auch die Runconfiguration
    * Run-Config auch angepasst, sodass Run selbst auch läuft
        * Bei der Runconfig auf Zahnrad -> in C/C++ Application eintragen "Fair-Clustering"
        * Merke: Normale Config kann Build einstellen, mit Postfix den Run einstellen
* Sa: 2.12
    * Build und Runconfig eingestellt wie auf Laptop
    * Zusätzliche Regel für die Buildconfig eingestellt
        * Selber Ort wie oben: make -> make build
        * Run Funktioniert nur, wenn Run-Config ausgewählt
    * Formatierung der Klammern vereintlicht
    * Angefangen Gonzalez zu implementieren (und debuggen)
        * Tatsächlich fertig geworden
        * Erste Tests sehen vielversprechend aus
    * Möglichkeit eingebaut die geclusterten Punkte als CSV auszugeben für besseren Datentransver zwischen Programmen
        * CSV begint mit `maxRadius,x`
        * Dann jede Zeile:`dimension,isCenter,clusternum,color(Int),coord1,coord2,...,coordN`
    * Pyhonskript zur Darstellung der Cluster geschrieben
        * Liest csv ein
            * Schaut nach ob am anfang der CSV `maxRadius,'num'` steht und zeichnet dementsprechend einen Kreis
        * Plottet Punkte mit Zentrenmarkierung
            * Farbe kann Cluster oder Grundfarbe sein
            * Radius Variabel mit dabei
        * Getestet mit verschiedenen Clustergrößen
* Di: 5.12
    * [x] Treffen mit Daniel
        * [ ] Zentrendistanz bei Wahl auf 0 setzten
        * [ ] Liste um Zentren zurück zu geben
        * [ ] Matching/Flussalgorithmen durchlesen `LibLemon`
            * Max Flow (PreFlow Alg)
        * [ ] Sanaty-Check (Distanzen zu Zentrum mit Max Radius Gegenchecken)
* Fr: 8.12
    * Doch nochmal neue VM Aufsetzen, da alte einfach zu klein wird. Außerdem neueres Betriebsystem
        * [x] Iso Laden und in VBox aufsetzen
        * [x] VSCode installieren
        * [x] C-Compliler Checken
        * [x] Git Hub Desktop runterladen
        * [x] Git Hub und Git Lab ssh-keys einrichten
        * [x] Push-Config richtig machen
        * [x] Lesezeichen machen
        * [x] Eclipse installieren
        * [x] Anaconda Installieren
            * [x] Gucken ob Pythonskript läuft
* Di: 12.12
    * Nochmal Chierichetti-Paper anschauen, und überlegen, wie ich subsample
    * Anmerkung, bei den Numerischen Werten ist geschrieben `such as` was nicht ausschliest, dass sie noch weitere nummerische Werte benutzt haben
        * Diabetes:
            * Punktwerte: age, time in hospital
            * Fair-Attribut: gender (Verhältniss: --- TO-DO ---)
            * Sample size: 1000
            * Wird nicht repoduzierbar sein, da es sich bei den Referenzierten Daten lediglich um die Messungen handelt und sonst keine Patientendaten vorhanden sind. Auch sind nur die Daten von 70 Patienten dabei, was einiges weniger ist als 1000
        * Bank calls:
            * Punktwerte:  age, balance, duration of call (Bereitsteller der Daten warnt vor der Verwendung von duration, aber für Benchmarking ok)
            * Fair-Attribut: marital ~~status (married <-> not married [einige Möglichkeiten] (wähle mal Divorced, Never-Married und Widowed als not married))~~ es gibt single, married und divorced. Zahle single und divorced zusammen (Verhältniss: 27214 married / 17997 not-married ≈ 1.51)
            * Sample size: 1000
            * Wähle `bank-full.csv`
                * Größerer Datensatz um selbst besser Randomisiert zu Samplen
                * nicht additional, da es sich um Metadaten und nicht um anrufspezifische Daten handelt
                * Sind sortiert nach Datum
        * Census:
            * Punkwerte: age, fnlwgt(erklärung adult.names), education-num, capital-gain, hours-perweek
            * Fair-Attribut: gender (Gibt nur Spalte Sex) (Verhältniss: Male 21790 / Female 10771 ≈ 2.02)
            * Sample size: 600
            * Es existiert ein Train-Test-Split, für mich irrelevant 
            * --> wähle die Traindaten -> `adult.data`
    * Wiki in Markdown eingerichtet
* Mi: 13.12
    * 	[x] Mail an Daniel wegen fehlenden Diabetes-Daten
    * 	Daten aus dem Git-Repository, welches Daniel gefunden hat holen
    * 	In Laptop-VM jetzt erstmal auf VSCode Umgestiegen.
        * 	Funktioniert grade ählich gut wie Eclipse, aber ohne die Config-Probleme
    * 	Daten in richtige Ordnerstruktur gepackt
        * 	Bereits benutzte Pfade in Programmen geändert
    * 	Main-Programm Pfade für input- und output-File werden über die Konsole eingelesen
        * 	Main entsprechend angepasst
        * 	Shellskript könnte jetzt Programm mehrfach mit verschiedenen Daten aufrufen
            * 	Es fehlen noch andere Daten wie Algorithmenauswahl und Clusterwahl
* Sa: 16.12
    * Commandozeilen-API anfangen
        * Gozalez mal richtig benannt
        * API erstmal vorgeschrieben
* So: 17.12
    * Bash-Skript AlgFeeder
        * Kann benutzt werden um den Algorithmus mehrfach automatisiert aufzurufen
        * Nimmt Eingangsdaten, Output-Ordner, Maximale Anzahl der Cluster und hat sogar eine Helperfunktion
    * API Branch in main Branch gemerged
    * Auto-Merge Testen auf beiden Repos
        * Erfolgreich
    * Erneuertes Log hochgeladen
* Mo: 18.12
    * Überflüssige Outputdaten gelöscht (Pathtesting)
    * Weg-Plan erstellen was jetzt als nächstes kommt
* Di: 19.12
    * Angefangen mit DataCleaner-Skript
        * Kann schon die Zensusdaten und die Bankdaten auf csv normalisieren
        * Zählt die Verhältnisse des Fairen Attributes
    * Mail an Daniel wegen schlechter Reproduzierbarkeit des Chierichetti Papers
* Mi: 20.12 
    * Weiter mit DataCleaner
        * Aufgefallen, das ich bei Bank-Daten die Falsche Tabelle genommen habe, deswegen schlechtes martial-Feature
        * Leichtes Feature-Engeeniering um Binäre-Fair-Attributes zu bekommen
        * CleanedData wird jetzt gespeichert
        * Anfänge die Subsamples zu erzeugen
* Mi: 3.1
    * Weiter mit DataCleaner
        * Deterministisch Subsamples erzeugen
        * **Designentscheidung: disjunkte Samples**
    * Subsamples werden jetzt ohne Probleme erzeugt
    * PointParser mehr auf CSV des Pythonskripts umkrempeln
* Fr: 5.1
    * Makefile an neue Testdaten rangelassen
    * Gonzalez vom Object zum Namespace gemacht
    * Struct für Rückgabe von Gonzalez gebaut
        * Struct enthält Deep-Copy von Punkten
        * Gewählte Zentren
        * Max Radius
    * Fixen des Punkteparsens, da das nicht mehr so gut funktioniert (Problem mit Leerzeilen)
* Sa: 6.1
    * AnalyzerSkript angefangen
        * Punkte-Handling in ein eigenes Modul geschoben für bessere übersicht
        * Angefangen Shell-Commands über Python zu benutzen
    * TO-DO: Einlesen + Analyse
    * Iteratives ausführen des Shell-Skriptes
* So: 7.1
    * Analyzerskript weitermachen
        * Skript kann jetzt Generisch mehrere Files einlesen
            * Zusammensetzen von Datenpfad
            * Liste aus Listen für Radien
        * Erste Visuelle Ausgabe
            * Erst von einem File
            * Dann von mehreren Daten mit Mean und Min/max
    * Analyse bisher nur von Bankdaten
* Mo: 8.1
    * [x] Treffen mit Daniel
    * Daten auf dem Laptop erzeugen
    * Graph mit dem aus dem Paper vergleichen -> sieht gut aus
        * Es fällt auf, dass die Daten aus dem Paper eher der min-Linie annähern
    * Analyse auch für die Zensus-Daten
    * Refactoring des Analyseskripts
    * Anfangen die Lemon Libary zu lesesn
* Fr: 12.1
    * Plan wieder erstellen
    * Arbeit von Irina angefangen zu lesen
* So: 14.1
    * Diabetes Daten vernünftig machen
        * Erste Analyse
        * Subsamples erzeugen
        * Age zu numerischen Wert machen?
* Di: 16.1
    * Irinas Arbeit nochmal weiterlesen
    * Diabetes-Daten in Analyzer mit aufnehmen
    * Erstes Timing probiert
        * Tipp: time.perf_counter_ns()
* Mi 17.1
    * Vortrag von Irina besucht
    * Timing verbessert
    * Lemon Libary angefangen zu installieren
        * Nach diesem Guide: 
            * [Install](https://lemon.cs.elte.hu/trac/lemon/wiki/InstallLinux)
            * [How to Compile](https://lemon.cs.elte.hu/trac/lemon/wiki/HowToCompile)
        * Erstes Testskript sieht gut aus
        * Libary wird jetzt über das installierte benutzt und nicht das Lokale
* Do 18.1:
    * Bildpfade Repariert
        * -> Windows mag keine ":"
    * [x] Treffen mit Daniel und Melanie
    * Normalisierung der Daten auf [-1, 1] gelungen
        * Auswertung sieht nicht Signifikant anders aus
* Fr 19.1:
    * Nochmal linken gegen die kompilierte Libary probieren
* Di 23.1
    * Vorlage für Bachelorarbeit runterladen und anschauen
* Do 25.1
    * Latex auf Home-Ubuntu installieren
    * Vorlage aufräumen
* Fr 26.1
    * Latex vorlage weiter aufräumen
        * Eigene Kapitel anlegen
    * Autoanalyzer Clue-Methode
        * Die 3 einzelnen Graphen werden jetzt am Ende zu einem großen Bild zusammengepackt
        * Bild in Latex eingefügt
    * Abgefangen Zitierungen rauszusuchen
* Mi 7.2:
    * Zitierungen weiter machen
* Fr 9.2:
    * Erste Zeilen zur Data-Cleaning Pipeline schreiben
    * Ersten entwurf an Daniel und Melanie schicken
* Sa 17.2:
    * Erste Max-Flow Experimente
        * Alle Libary-Headder die von Testprogramm verwendet werden zu Relativen Pfaden umgeschrieben
    * Dynamisch aufgebauter Bibatiter Graph mit Flow berechnet
* Mi 21.2:
    * Erste Versuche den Max-Flow Modularer zu gestalten
        * Einzelne Abschnitte in Methoden unterteilen
        * Dafür Eigene Struct erstellen um Daten um den Graphen zu speichern
            * Probleme, da man die Lemon-Library Sachen nicht normal zu Variablen zuweisen kann
            * Probleme, da manche Variablen nicht uniitialisiert sein können
* Mo 26.2: 
    * Weiter versucht die Graph-Struct zum laufen zu bringen
        * Lemon Lib ist sehr einschränkend. Befürchte ich muss alles in einer Methode machen
* Di 27.2: 
    * Erneut versucht die Max-Flow Berechnung in Funktionen aufzuteilen
        * Es scheint zu Funktionieren. Bedingungen
            * **Der Graph und die CapacityMap dürfen nicht im Struct sein**
            * **Alle Funktionsaufrufe brauchen Graph, CapacityMap und GraphData als Parameter**
            * **Alle Davon müssen wegen Scope als Referenz übergeben werden:** 
            ```cpp
            void buildBipatiteGraph(Graph&, CapacityMap&, GraphData&)
            ```
    * Erfolgreich Sukzessive einen Bipatiten Graphen aufgebaut mit unterteilung in einzelne Methoden
* Mi 28.2: 
    * Flowzugriff einzelner Kanten
        * Funktioniert über die Referenzen in der Vector-Struktur auch GraphData
    * Weitere Daten aus den Kanten ablesen
        * Kann jetzt nicht nur den Flow, sondern auch die Id sowie die anliegenden Nodes abrufen 
    * Fairlettalgorithmus in Textform angefangen
* Do 29.2:
    * Fairlettalgorithmus in Textform soweit fertig gemacht
    * Pullrequest geschrieben
* Fr 1.3:
    * Pullrequest gemacht
    * Mit Melanie über ersten Bachelor-Entwurf gesprochen: Sieht gut aus
    * Latex endlich zentriert
* Mo 4.3:
    * Daniel geschrieben wegen Anmeldung 
        * Warte noch auf das "Go"
    * Angefangen die Dateien für den neuen Algorithmus anzulegen
        * Headder Datei mit voraussichtlich benötigten Methoden gefüllt
        * Neue Dateien zu Makefile hinzugefügt, sodass sie direkt mitkompiliert werden
    * Punkteklasse so modifiziert, dass sie jetzt auch eine FairlettID speichert
    * Implementierung der Methode `double fairlettFinder::calculateMaxRadius()`
* Di 5.3:
    * Debuggingmethoden einführen
    * Repository ein wenig aufgeräumt
        * Alle Binaries in .gitignore
        * alte eclipse Dateien gelöscht
        * unnötige vscode Sachen gelöscht
    * Methode für Knoten in Graph einzuführen schreiben und testen
* Do 7.3:
    * Antrag für Bachelor-Arbeit gestellt
    * Latex Algorithmenbeschreibung angefangen
    * Angefangen mit Methode zum hinzufügen der Kanten in den Graphen zum finden der Fairletts
* Fr. 8.3:
    * Repo auf Lenabuntu wieder geflickt
    * ColorFilter angefangen
* Sa. 9.3:
    * Laptop neu eingerichtet
        * Notwendige Sachen installiert
        * ssh Keys eingerichtet
        * git initialisiert
        * Latex aufgesetzt
* Mo 11.3:
    * Python richtig eingerichtet
    * Plötzlich wirft der Kompiler Warnings, dass elemente aus der Lemon-Library depricated sind
    * Weitere Funktionen ausgeschrieben und getestet
        * Es kann jetzt ein kompletter Graph aufgebaut werden
        * Der Fluss kann berechnet werden
        * Eine Methode checkt ob bei einem Radius ein Matching möglich ist
            * ggf wird Rot und Blau getauscht
        * Alle Radien werden durchprobiert um den optimalen zu finden
* Di 12.3:
    * [x] Besprechung mit Daniel
    * Python-Enviroment festhalten
* Mi 13.3:
    * Library neu Installieren (Auf Laptop)
        * Entpacken `unzip lemon-1.3.1.zip`
        * in Ordner gehen `cd lemon-1.3.1/`
        * neuen Build-Ordner erstellen `mkdir build`
        * rein gehen `cd build/`
        * mit cmake Dateien erstellen `cmake -DCMAKE_INSTALL_PREFIX=/home/stellarbyte/Installationen/Lemon-Lib ..` (hoffe mal das geht auf meinem Hauptrechner auch so einfach)
        * installieren `make install`
    * Headerfiles an die neuen Includes anpassen
    * Const an alles wo es möglich ist kleben
    * Lemon Lib in den Zitierungen hinzufügen
    * Fairlett-Code in Main Mergen
* Do 14.3:
    * Lemon Lib auf Hauptrechner installieren
    * Hauptskript in API und Testing getrennt
        * In Testing-Skript alle Tests in einzelne Methoden ausgelagert für bessere Übersicht
    * ~~Angefangen mit Methode~~ um Fairletts zu Markieren **Abgeschlossen!**
        * Mapper geschrieben, welcher IDs auf Index in Liste berechnet
        * Methode zum Aufbauen des Graphens ausgelagert
        * Methode geschrieben, der den wahren Index eines Punktes berechnet und diesen dann als Fairlett Markiert
            * Wahrscheinlich kann man das noch etwas besser strukturieren
    * Fairlett-marks getestet
* Mo 18.3:
    * Graph und Maxflow aus Fairlettfinder getrennt
        * Die Fairlett-Finder-Datei wurde sehr groß und ich habe jetzt die ganze Graphlogik in eine eigene Datei kopiert
    * Angefangen mit Red Clustering
        * Clustern aber nur mit Roten Punten
            * Erst Rot filtern
            * Gonzalez machen
            * Echte Punkteliste aktuallisieren
        * Rückgabe-Struct auf und abbau
        * ACHTUNG: Zentren werden noch nicht richtig zurückgegeben
* Di 19.3:
    * Rückgabe der Zentren gefixt
    * Fair-Red-Clustering Theoretisch abgeschlossen
        * Problem: Ausprobieren der Fairlett-Radien braucht extrem Lange
            * Der Maxflow checkt pro Sekunde knapp 20 potentielle Radien
            * Bei 236.544 Radien dauert das etwa 11.830 sec = 197 min 3,29 h
            * Mit Daniel darüber gesprochen
                * Tests zur Laufzeit durchgeführt
                * Meiste Zeit geht drauf beim Hinzufügen der Kanten -> noch keine Ahnung wie man das Efizienter machen kann
    * Weiter an API gebastelt
        * Main-Skript kann jetzt theoretisch mit verschiedenen Algorithmen umgehen
        * AlgFeeder an neue Schnittstelle angepasst
        * Kompilieren der Binary aus FeederSkript gelöscht
            * braucht sehr viel Zeit bei jedem neuen Aufruf
            * ist jetzt im Pythonskipt als eigene Methode für ganz am Anfang
* Mi 20.3:
    * Benchmarking Performance
        * Weiteres rumprobieren mit neuen Tools (perf) was denn jetzt so lange immer dauert
        * Einige Screenshots mit verschiedenen Punktemengen
    * Improving Performance
        * Test mit einer Look-Up-Matrix für die Distanzen
        * Tests zeigen einen Speedboost von knapp 4
* Di 26.3:
    * Treffen mit Daniel
* Do 28.3:
    * Binäre Suche beim finden des Optimalen Fairlett-Radius implementiert
        * Unglaubliche Algorithmenbeschleunigung
    * Viel den Code aufgeräumt
        * Unnötige Kommentare und Code entfernt
    * Autoanalyzer auf neuen Algorithmus angepasst
        * Man kann jetzt zusätzlich zu den Algorithmus als Input wählen
* Fr 29.3:
    * Mergen des neuen Algorithmus in Main
    * AutoAnalyzer mal mit großen Daten starten lassen
* Di 2.4:
    * ofByOneError bei der Binären Suche gefixt
    * Einige Debuging prints und imports von der Zeitmessung gelöscht
    * Process-Bar erweitert
        * Einige cleandere Ausgaben
        * Lässt sich jetzt zur Compilezeit bestimmen ob man sie haben will, oder nicht
    * Latex Datensatztabelle nicht mehr Blocksatz
* Mi 3.4:
    * Angefangen mit Fast-Anchor Clustering
        * Markdowndatei mit Algorithmus gefüllt
        * Dateien erstellt wie beim Red-Clustering
        * Methodennamen angepasst, hinzugefügt und gelöscht
        * Namespaces angepasst
        * Methode in Colorpoint geschrieben zum Filtern von Fairlett-Members
        * AnchorID in Colorpoint hinzugefügt
* Do 4.4:
    * Methode zur berechnung der Anker hinzugefügt und getestet
        * Verbessert mit einer Lookup-Matrix für die Distanzen
    * Berechnung des Max-Flows an Anker-Kriterium angepasst
    * Radius-Checker an Anker-Kriterium angepasst
    * Radius-Finder an Anker-Kriterium angepasst
* Fr 5.4:
    * Makefile-Rule erstellt um Algfeeder zu testen
    * Makieren der Fairletts an Anker-Kriterium angepasst
    * Methoden Zuweißen der Cluster anhand ihres Ankers 
    * Main-Klasse angepasst das sie jetzt auch den Fast-Anchor Algorithmus benutzen kann
    * Erste Tests mit QuickFairletChecker sehen gut aus
* Di 9.4:
    * [x] Gespräch mit Daniel
    * Fast-Anchor weiter Testen
    * Bugfix von Fast-Anchor
        * Falsche Annahme über Sortierung der Zentren zur Clusternummer
* Mi 10.4:
    * Erste größere Sample-Tests mit Fast-Anchor-Clustering
    * An einer Stelle Steigt der Radius Trotzdem trotz mehr Cluster
        * Fairlettbildung macht Radius kaputt
            * bank sample3 Punkte:
                * 300
                * 813
    * Umforulierung des Data-Cleaner Kapitels angefangen
* Fr 12.4:
    * Latex - Gonzalezalgorithmus auschreiben
    * Latex - Fairletts anfange
* Sa 13.4:
    * Korrekturen von Korrekturlesen zu verbessern
* Di 16.4:
    * Latex - Red Clustering ausformulieren
    * Latex - Red Clustering Algorithmen schreiben
    * Latex - Fast-Anchor Clustering anfangen
* Mo 22.4:
    * Angefangen den Autoanalyzer zu teilen in 
        * Skript das Algorithmen ausführt und Ergebnisse speichert
        * Skript das die ergebnisse einliest und Graphen daraus erzeugt 
* Di 23.4:
    * Analyzer-Pipeline noch verbessern
        * Einen kompletten run hinbekommen
        * Erste Versuche Vergleichsgraphen zu erzeugen
    * Latex - Algorithmen Kapitel soweit fertig gemacht
    * Latex - Angefangen in der Auswertung das Center-Aware Problem zu erklären






































