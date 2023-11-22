# Bachelor-Arbeit Notizen
## Allgemeine Notizen
### Termine
* [x] Treffen mit Melanie und Daniel am 7.11 um 10:30
* [x] Treffen mit Daniel am 20.11 um 15:00
* [ ] Treffen mit Daniel am 5.12 um 10:30
### To-Dos
* [x] Gitprojekt aufsetzen
    * [ ] Projektstrukur anlegen
    * [x] ersten C++ Code schreiben
    * [x] Auf GitHub hochladen
* [x] Irinas Arbeit Lesen
    * [x] Gelesen bis S.13
* [ ] Gonzales implementieren
* [ ] Ein- Ausgabe normen

## Hauptaufgaben/Plan
* [x] Möglichkeit Punkte einzulesen von Datei
    * [ ] Punkte des Papers
* [ ] Gonzales Implementieren
* [ ] Erste Auswertung mit Python
* [ ] Reinigen der Quelldaten auf mein Format

## Notizen zu einem Thema
* Farbe bei den Punkten hinzufügen

## Quellen
* Paper "Fair Clustering Through Fairlets" von Flavio Chierichetti, Ravi Kumar, Silvio Lattanzi, Sergei Vassilvitskii
    * Dataset: Diabetis: https://archive.ics.uci.edu/dataset/34/diabetes
    * Dataset: Zensus: https://archive.ics.uci.edu/dataset/2/adult
    * Dataset: Bank Telefon: https://archive.ics.uci.edu/dataset/222/bank+marketing

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
* Mi: 22.11
    * Erfolgreich GitLab Zugang gelegt
        1) schauen ob ssh-Key vorhanden ist `cd ~/.ssh/ && ls`
        2) agend starten `eval $(ssh-agent -s)`
        3) code holen und kopieren `cat ~/.ssh/id_ed25519.pub`
        4) In richtigen Ordner gehen
        5) in User-Einstellungen ssh-key mit gutem Namen anlegen
        6) Verbindung Testen mit `ssh -T git@gitlab.cs.uni-duesseldorf.de`
    * Lesezeichen auf StellarBuntu angelegt
    * Übertragen des Pads auf das Repo zum Backup