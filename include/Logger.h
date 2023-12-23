//logger.h Barbato Alberto
#include <fstream>
#include "Position.h"

class Logger {
public:
  Logger();
  enum LogType{PASSAGGIO_VIA,TIRO_DADI,ARRIVO,ACQUISTO_TERRENO,
               COSTRUZIONE_CASA,COSTRUZIONE_ALBERGO,
               PAGAMENTO_PERNOTTAMENTO,FINE_TURNO,
               ELIMINAZIONE,VITTORIA};
  static const int PLACEHOLDER = -1;
  //log prende un LogType, il quae ha un numero di paramentri associati ( da Scrivere come commento)
  //TO DO:
  void log(LogType lt, int tag1,int valore=0, Position pos1=0, int tag2=-1, int fiorini=-1);

private:
  std::ofstream m_output_file;
};