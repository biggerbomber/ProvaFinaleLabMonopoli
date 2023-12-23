//@barbato alberto 2073961

#ifndef MONOPOLYGAME_H
#define MONOPOLYGAME_H
#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include <iostream>
#include <memory>
#include <fstream>
class Player;
class MonopolyGame{
public:
  const static int N_PLAYER=4;
  enum PlayerType {BOT ,HUMAN};
  enum PlayerTag{ALPHA, BETA, GAMMA,DELTA};

  MonopolyGame(PlayerType);
  void run();
private:
  Board m_board;
  std::array<std::shared_ptr<Player>,N_PLAYER> m_players;
  std::array<int, N_PLAYER> m_num_turno;
  std::ofstream m_output_file;
};

std::ostream& operator<<(std::ostream&, const MonopolyGame&);
std::ostream& operator<<(std::ostream&, const MonopolyGame::PlayerTag&);

int roll_dice();

#endif