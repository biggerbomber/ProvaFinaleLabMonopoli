//monopolygame.cpp
#include "MonopolyGame.h"
#include "Bot.h"
#include "Human.h"
#include <memory>

MonopolyGame::MonopolyGame(MonopolyGame::PlayerType pt) {
  switch (pt)
  {
  case MonopolyGame::PlayerType::BOT:
    m_players[0] = std::make_shared<Bot>(0, m_board.get_partenza(), this);
    break;
  case MonopolyGame::PlayerType::HUMAN:
    m_players[0] = std::make_shared<Human>(0, m_board.get_partenza(), this);
    break;
  default:
    throw std::invalid_argument("What?");
    break;
  }

  for (int i = 1; i < N_PLAYER; i++) {
    m_players[i] = std::make_shared<Bot>(i, m_board.get_partenza(), this);
  }
}

void MonopolyGame::show(){}




void MonopolyGame::log(Logger::LogType lt, int tag1, Position pos1, int tag2, int fiorini)
{
  m_log.log(lt, tag1, pos1, tag2, fiorini);
}

std::shared_ptr<Player> MonopolyGame::get_player_from_tag(int)
{
  return std::shared_ptr<Player>(new Bot(0,0,0));
}
