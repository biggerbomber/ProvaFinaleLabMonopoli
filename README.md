# ProvaFinaleLabMonopoli
 Prova finale Barbato-Casucci-Pinonn
Link Repository : [link][https://github.com/biggerbomber/ProvaFinaleLabMonopoli]

## Introduzione
Benvenuti nel progetto finale dedicato alla riproduzione del gioco da tavolo Monopoly, sviluppato in linguaggio C++. Prodotta da Barbato Alberto, Casucci Leonardo e Pinton Mattia

## Come Avviare
1. Impostare la compilazione utilizando cmake, all iterno di "build" con `cmake ..`
2. Compilare con `make` (Linux/Windows) oppure direttamente dall interno di visual studio
3. in "build" eserguire da terminale il comando `./monopoly <args>` dove args puo essere "human" oppure "computer"

### Attenzione
1. Visto che il cmake è stato impostare con opzioni di compilazione -O2 (come richiesto dal testo), è necessario compilare il progetto senza flag di debug che possono fare conlitto con -O2 (eg -RTF)
2. Riguardo Visual Studio, per avviare il progetto è necessario impostare "monopoly" come progetto di avvio


## Scelte di Implementazione e Problemi di Sviluppo

### Divisione dello sviluppo del codice
Abbiamo deciso di dividere il codice in 3 libreria statiche concettualmente separate:
1. MonoplyGameLib //Barbato Alberto
2. BoardLib //Pinton Mattia
3. PlayerLib //Casucci Leonardo

Questo ha permesso, dopo esserci accordati sulle varie interfacce della classi, di lavorare indipendentemente l'uno dall altro, velocizzando drasticamente lo sviluppo del codice.

### Problemi con Dipendenze Circolari
Durante lo sviluppo, ci siamo trovati di fronte a problemi legati a dipendenze circolari tra le classi del progetto.
La nostra struttura delle classi è stata rivista per ridurre la dipendenza tra di esse e migliorare la modularità del codice.
Inoltre nella fase di debuging abbiamo scoperto memory leak dovuti all utilizzo contemporaneo di dipendenze circolari e smart pointer. Quest ultimi sono stati risolti dopo la revisione delle classi.


### Uso di `endl` anziché `\n`
Abbiamo scelto di utilizzare `std::endl` anziché `\n` per la gestione dei caratteri di nuova riga.
Ci è parso più chiaro, ed inoltre "std::endl" esegue anche il flush del buffer di output, rendendo (teoricamente) il flusso di log più reattivo dal punto di vista dell utente.


### Presenza della Classe Astratta `Player.h`
Abbiamo creato la classe astratta Player.h perché avevamo bisogno di gestire vari tipi di giocatori che si comportano in modi diversi.
Abbiamo riscontrato che l'unica differenza tra un player umano e un bot è la modalità di gestione della cella di arrivo: perciò abbiamo astratto tutto il resto in comune e evitato di duplicare codice inutilmente.

## Requsisti
-1)  Un computer

0)   Una connessione internet

0,5) Compilatore C++ 

1)   Cmake


## Licenza
Questo progetto è rilasciato sotto la licenza BarbCasuPint@TreMosche.

Grazie della lettura.

- 011 Moschettieri