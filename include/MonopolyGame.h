//@barbato alberto 2073961

#ifndef MONOPOLYGAME_H
#define MONOPOLYGAME_H
#include "Position.h"
#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include "Logger.h"
#include "EventType.h"
#include <iostream>
#include <memory>
#include <fstream>

//Questa classe organizza tutti gli elementi della partita e attua il suo svolgimento 
class MonopolyGame{
public:

  const static int N_PLAYER=4;
  const static int FIORINI_PASSAGGIO_VIA = 20;
  const static int MAX_TURNI=2000;
  //usato come parametro per inizializzare MonopolyGame
  enum GameType {BOT ,HUMAN};
  //utilizzata nella generazione dei turni
  struct TurnoPlayer {
    int p_tag;
    int n_dice;
  };
  //Inizializza il gioco, Compresi i turni di gioco
  MonopolyGame(GameType);
  //Inizia la partita, ritona quando � conclusa
  void run();
  //funzione stub per accedere a Logger senza esporlo pubblicamente
  void log(EventType lt, int tag1, Position pos1 = 0, int tag2 = -1, int fiorini = -1);
private:
  //Stampa su console il risultato del comando "show"
  void show();
  void stampa_possedimenti();
  void stampa_fiorini();

  //gestisce la fine della partita, superati i turni massimi
  void fine_partita_max_turni();
  //gestiste la fine della partita, quando rimane un solo giocatore
  void fine_partita_vittoria();

  //Esegue un turno di gioco.
  //Parametri: il numero di turno corrente [0,1,2,3]
  //Valore Ritornato: Evento che ha portato alla fine del turno
  EventType run_turno(int);

  //Gestisce le scelte dei player:
  //Parametri: stared_ptr<Player> � il player attivo al momento
  //           shared_ptr<Tyle> � la casella di cui si chiede la gestione
  // 
  // Internamente compie le azioni per gestire le richieste del player(EventType) che pu� gestire, 
  // e aggiorna l'evento quando le ha compiute
  // 
  // Valore Restituito: L'evento scelta del Player
  EventType gestisci_eventi(std::shared_ptr<Player>, std::shared_ptr<Tile>);

 
  std::shared_ptr<Player> get_player_from_tag(int);

  Board m_board;
  std::array<std::shared_ptr<Player>,N_PLAYER> m_players;
  std::array<int, N_PLAYER> m_num_turno;
  Logger m_log;
  GameType m_game_type;
};


//Tira due dadi a sei faccie e ritona la loro somma
int roll_dice();

//gestisce la decisione dei turni di gioco,Ricorsivamente
//Parametri : Un vettore di "TurnoPlayer" da controllare, ordinare e modificare se necessario
//            [index_start,index_end[ intervallo di azione
//            Logger* necessario per la stampa dei tiri di dado 
void gestisci_turni(std::array<MonopolyGame::TurnoPlayer, MonopolyGame::N_PLAYER>&, int index_start, int index_end,Logger*);

#endif