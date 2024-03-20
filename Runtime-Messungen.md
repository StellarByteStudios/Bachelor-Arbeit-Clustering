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

#### Zeiten
#### Fazit


### Nachschlaten Statt ausrechnen
#### Setup
#### Zeiten