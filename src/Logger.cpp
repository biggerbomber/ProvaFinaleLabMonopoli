//@barbato alberto 2073961

#include "Logger.h"

//logger.cpp

Logger::Logger(){
  std::cout << "Inizializzazione Logger...\n";
  m_output_file = std::ofstream("../data/Gazzettino.txt");
  std::cout << "Successo\n";
}

void Logger::log(EventType lt, int tag1,Position pos1, int tag2, int fiorini){

  switch (lt)
  {
  case EventType::PASSAGGIO_VIA:
    std::cout << "- Giocatore " << tag1 << " e' passato dal via e ha ritirato 20 fiorini" << std::endl;
    m_output_file << "- Giocatore " << tag1 << " e' passato dal via e ha ritirato 20 fiorini" << std::endl;
    break;
  case EventType::TIRO_DADI:
    std::cout << "- Giocatore " << tag1 << " ha tirato i dati e ha ottenuto un valore di " << pos1.get_valore()<<std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha tirato i dati e ha ottenuto un valore di " << pos1.get_valore() << std::endl;
    break;
  case EventType::ARRIVO:
    std::cout << "- Giocatore " << tag1 << " e' arrivato alla casella " << pos1 << std::endl;
    m_output_file << "- Giocatore " << tag1 << " e' arrivato alla casella " << pos1 << std::endl;
    break;
  case EventType::ACQUISTO_TERRENO:
    std::cout << "- Giocatore " << tag1 << " ha acquistato il terreno " << pos1 << std::endl; 
    m_output_file << "- Giocatore " << tag1 << " ha acquistato il terreno " << pos1 << std::endl;
    break;
  case EventType::COSTRUZIONE_CASA:
    std::cout << "- Giocatore " << tag1 << " ha costruito una casa sul terreno " << pos1 << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha costruito una casa sul terreno " << pos1 << std::endl;
    break;
  case EventType::COSTRUZIONE_ALBERGO:
    std::cout << "- Giocatore " << tag1 << " ha migliorato una casa in albergo sul terreno " << pos1 << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha migliorato una casa in albergo sul terreno " << pos1 << std::endl;
    break;
  case EventType::PAGAMENTO_PERNOTTAMENTO:
    std::cout << "- Giocatore " << tag1 << " ha pagato " << fiorini << " fiorini a giocatore " << tag2 << " per pernottamento nella casella " << pos1 << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha pagato " << fiorini << " fiorini a giocatore " << tag2 << " per pernottamento nella casella " << pos1 << std::endl;
    break;
  case EventType::FINE_TURNO:
    std::cout << "- Giocatore " << tag1 << " ha finito il turno" << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha finito il turno" << std::endl;
    break;
  case EventType::ELIMINAZIONE:
    std::cout << "- Giocatore " << tag1 << " e' stato eliminato" << std::endl;
    m_output_file << "- Giocatore " << tag1 << " e' stato eliminato" << std::endl;
    break;
  case EventType::VITTORIA:
    std::cout << "- Giocatore " << tag1 << " ha vinto la partita" << std::endl;
    m_output_file << "- Giocatore " << tag1 << " ha vinto la partita" << std::endl;
    break;
  default:
    break;
  }
}
