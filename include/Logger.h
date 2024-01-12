//Barbato Alberto 2073961
#include <fstream>
#include "Position.h"
#include "EventType.h"
//Classe utilizzata per gestire la stampa
//su file e su console con una chiamata a funzione unificata
class Logger {
public:
  //inizializza l'ostream con un file di default in "data/Gazzettino.txt"
  Logger();

  // Stampa su file e su console in base all EventType Fornito
  //
  // Diversi EventType richiedono diversi parametri aggiuntivi:
  // EventType e tag1(tag del Player giocante in quel momento) sono sempre obbligatori
  // Parametri Extra:
    // PASSAGGIO_VIA: [fiorini: denaro guedagnato al passaggio]
    // TIRO_DADI: [pos1: usato come "wrapper" per il valore del tiro di dadi]
    // ARRIVO: [pos1: usato come posizione di arrivo]
    // ACQUISTO_TERRENO: [pos1: posizione acquisto]
    // COSTRUZIONE_CASA: [pos1: posizione acquisto]
    // COSTRUZIONE_ALBERGO: [pos1: posizione acquisto]
    // PAGAMENTO_PERNOTTAMENTO: [pos1: ""], [tag2: tag del Player Propietario], [fiorini: costo perottamento]
    // SHOW_COMMAND: N/A (NON STAMPA NULLA)
    // FINE_TURNO: N/A
    // ELIMINAZIONE: N/A
    // VITTORIA: N/A
  void log(EventType lt, int tag1, Position pos1 = 0, int tag2 = -1, int fiorini = -1);

private:
  std::ofstream m_output_file;
};