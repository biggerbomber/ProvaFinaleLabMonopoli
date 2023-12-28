//@barbato alberto 2073961

#ifndef MONOPOLYGAME_H
#define MONOPOLYGAME_H
#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include "Logger.h"
#include <iostream>
#include <memory>
#include <fstream>
#include "ExpandNamespace.h"
#include <EventType.h>

class MonopolyGame{
public:
  const static int N_PLAYER=4;
  const static int FIORINI_PASSAGGIO_VIA = 20;
  const static int MAX_TURNI=100;
  enum PlayerType {BOT ,HUMAN};
  struct TurnoPlayer {
    int p_tag;
    int n_dice;
  };
  MonopolyGame(PlayerType);
  void run();
  void log(EventType lt, int tag1, Position pos1 = 0, int tag2 = -1, int fiorini = -1);
  void show();
  void stampa_possedimenti();
  void stampa_fiorini();
  std::shared_ptr<Player> get_player_from_tag(int);
private:
  Board m_board;
  std::array<std::shared_ptr<Player>,N_PLAYER> m_players;
  std::array<int, N_PLAYER> m_num_turno;
  Logger m_log;
  PlayerType m_game_type;
};

std::ostream& operator<<(std::ostream&, const MonopolyGame&);


int roll_dice();
void gestisci_turni(std::array<MonopolyGame::TurnoPlayer, MonopolyGame::N_PLAYER>&, int index_start, int index_end,Logger*);

#endif