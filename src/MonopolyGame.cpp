//monopolygame.cpp
#include "../include/MonopolyGame.h"






std::ostream& operator<<(std::ostream& os , const MonopolyGame::PlayerTag& tg) {

  return os << static_cast<int>(tg);

}
