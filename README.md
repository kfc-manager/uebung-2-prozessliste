# Aufgabenstellung

Schreiben Sie ein Programm, das mit Hilfe einer doppelt verketteten Liste eine Prozesstabelle realisiert!

Die Elemente der Liste entsprechen den (vereinfachten) Prozessleitblöcken. Pro Prozess werden die Prozess-ID (PID) und die ID des Elternprozesses (parent PID, PPID) gespeichert.

Definieren Sie in dl_proc_list.c einen geeigneten Datentyp (struct) namens dl_proc_list und implementieren Sie die folgenden Funktionen:

- dl_proc_list* dl_proc_list_create() zum Erstellen der Liste
  - Die Liste soll zu Beginn einen Prozess mit PID = 1 und PPID = 0 enthalten.
  
- int dl_proc_list_insert(dl_proc_list* list, int pid) zum Einfügen eines Prozesses mit PID pid in die Liste
  - Die Liste soll dabei stets aufsteigend sortiert sein.
  - Jede Prozess-ID darf höchstens einmal vorkommen.
  - Als neuer Elternprozess wird der Prozess mit der bisher höchsten Prozess-ID festgelegt.
  
- int dl_proc_list_get(dl_proc_list* list, int position, int* pid, int* ppid) zum Abfragen der PID und PPID des Prozesses an der gegebenen Position in der Liste. Die Werte sollen in den Parameteren pid und ppid gespeichert werden.

- int dl_proc_list_remove(dl_proc_list* list, int pid) zum Entfernen des Prozesses mit PID pid aus der Liste
  - Das Löschen des Prozesses mit PID = 1 soll verhindert werden.
  - Die Kindprozesse des zu löschenden Prozesses p erhalten den Elternprozess von p als neuen Elternprozess.
  
- void dl_proc_list_free(dl_proc_list* list) zum Freigeben der reservierten Ressourcen

Implementieren Sie dann ein Programm proctable.c. Es soll das Folgende leisten:

- Über die Kommandozeilenargumente des Programms soll die Prozesstabelle wie folgt manipuliert werden können:
  - Die Kommandozeilenargumente sind als Prozess-IDs (Integer-Werte) zu interpretieren! Verwenden Sie die Funktion strtol zur Umwandlung eines Strings in einen Integer-Wert! Argumente mit dem Integer-Wert 0 werden ignoriert; geben Sie dabei eine entsprechende Warnung aus!
  
  - Prozess einfügen: Ein positiver Integer-Wert stellt einen neuen Prozess dar, der in die Liste eingefügt wird. Das Einfügen von vorhandenen Prozess-IDs ist nicht zugelassen und soll mit einer Fehlermeldung quittiert werden, ohne dass das Programm abbricht.
  
  - Prozess löschen: Ein negativer Integer-Wert löscht den Prozess mit dem entsprechenden positiven Wert der ID aus der Liste. Ist der zu löschende Prozess nicht vorhanden, soll eine Fehlermeldung ausgegeben werden.
  
- Am Ende des Programms soll der Inhalt der Prozesstabelle, also sowohl Prozess-ID und Parent-ID, zeilenweise ausgegeben werden.

Beachten Sie dabei:

- Geben Sie für die Funktionen der doppelt verketteten Liste im Fehlerfall negative Werte und im Erfolgsfall 0 zurück. Falls der Rückgabentyp ein Pointer ist, soll die Funktion im Fehlerfall NULL zurückgegeben.

- Fehler von Bibliotheksfunktionen müssen abgefangen werden. Geben Sie eine entsprechende Fehlermeldung aus (vgl. perror(3))!

- Alle Fehler- und Warnungsmeldungen müssen auf dem Fehlerausgabekanal (stderr) ausgegeben werden.

- Geben Sie allen allozierten Speicher zum Programmende wieder frei!

Beispiel für Programmaufruf und Ausgabe:

![alt text](https://github.com/kfc-manager/uebung-2-prozessliste/blob/main/Screenshot.png?raw=true)
