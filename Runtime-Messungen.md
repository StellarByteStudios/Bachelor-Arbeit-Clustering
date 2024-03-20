# Messen und analysieren der Laufzeit

## Probleme
Bei einer größeren Menge von Punkten braucht das Programm sehr lange. Erste Analysen haben gezeigt, dass vorallem das finden des optimalen Radiuses sehr lange dauert. Dort muss jeder mögliche Radius ausprobiert werden ($\mathcal{O}(n²)$). Für jeden Check müssen nochmal alle Distanzen von allen Paarweisen Punkten abgecheckt werden ebenfalls nochmal $\mathcal{O}(n²)$ wobei wir dann bei $\mathcal{O}(n⁴)$ landen

---
## Tests

### Unmodifizierte Variante
#### Setup
Die Ersten Tests waren mit vielen Prints im Code um die einzelnen Zeiten rauszufriemeln. Hier ein Screeshot der die Zeiten eines einzelnen Checks zeigt (hier wurde mit insgesammt 1000 Punkten gerechnet): ![Screenshot-FineTiming](<Screenshots/Timingausgabe-Red-Clustering (Cutted).png>)

Anschließend habe ich weiter mit Perf getestet einmal mit 100 einmal mit 200 Punkten. Es Folgen die Perf-Screenshots:
**100 Punkte:**
![Screenshot-Perf 100](<Screenshots/Erster Report mit allem ohne Prints.png>)
![Screenshot-Perf 100 Asm](<Screenshots/Erster Report mit allem ohne Prints (Assembly Ausschnitt).png>)


**200 Punkte:**
![Screenshot-Perf 200](<Screenshots/Report (200 Punkte) mit allem ohne Prints.png>)
![Screenshot-Perf 200 Asm](<Screenshots/Report (200 Punkte) mit allem ohne Prints (Assembly Ausschnitt).png>)

#### Perfanalyse unmod
Die Analyse zeigt, das tatsächlich die meiste Zeit verloren geht bei der Berechnung der Potenz welche zum überprüfen der Distanz benutzt wird

#### Zeiten
##### 100 Punkte
* Execution Time getestet mit `time make runTest` (Gonzalez ist mit einbegriffen): user = 0m6,840s;   sys = 0m0,036s
* Checks pro Minute: 
    * Gemessene Zeit fürs Checken: 6.952606 Sec
    * Das sind 3203 µSec pro check
    * 18732.438339 Checks pro minute


##### 200 Punkte
* Execution Time getestet mit `time make runTest` (Gonzalez ist mit einbegriffen): user = 0m53,355s;   sys = 0m0,244s
* Checks pro Minute:
    * Gemessene Zeit fürs Checken: 54.187462 Sec
    * Das sind 9742 µSec pro check
    * 6158.899610 Checks pro minute


##### 300 Punkte
* Execution Time getestet mit `time make runTest` (Gonzalez ist mit einbegriffen): user = 5m1,451s;   sys = 0m3,216s 
* Checks pro Minute:
    * Gemessene Zeit fürs Checken: 285.643795 Sec
    * Das sind 21809 µSec pro check
    * 2751.157779 Checks pro minute

#### Fazit
Die meiste Zeit geht wirklich beim ausrechen, ob eine Kante hinzugefügt werden soll drauf.  
**Idee:** man könnte die Distanzen ein mal berechnen und in einer n x n Matrix speichern


### Nachschlagen statt ausrechnen
#### Setup
#### Zeiten