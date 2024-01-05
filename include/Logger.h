//Barbato Alberto 2073961
#include <fstream>
#include "Position.h"
#include "EventType.h"

class Logger {
public:
  Logger();
  //log prende un EventType, il quae ha un numero di paramentri associati ( da Scrivere come commento)
  //TO DO:(La positioc per TIRO_DADI è un wrapper per un intero
  void log(EventType lt, int tag1, Position pos1=0, int tag2=-1, int fiorini=-1);

private:
  std::ofstream m_output_file;
};