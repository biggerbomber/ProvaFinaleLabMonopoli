//@barbato alberto 2073961

#include "../include/Logger.h"

//logger.cpp

Logger::Logger(){
  std::cout << "Inizializzazione Logger...\n";
  m_output_file = std::ofstream("../data/Gazzettino.txt");
  std::cout << "Successo\n";
}

void Logger::log(LogType lt, int tag1, int valore,Position pos1, int tag2, int fiorini){

  switch (lt)
  {
  case Logger::PASSAGGIO_VIA:
    std::cout << "- Giocatore " << tag1 << " è passato dal via e ha ritirato 20 fiorini" << std::endl;
    m_output_file << "- Giocatore " << tag1 << " è passato dal via e ha ritirato 20 fiorini" << std::endl;
    break;
  case Logger::TIRO_DADI:
    std::cout << "- Giocatore " << tag1 << " ha tirato i dati e ha ottenuto un valore di " << valore<<std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha tirato i dati e ha ottenuto un valore di " << valore << std::endl;
    break;
  case Logger::ARRIVO:
    std::cout << "- Giocatore " << tag1 << " è arrivato alla casella " << pos1 << std::endl;
    m_output_file << "- Giocatore " << tag1 << " è arrivato alla casella " << pos1 << std::endl;
    break;
  case Logger::ACQUISTO_TERRENO:
    std::cout << "- Giocatore " << tag1 << " ha acquistato il terreno " << pos1 << std::endl; 
    m_output_file << "- Giocatore " << tag1 << " ha acquistato il terreno " << pos1 << std::endl;
    break;
  case Logger::COSTRUZIONE_CASA:
    std::cout << "- Giocatore " << tag1 << " ha costruito una casa sul terreno " << pos1 << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha costruito una casa sul terreno " << pos1 << std::endl;
    break;
  case Logger::COSTRUZIONE_ALBERGO:
    std::cout << "- Giocatore " << tag1 << " ha migliorato una casa in albergo sul terreno " << pos1 << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha migliorato una casa in albergo sul terreno " << pos1 << std::endl;
    break;
  case Logger::PAGAMENTO_PERNOTTAMENTO:
    std::cout << "- Giocatore " << tag1 << " ha pagato " << fiorini << " fiorini a giocatore " << tag2 << " per pernottamento nella casella " << pos1 << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha pagato " << fiorini << " fiorini a giocatore " << tag2 << " per pernottamento nella casella " << pos1 << std::endl;
    break;
  case Logger::FINE_TURNO:
    std::cout << "- Giocatore " << tag1 << " ha finito il turno" << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha finito il turno" << std::endl;
    break;
  case Logger::ELIMINAZIONE:
    std::cout << "- Giocatore " << tag1 << " è stato eliminato" << std::endl;
    m_output_file << "- Giocatore " << tag1 << " è stato eliminato" << std::endl;
    break;
  case Logger::VITTORIA:
    std::cout << "- Giocatore " << tag1 << " ha vinto la partita" << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha vinto la partita" << std::endl;
    break;
  default:
    break;
  }
}
