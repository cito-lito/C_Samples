##Newton-Verfahren

Das Newton-Verfahren ist ein Standardverfahren zur numerischen Lösung von nichtlinearen Gleichungen und Gleichungssystemen. Die Idee dieses Verfahrens ist, die Funktion in einem Ausgangspunkt(Xo) zu linearisieren (ihre Tangente bestimmen) und die Nullstelle der Tangente als verbesserte Näherung der Nullstelle der Funktion zu verwenden. Die erhaltene Näherung ist der neue Ausgangspunkt.

X = Xo – (F(x) / F´(x))


Beispiel:

# f(x) = x3 – x – 2

Algorithmus:

Xo eingeben

X1 = Xo

ist F´(x) null? 

ja-→ stop das Programm (mit Rückgabe null)

nein-→ Xo = X1 – F(x) / F´(x)

wiederhole solange (Xo – X1) größer gleich 0.000001(Genauigkeit).

