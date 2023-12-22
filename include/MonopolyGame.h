#ifndef MONOPOLYGAME_H
#define MONOPOLYGAME_H
#include "Board.h"
#include "Player.h"
#include <iostream>

class MonopolyGame{
public:
    const static int N_PLAYER=4;
    enum PlayerType {BOT ,HUMAN};

    MonopolyGame(PlayerType);
    void Run();
private:
    Board m_board;
    std::array<Player,N_PLAYER> m_players;
    //Aggiungere i/o
};

std::ostream& operator<<(std::ostream&, const MonopolyGame&);


#endif