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
class Player;
class MonopolyGame{
public:
  const static int N_PLAYER=4;
  enum PlayerType {BOT ,HUMAN};

  MonopolyGame(PlayerType);
  void run();
  void log(Logger::LogType lt, int tag1, Position pos1 = 0, int tag2 = -1, int fiorini = -1);
  std::shared_ptr<Player> get_player_from_tag(int);
private:
  Board m_board;
  std::array<std::shared_ptr<Player>,N_PLAYER> m_players;
  std::array<int, N_PLAYER> m_num_turno;
  Logger m_log;
};

std::ostream& operator<<(std::ostream&, const MonopolyGame&);


int roll_dice();

#endif