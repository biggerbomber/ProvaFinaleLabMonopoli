//monopolygame.cpp
#include "../include/MonopolyGame.h"
#include "../include/Bot.h"
#include "../include/Human.h"
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




std::shared_ptr<Player> MonopolyGame::get_player_from_tag(int)
{
  return std::shared_ptr<Player>(new Bot(0,0,0));
}
