//@Casucci Leonardo 2073980

#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot: public Player {
public:
	Bot(int, Position,MonopolyGame*);
	bool gestisci_casella(std::shared_ptr<Tile>);
};

#endif