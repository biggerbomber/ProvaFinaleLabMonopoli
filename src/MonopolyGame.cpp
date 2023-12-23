//monopolygame.cpp
#include "../include/MonopolyGame.h"
#include "../include/Bot.h"

std::shared_ptr<Player> MonopolyGame::get_player_from_tag(int)
{
  return std::shared_ptr<Player>(new Bot(0,0,0));
}
