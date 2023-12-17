# Bachelor-Arbeit Notizen

## Allgemeine Notizen
### Termine
* [x] Treffen mit Melanie und Daniel am 7.11 um 10:30
* [x] Treffen mit Daniel am 20.11 um 15:00
* [x] Treffen mit Daniel am 5.12 um 10:30
* [ ] Treffen mit Daniel (Melanie?) am 8.1 um 13:00
### To-Dos
* [x] Gitprojekt aufsetzen
    * [x] Projektstrukur anlegen
    * [x] ersten C++ Code schreiben
    * [x] Auf GitHub hochladen
* [x] Irinas Arbeit Lesen
    * [x] Gelesen bis S.13
* [x] Gonzales implementieren
* [x] Ein- Ausgabe normen
* [ ] Subsamples machen
* [ ] Skript für automatisches Testen
* [ ] Linken der Libary
* [ ] Daten reproduzierbar aus Paper?
* [ ] Gozalez soll auch Zentren zurückgeben
* [ ] Danielgespräch Liste
    * [ ] Zentrendistanz bei Wahl auf 0 setzten
    * [ ] Liste um Zentren zurück zu geben
    * [ ] Matching/Flussalgorithmen durchlesen `LibLemon`
        * Max Flow (PreFlow Alg)
    * [ ] Sanaty-Check (Distanzen zu Zentrum mit Max Radius Gegenchecken)

### Notizen zum Thema/Code
* POpen um Konsolenbefehle auszuführen mit Python

## Hauptaufgaben/Plan
* [x] Möglichkeit Punkte einzulesen von Datei
    * [ ] Punkte des Papers
* [x] Gonzales Implementieren
* [x] Erste Auswertung mit Python
* [ ] Reinigen der Quelldaten auf mein Format
    * [ ] Subsamples machen



## Quellen
### Algemeine Links
* Paper "Fair Clustering Through Fairlets" von Flavio Chierichetti, Ravi Kumar, Silvio Lattanzi, Sergei Vassilvitskii https://arxiv.org/abs/1802.05733
    * Dataset: Diabetis: https://archive.ics.uci.edu/dataset/34/diabetes
        * GitHub Dataset: https://github.com/guptakhil/fair-clustering-fairlets/blob/master/data/diabetic_data.csv
    * Dataset: Zensus: https://archive.ics.uci.edu/dataset/2/adult
    * Dataset: Bank Telefon: https://archive.ics.uci.edu/dataset/222/bank+marketing

### Zizierungsvorgaben
* Bank Telefon:   [Moro et al., 2011] S. Moro, R. Laureano and P. Cortez. Using Data Mining for Bank Direct Marketing: An Application of the CRISP-DM Methodology. In P. Novais et al. (Eds.), Proceedings of the European Simulation and Modelling Conference - ESM'2011, pp. 117-121, Guimarães, Portugal, October, 2011. EUROSIS.

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
    * Angefangen Gonzales zu implementieren (und debuggen)
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
            * Fair-Attribut: marital status (married <-> not married [einige Möglichkeiten]) (Verhältniss: --- TO-DO ---)
            * Sample size: 1000
            * Wähle `bank-full.csv`
                * Größerer Datensatz um selbst besser Randomisiert zu Samplen
                * nicht additional, da es sich um Metadaten und nicht um anrufspezifische Daten handelt
                * Sind sortiert nach Datum
        * Census:
            * Punkwerte: age, fnlwgt(erklärung adult.names), education-num, capital-gain, hours-perweek
            * Fair-Attribut: gender (Verhältniss: --- TO-DO ---)
            * Sample size: 600
            * Es existiert ein Train-Test-Split, für mich irrelevant 
            * --> wähle die Traindaten -> `adult.data`
            * 
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


## Wikis
### Git Setup
1) agend für ssh starten `eval $(ssh-agent -s)`
2) schauen ob ssh-Key vorhanden ist `cd ~/.ssh/ && ls`
3) **Falls Key nicht vorhanden:** 
    5) In ssh-Ordner gehen `cd ~/.ssh/ && ls`
    5) `ssh-keygen -t ed25519 -C "krollmann.carsten@gmail.com"`
4) code holen und kopieren `cat ~/.ssh/id_ed25519.pub` (oder anderes Keyfile)
5) In richtigen Ordner gehen
6) in User-Einstellungen ssh-key mit gutem Namen anlegen
    7) Github: Profil -> Settings -> SSH und GPG keys -> SSH keys (New SSH key)
    8) GitLab: Profilbild -> Edit Profile -> SSH Keys -> Your SSH keys (Add new key)
8) Verbindung Testen mit `ssh -T git@gitlab.cs.uni-duesseldorf.de` oder `ssh -T git@github.com`

### Github Desktop mit Sync
1) In vernünftigen Downloadordner gehen
2) Download: `sudo wget https://github.com/shiftkey/desktop/releases/download/release-3.1.1-linux1/GitHubDesktop-linux-3.1.1-linux1.deb`
3) Install: `sudo dpkg -i GitHubDesktop-linux-3.1.1-linux1.deb`
4) Sync der Repos
    5) Beide Repos händisch klonen über SSH in geeignete Ordner
    6) in beiden Repos die Datei in `Repo/.git/config` öffnen
    7) in die GitHub Config den Abschnitt unter `[remote "origin"]` den Teil von GitLab kopieren
8) Das Github Repo mit GitHub-Desktop öffnen

















